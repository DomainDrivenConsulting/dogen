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
#include "dogen.physical/types/entities/name_group.hpp"

namespace dogen::physical::entities {

name_group::name_group(
    const std::list<dogen::physical::entities::location>& locations,
    const std::unordered_map<std::string, std::string>& canonical_locations)
    : locations_(locations),
      canonical_locations_(canonical_locations) { }

void name_group::swap(name_group& other) noexcept {
    using std::swap;
    swap(locations_, other.locations_);
    swap(canonical_locations_, other.canonical_locations_);
}

bool name_group::operator==(const name_group& rhs) const {
    return locations_ == rhs.locations_ &&
        canonical_locations_ == rhs.canonical_locations_;
}

name_group& name_group::operator=(name_group other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::physical::entities::location>& name_group::locations() const {
    return locations_;
}

std::list<dogen::physical::entities::location>& name_group::locations() {
    return locations_;
}

void name_group::locations(const std::list<dogen::physical::entities::location>& v) {
    locations_ = v;
}

void name_group::locations(const std::list<dogen::physical::entities::location>&& v) {
    locations_ = std::move(v);
}

const std::unordered_map<std::string, std::string>& name_group::canonical_locations() const {
    return canonical_locations_;
}

std::unordered_map<std::string, std::string>& name_group::canonical_locations() {
    return canonical_locations_;
}

void name_group::canonical_locations(const std::unordered_map<std::string, std::string>& v) {
    canonical_locations_ = v;
}

void name_group::canonical_locations(const std::unordered_map<std::string, std::string>&& v) {
    canonical_locations_ = std::move(v);
}

}