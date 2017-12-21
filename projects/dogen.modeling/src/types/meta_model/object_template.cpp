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
#include "dogen.modeling/io/meta_model/name_io.hpp"
#include "dogen.modeling/io/meta_model/element_io.hpp"
#include "dogen.modeling/io/meta_model/attribute_io.hpp"
#include "dogen.modeling/types/meta_model/element_visitor.hpp"
#include "dogen.modeling/types/meta_model/object_template.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::modeling::meta_model::attribute>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<dogen::modeling::meta_model::name, std::list<dogen::modeling::meta_model::attribute> >& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << i->first;
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::modeling::meta_model::name>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace modeling {
namespace meta_model {

object_template::object_template()
    : is_immutable_(static_cast<bool>(0)),
      is_fluent_(static_cast<bool>(0)),
      is_child_(static_cast<bool>(0)) { }

object_template::object_template(
    const dogen::modeling::meta_model::name& name,
    const std::string& documentation,
    const dogen::annotations::annotation& annotation,
    const dogen::modeling::meta_model::origin_types origin_type,
    const boost::optional<dogen::modeling::meta_model::name>& contained_by,
    const bool in_global_module,
    const std::list<dogen::modeling::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::modeling::meta_model::name& meta_name,
    const bool is_element_extension,
    const dogen::formatting::decoration_properties& decoration_properties,
    const std::unordered_map<std::string, dogen::modeling::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::modeling::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const std::list<dogen::modeling::meta_model::attribute>& all_attributes,
    const std::list<dogen::modeling::meta_model::attribute>& local_attributes,
    const std::unordered_map<dogen::modeling::meta_model::name, std::list<dogen::modeling::meta_model::attribute> >& inherited_attributes,
    const bool is_immutable,
    const bool is_fluent,
    const std::list<dogen::modeling::meta_model::name>& parents,
    const bool is_child)
    : dogen::modeling::meta_model::element(
      name,
      documentation,
      annotation,
      origin_type,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      is_element_extension,
      decoration_properties,
      artefact_properties,
      archetype_location_properties),
      all_attributes_(all_attributes),
      local_attributes_(local_attributes),
      inherited_attributes_(inherited_attributes),
      is_immutable_(is_immutable),
      is_fluent_(is_fluent),
      parents_(parents),
      is_child_(is_child) { }

void object_template::accept(const element_visitor& v) const {
    v.visit(*this);
}

void object_template::accept(element_visitor& v) const {
    v.visit(*this);
    }

void object_template::accept(const element_visitor& v) {
    v.visit(*this);
}

void object_template::accept(element_visitor& v) {
    v.visit(*this);
}

void object_template::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::modeling::meta_model::object_template\"" << ", "
      << "\"__parent_0__\": ";
    dogen::modeling::meta_model::element::to_stream(s);
    s << ", "
      << "\"all_attributes\": " << all_attributes_ << ", "
      << "\"local_attributes\": " << local_attributes_ << ", "
      << "\"inherited_attributes\": " << inherited_attributes_ << ", "
      << "\"is_immutable\": " << is_immutable_ << ", "
      << "\"is_fluent\": " << is_fluent_ << ", "
      << "\"parents\": " << parents_ << ", "
      << "\"is_child\": " << is_child_
      << " }";
}

void object_template::swap(object_template& other) noexcept {
    dogen::modeling::meta_model::element::swap(other);

    using std::swap;
    swap(all_attributes_, other.all_attributes_);
    swap(local_attributes_, other.local_attributes_);
    swap(inherited_attributes_, other.inherited_attributes_);
    swap(is_immutable_, other.is_immutable_);
    swap(is_fluent_, other.is_fluent_);
    swap(parents_, other.parents_);
    swap(is_child_, other.is_child_);
}

bool object_template::equals(const dogen::modeling::meta_model::element& other) const {
    const object_template* const p(dynamic_cast<const object_template* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool object_template::operator==(const object_template& rhs) const {
    return dogen::modeling::meta_model::element::compare(rhs) &&
        all_attributes_ == rhs.all_attributes_ &&
        local_attributes_ == rhs.local_attributes_ &&
        inherited_attributes_ == rhs.inherited_attributes_ &&
        is_immutable_ == rhs.is_immutable_ &&
        is_fluent_ == rhs.is_fluent_ &&
        parents_ == rhs.parents_ &&
        is_child_ == rhs.is_child_;
}

object_template& object_template::operator=(object_template other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::modeling::meta_model::attribute>& object_template::all_attributes() const {
    return all_attributes_;
}

std::list<dogen::modeling::meta_model::attribute>& object_template::all_attributes() {
    return all_attributes_;
}

void object_template::all_attributes(const std::list<dogen::modeling::meta_model::attribute>& v) {
    all_attributes_ = v;
}

void object_template::all_attributes(const std::list<dogen::modeling::meta_model::attribute>&& v) {
    all_attributes_ = std::move(v);
}

const std::list<dogen::modeling::meta_model::attribute>& object_template::local_attributes() const {
    return local_attributes_;
}

std::list<dogen::modeling::meta_model::attribute>& object_template::local_attributes() {
    return local_attributes_;
}

void object_template::local_attributes(const std::list<dogen::modeling::meta_model::attribute>& v) {
    local_attributes_ = v;
}

void object_template::local_attributes(const std::list<dogen::modeling::meta_model::attribute>&& v) {
    local_attributes_ = std::move(v);
}

const std::unordered_map<dogen::modeling::meta_model::name, std::list<dogen::modeling::meta_model::attribute> >& object_template::inherited_attributes() const {
    return inherited_attributes_;
}

std::unordered_map<dogen::modeling::meta_model::name, std::list<dogen::modeling::meta_model::attribute> >& object_template::inherited_attributes() {
    return inherited_attributes_;
}

void object_template::inherited_attributes(const std::unordered_map<dogen::modeling::meta_model::name, std::list<dogen::modeling::meta_model::attribute> >& v) {
    inherited_attributes_ = v;
}

void object_template::inherited_attributes(const std::unordered_map<dogen::modeling::meta_model::name, std::list<dogen::modeling::meta_model::attribute> >&& v) {
    inherited_attributes_ = std::move(v);
}

bool object_template::is_immutable() const {
    return is_immutable_;
}

void object_template::is_immutable(const bool v) {
    is_immutable_ = v;
}

bool object_template::is_fluent() const {
    return is_fluent_;
}

void object_template::is_fluent(const bool v) {
    is_fluent_ = v;
}

const std::list<dogen::modeling::meta_model::name>& object_template::parents() const {
    return parents_;
}

std::list<dogen::modeling::meta_model::name>& object_template::parents() {
    return parents_;
}

void object_template::parents(const std::list<dogen::modeling::meta_model::name>& v) {
    parents_ = v;
}

void object_template::parents(const std::list<dogen::modeling::meta_model::name>&& v) {
    parents_ = std::move(v);
}

bool object_template::is_child() const {
    return is_child_;
}

void object_template::is_child(const bool v) {
    is_child_ = v;
}

} } }
