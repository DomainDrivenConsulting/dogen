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
#ifndef MASD_DOGEN_VARIABILITY_TYPES_ARCHETYPE_LOCATION_REPOSITORY_PARTS_BUILDER_HPP
#define MASD_DOGEN_VARIABILITY_TYPES_ARCHETYPE_LOCATION_REPOSITORY_PARTS_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "masd.dogen.variability/types/archetype_location.hpp"
#include "masd.dogen.variability/types/archetype_location_repository_parts.hpp"

namespace masd::dogen::variability {

class archetype_location_repository_parts_builder final {
private:
    void validate(const std::string& meta_name, const std::string& family,
        const std::string& intra_backend_segment, const archetype_location& al);

public:
    void add(const std::string& meta_name, const std::string& family,
        const std::string& intra_backend_segment,
        const std::string& canonical_archetype, const archetype_location& al);
    archetype_location_repository_parts build();

private:
    archetype_location_repository_parts parts_;
};

}

#endif
