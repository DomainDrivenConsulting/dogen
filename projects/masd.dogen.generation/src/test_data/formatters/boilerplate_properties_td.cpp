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
#include "masd.dogen.coding/test_data/meta_model/technical_space_td.hpp"
#include "masd.dogen.generation/test_data/formatters/boilerplate_properties_td.hpp"

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

masd::dogen::coding::meta_model::technical_space
create_masd_dogen_coding_meta_model_technical_space(const unsigned int position) {
    return masd::dogen::coding::meta_model::technical_space_generator::create(position);
}

bool create_bool(const unsigned int position) {
    return (position % 2) != 0;
}

}

namespace masd::dogen::generation::formatters {

boilerplate_properties_generator::boilerplate_properties_generator() : position_(0) { }

void boilerplate_properties_generator::
populate(const unsigned int position, result_type& v) {
    v.preamble(create_std_string(position + 0));
    v.postamble(create_std_string(position + 1));
    v.dependencies(create_std_list_std_string(position + 2));
    v.header_guard(create_std_string(position + 3));
    v.technical_space(create_masd_dogen_coding_meta_model_technical_space(position + 4));
    v.generate_preamble(create_bool(position + 5));
    v.generate_header_guards(create_bool(position + 6));
}

boilerplate_properties_generator::result_type
boilerplate_properties_generator::create(const unsigned int position) {
    boilerplate_properties r;
    boilerplate_properties_generator::populate(position, r);
    return r;
}

boilerplate_properties_generator::result_type*
boilerplate_properties_generator::create_ptr(const unsigned int position) {
    boilerplate_properties* p = new boilerplate_properties();
    boilerplate_properties_generator::populate(position, *p);
    return p;
}

boilerplate_properties_generator::result_type
boilerplate_properties_generator::operator()() {
    return create(position_++);
}

}