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
#include "dogen.text.cpp/types/transforms/odb/builtin_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/odb/primitive_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/odb/class_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/odb/enum_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/odb/common_odb_options_transform.hpp"
#include "dogen.text.cpp/types/transforms/odb/object_odb_options_transform.hpp"
#include "dogen.text.cpp/types/transforms/odb/primitive_odb_options_transform.hpp"
#include "dogen.text/types/transforms/cpp/odb/initializer.hpp"

namespace dogen::text::transforms::cpp::odb {

void initializer::initialize(text_transform_registrar& ttrg,
    helper_registrar& /*hrg*/) {
    using namespace text::cpp::transforms::odb;
    register_text_transform<builtin_header_transform>(ttrg);
    register_text_transform<primitive_header_transform>(ttrg);
    register_text_transform<class_header_transform>(ttrg);
    register_text_transform<enum_header_transform>(ttrg);
    register_text_transform<common_odb_options_transform>(ttrg);
    register_text_transform<object_odb_options_transform>(ttrg);
    register_text_transform<primitive_odb_options_transform>(ttrg);
}

}