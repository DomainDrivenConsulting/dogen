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
#ifndef MASD_DOGEN_GENERATION_CPP_TYPES_FORMATTERS_REGISTRAR_HPP
#define MASD_DOGEN_GENERATION_CPP_TYPES_FORMATTERS_REGISTRAR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <memory>
#include <forward_list>
#include <unordered_map>
#include "masd.dogen.archetypes/types/location.hpp"
#include "masd.dogen.archetypes/types/locations_group.hpp"
#include "masd.dogen.archetypes/types/location_repository_parts.hpp"
#include "masd.dogen.generation.cpp/types/formatters/repository.hpp"
#include "masd.dogen.generation.cpp/types/formatters/helper_formatter_interface.hpp"
#include "masd.dogen.generation.cpp/types/formatters/artefact_formatter_interface.hpp"


namespace masd::dogen::generation::cpp::formatters {

/**
 * @brief Manages formatter registration.
 */
class registrar final {
private:
    /**
     * @brief Ensures the formatter passes a modicum of sanity checks.
     */
    /**@{*/
    void validate(std::shared_ptr<artefact_formatter_interface> f) const;
    void validate(std::shared_ptr<helper_formatter_interface> hf) const;
    /**@{*/

public:
    /**
     * @brief Ensures the registrar is ready to be used.
     */
    void validate() const;

public:
    /**
     * @brief Registers an artefact formatter.
     */
    void register_formatter(std::shared_ptr<artefact_formatter_interface> f);

    /**
     * @brief Registers a helper formatter.
     */
    void register_helper_formatter(
        std::shared_ptr<helper_formatter_interface> hf);

public:
    /**
     * @brief Returns all available formatters.
     */
    const repository& formatter_repository() const;

    /**
     * @brief Returns the archetype locations for the registered
     * formatters.
     */
    const std::forward_list<archetypes::location>&
    archetype_locations() const;

    /**
     * @brief Returns the archetype locations for each meta-type.
     */
    const std::unordered_map<std::string,
                             archetypes::locations_group>&
    archetype_locations_by_meta_name() const;

    /**
     * @brief Returns the archetype locations for each family.
     */
    const std::unordered_map<std::string,
                             std::list<archetypes::location>>&
    archetype_locations_by_family() const;

    const archetypes::location_repository_parts&
    archetype_location_repository_parts() const;

    /**
     * @brief Returns all of the available helper formatters.
     */
    const std::unordered_map<
        std::string,
        std::unordered_map<std::string,
                           std::list<
                               std::shared_ptr<helper_formatter_interface>>>>&
    helper_formatters() const;

private:
    repository formatter_repository_;
    std::forward_list<archetypes::location> archetype_locations_;
    std::unordered_map<std::string,
                       archetypes::locations_group>
    archetype_locations_by_meta_name_;
    std::unordered_map<std::string,
                       std::list<archetypes::location>>
    archetype_locations_by_family_;
    archetypes::location_repository_parts
    archetype_location_repository_parts_;
};

template<typename Formatter>
inline void register_formatter(registrar& rg) {
    const auto f(std::make_shared<Formatter>());
    rg.register_formatter(f);
}

template<typename Formatter>
inline void register_formatter(registrar& rg, const std::string& facet_name) {
    const auto f(std::make_shared<Formatter>(facet_name));
    rg.register_formatter(f);
}

template<typename Formatter>
inline void register_helper_formatter(registrar& rg) {
    const auto f(std::make_shared<Formatter>());
    rg.register_helper_formatter(f);
}

}

#endif
