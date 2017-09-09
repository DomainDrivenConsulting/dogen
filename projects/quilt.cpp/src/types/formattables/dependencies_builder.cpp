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
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/yarn/io/meta_model/name_io.hpp"
#include "dogen/quilt.cpp/types/formattables/building_error.hpp"
#include "dogen/quilt.cpp/io/formattables/directive_group_io.hpp"
#include "dogen/quilt.cpp/types/formattables/canonical_archetype_resolver.hpp"
#include "dogen/quilt.cpp/types/formattables/dependencies_builder.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formattables.dependencies_builder"));

const auto empty_list = std::list<std::string> {};
const std::string pair_type("pair");
const std::string string_type("string");
const std::string variant_type("variant");
const std::string ptree_type("ptree");
const std::string path_type("path");
const std::string date_type("date");
const std::string ptime_type("ptime");

const std::string empty_directive("Cannot add empty include directive.");
const std::string name_not_found("Cannot find name: ");
const std::string archetype_not_found("Cannot find archetype name: ");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

dependencies_builder::dependencies_builder(
    const directive_group_repository& dgrp,
    const std::unordered_map<std::string, formattable>& formattables)
    : repository_(dgrp), formattables_(formattables) {}

boost::optional<directive_group>
dependencies_builder::get_directive_group(
    const yarn::meta_model::name& n, const std::string& archetype) const {
    const auto& c(repository_.by_id());
    const auto i(c.find(n.id()));
    if (i == c.end())
        return boost::optional<directive_group>();

    const auto j(i->second.find(archetype));
    if (j == i->second.end())
        return boost::optional<directive_group>();

    return j->second;
}

bool dependencies_builder::is_enabled(const yarn::meta_model::name& n,
    const std::string& archetype) const {
    const auto i(formattables_.find(n.id()));
    if (i == formattables_.end()) {
        BOOST_LOG_SEV(lg, error) << name_not_found << n.id();
        BOOST_THROW_EXCEPTION(building_error(name_not_found + n.id()));
    }

    const auto& formattable(i->second);
    const auto& eprops(formattable.element_properties());
    const auto& art_props(eprops.artefact_properties());
    const auto j(art_props.find(archetype));
    if (j == art_props.end()) {
        BOOST_LOG_SEV(lg, error) << archetype_not_found << archetype
                                 << " element id: " << n.id();
        BOOST_THROW_EXCEPTION(
            building_error(archetype_not_found + archetype));
    }

    const bool r(j->second.enabled());
    if (!r) {
        BOOST_LOG_SEV(lg, trace) << "Archetype disabled. Archetype: "
                                 << archetype << " on type: " << n.id() << "'";
    }
    return r;
}

void dependencies_builder::
add(const std::string& inclusion_directive) {
    BOOST_LOG_SEV(lg, debug) << "Adding directive: " << inclusion_directive;

    if (inclusion_directive.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_directive;
        BOOST_THROW_EXCEPTION(building_error(empty_directive));
    }
    dependencies_.push_back(inclusion_directive);
}

void dependencies_builder::
add(const std::list<std::string>& inclusion_directives) {
    for (const auto& id : inclusion_directives)
        add(id);
}

void dependencies_builder::
add(const yarn::meta_model::name& n, const std::string& archetype) {
    BOOST_LOG_SEV(lg, debug) << "Adding name: " << n.id();

    canonical_archetype_resolver res(formattables_);
    const auto resolved_arch(res.resolve(n.id(), archetype));

    if (!is_enabled(n, resolved_arch)) {
        BOOST_LOG_SEV(lg, trace) << "Resolved archetype not enabled: "
                                 << resolved_arch;
        return;
    }

    const auto dg(get_directive_group(n, archetype));
    if (dg) {
        add(dg->primary());
        add(dg->secondary());
        BOOST_LOG_SEV(lg, trace) << "Adding inclusion directive group: " << *dg;
    } else
        BOOST_LOG_SEV(lg, trace) << "Could not find an inclusion directive.";
}

void dependencies_builder::add(const boost::optional<yarn::meta_model::name>& n,
    const std::string& archetype) {

    if (!n)
        return;

    add(*n, archetype);
}

void dependencies_builder::add(const std::list<yarn::meta_model::name>& names,
    const std::string& archetype) {
    for (const auto& n : names)
        add(n, archetype);
}

std::list<std::string> dependencies_builder::build() {
    BOOST_LOG_SEV(lg, debug) << "Built inclusion dependencies for archetype.";
    BOOST_LOG_SEV(lg, debug) << "Result: " << dependencies_;

    return dependencies_;
}

} } } }
