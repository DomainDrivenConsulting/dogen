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
#include "dogen.codec/types/entities/model_set.hpp"

namespace dogen::codec::entities {

model_set::model_set(
    const dogen::codec::entities::model& target,
    const std::list<dogen::codec::entities::model>& references,
    const dogen::codec::entities::reference_graph_data& reference_graph_data)
    : target_(target),
      references_(references),
      reference_graph_data_(reference_graph_data) { }

void model_set::swap(model_set& other) noexcept {
    using std::swap;
    swap(target_, other.target_);
    swap(references_, other.references_);
    swap(reference_graph_data_, other.reference_graph_data_);
}

bool model_set::operator==(const model_set& rhs) const {
    return target_ == rhs.target_ &&
        references_ == rhs.references_ &&
        reference_graph_data_ == rhs.reference_graph_data_;
}

model_set& model_set::operator=(model_set other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::codec::entities::model& model_set::target() const {
    return target_;
}

dogen::codec::entities::model& model_set::target() {
    return target_;
}

void model_set::target(const dogen::codec::entities::model& v) {
    target_ = v;
}

void model_set::target(const dogen::codec::entities::model&& v) {
    target_ = std::move(v);
}

const std::list<dogen::codec::entities::model>& model_set::references() const {
    return references_;
}

std::list<dogen::codec::entities::model>& model_set::references() {
    return references_;
}

void model_set::references(const std::list<dogen::codec::entities::model>& v) {
    references_ = v;
}

void model_set::references(const std::list<dogen::codec::entities::model>&& v) {
    references_ = std::move(v);
}

const dogen::codec::entities::reference_graph_data& model_set::reference_graph_data() const {
    return reference_graph_data_;
}

dogen::codec::entities::reference_graph_data& model_set::reference_graph_data() {
    return reference_graph_data_;
}

void model_set::reference_graph_data(const dogen::codec::entities::reference_graph_data& v) {
    reference_graph_data_ = v;
}

void model_set::reference_graph_data(const dogen::codec::entities::reference_graph_data&& v) {
    reference_graph_data_ = std::move(v);
}

}
