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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_PATH_CONTRIBUTION_TYPES_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_PATH_CONTRIBUTION_TYPES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

namespace masd::dogen::coding::meta_model {

/**
 * @brief Different kinds of contributions that can be made to the final path computation.
 */
enum class path_contribution_types : unsigned int {
    invalid = 0, ///< Represents an uninitialised enum
    none = 1, ///< The item does not contribute at all to the path.
    as_folders = 2, ///< The itemcontributes folders to the path.
    as_path_components = 3 ///< The item contributes a single folder to the path, as a delimited string.
};

}

#endif
