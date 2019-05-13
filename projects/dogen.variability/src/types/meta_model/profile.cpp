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
#include "dogen.variability/io/meta_model/element_io.hpp"
#include "dogen.variability/types/meta_model/profile.hpp"
#include "dogen.variability/io/meta_model/configuration_point_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<std::string, dogen::variability::meta_model::configuration_point>& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << "\"" << tidy_up_string(i->first) << "\"";
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

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

namespace dogen::variability::meta_model {

profile::profile()
    : merged_(static_cast<bool>(0)) { }

profile::profile(
    const dogen::variability::meta_model::name& name,
    const std::string& description,
    const std::unordered_map<std::string, dogen::variability::meta_model::configuration_point>& configuration_points,
    const std::list<std::string>& parents,
    const std::unordered_set<std::string>& labels,
    const bool merged,
    const std::string& base_layer_profile)
    : dogen::variability::meta_model::element(
      name,
      description),
      configuration_points_(configuration_points),
      parents_(parents),
      labels_(labels),
      merged_(merged),
      base_layer_profile_(base_layer_profile) { }

void profile::to_stream(std::ostream& s) const {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::variability::meta_model::profile\"" << ", "
      << "\"__parent_0__\": ";
    dogen::variability::meta_model::element::to_stream(s);
    s << ", "
      << "\"configuration_points\": " << configuration_points_ << ", "
      << "\"parents\": " << parents_ << ", "
      << "\"labels\": " << labels_ << ", "
      << "\"merged\": " << merged_ << ", "
      << "\"base_layer_profile\": " << "\"" << tidy_up_string(base_layer_profile_) << "\""
      << " }";
}

void profile::swap(profile& other) noexcept {
    dogen::variability::meta_model::element::swap(other);

    using std::swap;
    swap(configuration_points_, other.configuration_points_);
    swap(parents_, other.parents_);
    swap(labels_, other.labels_);
    swap(merged_, other.merged_);
    swap(base_layer_profile_, other.base_layer_profile_);
}

bool profile::equals(const dogen::variability::meta_model::element& other) const {
    const profile* const p(dynamic_cast<const profile* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool profile::operator==(const profile& rhs) const {
    return dogen::variability::meta_model::element::compare(rhs) &&
        configuration_points_ == rhs.configuration_points_ &&
        parents_ == rhs.parents_ &&
        labels_ == rhs.labels_ &&
        merged_ == rhs.merged_ &&
        base_layer_profile_ == rhs.base_layer_profile_;
}

profile& profile::operator=(profile other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, dogen::variability::meta_model::configuration_point>& profile::configuration_points() const {
    return configuration_points_;
}

std::unordered_map<std::string, dogen::variability::meta_model::configuration_point>& profile::configuration_points() {
    return configuration_points_;
}

void profile::configuration_points(const std::unordered_map<std::string, dogen::variability::meta_model::configuration_point>& v) {
    configuration_points_ = v;
}

void profile::configuration_points(const std::unordered_map<std::string, dogen::variability::meta_model::configuration_point>&& v) {
    configuration_points_ = std::move(v);
}

const std::list<std::string>& profile::parents() const {
    return parents_;
}

std::list<std::string>& profile::parents() {
    return parents_;
}

void profile::parents(const std::list<std::string>& v) {
    parents_ = v;
}

void profile::parents(const std::list<std::string>&& v) {
    parents_ = std::move(v);
}

const std::unordered_set<std::string>& profile::labels() const {
    return labels_;
}

std::unordered_set<std::string>& profile::labels() {
    return labels_;
}

void profile::labels(const std::unordered_set<std::string>& v) {
    labels_ = v;
}

void profile::labels(const std::unordered_set<std::string>&& v) {
    labels_ = std::move(v);
}

bool profile::merged() const {
    return merged_;
}

void profile::merged(const bool v) {
    merged_ = v;
}

const std::string& profile::base_layer_profile() const {
    return base_layer_profile_;
}

std::string& profile::base_layer_profile() {
    return base_layer_profile_;
}

void profile::base_layer_profile(const std::string& v) {
    base_layer_profile_ = v;
}

void profile::base_layer_profile(const std::string&& v) {
    base_layer_profile_ = std::move(v);
}

}
