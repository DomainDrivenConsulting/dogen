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
#include "dogen/quilt.cpp/types/properties/element_properties.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

element_properties::element_properties(element_properties&& rhs)
    : file_properties_(std::move(rhs.file_properties_)),
      formatter_properties_(std::move(rhs.formatter_properties_)),
      helper_properties_(std::move(rhs.helper_properties_)) { }

element_properties::element_properties(
    const boost::optional<dogen::formatters::file_properties>& file_properties,
    const std::unordered_map<std::string, dogen::quilt::cpp::properties::formatter_properties>& formatter_properties,
    const std::list<dogen::quilt::cpp::properties::helper_properties>& helper_properties)
    : file_properties_(file_properties),
      formatter_properties_(formatter_properties),
      helper_properties_(helper_properties) { }

void element_properties::swap(element_properties& other) noexcept {
    using std::swap;
    swap(file_properties_, other.file_properties_);
    swap(formatter_properties_, other.formatter_properties_);
    swap(helper_properties_, other.helper_properties_);
}

bool element_properties::operator==(const element_properties& rhs) const {
    return file_properties_ == rhs.file_properties_ &&
        formatter_properties_ == rhs.formatter_properties_ &&
        helper_properties_ == rhs.helper_properties_;
}

element_properties& element_properties::operator=(element_properties other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::optional<dogen::formatters::file_properties>& element_properties::file_properties() const {
    return file_properties_;
}

boost::optional<dogen::formatters::file_properties>& element_properties::file_properties() {
    return file_properties_;
}

void element_properties::file_properties(const boost::optional<dogen::formatters::file_properties>& v) {
    file_properties_ = v;
}

void element_properties::file_properties(const boost::optional<dogen::formatters::file_properties>&& v) {
    file_properties_ = std::move(v);
}

const std::unordered_map<std::string, dogen::quilt::cpp::properties::formatter_properties>& element_properties::formatter_properties() const {
    return formatter_properties_;
}

std::unordered_map<std::string, dogen::quilt::cpp::properties::formatter_properties>& element_properties::formatter_properties() {
    return formatter_properties_;
}

void element_properties::formatter_properties(const std::unordered_map<std::string, dogen::quilt::cpp::properties::formatter_properties>& v) {
    formatter_properties_ = v;
}

void element_properties::formatter_properties(const std::unordered_map<std::string, dogen::quilt::cpp::properties::formatter_properties>&& v) {
    formatter_properties_ = std::move(v);
}

const std::list<dogen::quilt::cpp::properties::helper_properties>& element_properties::helper_properties() const {
    return helper_properties_;
}

std::list<dogen::quilt::cpp::properties::helper_properties>& element_properties::helper_properties() {
    return helper_properties_;
}

void element_properties::helper_properties(const std::list<dogen::quilt::cpp::properties::helper_properties>& v) {
    helper_properties_ = v;
}

void element_properties::helper_properties(const std::list<dogen::quilt::cpp::properties::helper_properties>&& v) {
    helper_properties_ = std::move(v);
}

} } } }
