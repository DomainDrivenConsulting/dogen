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
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.variability/types/entities/configuration.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::entities::configuration>& lhs,
const boost::shared_ptr<dogen::variability::entities::configuration>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::physical::entities {

artefact::artefact()
    : formatting_style_(static_cast<dogen::physical::entities::formatting_styles>(0)) { }

artefact::artefact(artefact&& rhs)
    : meta_name_(std::move(rhs.meta_name_)),
      configuration_(std::move(rhs.configuration_)),
      provenance_(std::move(rhs.provenance_)),
      name_(std::move(rhs.name_)),
      file_path_(std::move(rhs.file_path_)),
      content_(std::move(rhs.content_)),
      path_properties_(std::move(rhs.path_properties_)),
      dependencies_(std::move(rhs.dependencies_)),
      unified_diff_(std::move(rhs.unified_diff_)),
      operation_(std::move(rhs.operation_)),
      enablement_properties_(std::move(rhs.enablement_properties_)),
      formatting_style_(std::move(rhs.formatting_style_)),
      formatting_input_(std::move(rhs.formatting_input_)) { }

artefact::artefact(
    const dogen::identification::entities::physical_meta_name& meta_name,
    const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
    const dogen::identification::entities::logical_provenance& provenance,
    const dogen::identification::entities::physical_name& name,
    const boost::filesystem::path& file_path,
    const std::string& content,
    const dogen::physical::entities::path_properties& path_properties,
    const std::vector<boost::filesystem::path>& dependencies,
    const std::string& unified_diff,
    const dogen::physical::entities::operation& operation,
    const dogen::physical::entities::enablement_properties& enablement_properties,
    const dogen::physical::entities::formatting_styles formatting_style,
    const std::string& formatting_input)
    : meta_name_(meta_name),
      configuration_(configuration),
      provenance_(provenance),
      name_(name),
      file_path_(file_path),
      content_(content),
      path_properties_(path_properties),
      dependencies_(dependencies),
      unified_diff_(unified_diff),
      operation_(operation),
      enablement_properties_(enablement_properties),
      formatting_style_(formatting_style),
      formatting_input_(formatting_input) { }

void artefact::swap(artefact& other) noexcept {
    using std::swap;
    swap(meta_name_, other.meta_name_);
    swap(configuration_, other.configuration_);
    swap(provenance_, other.provenance_);
    swap(name_, other.name_);
    swap(file_path_, other.file_path_);
    swap(content_, other.content_);
    swap(path_properties_, other.path_properties_);
    swap(dependencies_, other.dependencies_);
    swap(unified_diff_, other.unified_diff_);
    swap(operation_, other.operation_);
    swap(enablement_properties_, other.enablement_properties_);
    swap(formatting_style_, other.formatting_style_);
    swap(formatting_input_, other.formatting_input_);
}

bool artefact::operator==(const artefact& rhs) const {
    return meta_name_ == rhs.meta_name_ &&
        configuration_ == rhs.configuration_ &&
        provenance_ == rhs.provenance_ &&
        name_ == rhs.name_ &&
        file_path_ == rhs.file_path_ &&
        content_ == rhs.content_ &&
        path_properties_ == rhs.path_properties_ &&
        dependencies_ == rhs.dependencies_ &&
        unified_diff_ == rhs.unified_diff_ &&
        operation_ == rhs.operation_ &&
        enablement_properties_ == rhs.enablement_properties_ &&
        formatting_style_ == rhs.formatting_style_ &&
        formatting_input_ == rhs.formatting_input_;
}

artefact& artefact::operator=(artefact other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::identification::entities::physical_meta_name& artefact::meta_name() const {
    return meta_name_;
}

dogen::identification::entities::physical_meta_name& artefact::meta_name() {
    return meta_name_;
}

void artefact::meta_name(const dogen::identification::entities::physical_meta_name& v) {
    meta_name_ = v;
}

void artefact::meta_name(const dogen::identification::entities::physical_meta_name&& v) {
    meta_name_ = std::move(v);
}

const boost::shared_ptr<dogen::variability::entities::configuration>& artefact::configuration() const {
    return configuration_;
}

boost::shared_ptr<dogen::variability::entities::configuration>& artefact::configuration() {
    return configuration_;
}

void artefact::configuration(const boost::shared_ptr<dogen::variability::entities::configuration>& v) {
    configuration_ = v;
}

void artefact::configuration(const boost::shared_ptr<dogen::variability::entities::configuration>&& v) {
    configuration_ = std::move(v);
}

const dogen::identification::entities::logical_provenance& artefact::provenance() const {
    return provenance_;
}

dogen::identification::entities::logical_provenance& artefact::provenance() {
    return provenance_;
}

void artefact::provenance(const dogen::identification::entities::logical_provenance& v) {
    provenance_ = v;
}

void artefact::provenance(const dogen::identification::entities::logical_provenance&& v) {
    provenance_ = std::move(v);
}

const dogen::identification::entities::physical_name& artefact::name() const {
    return name_;
}

dogen::identification::entities::physical_name& artefact::name() {
    return name_;
}

void artefact::name(const dogen::identification::entities::physical_name& v) {
    name_ = v;
}

void artefact::name(const dogen::identification::entities::physical_name&& v) {
    name_ = std::move(v);
}

const boost::filesystem::path& artefact::file_path() const {
    return file_path_;
}

boost::filesystem::path& artefact::file_path() {
    return file_path_;
}

void artefact::file_path(const boost::filesystem::path& v) {
    file_path_ = v;
}

void artefact::file_path(const boost::filesystem::path&& v) {
    file_path_ = std::move(v);
}

const std::string& artefact::content() const {
    return content_;
}

std::string& artefact::content() {
    return content_;
}

void artefact::content(const std::string& v) {
    content_ = v;
}

void artefact::content(const std::string&& v) {
    content_ = std::move(v);
}

const dogen::physical::entities::path_properties& artefact::path_properties() const {
    return path_properties_;
}

dogen::physical::entities::path_properties& artefact::path_properties() {
    return path_properties_;
}

void artefact::path_properties(const dogen::physical::entities::path_properties& v) {
    path_properties_ = v;
}

void artefact::path_properties(const dogen::physical::entities::path_properties&& v) {
    path_properties_ = std::move(v);
}

const std::vector<boost::filesystem::path>& artefact::dependencies() const {
    return dependencies_;
}

std::vector<boost::filesystem::path>& artefact::dependencies() {
    return dependencies_;
}

void artefact::dependencies(const std::vector<boost::filesystem::path>& v) {
    dependencies_ = v;
}

void artefact::dependencies(const std::vector<boost::filesystem::path>&& v) {
    dependencies_ = std::move(v);
}

const std::string& artefact::unified_diff() const {
    return unified_diff_;
}

std::string& artefact::unified_diff() {
    return unified_diff_;
}

void artefact::unified_diff(const std::string& v) {
    unified_diff_ = v;
}

void artefact::unified_diff(const std::string&& v) {
    unified_diff_ = std::move(v);
}

const dogen::physical::entities::operation& artefact::operation() const {
    return operation_;
}

dogen::physical::entities::operation& artefact::operation() {
    return operation_;
}

void artefact::operation(const dogen::physical::entities::operation& v) {
    operation_ = v;
}

void artefact::operation(const dogen::physical::entities::operation&& v) {
    operation_ = std::move(v);
}

const dogen::physical::entities::enablement_properties& artefact::enablement_properties() const {
    return enablement_properties_;
}

dogen::physical::entities::enablement_properties& artefact::enablement_properties() {
    return enablement_properties_;
}

void artefact::enablement_properties(const dogen::physical::entities::enablement_properties& v) {
    enablement_properties_ = v;
}

void artefact::enablement_properties(const dogen::physical::entities::enablement_properties&& v) {
    enablement_properties_ = std::move(v);
}

dogen::physical::entities::formatting_styles artefact::formatting_style() const {
    return formatting_style_;
}

void artefact::formatting_style(const dogen::physical::entities::formatting_styles v) {
    formatting_style_ = v;
}

const std::string& artefact::formatting_input() const {
    return formatting_input_;
}

std::string& artefact::formatting_input() {
    return formatting_input_;
}

void artefact::formatting_input(const std::string& v) {
    formatting_input_ = v;
}

void artefact::formatting_input(const std::string&& v) {
    formatting_input_ = std::move(v);
}

}
