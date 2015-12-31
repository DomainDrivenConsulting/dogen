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
#include "dogen/yarn/types/location.hpp"

namespace dogen {
namespace yarn {

location::location(
    const std::list<std::string>& external_modules,
    const std::list<std::string>& model_modules,
    const std::list<std::string>& internal_modules,
    const std::string& element)
    : external_modules_(external_modules),
      model_modules_(model_modules),
      internal_modules_(internal_modules),
      element_(element) { }

void location::swap(location& other) noexcept {
    using std::swap;
    swap(external_modules_, other.external_modules_);
    swap(model_modules_, other.model_modules_);
    swap(internal_modules_, other.internal_modules_);
    swap(element_, other.element_);
}

bool location::operator==(const location& rhs) const {
    return external_modules_ == rhs.external_modules_ &&
        model_modules_ == rhs.model_modules_ &&
        internal_modules_ == rhs.internal_modules_ &&
        element_ == rhs.element_;
}

location& location::operator=(location other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<std::string>& location::external_modules() const {
    return external_modules_;
}

std::list<std::string>& location::external_modules() {
    return external_modules_;
}

void location::external_modules(const std::list<std::string>& v) {
    external_modules_ = v;
}

void location::external_modules(const std::list<std::string>&& v) {
    external_modules_ = std::move(v);
}

const std::list<std::string>& location::model_modules() const {
    return model_modules_;
}

std::list<std::string>& location::model_modules() {
    return model_modules_;
}

void location::model_modules(const std::list<std::string>& v) {
    model_modules_ = v;
}

void location::model_modules(const std::list<std::string>&& v) {
    model_modules_ = std::move(v);
}

const std::list<std::string>& location::internal_modules() const {
    return internal_modules_;
}

std::list<std::string>& location::internal_modules() {
    return internal_modules_;
}

void location::internal_modules(const std::list<std::string>& v) {
    internal_modules_ = v;
}

void location::internal_modules(const std::list<std::string>&& v) {
    internal_modules_ = std::move(v);
}

const std::string& location::element() const {
    return element_;
}

std::string& location::element() {
    return element_;
}

void location::element(const std::string& v) {
    element_ = v;
}

void location::element(const std::string&& v) {
    element_ = std::move(v);
}

} }
