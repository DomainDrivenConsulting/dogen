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
#include <ostream>
#include "dogen.identification/io/entities/uri_io.hpp"
#include "dogen.identification/io/entities/sha1_hash_io.hpp"
#include "dogen.identification/io/entities/model_type_io.hpp"
#include "dogen.identification/io/entities/injection_id_io.hpp"
#include "dogen.identification/io/entities/injection_location_io.hpp"
#include "dogen.identification/types/entities/injection_provenance.hpp"

namespace dogen::identification::entities {

injection_provenance::injection_provenance()
    : model_type_(static_cast<dogen::identification::entities::model_type>(0)) { }

injection_provenance::injection_provenance(
    const dogen::identification::entities::uri& model_uri,
    const dogen::identification::entities::model_type model_type,
    const dogen::identification::entities::sha1_hash& model_sha1_hash,
    const dogen::identification::entities::injection_id& injection_id,
    const dogen::identification::entities::injection_location& location)
    : model_uri_(model_uri),
      model_type_(model_type),
      model_sha1_hash_(model_sha1_hash),
      injection_id_(injection_id),
      location_(location) { }

void injection_provenance::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::identification::entities::injection_provenance\"" << ", "
      << "\"model_uri\": " << model_uri_ << ", "
      << "\"model_type\": " << model_type_ << ", "
      << "\"model_sha1_hash\": " << model_sha1_hash_ << ", "
      << "\"injection_id\": " << injection_id_ << ", "
      << "\"location\": " << location_
      << " }";
}

void injection_provenance::swap(injection_provenance& other) noexcept {
    using std::swap;
    swap(model_uri_, other.model_uri_);
    swap(model_type_, other.model_type_);
    swap(model_sha1_hash_, other.model_sha1_hash_);
    swap(injection_id_, other.injection_id_);
    swap(location_, other.location_);
}

bool injection_provenance::compare(const injection_provenance& rhs) const {
    return model_uri_ == rhs.model_uri_ &&
        model_type_ == rhs.model_type_ &&
        model_sha1_hash_ == rhs.model_sha1_hash_ &&
        injection_id_ == rhs.injection_id_ &&
        location_ == rhs.location_;
}

const dogen::identification::entities::uri& injection_provenance::model_uri() const {
    return model_uri_;
}

dogen::identification::entities::uri& injection_provenance::model_uri() {
    return model_uri_;
}

void injection_provenance::model_uri(const dogen::identification::entities::uri& v) {
    model_uri_ = v;
}

void injection_provenance::model_uri(const dogen::identification::entities::uri&& v) {
    model_uri_ = std::move(v);
}

dogen::identification::entities::model_type injection_provenance::model_type() const {
    return model_type_;
}

void injection_provenance::model_type(const dogen::identification::entities::model_type v) {
    model_type_ = v;
}

const dogen::identification::entities::sha1_hash& injection_provenance::model_sha1_hash() const {
    return model_sha1_hash_;
}

dogen::identification::entities::sha1_hash& injection_provenance::model_sha1_hash() {
    return model_sha1_hash_;
}

void injection_provenance::model_sha1_hash(const dogen::identification::entities::sha1_hash& v) {
    model_sha1_hash_ = v;
}

void injection_provenance::model_sha1_hash(const dogen::identification::entities::sha1_hash&& v) {
    model_sha1_hash_ = std::move(v);
}

const dogen::identification::entities::injection_id& injection_provenance::injection_id() const {
    return injection_id_;
}

dogen::identification::entities::injection_id& injection_provenance::injection_id() {
    return injection_id_;
}

void injection_provenance::injection_id(const dogen::identification::entities::injection_id& v) {
    injection_id_ = v;
}

void injection_provenance::injection_id(const dogen::identification::entities::injection_id&& v) {
    injection_id_ = std::move(v);
}

const dogen::identification::entities::injection_location& injection_provenance::location() const {
    return location_;
}

dogen::identification::entities::injection_location& injection_provenance::location() {
    return location_;
}

void injection_provenance::location(const dogen::identification::entities::injection_location& v) {
    location_ = v;
}

void injection_provenance::location(const dogen::identification::entities::injection_location&& v) {
    location_ = std::move(v);
}

}
