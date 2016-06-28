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
#include "dogen/quilt.cpp/test_data/settings/helper_settings_td.hpp"
#include "dogen/quilt.cpp/test_data/properties/helper_descriptor_td.hpp"

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

dogen::quilt::cpp::settings::helper_settings
create_dogen_quilt_cpp_settings_helper_settings(const unsigned int position) {
    return dogen::quilt::cpp::settings::helper_settings_generator::create(position);
}

boost::optional<dogen::quilt::cpp::settings::helper_settings>
create_boost_optional_dogen_quilt_cpp_settings_helper_settings(unsigned int position) {
    boost::optional<dogen::quilt::cpp::settings::helper_settings> r(
        create_dogen_quilt_cpp_settings_helper_settings(position));
    return r;
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

helper_descriptor_generator::helper_descriptor_generator() : position_(0) { }

void helper_descriptor_generator::
populate(const unsigned int position, result_type& v) {
    v.namespaces(create_std_list_std_string(position + 0));
    v.name_identifiable(create_std_string(position + 1));
    v.name_qualified(create_std_string(position + 2));
    v.name_tree_qualified(create_std_string(position + 3));
    v.name_tree_identifiable(create_std_string(position + 4));
    v.settings(create_boost_optional_dogen_quilt_cpp_settings_helper_settings(position + 5));
    v.is_primitive(create_bool(position + 6));
}

helper_descriptor_generator::result_type
helper_descriptor_generator::create(const unsigned int position) {
    helper_descriptor r;
    helper_descriptor_generator::populate(position, r);
    return r;
}

helper_descriptor_generator::result_type*
helper_descriptor_generator::create_ptr(const unsigned int position) {
    helper_descriptor* p = new helper_descriptor();
    helper_descriptor_generator::populate(position, *p);
    return p;
}

helper_descriptor_generator::result_type
helper_descriptor_generator::operator()() {
    return create(position_++);
}

} } } }
