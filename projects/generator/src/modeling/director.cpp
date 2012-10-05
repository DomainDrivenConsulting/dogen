/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <boost/filesystem.hpp>
#include "dogen/generator/modeling/dia_to_sml.hpp"
#include "dogen/generator/modeling/sml_builder.hpp"
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/utility/serialization/xml_helper.hpp"
#include "dogen/dia/xml/hydrator.hpp"
#include "dogen/dia/serialization/diagram_ser.hpp"
#include "dogen/sml/serialization/model_ser.hpp"
#include "dogen/generator/modeling/primitive_model_factory.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/generator/modeling/director.hpp"

namespace {

static dogen::utility::log::logger
lg(dogen::utility::log::logger_factory("modeling::director"));

const std::string empty;
const std::string merged("merged_");
const std::string xml_extension(".xml");
const std::string text_extension(".txt");
const std::string binary_extension(".bin");
const std::string dia_model("dia");
const std::string sml_model("sml");
const std::string invalid_archive_type("Invalid or unexpected archive type");

}

namespace dogen {
namespace generator {
namespace modeling {

director::director(config::settings settings)
    : settings_(settings), verbose_(settings_.troubleshooting().verbose()) { }

std::string director::
extension(utility::serialization::archive_types archive_type,
    std::string model) const {
    using utility::serialization::archive_types;
    switch (archive_type) {
    case archive_types::xml:
        return xml_extension + model;
    case archive_types::text:
        return text_extension + model;
    case archive_types::binary:
        return binary_extension + model;
    default:
        break;
    }
    throw dogen::utility::exception::invalid_enum_value(invalid_archive_type);
}

bool director::is_save_dia_model_enabled() const {
    return settings_.troubleshooting().save_dia_model() !=
        utility::serialization::archive_types::invalid;
}

void director::save_diagram(dia::diagram d, std::string name) const {
    if (!is_save_dia_model_enabled())
        return;

    boost::filesystem::path p(settings_.troubleshooting().debug_dir());
    p /= name;

    using utility::serialization::archive_types;
    archive_types at(settings_.troubleshooting().save_dia_model());
    p.replace_extension(extension(at, dia_model));
    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg, info) << "Saving Dia model to path: " << p;

    using dogen::utility::serialization::xml_serialize;
    xml_serialize<dia::diagram>(p, d);
}

dia::diagram
director::hydrate_diagram(boost::filesystem::path path) const {
    dia::xml::hydrator h(path);
    dia::diagram r(h.hydrate());
    save_diagram(r, path.stem().string());
    return r;
}

bool director::is_save_sml_model_enabled() const {
    return settings_.troubleshooting().save_sml_model() !=
        utility::serialization::archive_types::invalid;
}

void director::save_model(sml::model m, std::string prefix) const {
    if (!is_save_sml_model_enabled())
        return;

    boost::filesystem::path p(settings_.troubleshooting().debug_dir());
    p /= prefix + m.name();

    using utility::serialization::archive_types;
    archive_types at(settings_.troubleshooting().save_sml_model());
    p.replace_extension(extension(at, sml_model));
    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg, info) << "Saving SML model to path: " << p;

    using dogen::utility::serialization::xml_serialize;
    xml_serialize<sml::model>(p, m);
}

sml::model director::
to_sml(dia::diagram d, std::string file_name, bool is_target) const {
    const std::string epp(settings_.modeling().external_package_path());
    const std::string name(settings_.modeling().disable_model_package() ?
        empty : file_name);

    using dogen::generator::modeling::dia_to_sml;
    dia_to_sml dia_to_sml(d, name, epp, is_target, verbose_);

    sml::model m(dia_to_sml.transform());
    save_model(m, empty);
    return std::move(m);
}

bool director::has_generatable_types(sml::model m) const {
    bool r(false);

    for (const auto p : m.pods()) {
        if (p.second.generate()) {
            r = true;
            break;
        }
    }
    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg, debug) << "Total pods found by builder: "
                             << m.pods().size();
    return r;
}

boost::optional<sml::model> director::create_model() const {
    sml_builder builder(verbose_, settings_.sql().schema_name());
    builder.add(primitive_model_factory::create());

    using sml::model;
    const auto lambda([&](boost::filesystem::path p, bool is_target) {
            const dia::diagram d(hydrate_diagram(p));
            return model(to_sml(d, p.stem().string(), is_target));
        });

    const bool is_target(true);
    builder.add_target(lambda(settings_.modeling().target(), is_target));
    for (const auto r : settings_.modeling().references())
        builder.add(lambda(r, !is_target));

    model m(builder.build());

    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg, debug) << "Merged model: " << m;
    save_model(m, merged);

    if (has_generatable_types(m))
        return boost::optional<model>(m);

    BOOST_LOG_SEV(lg, warn) << "No generatable types found.";

    return boost::optional<model>();
}

} } }
