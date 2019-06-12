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
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/traits.hpp"
#include "dogen.generation.cpp/types/formatters/serialization/traits.hpp"

namespace dogen::generation::cpp::formatters::serialization {

std::string traits::facet() {
    static std::string r(cpp::traits::backend() + ".serialization");
    return r;
}

std::string traits::canonical_archetype() {
    static std::string r(traits::facet() + ".canonical_archetype");
    return r;
}

std::string traits::class_header_archetype() {
    static std::string r(traits::facet() + ".class_header");
    return r;
}

std::string traits::class_implementation_archetype() {
    static std::string r(traits::facet() + ".class_implementation");
    return r;
}

std::string traits::enum_header_archetype() {
    static std::string r(traits::facet() + ".enum_header");
    return r;
}

std::string traits::class_forward_declarations_archetype() {
    static std::string r(traits::facet() + ".class_forward_declarations");
    return r;
}

std::string traits::primitive_forward_declarations_archetype() {
    static std::string r(traits::facet() + ".primitive_forward_declarations");
    return r;
}

std::string traits::registrar_header_archetype() {
    static std::string r(traits::facet() + ".registrar_header");
    return r;
}

std::string traits::registrar_implementation_archetype() {
    static std::string r(traits::facet() + ".registrar_implementation");
    return r;
}

std::string traits::builtin_header_archetype() {
    static std::string r(traits::facet() + ".builtin_header");
    return r;
}

std::string traits::primitive_header_archetype() {
    static std::string r(traits::facet() + ".primitive_header");
    return r;
}

std::string traits::primitive_implementation_archetype() {
    static std::string r(traits::facet() + ".primitive_implementation");
    return r;
}

std::string traits::type_registrar_header_archetype() {
    static std::string r(traits::facet() + ".type_registrar_header");
    return r;
}

std::string traits::type_registrar_implementation_archetype() {
    static std::string r(traits::facet() + ".type_registrar_implementation");
    return r;
}

}
