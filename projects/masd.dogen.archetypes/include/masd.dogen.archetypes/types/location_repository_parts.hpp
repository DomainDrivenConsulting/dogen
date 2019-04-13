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
#ifndef MASD_DOGEN_ARCHETYPES_TYPES_LOCATION_REPOSITORY_PARTS_HPP
#define MASD_DOGEN_ARCHETYPES_TYPES_LOCATION_REPOSITORY_PARTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "masd.dogen.archetypes/types/location.hpp"
#include "masd.dogen.archetypes/types/locations_group.hpp"

namespace masd::dogen::archetypes {

class location_repository_parts final {
public:
    location_repository_parts() = default;
    location_repository_parts(const location_repository_parts&) = default;
    location_repository_parts(location_repository_parts&&) = default;
    ~location_repository_parts() = default;

public:
    location_repository_parts(
        const std::list<masd::dogen::archetypes::location>& all,
        const std::unordered_map<std::string, masd::dogen::archetypes::locations_group>& by_meta_name,
        const std::unordered_map<std::string, std::list<masd::dogen::archetypes::location> >& by_family,
        const std::unordered_map<std::string, std::list<masd::dogen::archetypes::location> >& by_intra_backend_segment);

public:
    /**
     * @brief All archetype locations for the archetypes owned by this transform,
     * listing all available backends, facets and archetypes.
     */
    /**@{*/
    const std::list<masd::dogen::archetypes::location>& all() const;
    std::list<masd::dogen::archetypes::location>& all();
    void all(const std::list<masd::dogen::archetypes::location>& v);
    void all(const std::list<masd::dogen::archetypes::location>&& v);
    /**@}*/

    /**
     * @brief Returns the archetype locations for each meta name.
     */
    /**@{*/
    const std::unordered_map<std::string, masd::dogen::archetypes::locations_group>& by_meta_name() const;
    std::unordered_map<std::string, masd::dogen::archetypes::locations_group>& by_meta_name();
    void by_meta_name(const std::unordered_map<std::string, masd::dogen::archetypes::locations_group>& v);
    void by_meta_name(const std::unordered_map<std::string, masd::dogen::archetypes::locations_group>&& v);
    /**@}*/

    /**
     * @brief All archetype locations for a given family.
     *
     * Families are backend specific sets of archetype locations, with associated
     * properties such as file extensions.
     */
    /**@{*/
    const std::unordered_map<std::string, std::list<masd::dogen::archetypes::location> >& by_family() const;
    std::unordered_map<std::string, std::list<masd::dogen::archetypes::location> >& by_family();
    void by_family(const std::unordered_map<std::string, std::list<masd::dogen::archetypes::location> >& v);
    void by_family(const std::unordered_map<std::string, std::list<masd::dogen::archetypes::location> >&& v);
    /**@}*/

    /**
     * @brief All archetype locations for a given intra-backend segment.
     *
     * Intra-backend segments are backend specific sets of archetype locations, with
     * associated properties.
     */
    /**@{*/
    const std::unordered_map<std::string, std::list<masd::dogen::archetypes::location> >& by_intra_backend_segment() const;
    std::unordered_map<std::string, std::list<masd::dogen::archetypes::location> >& by_intra_backend_segment();
    void by_intra_backend_segment(const std::unordered_map<std::string, std::list<masd::dogen::archetypes::location> >& v);
    void by_intra_backend_segment(const std::unordered_map<std::string, std::list<masd::dogen::archetypes::location> >&& v);
    /**@}*/

public:
    bool operator==(const location_repository_parts& rhs) const;
    bool operator!=(const location_repository_parts& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(location_repository_parts& other) noexcept;
    location_repository_parts& operator=(location_repository_parts other);

private:
    std::list<masd::dogen::archetypes::location> all_;
    std::unordered_map<std::string, masd::dogen::archetypes::locations_group> by_meta_name_;
    std::unordered_map<std::string, std::list<masd::dogen::archetypes::location> > by_family_;
    std::unordered_map<std::string, std::list<masd::dogen::archetypes::location> > by_intra_backend_segment_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::archetypes::location_repository_parts& lhs,
    masd::dogen::archetypes::location_repository_parts& rhs) {
    lhs.swap(rhs);
}

}

#endif
