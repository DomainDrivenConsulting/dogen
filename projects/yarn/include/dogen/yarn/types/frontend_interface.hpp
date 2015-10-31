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
#ifndef DOGEN_YARN_TYPES_FRONTEND_INTERFACE_HPP
#define DOGEN_YARN_TYPES_FRONTEND_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <boost/optional.hpp>
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/input_descriptor.hpp"
#include "dogen/dynamic/types/workflow.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Reads an intermediate model from an input descriptor.
 */
class frontend_interface {
public:
    frontend_interface() = default;
    frontend_interface(const frontend_interface&) = delete;
    frontend_interface(frontend_interface&&) = default;
    virtual ~frontend_interface() noexcept = 0;

public:
    /**
     * @brief Unique identifier for the frontend, used for logging
     * purposes.
     */
    virtual std::string id() const = 0;

    /**
     * @brief List of extensions supported by this frontend.
     */
    virtual std::list<std::string> supported_extensions() const = 0;

    /**
     * @brief Reads the contents of the input descriptor and
     * transforms it into an intermediate model.
     */
    virtual intermediate_model execute(const dynamic::workflow& w,
        const input_descriptor& d) = 0;
};

} }

#endif
