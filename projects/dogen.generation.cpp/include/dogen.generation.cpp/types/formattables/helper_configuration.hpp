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
#ifndef DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_HELPER_CONFIGURATION_HPP
#define DOGEN_GENERATION_CPP_TYPES_FORMATTABLES_HELPER_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.generation.cpp/types/formattables/streaming_properties.hpp"

namespace dogen {
namespace generation {
namespace cpp {
namespace formattables {

class helper_configuration final {
public:
    helper_configuration() = default;
    helper_configuration(const helper_configuration&) = default;
    helper_configuration(helper_configuration&&) = default;
    ~helper_configuration() = default;

public:
    helper_configuration(
        const std::unordered_map<std::string, std::string>& helper_families,
        const std::unordered_map<std::string, dogen::generation::cpp::formattables::streaming_properties>& streaming_properties);

public:
    const std::unordered_map<std::string, std::string>& helper_families() const;
    std::unordered_map<std::string, std::string>& helper_families();
    void helper_families(const std::unordered_map<std::string, std::string>& v);
    void helper_families(const std::unordered_map<std::string, std::string>&& v);

    const std::unordered_map<std::string, dogen::generation::cpp::formattables::streaming_properties>& streaming_properties() const;
    std::unordered_map<std::string, dogen::generation::cpp::formattables::streaming_properties>& streaming_properties();
    void streaming_properties(const std::unordered_map<std::string, dogen::generation::cpp::formattables::streaming_properties>& v);
    void streaming_properties(const std::unordered_map<std::string, dogen::generation::cpp::formattables::streaming_properties>&& v);

public:
    bool operator==(const helper_configuration& rhs) const;
    bool operator!=(const helper_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(helper_configuration& other) noexcept;
    helper_configuration& operator=(helper_configuration other);

private:
    std::unordered_map<std::string, std::string> helper_families_;
    std::unordered_map<std::string, dogen::generation::cpp::formattables::streaming_properties> streaming_properties_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::generation::cpp::formattables::helper_configuration& lhs,
    dogen::generation::cpp::formattables::helper_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
