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
#include "dogen.archetypes/io/location_io.hpp"
#include "dogen.variability/io/meta_model/value_io.hpp"
#include "dogen.variability/types/meta_model/value.hpp"
#include "dogen.variability/io/meta_model/element_io.hpp"
#include "dogen.variability/types/meta_model/feature.hpp"
#include "dogen.variability/io/meta_model/value_type_io.hpp"
#include "dogen.variability/io/meta_model/binding_point_io.hpp"
#include "dogen.variability/io/meta_model/binding_action_io.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::meta_model::value>& lhs,
const boost::shared_ptr<dogen::variability::meta_model::value>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline std::ostream& operator<<(std::ostream& s, const boost::shared_ptr<dogen::variability::meta_model::value>& v) {
    s << "{ " << "\"__type__\": " << "\"boost::shared_ptr\"" << ", "
      << "\"memory\": " << "\"" << static_cast<void*>(v.get()) << "\"" << ", ";

    if (v)
        s << "\"data\": " << *v;
    else
        s << "\"data\": ""\"<null>\"";
    s << " }";
    return s;
}

}

namespace dogen::variability::meta_model {

feature::feature()
    : value_type_(static_cast<dogen::variability::meta_model::value_type>(0)),
      binding_point_(static_cast<dogen::variability::meta_model::binding_point>(0)),
      profile_binding_action_(static_cast<dogen::variability::meta_model::binding_action>(0)),
      configuration_binding_action_(static_cast<dogen::variability::meta_model::binding_action>(0)),
      is_partially_matchable_(static_cast<bool>(0)) { }

feature::feature(
    const dogen::variability::meta_model::name& name,
    const std::string& description,
    const dogen::archetypes::location& location,
    const boost::shared_ptr<dogen::variability::meta_model::value>& default_value,
    const dogen::variability::meta_model::value_type value_type,
    const dogen::variability::meta_model::binding_point binding_point,
    const dogen::variability::meta_model::binding_action profile_binding_action,
    const dogen::variability::meta_model::binding_action configuration_binding_action,
    const bool is_partially_matchable)
    : dogen::variability::meta_model::element(
      name,
      description),
      location_(location),
      default_value_(default_value),
      value_type_(value_type),
      binding_point_(binding_point),
      profile_binding_action_(profile_binding_action),
      configuration_binding_action_(configuration_binding_action),
      is_partially_matchable_(is_partially_matchable) { }

void feature::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::variability::meta_model::feature\"" << ", "
      << "\"__parent_0__\": ";
    dogen::variability::meta_model::element::to_stream(s);
    s << ", "
      << "\"location\": " << location_ << ", "
      << "\"default_value\": " << default_value_ << ", "
      << "\"value_type\": " << value_type_ << ", "
      << "\"binding_point\": " << binding_point_ << ", "
      << "\"profile_binding_action\": " << profile_binding_action_ << ", "
      << "\"configuration_binding_action\": " << configuration_binding_action_ << ", "
      << "\"is_partially_matchable\": " << is_partially_matchable_
      << " }";
}

void feature::swap(feature& other) noexcept {
    dogen::variability::meta_model::element::swap(other);

    using std::swap;
    swap(location_, other.location_);
    swap(default_value_, other.default_value_);
    swap(value_type_, other.value_type_);
    swap(binding_point_, other.binding_point_);
    swap(profile_binding_action_, other.profile_binding_action_);
    swap(configuration_binding_action_, other.configuration_binding_action_);
    swap(is_partially_matchable_, other.is_partially_matchable_);
}

bool feature::equals(const dogen::variability::meta_model::element& other) const {
    const feature* const p(dynamic_cast<const feature* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool feature::operator==(const feature& rhs) const {
    return dogen::variability::meta_model::element::compare(rhs) &&
        location_ == rhs.location_ &&
        default_value_ == rhs.default_value_ &&
        value_type_ == rhs.value_type_ &&
        binding_point_ == rhs.binding_point_ &&
        profile_binding_action_ == rhs.profile_binding_action_ &&
        configuration_binding_action_ == rhs.configuration_binding_action_ &&
        is_partially_matchable_ == rhs.is_partially_matchable_;
}

feature& feature::operator=(feature other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::archetypes::location& feature::location() const {
    return location_;
}

dogen::archetypes::location& feature::location() {
    return location_;
}

void feature::location(const dogen::archetypes::location& v) {
    location_ = v;
}

void feature::location(const dogen::archetypes::location&& v) {
    location_ = std::move(v);
}

const boost::shared_ptr<dogen::variability::meta_model::value>& feature::default_value() const {
    return default_value_;
}

boost::shared_ptr<dogen::variability::meta_model::value>& feature::default_value() {
    return default_value_;
}

void feature::default_value(const boost::shared_ptr<dogen::variability::meta_model::value>& v) {
    default_value_ = v;
}

void feature::default_value(const boost::shared_ptr<dogen::variability::meta_model::value>&& v) {
    default_value_ = std::move(v);
}

dogen::variability::meta_model::value_type feature::value_type() const {
    return value_type_;
}

void feature::value_type(const dogen::variability::meta_model::value_type v) {
    value_type_ = v;
}

dogen::variability::meta_model::binding_point feature::binding_point() const {
    return binding_point_;
}

void feature::binding_point(const dogen::variability::meta_model::binding_point v) {
    binding_point_ = v;
}

dogen::variability::meta_model::binding_action feature::profile_binding_action() const {
    return profile_binding_action_;
}

void feature::profile_binding_action(const dogen::variability::meta_model::binding_action v) {
    profile_binding_action_ = v;
}

dogen::variability::meta_model::binding_action feature::configuration_binding_action() const {
    return configuration_binding_action_;
}

void feature::configuration_binding_action(const dogen::variability::meta_model::binding_action v) {
    configuration_binding_action_ = v;
}

bool feature::is_partially_matchable() const {
    return is_partially_matchable_;
}

void feature::is_partially_matchable(const bool v) {
    is_partially_matchable_ = v;
}

}
