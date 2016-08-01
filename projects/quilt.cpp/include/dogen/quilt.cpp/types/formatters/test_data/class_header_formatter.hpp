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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTERS_TEST_DATA_CLASS_HEADER_FORMATTER_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTERS_TEST_DATA_CLASS_HEADER_FORMATTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/filesystem/path.hpp>
#include "dogen/quilt.cpp/types/formatters/new_class_formatter_interface.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace test_data {

class class_header_formatter final : public new_class_formatter_interface {
public:
    /**
     * @brief Returns the formatter name.
     */
    static std::string static_formatter_name();

public:
    std::string id() const override;

    dynamic::ownership_hierarchy ownership_hierarchy() const override;

    file_types file_type() const override;

    properties::origin_types formattable_origin_type() const override;

    void register_inclusion_dependencies_provider(
        properties::registrar& rg) const override;

    dogen::formatters::file
    format(const context& ctx, const yarn::object& o) const override;
};

} } } } }

#endif
