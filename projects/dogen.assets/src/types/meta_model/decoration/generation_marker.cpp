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
#include "dogen.assets/io/meta_model/element_io.hpp"
#include "dogen.assets/types/meta_model/element_visitor.hpp"
#include "dogen.assets/types/meta_model/decoration/generation_marker.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace dogen::assets::meta_model::decoration {

generation_marker::generation_marker()
    : add_date_time_(static_cast<bool>(0)),
      add_dogen_version_(static_cast<bool>(0)),
      add_model_to_text_transform_details_(static_cast<bool>(0)),
      add_warning_(static_cast<bool>(0)),
      add_origin_sha1_hash_(static_cast<bool>(0)) { }

generation_marker::generation_marker(
    const dogen::assets::meta_model::name& name,
    const std::string& documentation,
    const dogen::assets::meta_model::origin_types origin_type,
    const std::string& origin_sha1_hash,
    const std::string& origin_element_id,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<dogen::assets::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::assets::meta_model::name& meta_name,
    const dogen::assets::meta_model::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
    const bool is_element_extension,
    const std::unordered_map<std::string, dogen::assets::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::assets::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const boost::optional<dogen::assets::meta_model::decoration::element_properties>& decoration,
    const bool add_date_time,
    const bool add_dogen_version,
    const bool add_model_to_text_transform_details,
    const bool add_warning,
    const bool add_origin_sha1_hash,
    const std::string& message,
    const std::string& date_time)
    : dogen::assets::meta_model::element(
      name,
      documentation,
      origin_type,
      origin_sha1_hash,
      origin_element_id,
      contained_by,
      in_global_module,
      static_stereotypes,
      dynamic_stereotypes,
      meta_name,
      intrinsic_technical_space,
      configuration,
      is_element_extension,
      artefact_properties,
      archetype_location_properties,
      decoration),
      add_date_time_(add_date_time),
      add_dogen_version_(add_dogen_version),
      add_model_to_text_transform_details_(add_model_to_text_transform_details),
      add_warning_(add_warning),
      add_origin_sha1_hash_(add_origin_sha1_hash),
      message_(message),
      date_time_(date_time) { }

void generation_marker::accept(const element_visitor& v) const {
    v.visit(*this);
}

void generation_marker::accept(element_visitor& v) const {
    v.visit(*this);
    }

void generation_marker::accept(const element_visitor& v) {
    v.visit(*this);
}

void generation_marker::accept(element_visitor& v) {
    v.visit(*this);
}

void generation_marker::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::assets::meta_model::decoration::generation_marker\"" << ", "
      << "\"__parent_0__\": ";
    dogen::assets::meta_model::element::to_stream(s);
    s << ", "
      << "\"add_date_time\": " << add_date_time_ << ", "
      << "\"add_dogen_version\": " << add_dogen_version_ << ", "
      << "\"add_model_to_text_transform_details\": " << add_model_to_text_transform_details_ << ", "
      << "\"add_warning\": " << add_warning_ << ", "
      << "\"add_origin_sha1_hash\": " << add_origin_sha1_hash_ << ", "
      << "\"message\": " << "\"" << tidy_up_string(message_) << "\"" << ", "
      << "\"date_time\": " << "\"" << tidy_up_string(date_time_) << "\""
      << " }";
}

void generation_marker::swap(generation_marker& other) noexcept {
    dogen::assets::meta_model::element::swap(other);

    using std::swap;
    swap(add_date_time_, other.add_date_time_);
    swap(add_dogen_version_, other.add_dogen_version_);
    swap(add_model_to_text_transform_details_, other.add_model_to_text_transform_details_);
    swap(add_warning_, other.add_warning_);
    swap(add_origin_sha1_hash_, other.add_origin_sha1_hash_);
    swap(message_, other.message_);
    swap(date_time_, other.date_time_);
}

bool generation_marker::equals(const dogen::assets::meta_model::element& other) const {
    const generation_marker* const p(dynamic_cast<const generation_marker* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool generation_marker::operator==(const generation_marker& rhs) const {
    return dogen::assets::meta_model::element::compare(rhs) &&
        add_date_time_ == rhs.add_date_time_ &&
        add_dogen_version_ == rhs.add_dogen_version_ &&
        add_model_to_text_transform_details_ == rhs.add_model_to_text_transform_details_ &&
        add_warning_ == rhs.add_warning_ &&
        add_origin_sha1_hash_ == rhs.add_origin_sha1_hash_ &&
        message_ == rhs.message_ &&
        date_time_ == rhs.date_time_;
}

generation_marker& generation_marker::operator=(generation_marker other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool generation_marker::add_date_time() const {
    return add_date_time_;
}

void generation_marker::add_date_time(const bool v) {
    add_date_time_ = v;
}

bool generation_marker::add_dogen_version() const {
    return add_dogen_version_;
}

void generation_marker::add_dogen_version(const bool v) {
    add_dogen_version_ = v;
}

bool generation_marker::add_model_to_text_transform_details() const {
    return add_model_to_text_transform_details_;
}

void generation_marker::add_model_to_text_transform_details(const bool v) {
    add_model_to_text_transform_details_ = v;
}

bool generation_marker::add_warning() const {
    return add_warning_;
}

void generation_marker::add_warning(const bool v) {
    add_warning_ = v;
}

bool generation_marker::add_origin_sha1_hash() const {
    return add_origin_sha1_hash_;
}

void generation_marker::add_origin_sha1_hash(const bool v) {
    add_origin_sha1_hash_ = v;
}

const std::string& generation_marker::message() const {
    return message_;
}

std::string& generation_marker::message() {
    return message_;
}

void generation_marker::message(const std::string& v) {
    message_ = v;
}

void generation_marker::message(const std::string&& v) {
    message_ = std::move(v);
}

const std::string& generation_marker::date_time() const {
    return date_time_;
}

std::string& generation_marker::date_time() {
    return date_time_;
}

void generation_marker::date_time(const std::string& v) {
    date_time_ = v;
}

void generation_marker::date_time(const std::string&& v) {
    date_time_ = std::move(v);
}

}
