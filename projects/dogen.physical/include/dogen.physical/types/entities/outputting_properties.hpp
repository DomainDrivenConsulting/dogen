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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_OUTPUTTING_PROPERTIES_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_OUTPUTTING_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>

namespace dogen::physical::entities {

/**
 * @brief Properties related to outputting.
 */
class outputting_properties final {
public:
    outputting_properties(const outputting_properties&) = default;
    outputting_properties(outputting_properties&&) = default;
    ~outputting_properties() = default;

public:
    outputting_properties();

public:
    outputting_properties(
        const bool force_write,
        const bool delete_extra_files,
        const std::vector<std::string>& ignore_files_matching_regex,
        const bool delete_empty_directories);

public:
    bool force_write() const;
    void force_write(const bool v);

    bool delete_extra_files() const;
    void delete_extra_files(const bool v);

    const std::vector<std::string>& ignore_files_matching_regex() const;
    std::vector<std::string>& ignore_files_matching_regex();
    void ignore_files_matching_regex(const std::vector<std::string>& v);
    void ignore_files_matching_regex(const std::vector<std::string>&& v);

    bool delete_empty_directories() const;
    void delete_empty_directories(const bool v);

public:
    bool operator==(const outputting_properties& rhs) const;
    bool operator!=(const outputting_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(outputting_properties& other) noexcept;
    outputting_properties& operator=(outputting_properties other);

private:
    bool force_write_;
    bool delete_extra_files_;
    std::vector<std::string> ignore_files_matching_regex_;
    bool delete_empty_directories_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::outputting_properties& lhs,
    dogen::physical::entities::outputting_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
