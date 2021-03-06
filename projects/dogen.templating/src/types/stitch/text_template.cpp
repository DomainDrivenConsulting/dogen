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
#include "dogen.templating/types/stitch/text_template.hpp"

namespace dogen::templating::stitch {

text_template::text_template(
    const std::unordered_set<std::string>& expected_keys,
    const std::unordered_map<std::string, std::string>& supplied_kvps,
    const dogen::templating::stitch::properties& properties,
    const dogen::templating::stitch::text_template_body& body)
    : expected_keys_(expected_keys),
      supplied_kvps_(supplied_kvps),
      properties_(properties),
      body_(body) { }

void text_template::swap(text_template& other) noexcept {
    using std::swap;
    swap(expected_keys_, other.expected_keys_);
    swap(supplied_kvps_, other.supplied_kvps_);
    swap(properties_, other.properties_);
    swap(body_, other.body_);
}

bool text_template::operator==(const text_template& rhs) const {
    return expected_keys_ == rhs.expected_keys_ &&
        supplied_kvps_ == rhs.supplied_kvps_ &&
        properties_ == rhs.properties_ &&
        body_ == rhs.body_;
}

text_template& text_template::operator=(text_template other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_set<std::string>& text_template::expected_keys() const {
    return expected_keys_;
}

std::unordered_set<std::string>& text_template::expected_keys() {
    return expected_keys_;
}

void text_template::expected_keys(const std::unordered_set<std::string>& v) {
    expected_keys_ = v;
}

void text_template::expected_keys(const std::unordered_set<std::string>&& v) {
    expected_keys_ = std::move(v);
}

const std::unordered_map<std::string, std::string>& text_template::supplied_kvps() const {
    return supplied_kvps_;
}

std::unordered_map<std::string, std::string>& text_template::supplied_kvps() {
    return supplied_kvps_;
}

void text_template::supplied_kvps(const std::unordered_map<std::string, std::string>& v) {
    supplied_kvps_ = v;
}

void text_template::supplied_kvps(const std::unordered_map<std::string, std::string>&& v) {
    supplied_kvps_ = std::move(v);
}

const dogen::templating::stitch::properties& text_template::properties() const {
    return properties_;
}

dogen::templating::stitch::properties& text_template::properties() {
    return properties_;
}

void text_template::properties(const dogen::templating::stitch::properties& v) {
    properties_ = v;
}

void text_template::properties(const dogen::templating::stitch::properties&& v) {
    properties_ = std::move(v);
}

const dogen::templating::stitch::text_template_body& text_template::body() const {
    return body_;
}

dogen::templating::stitch::text_template_body& text_template::body() {
    return body_;
}

void text_template::body(const dogen::templating::stitch::text_template_body& v) {
    body_ = v;
}

void text_template::body(const dogen::templating::stitch::text_template_body&& v) {
    body_ = std::move(v);
}

}
