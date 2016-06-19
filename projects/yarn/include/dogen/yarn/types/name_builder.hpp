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
#ifndef DOGEN_YARN_TYPES_NAME_BUILDER_HPP
#define DOGEN_YARN_TYPES_NAME_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include "dogen/yarn/types/name.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Builds a name.
 *
 * If setup in model name mode, the following will hold:
 *
 * @li the simple name will be set from the model name (and cannot be
 * set individually);
 * @li the model name will not contribute to the qualified name.
 */
class name_builder {
public:
    explicit name_builder(const bool model_name_mode_ = false);
    explicit name_builder(const name& n, const bool model_name_mode_ = false);

private:
    void create_name_id();

public:
    name_builder& simple_name(const std::string& sn);
    name_builder& model_name(const std::string& mn);
    name_builder& model_name(const yarn::location& l);
    name_builder& model_modules(const std::list<std::string>& mm);
    name_builder& internal_modules(const std::string& im);
    name_builder& internal_modules(const std::list<std::string>& im);
    name_builder& external_modules(const std::string& em);
    name_builder& external_modules(const std::list<std::string>& em);
    name_builder& location(const yarn::location& l);

public:
    name build();

private:
    const bool model_name_mode_;
    name name_;
};

} }

#endif
