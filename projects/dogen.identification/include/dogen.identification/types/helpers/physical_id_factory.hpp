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
#ifndef DOGEN_IDENTIFICATION_TYPES_HELPERS_PHYSICAL_ID_FACTORY_HPP
#define DOGEN_IDENTIFICATION_TYPES_HELPERS_PHYSICAL_ID_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen.identification/types/entities/technical_space.hpp"
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.identification/types/entities/physical_id.hpp"

namespace dogen::identification::helpers {

/**
 * @brief Creates a unique identifier representing points in physical
 * space.
 */
class physical_id_factory final {
public:
    static entities::physical_id make(const std::string& logical_id,
        const std::string& physical_meta_id);
    static entities::physical_id make(const entities::logical_id& logical_id,
        const std::string& physical_meta_id);
    static entities::physical_id make(const entities::logical_id& logical_id,
        const entities::physical_meta_id& physical_meta_id);
    static entities::physical_id make(const entities::logical_id& logical_id,
        const entities::technical_space& ts);
};

}

#endif
