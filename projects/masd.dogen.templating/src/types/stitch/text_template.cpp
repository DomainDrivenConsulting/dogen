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
#include "masd.dogen.templating/types/stitch/text_template.hpp"

namespace masd::dogen::templating::stitch {

text_template::text_template(text_template&& rhs)
    : expected_keys_(std::move(rhs.expected_keys_)),
      supplied_kvps_(std::move(rhs.supplied_kvps_)),
      input_path_(std::move(rhs.input_path_)),
      output_path_(std::move(rhs.output_path_)),
      properties_(std::move(rhs.properties_)),
      variables_(std::move(rhs.variables_)),
      body_(std::move(rhs.body_)) { }

text_template::text_template(
    const std::unordered_set<std::string>& expected_keys,
    const std::unordered_map<std::string, std::string>& supplied_kvps,
    const boost::filesystem::path& input_path,
    const boost::filesystem::path& output_path,
    const masd::dogen::templating::stitch::properties& properties,
    const std::unordered_map<std::string, std::string>& variables,
    const masd::dogen::templating::stitch::text_template_body& body)
    : expected_keys_(expected_keys),
      supplied_kvps_(supplied_kvps),
      input_path_(input_path),
      output_path_(output_path),
      properties_(properties),
      variables_(variables),
      body_(body) { }

void text_template::swap(text_template& other) noexcept {
    using std::swap;
    swap(expected_keys_, other.expected_keys_);
    swap(supplied_kvps_, other.supplied_kvps_);
    swap(input_path_, other.input_path_);
    swap(output_path_, other.output_path_);
    swap(properties_, other.properties_);
    swap(variables_, other.variables_);
    swap(body_, other.body_);
}

bool text_template::operator==(const text_template& rhs) const {
    return expected_keys_ == rhs.expected_keys_ &&
        supplied_kvps_ == rhs.supplied_kvps_ &&
        input_path_ == rhs.input_path_ &&
        output_path_ == rhs.output_path_ &&
        properties_ == rhs.properties_ &&
        variables_ == rhs.variables_ &&
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

const boost::filesystem::path& text_template::input_path() const {
    return input_path_;
}

boost::filesystem::path& text_template::input_path() {
    return input_path_;
}

void text_template::input_path(const boost::filesystem::path& v) {
    input_path_ = v;
}

void text_template::input_path(const boost::filesystem::path&& v) {
    input_path_ = std::move(v);
}

const boost::filesystem::path& text_template::output_path() const {
    return output_path_;
}

boost::filesystem::path& text_template::output_path() {
    return output_path_;
}

void text_template::output_path(const boost::filesystem::path& v) {
    output_path_ = v;
}

void text_template::output_path(const boost::filesystem::path&& v) {
    output_path_ = std::move(v);
}

const masd::dogen::templating::stitch::properties& text_template::properties() const {
    return properties_;
}

masd::dogen::templating::stitch::properties& text_template::properties() {
    return properties_;
}

void text_template::properties(const masd::dogen::templating::stitch::properties& v) {
    properties_ = v;
}

void text_template::properties(const masd::dogen::templating::stitch::properties&& v) {
    properties_ = std::move(v);
}

const std::unordered_map<std::string, std::string>& text_template::variables() const {
    return variables_;
}

std::unordered_map<std::string, std::string>& text_template::variables() {
    return variables_;
}

void text_template::variables(const std::unordered_map<std::string, std::string>& v) {
    variables_ = v;
}

void text_template::variables(const std::unordered_map<std::string, std::string>&& v) {
    variables_ = std::move(v);
}

const masd::dogen::templating::stitch::text_template_body& text_template::body() const {
    return body_;
}

masd::dogen::templating::stitch::text_template_body& text_template::body() {
    return body_;
}

void text_template::body(const masd::dogen::templating::stitch::text_template_body& v) {
    body_ = v;
}

void text_template::body(const masd::dogen::templating::stitch::text_template_body&& v) {
    body_ = std::move(v);
}

}
