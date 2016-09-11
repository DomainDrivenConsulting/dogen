/* -*- mode++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
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
#ifndef DOGEN_QUILT_CPP_TYPES_PROPERTIES_NAME_BUILDER_HPP
#define DOGEN_QUILT_CPP_TYPES_PROPERTIES_NAME_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/name_tree.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

/**
 * @brief Builds string representations of names, according to the
 * grammar of C++.
 */
class name_builder {
public:
    name_builder() = default;
    name_builder(const name_builder&) = default;
    name_builder(name_builder&&) = default;
    ~name_builder() noexcept = default;

public:
    /**
     * @brief Flattens all the Yarn namespace information stored in
     * name into a list of strings with C++ namespaces.
     */
    std::list<std::string>
    namespace_list(const yarn::name& n,
        const bool detect_model_name = true) const;
};

} } } }

#endif
