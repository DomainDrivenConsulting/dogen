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
#include "dogen.physical/types/entities/relations.hpp"

namespace dogen::physical::entities {

relations::relations()
    : status_(static_cast<dogen::physical::entities::relation_status>(0)) { }

relations::relations(
    const dogen::physical::entities::relation_status status,
    const std::list<dogen::physical::entities::constant_relation>& constant,
    const std::list<dogen::physical::entities::variable_relation>& variable,
    const std::list<dogen::physical::entities::hard_coded_relation>& hard_coded)
    : status_(status),
      constant_(constant),
      variable_(variable),
      hard_coded_(hard_coded) { }

void relations::swap(relations& other) noexcept {
    using std::swap;
    swap(status_, other.status_);
    swap(constant_, other.constant_);
    swap(variable_, other.variable_);
    swap(hard_coded_, other.hard_coded_);
}

bool relations::operator==(const relations& rhs) const {
    return status_ == rhs.status_ &&
        constant_ == rhs.constant_ &&
        variable_ == rhs.variable_ &&
        hard_coded_ == rhs.hard_coded_;
}

relations& relations::operator=(relations other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::physical::entities::relation_status relations::status() const {
    return status_;
}

void relations::status(const dogen::physical::entities::relation_status v) {
    status_ = v;
}

const std::list<dogen::physical::entities::constant_relation>& relations::constant() const {
    return constant_;
}

std::list<dogen::physical::entities::constant_relation>& relations::constant() {
    return constant_;
}

void relations::constant(const std::list<dogen::physical::entities::constant_relation>& v) {
    constant_ = v;
}

void relations::constant(const std::list<dogen::physical::entities::constant_relation>&& v) {
    constant_ = std::move(v);
}

const std::list<dogen::physical::entities::variable_relation>& relations::variable() const {
    return variable_;
}

std::list<dogen::physical::entities::variable_relation>& relations::variable() {
    return variable_;
}

void relations::variable(const std::list<dogen::physical::entities::variable_relation>& v) {
    variable_ = v;
}

void relations::variable(const std::list<dogen::physical::entities::variable_relation>&& v) {
    variable_ = std::move(v);
}

const std::list<dogen::physical::entities::hard_coded_relation>& relations::hard_coded() const {
    return hard_coded_;
}

std::list<dogen::physical::entities::hard_coded_relation>& relations::hard_coded() {
    return hard_coded_;
}

void relations::hard_coded(const std::list<dogen::physical::entities::hard_coded_relation>& v) {
    hard_coded_ = v;
}

void relations::hard_coded(const std::list<dogen::physical::entities::hard_coded_relation>&& v) {
    hard_coded_ = std::move(v);
}

}
