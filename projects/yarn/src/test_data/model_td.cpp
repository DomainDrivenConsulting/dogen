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
#include "dogen/yarn/test_data/name_td.hpp"
#include "dogen/yarn/test_data/model_td.hpp"
#include "dogen/yarn/test_data/module_td.hpp"
#include "dogen/yarn/test_data/element_td.hpp"
#include "dogen/yarn/test_data/origin_types_td.hpp"

namespace {

dogen::yarn::name
create_dogen_yarn_name(const unsigned int position) {
    return dogen::yarn::name_generator::create(position);
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

dogen::yarn::element*
create_dogen_yarn_element_ptr(const unsigned int position) {
    return dogen::yarn::element_generator::create_ptr(position);
}

boost::shared_ptr<dogen::yarn::element>
create_boost_shared_ptr_dogen_yarn_element(unsigned int position) {
    boost::shared_ptr<dogen::yarn::element> r(
        create_dogen_yarn_element_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::element> > create_std_unordered_map_std_string_boost_shared_ptr_dogen_yarn_element(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<dogen::yarn::element> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_dogen_yarn_element(position + i)));
    }
    return r;
}

dogen::yarn::origin_types
create_dogen_yarn_origin_types(const unsigned int position) {
    return dogen::yarn::origin_types_generator::create(position);
}

std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types> create_std_unordered_map_dogen_yarn_name_dogen_yarn_origin_types(unsigned int position) {
    std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_dogen_yarn_name(position + i), create_dogen_yarn_origin_types(position + i)));
    }
    return r;
}

std::unordered_set<dogen::yarn::name> create_std_unordered_set_dogen_yarn_name(unsigned int position) {
    std::unordered_set<dogen::yarn::name> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(create_dogen_yarn_name(position + i));
    }
    return r;
}

dogen::yarn::module
create_dogen_yarn_module(const unsigned int position) {
    return dogen::yarn::module_generator::create(position);
}

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace yarn {

model_generator::model_generator() : position_(0) { }

void model_generator::
populate(const unsigned int position, result_type& v) {
    v.name(create_dogen_yarn_name(position + 0));
    v.elements(create_std_unordered_map_std_string_boost_shared_ptr_dogen_yarn_element(position + 1));
    v.references(create_std_unordered_map_dogen_yarn_name_dogen_yarn_origin_types(position + 2));
    v.leaves(create_std_unordered_set_dogen_yarn_name(position + 3));
    v.root_module(create_dogen_yarn_module(position + 4));
    v.has_generatable_types(create_bool(position + 5));
}

model_generator::result_type
model_generator::create(const unsigned int position) {
    model r;
    model_generator::populate(position, r);
    return r;
}

model_generator::result_type*
model_generator::create_ptr(const unsigned int position) {
    model* p = new model();
    model_generator::populate(position, *p);
    return p;
}

model_generator::result_type
model_generator::operator()() {
    return create(position_++);
}

} }
