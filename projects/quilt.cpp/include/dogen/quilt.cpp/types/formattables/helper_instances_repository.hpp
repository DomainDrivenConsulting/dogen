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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_HELPER_INSTANCES_REPOSITORY_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_HELPER_INSTANCES_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen/quilt.cpp/types/formattables/helper_instance.hpp"
#include "dogen/quilt.cpp/serialization/formattables/helper_instances_repository_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class helper_instances_repository final {
public:
    helper_instances_repository() = default;
    helper_instances_repository(const helper_instances_repository&) = default;
    helper_instances_repository(helper_instances_repository&&) = default;
    ~helper_instances_repository() = default;

public:
    explicit helper_instances_repository(const std::unordered_map<std::string, std::list<dogen::quilt::cpp::formattables::helper_instance> >& helper_instances_by_name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const helper_instances_repository& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, helper_instances_repository& v, unsigned int version);

public:
    const std::unordered_map<std::string, std::list<dogen::quilt::cpp::formattables::helper_instance> >& helper_instances_by_name() const;
    std::unordered_map<std::string, std::list<dogen::quilt::cpp::formattables::helper_instance> >& helper_instances_by_name();
    void helper_instances_by_name(const std::unordered_map<std::string, std::list<dogen::quilt::cpp::formattables::helper_instance> >& v);
    void helper_instances_by_name(const std::unordered_map<std::string, std::list<dogen::quilt::cpp::formattables::helper_instance> >&& v);

public:
    bool operator==(const helper_instances_repository& rhs) const;
    bool operator!=(const helper_instances_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(helper_instances_repository& other) noexcept;
    helper_instances_repository& operator=(helper_instances_repository other);

private:
    std::unordered_map<std::string, std::list<dogen::quilt::cpp::formattables::helper_instance> > helper_instances_by_name_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::formattables::helper_instances_repository& lhs,
    dogen::quilt::cpp::formattables::helper_instances_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
