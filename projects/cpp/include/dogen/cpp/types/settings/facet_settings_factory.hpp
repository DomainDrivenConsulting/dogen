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
#ifndef DOGEN_CPP_TYPES_SETTINGS_FACET_SETTINGS_FACTORY_HPP
#define DOGEN_CPP_TYPES_SETTINGS_FACET_SETTINGS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <forward_list>
#include <unordered_map>
#include <boost/property_tree/ptree.hpp>
#include "dogen/dynamic/types/object.hpp"
#include "dogen/dynamic/types/field_definition.hpp"
#include "dogen/cpp/types/settings/facet_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

/**
 * @brief Constructs settings for all facets.
 */
class facet_settings_factory {
public:
    facet_settings_factory() = default;
    facet_settings_factory(const facet_settings_factory&) = default;
    facet_settings_factory(facet_settings_factory&&) = default;
    ~facet_settings_factory() = default;

private:
    /**
     * @brief Creates the settings for the facet implied by the facet
     * fields.
     */
    facet_settings create_settings_for_facet(
        const std::forward_list<dynamic::field_definition>& facet_fields,
        const dynamic::object& o) const;

public:
    /**
     * @brief Builds the facet settings from the dynamic object.
     *
     * @return Facet settings by facet name.
     */
    std::unordered_map<std::string, facet_settings>
    make(const std::unordered_map<
        std::string,
        std::forward_list<dynamic::field_definition>
        >& field_definitions_by_facet_name,
        const dynamic::object& o) const;
};

} } }

#endif
