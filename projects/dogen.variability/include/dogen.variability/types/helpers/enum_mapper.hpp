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
#ifndef DOGEN_VARIABILITY_TYPES_HELPERS_ENUM_MAPPER_HPP
#define DOGEN_VARIABILITY_TYPES_HELPERS_ENUM_MAPPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen.variability/types/meta_model/value_type.hpp"
#include "dogen.variability/types/meta_model/template_kind.hpp"
#include "dogen.variability/types/meta_model/binding_point.hpp"

namespace dogen::variability::helpers {

class enum_mapper final {
public:
    /**
     * @brief Converts a string to a value type.
     */
    static meta_model::value_type to_value_type(const std::string& s);

    /**
     * @brief Converts a string to a template kind.
     */
    static meta_model::template_kind to_template_kind(const std::string& s);

    /**
     * @brief Converts a string to a binding point.
     */
    static meta_model::binding_point to_binding_point(const std::string& s);

public:
    /**
     * @brief Converts a value type to a string.
     */
    static std::string from_value_type(const meta_model::value_type v);

    /**
     * @brief Converts a template kind to a string.
     */
    static std::string from_template_kind(const meta_model::template_kind v);

    /**
     * @brief Converts a binding point to a string.
     */
    static std::string from_binding_point(const meta_model::binding_point s);
};

}

#endif
