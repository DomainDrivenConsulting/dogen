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
#include "dogen.identification/types/entities/logical_provenance.hpp"

namespace dogen::identification::entities {

logical_provenance::logical_provenance(
    const dogen::identification::entities::injection_provenance& injection,
    const dogen::identification::entities::logical_name& logical_name)
    : injection_(injection),
      logical_name_(logical_name) { }

void logical_provenance::swap(logical_provenance& other) noexcept {
    using std::swap;
    swap(injection_, other.injection_);
    swap(logical_name_, other.logical_name_);
}

bool logical_provenance::operator==(const logical_provenance& rhs) const {
    return injection_ == rhs.injection_ &&
        logical_name_ == rhs.logical_name_;
}

logical_provenance& logical_provenance::operator=(logical_provenance other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::identification::entities::injection_provenance& logical_provenance::injection() const {
    return injection_;
}

dogen::identification::entities::injection_provenance& logical_provenance::injection() {
    return injection_;
}

void logical_provenance::injection(const dogen::identification::entities::injection_provenance& v) {
    injection_ = v;
}

void logical_provenance::injection(const dogen::identification::entities::injection_provenance&& v) {
    injection_ = std::move(v);
}

const dogen::identification::entities::logical_name& logical_provenance::logical_name() const {
    return logical_name_;
}

dogen::identification::entities::logical_name& logical_provenance::logical_name() {
    return logical_name_;
}

void logical_provenance::logical_name(const dogen::identification::entities::logical_name& v) {
    logical_name_ = v;
}

void logical_provenance::logical_name(const dogen::identification::entities::logical_name&& v) {
    logical_name_ = std::move(v);
}

}
