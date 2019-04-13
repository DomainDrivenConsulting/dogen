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
#ifndef MASD_DOGEN_ARCHETYPES_TYPES_ARCHETYPE_LOCATION_HPP
#define MASD_DOGEN_ARCHETYPES_TYPES_ARCHETYPE_LOCATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace masd::dogen::archetypes {

/**
 * @brief Location of an archetype or set of archetypes in the hierarchical artchetype space.
 *
 * These must be populated in order, e.g. in order to have a backend we must have a
 * kernel; in order to have a facet we must have a backend and in order to have a
 * formatter we must have a facet. We may not have any.
 */
class archetype_location final {
public:
    archetype_location() = default;
    archetype_location(const archetype_location&) = default;
    archetype_location(archetype_location&&) = default;
    ~archetype_location() = default;

public:
    archetype_location(
        const std::string& kernel,
        const std::string& backend,
        const std::string& facet,
        const std::string& archetype);

public:
    /**
     * @brief Name of the kernel that owns this field, if any.
     */
    /**@{*/
    const std::string& kernel() const;
    std::string& kernel();
    void kernel(const std::string& v);
    void kernel(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the backend that owns this field, if any.
     */
    /**@{*/
    const std::string& backend() const;
    std::string& backend();
    void backend(const std::string& v);
    void backend(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the facet that owns this field, if any.
     */
    /**@{*/
    const std::string& facet() const;
    std::string& facet();
    void facet(const std::string& v);
    void facet(const std::string&& v);
    /**@}*/

    /**
     * @brief Name of the archetype that owns this field, if any.
     */
    /**@{*/
    const std::string& archetype() const;
    std::string& archetype();
    void archetype(const std::string& v);
    void archetype(const std::string&& v);
    /**@}*/

public:
    bool operator==(const archetype_location& rhs) const;
    bool operator!=(const archetype_location& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(archetype_location& other) noexcept;
    archetype_location& operator=(archetype_location other);

private:
    std::string kernel_;
    std::string backend_;
    std::string facet_;
    std::string archetype_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::archetypes::archetype_location& lhs,
    masd::dogen::archetypes::archetype_location& rhs) {
    lhs.swap(rhs);
}

}

#endif
