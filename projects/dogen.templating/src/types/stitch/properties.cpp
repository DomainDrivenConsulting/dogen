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
#include "dogen.templating/types/stitch/properties.hpp"

namespace dogen::templating::stitch {

properties::properties(
    const std::string& stream_variable_name,
    const std::list<std::string>& inclusion_dependencies,
    const std::list<std::string>& containing_namespaces,
    const std::string& wale_template,
    const std::unordered_map<std::string, std::string>& wale_kvps)
    : stream_variable_name_(stream_variable_name),
      inclusion_dependencies_(inclusion_dependencies),
      containing_namespaces_(containing_namespaces),
      wale_template_(wale_template),
      wale_kvps_(wale_kvps) { }

void properties::swap(properties& other) noexcept {
    using std::swap;
    swap(stream_variable_name_, other.stream_variable_name_);
    swap(inclusion_dependencies_, other.inclusion_dependencies_);
    swap(containing_namespaces_, other.containing_namespaces_);
    swap(wale_template_, other.wale_template_);
    swap(wale_kvps_, other.wale_kvps_);
}

bool properties::operator==(const properties& rhs) const {
    return stream_variable_name_ == rhs.stream_variable_name_ &&
        inclusion_dependencies_ == rhs.inclusion_dependencies_ &&
        containing_namespaces_ == rhs.containing_namespaces_ &&
        wale_template_ == rhs.wale_template_ &&
        wale_kvps_ == rhs.wale_kvps_;
}

properties& properties::operator=(properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& properties::stream_variable_name() const {
    return stream_variable_name_;
}

std::string& properties::stream_variable_name() {
    return stream_variable_name_;
}

void properties::stream_variable_name(const std::string& v) {
    stream_variable_name_ = v;
}

void properties::stream_variable_name(const std::string&& v) {
    stream_variable_name_ = std::move(v);
}

const std::list<std::string>& properties::inclusion_dependencies() const {
    return inclusion_dependencies_;
}

std::list<std::string>& properties::inclusion_dependencies() {
    return inclusion_dependencies_;
}

void properties::inclusion_dependencies(const std::list<std::string>& v) {
    inclusion_dependencies_ = v;
}

void properties::inclusion_dependencies(const std::list<std::string>&& v) {
    inclusion_dependencies_ = std::move(v);
}

const std::list<std::string>& properties::containing_namespaces() const {
    return containing_namespaces_;
}

std::list<std::string>& properties::containing_namespaces() {
    return containing_namespaces_;
}

void properties::containing_namespaces(const std::list<std::string>& v) {
    containing_namespaces_ = v;
}

void properties::containing_namespaces(const std::list<std::string>&& v) {
    containing_namespaces_ = std::move(v);
}

const std::string& properties::wale_template() const {
    return wale_template_;
}

std::string& properties::wale_template() {
    return wale_template_;
}

void properties::wale_template(const std::string& v) {
    wale_template_ = v;
}

void properties::wale_template(const std::string&& v) {
    wale_template_ = std::move(v);
}

const std::unordered_map<std::string, std::string>& properties::wale_kvps() const {
    return wale_kvps_;
}

std::unordered_map<std::string, std::string>& properties::wale_kvps() {
    return wale_kvps_;
}

void properties::wale_kvps(const std::unordered_map<std::string, std::string>& v) {
    wale_kvps_ = v;
}

void properties::wale_kvps(const std::unordered_map<std::string, std::string>&& v) {
    wale_kvps_ = std::move(v);
}

}
