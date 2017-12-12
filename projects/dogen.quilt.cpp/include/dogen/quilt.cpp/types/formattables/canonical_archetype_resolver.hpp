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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_CANONICAL_FORMATTER_RESOLVER_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_CANONICAL_FORMATTER_RESOLVER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include "dogen/quilt.cpp/types/formattables/formattable.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

/**
 * @brief If given an archetype in canonical form and an element id,
 * resolves it to the concrete archetype for that element.
 *
 * If supplied a non-canonical archetype, simply returns it back to
 * the caller.
 */
class canonical_archetype_resolver {
public:
    canonical_archetype_resolver(
        const std::unordered_map<std::string, formattable>& formattables);

private:
    bool is_canonical_archetype(const std::string& archetype) const;

public:
    std::string resolve(const std::string& element_id,
        const std::string& archetype) const;

private:
    const std::unordered_map<std::string, formattable>& formattables_;
};

} } } }

#endif
