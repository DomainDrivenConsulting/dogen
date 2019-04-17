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
#include "masd.dogen.variability/test_data/value_td.hpp"
#include "masd.dogen.variability/test_data/annotation_td.hpp"
#include "masd.dogen.variability/test_data/scope_types_td.hpp"

namespace {

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

masd::dogen::variability::value*
create_masd_dogen_variability_value_ptr(const unsigned int position) {
    return masd::dogen::variability::value_generator::create_ptr(position);
}

boost::shared_ptr<masd::dogen::variability::value>
create_boost_shared_ptr_masd_dogen_variability_value(unsigned int position) {
    boost::shared_ptr<masd::dogen::variability::value> r(
        create_masd_dogen_variability_value_ptr(position));
    return r;
}

std::unordered_map<std::string, boost::shared_ptr<masd::dogen::variability::value> > create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_variability_value(unsigned int position) {
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::variability::value> > r;
    for (unsigned int i(0); i < 4; ++i) {
        r.insert(std::make_pair(create_std_string(position + i), create_boost_shared_ptr_masd_dogen_variability_value(position + i)));
    }
    return r;
}

masd::dogen::variability::scope_types
create_masd_dogen_variability_scope_types(const unsigned int position) {
    return masd::dogen::variability::scope_types_generator::create(position);
}

}

namespace masd::dogen::variability {

annotation_generator::annotation_generator() : position_(0) { }

void annotation_generator::
populate(const unsigned int position, result_type& v) {
    v.tagged_values(create_std_unordered_map_std_string_boost_shared_ptr_masd_dogen_variability_value(position + 0));
    v.scope(create_masd_dogen_variability_scope_types(position + 1));
}

annotation_generator::result_type
annotation_generator::create(const unsigned int position) {
    annotation r;
    annotation_generator::populate(position, r);
    return r;
}

annotation_generator::result_type*
annotation_generator::create_ptr(const unsigned int position) {
    annotation* p = new annotation();
    annotation_generator::populate(position, *p);
    return p;
}

annotation_generator::result_type
annotation_generator::operator()() {
    return create(position_++);
}

}