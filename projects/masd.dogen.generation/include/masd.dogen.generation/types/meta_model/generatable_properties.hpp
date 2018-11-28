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
#ifndef MASD_DOGEN_GENERATION_TYPES_META_MODEL_GENERATABLE_PROPERTIES_HPP
#define MASD_DOGEN_GENERATION_TYPES_META_MODEL_GENERATABLE_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "masd.dogen.extraction/types/decoration_properties.hpp"
#include "masd.dogen.generation/types/meta_model/artefact_properties.hpp"
#include "masd.dogen.generation/types/meta_model/local_archetype_location_properties.hpp"

namespace masd::dogen::generation::meta_model {

/**
 * @brief Element properties related to code generation.
 */
class generatable_properties final {
public:
    generatable_properties() = default;
    generatable_properties(const generatable_properties&) = default;
    generatable_properties(generatable_properties&&) = default;
    ~generatable_properties() = default;

public:
    generatable_properties(
        const masd::dogen::extraction::decoration_properties& decoration_properties,
        const std::unordered_map<std::string, masd::dogen::generation::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, masd::dogen::generation::meta_model::local_archetype_location_properties>& archetype_location_properties);

public:
    const masd::dogen::extraction::decoration_properties& decoration_properties() const;
    masd::dogen::extraction::decoration_properties& decoration_properties();
    void decoration_properties(const masd::dogen::extraction::decoration_properties& v);
    void decoration_properties(const masd::dogen::extraction::decoration_properties&& v);

    const std::unordered_map<std::string, masd::dogen::generation::meta_model::artefact_properties>& artefact_properties() const;
    std::unordered_map<std::string, masd::dogen::generation::meta_model::artefact_properties>& artefact_properties();
    void artefact_properties(const std::unordered_map<std::string, masd::dogen::generation::meta_model::artefact_properties>& v);
    void artefact_properties(const std::unordered_map<std::string, masd::dogen::generation::meta_model::artefact_properties>&& v);

    const std::unordered_map<std::string, masd::dogen::generation::meta_model::local_archetype_location_properties>& archetype_location_properties() const;
    std::unordered_map<std::string, masd::dogen::generation::meta_model::local_archetype_location_properties>& archetype_location_properties();
    void archetype_location_properties(const std::unordered_map<std::string, masd::dogen::generation::meta_model::local_archetype_location_properties>& v);
    void archetype_location_properties(const std::unordered_map<std::string, masd::dogen::generation::meta_model::local_archetype_location_properties>&& v);

public:
    bool operator==(const generatable_properties& rhs) const;
    bool operator!=(const generatable_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(generatable_properties& other) noexcept;
    generatable_properties& operator=(generatable_properties other);

private:
    masd::dogen::extraction::decoration_properties decoration_properties_;
    std::unordered_map<std::string, masd::dogen::generation::meta_model::artefact_properties> artefact_properties_;
    std::unordered_map<std::string, masd::dogen::generation::meta_model::local_archetype_location_properties> archetype_location_properties_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::generation::meta_model::generatable_properties& lhs,
    masd::dogen::generation::meta_model::generatable_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
