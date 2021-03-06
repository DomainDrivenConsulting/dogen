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
#ifndef DOGEN_TYPES_SPEC_ENTRY_HPP
#define DOGEN_TYPES_SPEC_ENTRY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace dogen {

/**
 * @brief Unit of functionality within Dogen.
 */
class spec_entry final {
public:
    spec_entry() = default;
    spec_entry(const spec_entry&) = default;
    spec_entry(spec_entry&&) = default;
    ~spec_entry() = default;

public:
    spec_entry(
        const std::string& name,
        const std::string& description);

public:
    /**
     * @brief Name for this spec entry.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief Human readable text describing this entry.
     */
    /**@{*/
    const std::string& description() const;
    std::string& description();
    void description(const std::string& v);
    void description(const std::string&& v);
    /**@}*/

public:
    bool operator==(const spec_entry& rhs) const;
    bool operator!=(const spec_entry& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(spec_entry& other) noexcept;
    spec_entry& operator=(spec_entry other);

private:
    std::string name_;
    std::string description_;
};

}

namespace std {

template<>
inline void swap(
    dogen::spec_entry& lhs,
    dogen::spec_entry& rhs) {
    lhs.swap(rhs);
}

}

#endif
