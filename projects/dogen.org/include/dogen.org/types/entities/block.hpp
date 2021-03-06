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
#ifndef DOGEN_ORG_TYPES_ENTITIES_BLOCK_HPP
#define DOGEN_ORG_TYPES_ENTITIES_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen.org/types/entities/parameter.hpp"
#include "dogen.org/types/entities/block_type.hpp"

namespace dogen::org::entities {

class block final {
public:
    block(const block&) = default;
    block(block&&) = default;
    ~block() = default;

public:
    block();

public:
    block(
        const std::string& name,
        const std::list<dogen::org::entities::parameter>& parameters,
        const std::string& contents,
        const dogen::org::entities::block_type type);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::list<dogen::org::entities::parameter>& parameters() const;
    std::list<dogen::org::entities::parameter>& parameters();
    void parameters(const std::list<dogen::org::entities::parameter>& v);
    void parameters(const std::list<dogen::org::entities::parameter>&& v);

    const std::string& contents() const;
    std::string& contents();
    void contents(const std::string& v);
    void contents(const std::string&& v);

    dogen::org::entities::block_type type() const;
    void type(const dogen::org::entities::block_type v);

public:
    bool operator==(const block& rhs) const;
    bool operator!=(const block& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(block& other) noexcept;
    block& operator=(block other);

private:
    std::string name_;
    std::list<dogen::org::entities::parameter> parameters_;
    std::string contents_;
    dogen::org::entities::block_type type_;
};

}

namespace std {

template<>
inline void swap(
    dogen::org::entities::block& lhs,
    dogen::org::entities::block& rhs) {
    lhs.swap(rhs);
}

}

#endif
