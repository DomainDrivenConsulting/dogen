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
#include "dogen/quilt.cpp/types/formatters/test_data/char_helper_stitch.hpp"
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace test_data {

void char_helper_stitch(
    nested_type_formatting_assistant& a,
    const properties::nested_type_info& t) {
a.stream() << std::endl;
a.stream() << t.name() << " create_" << t.identifiable_name() << "(const unsigned int position) {" << std::endl;
a.stream() << "    return static_cast<" << t.name() << ">(((position % 95) + 32) == 34) ? 35 : ((position % 95) + 32);" << std::endl;
a.stream() << "}" << std::endl;
}
} } } } }
