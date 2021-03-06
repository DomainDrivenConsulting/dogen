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
#ifndef DOGEN_VARIABILITY_TYPES_ENTITIES_VALUE_HPP
#define DOGEN_VARIABILITY_TYPES_ENTITIES_VALUE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen.variability/types/entities/value_visitor_fwd.hpp"

namespace dogen::variability::entities {

/**
 * @brief Base class of all value types.
 *
 * Represents a value for a configuration point, a default value for a feature, etc.
 */
class value {
public:
    value() = default;
    value(const value&) = default;
    value(value&&) = default;
    value& operator=(const value&) = default;

    virtual ~value() noexcept = 0;

public:
    virtual void accept(const value_visitor& v) const = 0;
    virtual void accept(value_visitor& v) const = 0;
    virtual void accept(const value_visitor& v) = 0;
    virtual void accept(value_visitor& v) = 0;

public:
    virtual void to_stream(std::ostream& s) const;

protected:
    bool compare(const value& rhs) const;
public:
    virtual bool equals(const value& other) const = 0;

protected:
    void swap(value& other) noexcept;

};

inline value::~value() noexcept { }

inline bool operator==(const value& lhs, const value& rhs) {
    return lhs.equals(rhs);
}

}

#endif
