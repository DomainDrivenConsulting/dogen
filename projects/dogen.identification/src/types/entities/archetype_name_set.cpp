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
#include "dogen.identification/types/entities/archetype_name_set.hpp"

namespace dogen::identification::entities {

archetype_name_set::archetype_name_set(
    const dogen::identification::entities::logical_meta_id& logical_meta_id,
    const std::list<dogen::identification::entities::physical_meta_name>& meta_names,
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::physical_meta_id>& canonical_locations,
    const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::physical_meta_id>& archetype_for_label)
    : logical_meta_id_(logical_meta_id),
      meta_names_(meta_names),
      canonical_locations_(canonical_locations),
      archetype_for_label_(archetype_for_label) { }

void archetype_name_set::swap(archetype_name_set& other) noexcept {
    using std::swap;
    swap(logical_meta_id_, other.logical_meta_id_);
    swap(meta_names_, other.meta_names_);
    swap(canonical_locations_, other.canonical_locations_);
    swap(archetype_for_label_, other.archetype_for_label_);
}

bool archetype_name_set::operator==(const archetype_name_set& rhs) const {
    return logical_meta_id_ == rhs.logical_meta_id_ &&
        meta_names_ == rhs.meta_names_ &&
        canonical_locations_ == rhs.canonical_locations_ &&
        archetype_for_label_ == rhs.archetype_for_label_;
}

archetype_name_set& archetype_name_set::operator=(archetype_name_set other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::identification::entities::logical_meta_id& archetype_name_set::logical_meta_id() const {
    return logical_meta_id_;
}

dogen::identification::entities::logical_meta_id& archetype_name_set::logical_meta_id() {
    return logical_meta_id_;
}

void archetype_name_set::logical_meta_id(const dogen::identification::entities::logical_meta_id& v) {
    logical_meta_id_ = v;
}

void archetype_name_set::logical_meta_id(const dogen::identification::entities::logical_meta_id&& v) {
    logical_meta_id_ = std::move(v);
}

const std::list<dogen::identification::entities::physical_meta_name>& archetype_name_set::meta_names() const {
    return meta_names_;
}

std::list<dogen::identification::entities::physical_meta_name>& archetype_name_set::meta_names() {
    return meta_names_;
}

void archetype_name_set::meta_names(const std::list<dogen::identification::entities::physical_meta_name>& v) {
    meta_names_ = v;
}

void archetype_name_set::meta_names(const std::list<dogen::identification::entities::physical_meta_name>&& v) {
    meta_names_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::physical_meta_id>& archetype_name_set::canonical_locations() const {
    return canonical_locations_;
}

std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::physical_meta_id>& archetype_name_set::canonical_locations() {
    return canonical_locations_;
}

void archetype_name_set::canonical_locations(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::physical_meta_id>& v) {
    canonical_locations_ = v;
}

void archetype_name_set::canonical_locations(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::physical_meta_id>&& v) {
    canonical_locations_ = std::move(v);
}

const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::physical_meta_id>& archetype_name_set::archetype_for_label() const {
    return archetype_for_label_;
}

std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::physical_meta_id>& archetype_name_set::archetype_for_label() {
    return archetype_for_label_;
}

void archetype_name_set::archetype_for_label(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::physical_meta_id>& v) {
    archetype_for_label_ = v;
}

void archetype_name_set::archetype_for_label(const std::unordered_map<dogen::identification::entities::physical_meta_id, dogen::identification::entities::physical_meta_id>&& v) {
    archetype_for_label_ = std::move(v);
}

}
