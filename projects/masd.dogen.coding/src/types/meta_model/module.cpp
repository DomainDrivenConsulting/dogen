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
#include <boost/algorithm/string.hpp>
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.coding/io/meta_model/element_io.hpp"
#include "masd.dogen.coding/types/meta_model/element_visitor.hpp"
#include "masd.dogen.coding/io/meta_model/orm_module_properties_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_set<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::optional<masd::dogen::coding::meta_model::orm_module_properties>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::optional\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace masd::dogen::coding::meta_model {

module::module()
    : is_root_(static_cast<bool>(0)),
      is_global_module_(static_cast<bool>(0)) { }

module::module(module&& rhs)
    : masd::dogen::coding::meta_model::element(
        std::forward<masd::dogen::coding::meta_model::element>(rhs)),
      contains_(std::move(rhs.contains_)),
      is_root_(std::move(rhs.is_root_)),
      is_global_module_(std::move(rhs.is_global_module_)),
      orm_properties_(std::move(rhs.orm_properties_)) { }

module::module(
    const masd::dogen::coding::meta_model::name& name,
    const std::string& documentation,
    const masd::dogen::annotations::annotation& annotation,
    const masd::dogen::coding::meta_model::origin_types origin_type,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<masd::dogen::coding::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const masd::dogen::coding::meta_model::name& meta_name,
    const masd::dogen::coding::meta_model::technical_space intrinsic_technical_space,
    const bool is_element_extension,
    const masd::dogen::extraction::decoration_properties& decoration_properties,
    const std::unordered_map<std::string, masd::dogen::coding::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, masd::dogen::coding::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const boost::optional<masd::dogen::coding::meta_model::decoration>& decoration,
    const std::unordered_set<std::string>& contains,
    const bool is_root,
    const bool is_global_module,
    const boost::optional<masd::dogen::coding::meta_model::orm_module_properties>& orm_properties)
    : masd::dogen::coding::meta_model::element(
      name,
      documentation,
      annotation,
      origin_type,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      intrinsic_technical_space,
      is_element_extension,
      decoration_properties,
      artefact_properties,
      archetype_location_properties,
      decoration),
      contains_(contains),
      is_root_(is_root),
      is_global_module_(is_global_module),
      orm_properties_(orm_properties) { }

void module::accept(const element_visitor& v) const {
    v.visit(*this);
}

void module::accept(element_visitor& v) const {
    v.visit(*this);
    }

void module::accept(const element_visitor& v) {
    v.visit(*this);
}

void module::accept(element_visitor& v) {
    v.visit(*this);
}

void module::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"masd::dogen::coding::meta_model::module\"" << ", "
      << "\"__parent_0__\": ";
    masd::dogen::coding::meta_model::element::to_stream(s);
    s << ", "
      << "\"contains\": " << contains_ << ", "
      << "\"is_root\": " << is_root_ << ", "
      << "\"is_global_module\": " << is_global_module_ << ", "
      << "\"orm_properties\": " << orm_properties_
      << " }";
}

void module::swap(module& other) noexcept {
    masd::dogen::coding::meta_model::element::swap(other);

    using std::swap;
    swap(contains_, other.contains_);
    swap(is_root_, other.is_root_);
    swap(is_global_module_, other.is_global_module_);
    swap(orm_properties_, other.orm_properties_);
}

bool module::equals(const masd::dogen::coding::meta_model::element& other) const {
    const module* const p(dynamic_cast<const module* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool module::operator==(const module& rhs) const {
    return masd::dogen::coding::meta_model::element::compare(rhs) &&
        contains_ == rhs.contains_ &&
        is_root_ == rhs.is_root_ &&
        is_global_module_ == rhs.is_global_module_ &&
        orm_properties_ == rhs.orm_properties_;
}

module& module::operator=(module other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_set<std::string>& module::contains() const {
    return contains_;
}

std::unordered_set<std::string>& module::contains() {
    return contains_;
}

void module::contains(const std::unordered_set<std::string>& v) {
    contains_ = v;
}

void module::contains(const std::unordered_set<std::string>&& v) {
    contains_ = std::move(v);
}

bool module::is_root() const {
    return is_root_;
}

void module::is_root(const bool v) {
    is_root_ = v;
}

bool module::is_global_module() const {
    return is_global_module_;
}

void module::is_global_module(const bool v) {
    is_global_module_ = v;
}

const boost::optional<masd::dogen::coding::meta_model::orm_module_properties>& module::orm_properties() const {
    return orm_properties_;
}

boost::optional<masd::dogen::coding::meta_model::orm_module_properties>& module::orm_properties() {
    return orm_properties_;
}

void module::orm_properties(const boost::optional<masd::dogen::coding::meta_model::orm_module_properties>& v) {
    orm_properties_ = v;
}

void module::orm_properties(const boost::optional<masd::dogen::coding::meta_model::orm_module_properties>&& v) {
    orm_properties_ = std::move(v);
}

}
