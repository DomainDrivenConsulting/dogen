/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/io/meta_model/letter_cases_io.hpp"
#include "dogen/yarn/io/meta_model/orm_database_systems_io.hpp"
#include "dogen/yarn/types/meta_model/orm_database_systems.hpp"
#include "dogen/quilt.cpp/types/formattables/artefact_properties.hpp"
#include "dogen/quilt.cpp/types/formattables/adaptation_error.hpp"
#include "dogen/quilt.cpp/types/formatters/artefact_formatter_interface.hpp"
#include "dogen/quilt.cpp/types/formattables/adapter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formattables.adapter"));

const std::string mysql("mysql");
const std::string postgresql("pgsql");
const std::string oracle("oracle");
const std::string sql_server("sqlserver");
const std::string sqllite("sqllite");

const std::string upper_case("upper");
const std::string lower_case("lower");

const std::string duplicate_archetype("Duplicate archetype: ");
const std::string duplicate_master(
    "More than one master segment found. Last: ");
const std::string invalid_daatabase_system(
    "Database system is invalid or unsupported: ");
const std::string invalid_case("Letter case is invalid or unsupported: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

std::string
adapter::to_odb_database(const yarn::meta_model::orm_database_systems ds) {
    using yarn::meta_model::orm_database_systems;

    switch (ds) {
    case orm_database_systems::mysql: return mysql;
    case orm_database_systems::postgresql: return postgresql;
    case orm_database_systems::oracle: return oracle;
    case orm_database_systems::sql_server: return sql_server;
    case orm_database_systems::sqllite: return sqllite;
    default: {
        const auto s(boost::lexical_cast<std::string>(ds));
        BOOST_LOG_SEV(lg, error) << invalid_daatabase_system << s;
        BOOST_THROW_EXCEPTION(adaptation_error(invalid_daatabase_system + s));
    } }
}

std::string adapter::
to_odb_sql_name_case(const yarn::meta_model::letter_cases lc) const {
    using yarn::meta_model::letter_cases;

    switch (lc) {
    case letter_cases::upper_case: return upper_case;
    case letter_cases::lower_case: return lower_case;
    default: {
        const auto s(boost::lexical_cast<std::string>(lc));
        BOOST_LOG_SEV(lg, error) << invalid_case << s;
        BOOST_THROW_EXCEPTION(adaptation_error(invalid_case + s));
    } }
}

std::list<std::string> adapter::
make_databases(const yarn::meta_model::orm_model_properties& omp) const {
    std::list<std::string> r;

    if (omp.database_systems().size() > 1)
        r.push_back("common");

    for (const auto ds : omp.database_systems())
        r.push_back(to_odb_database(ds));

    return r;
}

model adapter::adapt(const formatters::repository& frp,
    const yarn::meta_model::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Adapting yarn to formattables."
                             << " Elements in model: " << m.elements().size();

    model r;
    r.name(m.name());

    for (const auto& pair : m.facet_properties()) {
        facet_properties fp;
        fp.enabled(pair.second.enabled());
        fp.overwrite(pair.second.overwrite());
        r.facet_properties().insert(std::make_pair(pair.first, fp));
    }

    if (m.orm_properties()) {
        const auto op(*m.orm_properties());
        r.odb_databases(make_databases(op));
        if (op.letter_case())
            r.odb_sql_name_case(to_odb_sql_name_case(*op.letter_case()));
    }

    for (const auto& ptr : m.elements()) {
        const auto& e(*ptr);
        const auto id(e.name().id());
        BOOST_LOG_SEV(lg, debug) << "Processing element: " << id;

        /*
         * We need to check to see if we've already inserted an
         * element due to the segmentation of elements - we may need
         * to process the master element and one or more extensions.
         */
        auto i(r.formattables().find(id));
        if (i == r.formattables().end()) {
            formattable fbl;
            const auto pair(std::make_pair(id, fbl));
            const auto ret(r.formattables().insert(pair));
            i = ret.first;
            BOOST_LOG_SEV(lg, debug) << "Inserted element: " << id;
        } else
            BOOST_LOG_SEV(lg, debug) << "Element already inserted. ";

        /*
         * Setup the master segment depending on the extension flag.
         */
        auto& fbl(i->second);
        fbl.all_segments().push_back(ptr);
        if (!e.is_element_extension()) {
            if (fbl.master_segment()) {
                BOOST_LOG_SEV(lg, error) << duplicate_master << id;
                BOOST_THROW_EXCEPTION(adaptation_error(duplicate_master + id));
            }
            fbl.master_segment(ptr);
        }

        /*
         * Check to see if the element has any formatters. Some
         * elements such as object templates do not have formatters at
         * present.
         */
        const auto mt(e.meta_name().id());
        const auto j(frp.stock_artefact_formatters_by_meta_name().find(mt));
        if (j == frp.stock_artefact_formatters_by_meta_name().end()) {
            BOOST_LOG_SEV(lg, debug) << "Element has no formatters: " << id;
            continue;
        }
        BOOST_LOG_SEV(lg, debug) << "Element has formatters " << id;

        /*
         * Perform the artefact expansion by looking at all the
         * archetypes available via the formatters. Note that we check
         * for duplicates on insertion because of the element
         * segmentation scenario. Its there just to ensure we don't
         * have a formatter processing both a master and an extension.
         */
        auto& art_props(fbl.element_properties().artefact_properties());
        for (const auto& fmt : j->second) {
            const auto arch(fmt->archetype_location().archetype());
            const auto pair(std::make_pair(arch, artefact_properties()));
            const auto inserted(art_props.insert(pair).second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, error) << duplicate_archetype << arch;
                BOOST_THROW_EXCEPTION(
                    adaptation_error(duplicate_archetype + arch));
            }

            BOOST_LOG_SEV(lg, debug) << "Added formatter: " << arch
                                     << " to element: " << id;
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished adapting yarn to formattables."
                             << "Size: " << r.formattables().size();
    return r;
}

} } } }
