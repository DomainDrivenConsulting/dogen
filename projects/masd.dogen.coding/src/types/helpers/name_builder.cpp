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
#include <sstream>
#include <boost/throw_exception.hpp>
#include "masd.dogen.utility/log/logger.hpp"
#include "masd.dogen.utility/io/list_io.hpp"
#include "masd.dogen.utility/string/splitter.hpp"
#include "masd.dogen.modeling/io/meta_model/name_io.hpp"
#include "masd.dogen.modeling/io/meta_model/location_io.hpp"
#include "masd.dogen.modeling/types/meta_model/languages.hpp"
#include "masd.dogen.modeling/types/helpers/separators.hpp"
#include "masd.dogen.modeling/types/helpers/building_error.hpp"
#include "masd.dogen.modeling/types/helpers/string_processor.hpp"
#include "masd.dogen.modeling/types/helpers/pretty_printer.hpp"
#include "masd.dogen.modeling/types/helpers/identifiable_and_qualified_builder.hpp"
#include "masd.dogen.modeling/types/helpers/name_builder.hpp"

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("yarn.helpers.name_builder"));

const std::string empty_model_name("Model name is empty.");
const std::string unexpected_simple_name("Simple name is not expected.");

}

namespace masd::dogen::modeling::helpers {

name_builder::name_builder(const bool model_name_mode)
    : model_name_mode_(model_name_mode) { }

std::string name_builder::compute_id() {
    helpers::pretty_printer pp;
    pp.add(name_, model_name_mode_);
    const auto r(pp.print());
    BOOST_LOG_SEV(lg, debug) << "Computed id: " << r;
    return r;
}

void name_builder::simple_name(const std::string& sn) {
    if (model_name_mode_) {
        BOOST_LOG_SEV(lg, error) << unexpected_simple_name;
        BOOST_THROW_EXCEPTION(building_error(unexpected_simple_name));
    }

    name_.simple(sn);
    BOOST_LOG_SEV(lg, debug) << "Added simple name: " << sn;
}

void name_builder::model_name(const std::string& mn) {
    if (mn.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_model_name;
        BOOST_THROW_EXCEPTION(building_error(empty_model_name));
    }

    location_builder_.model_modules(mn);
    BOOST_LOG_SEV(lg, debug) << "Added model name: " << mn;
}

void name_builder::model_name(const meta_model::location& l) {
    location_builder_.model_modules(l.model_modules());
    BOOST_LOG_SEV(lg, debug) << "Added model name from location: " << l;
}

void name_builder::external_modules(const std::string& em) {
    location_builder_.external_modules(em);
}

void name_builder::external_modules(const std::list<std::string>& em) {
    location_builder_.external_modules(em);
}

void name_builder::model_modules(const std::string& mm) {
    location_builder_.model_modules(mm);
}

void name_builder::
model_modules(const std::list<std::string>& mm) {
    location_builder_.model_modules(mm);
}

void name_builder::internal_modules(const std::string& im) {
    location_builder_.internal_modules(im);
}

void name_builder::internal_modules(const std::list<std::string>& im) {
    location_builder_.internal_modules(im);
}

void name_builder::location(const meta_model::location& l) {
    location_builder_.location(l);
}

meta_model::name name_builder::build() {
    name_.location(location_builder_.build());
    if (model_name_mode_)
        name_.simple(*name_.location().model_modules().rbegin());

    name_.id(compute_id());

    identifiable_and_qualified_builder iqb;
    const auto iq(iqb.build(name_, model_name_mode_));
    name_.identifiable(iq.first);
    name_.qualified(iq.second);

    BOOST_LOG_SEV(lg, debug) << "Built name: " << name_;
    return name_;
}

meta_model::name name_builder::build(std::list<std::string> names) {
    /*
     * If we have a single name, we are either referencing a type
     * defined in the global namespace (possibly in a different
     * model), or a type defined at the top-level in this model. As we
     * cannot tell the difference, we must fill in just the simple
     * name and let the resolver handle it properly later on.
     */
    name_builder b;
    const auto front(names.front());
    if (names.size() == 1) {
        b.simple_name(front);
        BOOST_LOG_SEV(lg, debug) << "Simple name: " << front;
        return b.build();
    }

    /*
     * The back of the list must now be the type's simple name.
     */
    const auto back(names.back());
    b.simple_name(back);
    BOOST_LOG_SEV(lg, debug) << "Simple name: " << back;
    names.pop_back(); // consume the simple name

    if (!names.empty()) {
        /*
         * Whatever is left, if anything, must be a path to non-top-level
         * modules defined within the model.
         */
        b.internal_modules(names);
        BOOST_LOG_SEV(lg, debug) << "Internal modules: " << names;
        names.clear(); // consume internal modules
    }
    return b.build();
}

meta_model::name name_builder::build(const std::string& names) {
    using utility::string::splitter;
    const auto names_as_list(splitter::split_scoped(names));
    return build(names_as_list);
}

}
