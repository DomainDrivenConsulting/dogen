/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/two_layers_with_objects/test_data/Package_2/class_2_td.hpp"
#include "dogen/two_layers_with_objects/test_data/versioned_key_td.hpp"

namespace {

dogen::two_layers_with_objects::versioned_key
create_dogen_two_layers_with_objects_versioned_key(const unsigned int position) {
    return dogen::two_layers_with_objects::versioned_key_generator::create(position);
}

}

namespace dogen {
namespace two_layers_with_objects {
namespace Package_2 {

class_2_generator::class_2_generator() : position_(0) { }

void class_2_generator::
populate(const unsigned int position, result_type& v) {
    v.versioned_key(create_dogen_two_layers_with_objects_versioned_key(position + 0));
}

class_2_generator::result_type
class_2_generator::create(const unsigned int position) {
    class_2 r;
    class_2_generator::populate(position, r);
    return r;
}

class_2_generator::result_type
class_2_generator::operator()() {
    return create(position_++);

}

} } }
