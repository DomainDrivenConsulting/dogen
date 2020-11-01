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
#include <boost/io/ios_state.hpp>
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.logical/io/entities/attribute_io.hpp"
#include "dogen.logical/types/entities/element_visitor.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/io/entities/orm/primitive_properties_io.hpp"

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<dogen::logical::entities::orm::primitive_properties>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace dogen::logical::entities::structural {

primitive::primitive()
    : requires_manual_default_constructor_(static_cast<bool>(0)),
      requires_manual_move_constructor_(static_cast<bool>(0)),
      requires_stream_manipulators_(static_cast<bool>(0)),
      is_nullable_(static_cast<bool>(0)),
      use_type_aliasing_(static_cast<bool>(0)),
      is_immutable_(static_cast<bool>(0)) { }

primitive::primitive(primitive&& rhs)
    : dogen::logical::entities::element(
        std::forward<dogen::logical::entities::element>(rhs)),
      requires_manual_default_constructor_(std::move(rhs.requires_manual_default_constructor_)),
      requires_manual_move_constructor_(std::move(rhs.requires_manual_move_constructor_)),
      requires_stream_manipulators_(std::move(rhs.requires_stream_manipulators_)),
      is_nullable_(std::move(rhs.is_nullable_)),
      value_attribute_(std::move(rhs.value_attribute_)),
      use_type_aliasing_(std::move(rhs.use_type_aliasing_)),
      is_immutable_(std::move(rhs.is_immutable_)),
      orm_properties_(std::move(rhs.orm_properties_)) { }

primitive::primitive(
    const dogen::identification::entities::logical_name& name,
    const std::string& documentation,
    const dogen::identification::entities::codec_provenance& provenance,
    const dogen::identification::entities::logical_id& contained_by,
    const bool in_global_module,
    const dogen::logical::entities::stereotypes& stereotypes,
    const dogen::identification::entities::logical_meta_name& meta_name,
    const dogen::identification::entities::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const std::list<dogen::identification::entities::label>& labels,
    const dogen::logical::entities::generability_status generability_status,
    const std::unordered_map<dogen::identification::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
    const bool requires_manual_default_constructor,
    const bool requires_manual_move_constructor,
    const bool requires_stream_manipulators,
    const bool is_nullable,
    const dogen::logical::entities::attribute& value_attribute,
    const bool use_type_aliasing,
    const bool is_immutable,
    const boost::optional<dogen::logical::entities::orm::primitive_properties>& orm_properties)
    : dogen::logical::entities::element(
      name,
      documentation,
      provenance,
      contained_by,
      in_global_module,
      stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      labels,
      generability_status,
      decoration),
      requires_manual_default_constructor_(requires_manual_default_constructor),
      requires_manual_move_constructor_(requires_manual_move_constructor),
      requires_stream_manipulators_(requires_stream_manipulators),
      is_nullable_(is_nullable),
      value_attribute_(value_attribute),
      use_type_aliasing_(use_type_aliasing),
      is_immutable_(is_immutable),
      orm_properties_(orm_properties) { }

void primitive::accept(const element_visitor& v) const {
    v.visit(*this);
}

void primitive::accept(element_visitor& v) const {
    v.visit(*this);
    }

void primitive::accept(const element_visitor& v) {
    v.visit(*this);
}

void primitive::accept(element_visitor& v) {
    v.visit(*this);
}

void primitive::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::logical::entities::structural::primitive\"" << ", "
      << "\"__parent_0__\": ";
    dogen::logical::entities::element::to_stream(s);
    s << ", "
      << "\"requires_manual_default_constructor\": " << requires_manual_default_constructor_ << ", "
      << "\"requires_manual_move_constructor\": " << requires_manual_move_constructor_ << ", "
      << "\"requires_stream_manipulators\": " << requires_stream_manipulators_ << ", "
      << "\"is_nullable\": " << is_nullable_ << ", "
      << "\"value_attribute\": " << value_attribute_ << ", "
      << "\"use_type_aliasing\": " << use_type_aliasing_ << ", "
      << "\"is_immutable\": " << is_immutable_ << ", "
      << "\"orm_properties\": " << orm_properties_
      << " }";
}

void primitive::swap(primitive& other) noexcept {
    dogen::logical::entities::element::swap(other);

    using std::swap;
    swap(requires_manual_default_constructor_, other.requires_manual_default_constructor_);
    swap(requires_manual_move_constructor_, other.requires_manual_move_constructor_);
    swap(requires_stream_manipulators_, other.requires_stream_manipulators_);
    swap(is_nullable_, other.is_nullable_);
    swap(value_attribute_, other.value_attribute_);
    swap(use_type_aliasing_, other.use_type_aliasing_);
    swap(is_immutable_, other.is_immutable_);
    swap(orm_properties_, other.orm_properties_);
}

bool primitive::equals(const dogen::logical::entities::element& other) const {
    const primitive* const p(dynamic_cast<const primitive* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool primitive::operator==(const primitive& rhs) const {
    return dogen::logical::entities::element::compare(rhs) &&
        requires_manual_default_constructor_ == rhs.requires_manual_default_constructor_ &&
        requires_manual_move_constructor_ == rhs.requires_manual_move_constructor_ &&
        requires_stream_manipulators_ == rhs.requires_stream_manipulators_ &&
        is_nullable_ == rhs.is_nullable_ &&
        value_attribute_ == rhs.value_attribute_ &&
        use_type_aliasing_ == rhs.use_type_aliasing_ &&
        is_immutable_ == rhs.is_immutable_ &&
        orm_properties_ == rhs.orm_properties_;
}

primitive& primitive::operator=(primitive other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool primitive::requires_manual_default_constructor() const {
    return requires_manual_default_constructor_;
}

void primitive::requires_manual_default_constructor(const bool v) {
    requires_manual_default_constructor_ = v;
}

bool primitive::requires_manual_move_constructor() const {
    return requires_manual_move_constructor_;
}

void primitive::requires_manual_move_constructor(const bool v) {
    requires_manual_move_constructor_ = v;
}

bool primitive::requires_stream_manipulators() const {
    return requires_stream_manipulators_;
}

void primitive::requires_stream_manipulators(const bool v) {
    requires_stream_manipulators_ = v;
}

bool primitive::is_nullable() const {
    return is_nullable_;
}

void primitive::is_nullable(const bool v) {
    is_nullable_ = v;
}

const dogen::logical::entities::attribute& primitive::value_attribute() const {
    return value_attribute_;
}

dogen::logical::entities::attribute& primitive::value_attribute() {
    return value_attribute_;
}

void primitive::value_attribute(const dogen::logical::entities::attribute& v) {
    value_attribute_ = v;
}

void primitive::value_attribute(const dogen::logical::entities::attribute&& v) {
    value_attribute_ = std::move(v);
}

bool primitive::use_type_aliasing() const {
    return use_type_aliasing_;
}

void primitive::use_type_aliasing(const bool v) {
    use_type_aliasing_ = v;
}

bool primitive::is_immutable() const {
    return is_immutable_;
}

void primitive::is_immutable(const bool v) {
    is_immutable_ = v;
}

const boost::optional<dogen::logical::entities::orm::primitive_properties>& primitive::orm_properties() const {
    return orm_properties_;
}

boost::optional<dogen::logical::entities::orm::primitive_properties>& primitive::orm_properties() {
    return orm_properties_;
}

void primitive::orm_properties(const boost::optional<dogen::logical::entities::orm::primitive_properties>& v) {
    orm_properties_ = v;
}

void primitive::orm_properties(const boost::optional<dogen::logical::entities::orm::primitive_properties>&& v) {
    orm_properties_ = std::move(v);
}

}
