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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTERS_FILE_FORMATTER_INTERFACE_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTERS_FILE_FORMATTER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/dynamic/types/ownership_hierarchy.hpp"
#include "dogen/quilt.cpp/types/properties/registrar.hpp"
#include "dogen/quilt.cpp/types/properties/origin_types.hpp"
#include "dogen/quilt.cpp/types/formatters/file_types.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

class file_formatter_interface {
public:
    file_formatter_interface() = default;
    file_formatter_interface(const file_formatter_interface&) = delete;
    file_formatter_interface(file_formatter_interface&&) = default;
    virtual ~file_formatter_interface() noexcept = 0;

public:
    /**
     * @brief Unique identifier for the formatter.
     */
    virtual std::string id() const = 0;

    /**
     * @brief Ownership hierarchy for this formatter
     */
    virtual dynamic::ownership_hierarchy ownership_hierarchy() const = 0;

    /**
     * @brief Type of the file this formatter generates.
     */
    virtual file_types file_type() const = 0;

    /**
     * @brief Origin of the formattable this formatter handles.
     */
    virtual properties::origin_types formattable_origin_type() const = 0;

    /**
     * @brief Registers an inclusion dependency providers this
     * formatter may know of.
     */
    virtual void register_provider(properties::registrar& rg) const = 0;
};

} } } }

#endif
