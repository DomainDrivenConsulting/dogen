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
#include <sstream>
#include "dogen/quilt.cpp/test_data/properties/entity_td.hpp"
#include "dogen/quilt.cpp/test_data/properties/formattable_td.hpp"
#include "dogen/quilt.cpp/test_data/properties/registrar_info_td.hpp"
#include "dogen/quilt.cpp/test_data/properties/forward_declarations_info_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

std::list<std::string> create_std_list_std_string(unsigned int position) {
    std::list<std::string> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_std_string(position + i));
    }
    return r;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

void entity_generator::
populate(const unsigned int position, result_type& v) {
    dogen::quilt::cpp::properties::formattable_generator::populate(position, v);
    v.name(create_std_string(position + 0));
    v.qualified_name(create_std_string(position + 1));
    v.documentation(create_std_string(position + 2));
    v.namespaces(create_std_list_std_string(position + 3));
}

entity_generator::result_type*
entity_generator::create_ptr(const unsigned int position) {
    if ((position % 1) == 0)
        return dogen::quilt::cpp::properties::registrar_info_generator::create_ptr(position);
    return dogen::quilt::cpp::properties::forward_declarations_info_generator::create_ptr(position);
}

} } } }
