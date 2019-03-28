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
#include "masd.dogen.coding/types/meta_model/name_tree.hpp"

namespace masd::dogen::coding::meta_model {

name_tree::name_tree()
    : are_children_opaque_(static_cast<bool>(0)),
      is_circular_dependency_(static_cast<bool>(0)),
      is_current_simple_type_(static_cast<bool>(0)),
      is_floating_point_(static_cast<bool>(0)) { }

name_tree::name_tree(
    const masd::dogen::coding::meta_model::fully_qualified_representation& qualified,
    const masd::dogen::coding::meta_model::name& current,
    const std::list<masd::dogen::coding::meta_model::name_tree>& children,
    const bool are_children_opaque,
    const bool is_circular_dependency,
    const bool is_current_simple_type,
    const bool is_floating_point)
    : qualified_(qualified),
      current_(current),
      children_(children),
      are_children_opaque_(are_children_opaque),
      is_circular_dependency_(is_circular_dependency),
      is_current_simple_type_(is_current_simple_type),
      is_floating_point_(is_floating_point) { }

void name_tree::swap(name_tree& other) noexcept {
    using std::swap;
    swap(qualified_, other.qualified_);
    swap(current_, other.current_);
    swap(children_, other.children_);
    swap(are_children_opaque_, other.are_children_opaque_);
    swap(is_circular_dependency_, other.is_circular_dependency_);
    swap(is_current_simple_type_, other.is_current_simple_type_);
    swap(is_floating_point_, other.is_floating_point_);
}

bool name_tree::operator==(const name_tree& rhs) const {
    return qualified_ == rhs.qualified_ &&
        current_ == rhs.current_ &&
        children_ == rhs.children_ &&
        are_children_opaque_ == rhs.are_children_opaque_ &&
        is_circular_dependency_ == rhs.is_circular_dependency_ &&
        is_current_simple_type_ == rhs.is_current_simple_type_ &&
        is_floating_point_ == rhs.is_floating_point_;
}

name_tree& name_tree::operator=(name_tree other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const masd::dogen::coding::meta_model::fully_qualified_representation& name_tree::qualified() const {
    return qualified_;
}

masd::dogen::coding::meta_model::fully_qualified_representation& name_tree::qualified() {
    return qualified_;
}

void name_tree::qualified(const masd::dogen::coding::meta_model::fully_qualified_representation& v) {
    qualified_ = v;
}

void name_tree::qualified(const masd::dogen::coding::meta_model::fully_qualified_representation&& v) {
    qualified_ = std::move(v);
}

const masd::dogen::coding::meta_model::name& name_tree::current() const {
    return current_;
}

masd::dogen::coding::meta_model::name& name_tree::current() {
    return current_;
}

void name_tree::current(const masd::dogen::coding::meta_model::name& v) {
    current_ = v;
}

void name_tree::current(const masd::dogen::coding::meta_model::name&& v) {
    current_ = std::move(v);
}

const std::list<masd::dogen::coding::meta_model::name_tree>& name_tree::children() const {
    return children_;
}

std::list<masd::dogen::coding::meta_model::name_tree>& name_tree::children() {
    return children_;
}

void name_tree::children(const std::list<masd::dogen::coding::meta_model::name_tree>& v) {
    children_ = v;
}

void name_tree::children(const std::list<masd::dogen::coding::meta_model::name_tree>&& v) {
    children_ = std::move(v);
}

bool name_tree::are_children_opaque() const {
    return are_children_opaque_;
}

void name_tree::are_children_opaque(const bool v) {
    are_children_opaque_ = v;
}

bool name_tree::is_circular_dependency() const {
    return is_circular_dependency_;
}

void name_tree::is_circular_dependency(const bool v) {
    is_circular_dependency_ = v;
}

bool name_tree::is_current_simple_type() const {
    return is_current_simple_type_;
}

void name_tree::is_current_simple_type(const bool v) {
    is_current_simple_type_ = v;
}

bool name_tree::is_floating_point() const {
    return is_floating_point_;
}

void name_tree::is_floating_point(const bool v) {
    is_floating_point_ = v;
}

}
