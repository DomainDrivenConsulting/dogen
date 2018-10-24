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
#ifndef MASD_DOGEN_GENERATION_CSHARP_TYPES_FORMATTERS_HELPER_FORMATTER_INTERFACE_HPP
#define MASD_DOGEN_GENERATION_CSHARP_TYPES_FORMATTERS_HELPER_FORMATTER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include "masd.dogen.generation.csharp/types/formatters/assistant_fwd.hpp"
#include "masd.dogen.generation.csharp/types/formattables/helper_properties_fwd.hpp"

namespace masd::dogen::generation::csharp::formatters {

class helper_formatter_interface {
public:
    helper_formatter_interface() = default;
    helper_formatter_interface(const helper_formatter_interface&) = delete;
    helper_formatter_interface(helper_formatter_interface&&) = default;
    virtual ~helper_formatter_interface() noexcept = 0;

public:
    virtual std::string id() const = 0;
    virtual std::string family() const = 0;
    virtual std::list<std::string> owning_formatters() const = 0;
    virtual std::list<std::string> owning_facets() const = 0;
    virtual std::string helper_name() const = 0;
    virtual void format(assistant& a,
        const formattables::helper_properties& hp) const = 0;
};

}

#endif
