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
#include <string>
#include <ostream>
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/dia/io/object_types_io.hpp"

namespace {

const std::string prefix("object_types::");
const std::string invalid("invalid");
const std::string uml_large_package("uml_large_package");
const std::string uml_class("uml_class");

const std::string error_message("Invalid or unexpected object type");

}

namespace dogen {
namespace dia {

std::ostream& operator<<(std::ostream& stream, object_types value) {
    switch (value) {
    case object_types::invalid:
        return stream << prefix << invalid;
    case object_types::uml_large_package:
        return stream << prefix << uml_large_package;
    case object_types::uml_class:
        return stream << prefix << uml_class;
    default:
        break;
    }
    throw utility::exception::invalid_enum_value(error_message);
}

} }
