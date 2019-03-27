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
#include <boost/algorithm/string.hpp>
#include "masd.dogen.coding/io/meta_model/element_io.hpp"
#include "masd.dogen.generation.cpp/types/fabric/cmakelists.hpp"
#include "masd.dogen.generation.cpp/io/fabric/odb_targets_io.hpp"
#include "masd.dogen.generation.cpp/types/fabric/element_visitor.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace masd::dogen::generation::cpp::fabric {

cmakelists::cmakelists(
    const masd::dogen::coding::meta_model::name& name,
    const std::string& documentation,
    const masd::dogen::annotations::annotation& annotation,
    const masd::dogen::coding::meta_model::origin_types origin_type,
    const boost::optional<masd::dogen::coding::meta_model::name>& contained_by,
    const bool in_global_module,
    const std::list<masd::dogen::coding::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const masd::dogen::coding::meta_model::name& meta_name,
    const bool is_element_extension,
    const masd::dogen::extraction::decoration_properties& decoration_properties,
    const std::unordered_map<std::string, masd::dogen::coding::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, masd::dogen::coding::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const boost::optional<masd::dogen::coding::meta_model::decoration>& decoration,
    const std::string& include_directory_path,
    const std::string& source_directory_name,
    const std::string& header_file_extension,
    const std::string& implementation_file_extension,
    const masd::dogen::generation::cpp::fabric::odb_targets& odb_targets,
    const std::string& tests_directory_name)
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
      is_element_extension,
      decoration_properties,
      artefact_properties,
      archetype_location_properties,
      decoration),
      include_directory_path_(include_directory_path),
      source_directory_name_(source_directory_name),
      header_file_extension_(header_file_extension),
      implementation_file_extension_(implementation_file_extension),
      odb_targets_(odb_targets),
      tests_directory_name_(tests_directory_name) { }

void cmakelists::accept(const masd::dogen::coding::meta_model::element_visitor& v) const {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void cmakelists::accept(masd::dogen::coding::meta_model::element_visitor& v) const {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
    }

void cmakelists::accept(const masd::dogen::coding::meta_model::element_visitor& v) {
    typedef const element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void cmakelists::accept(masd::dogen::coding::meta_model::element_visitor& v) {
    typedef element_visitor* derived_ptr;
    const auto dv(dynamic_cast<derived_ptr>(&v));
    if (dv)
        dv->visit(*this);
}

void cmakelists::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"masd::dogen::generation::cpp::fabric::cmakelists\"" << ", "
      << "\"__parent_0__\": ";
    masd::dogen::coding::meta_model::element::to_stream(s);
    s << ", "
      << "\"include_directory_path\": " << "\"" << tidy_up_string(include_directory_path_) << "\"" << ", "
      << "\"source_directory_name\": " << "\"" << tidy_up_string(source_directory_name_) << "\"" << ", "
      << "\"header_file_extension\": " << "\"" << tidy_up_string(header_file_extension_) << "\"" << ", "
      << "\"implementation_file_extension\": " << "\"" << tidy_up_string(implementation_file_extension_) << "\"" << ", "
      << "\"odb_targets\": " << odb_targets_ << ", "
      << "\"tests_directory_name\": " << "\"" << tidy_up_string(tests_directory_name_) << "\""
      << " }";
}

void cmakelists::swap(cmakelists& other) noexcept {
    masd::dogen::coding::meta_model::element::swap(other);

    using std::swap;
    swap(include_directory_path_, other.include_directory_path_);
    swap(source_directory_name_, other.source_directory_name_);
    swap(header_file_extension_, other.header_file_extension_);
    swap(implementation_file_extension_, other.implementation_file_extension_);
    swap(odb_targets_, other.odb_targets_);
    swap(tests_directory_name_, other.tests_directory_name_);
}

bool cmakelists::equals(const masd::dogen::coding::meta_model::element& other) const {
    const cmakelists* const p(dynamic_cast<const cmakelists* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool cmakelists::operator==(const cmakelists& rhs) const {
    return masd::dogen::coding::meta_model::element::compare(rhs) &&
        include_directory_path_ == rhs.include_directory_path_ &&
        source_directory_name_ == rhs.source_directory_name_ &&
        header_file_extension_ == rhs.header_file_extension_ &&
        implementation_file_extension_ == rhs.implementation_file_extension_ &&
        odb_targets_ == rhs.odb_targets_ &&
        tests_directory_name_ == rhs.tests_directory_name_;
}

cmakelists& cmakelists::operator=(cmakelists other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& cmakelists::include_directory_path() const {
    return include_directory_path_;
}

std::string& cmakelists::include_directory_path() {
    return include_directory_path_;
}

void cmakelists::include_directory_path(const std::string& v) {
    include_directory_path_ = v;
}

void cmakelists::include_directory_path(const std::string&& v) {
    include_directory_path_ = std::move(v);
}

const std::string& cmakelists::source_directory_name() const {
    return source_directory_name_;
}

std::string& cmakelists::source_directory_name() {
    return source_directory_name_;
}

void cmakelists::source_directory_name(const std::string& v) {
    source_directory_name_ = v;
}

void cmakelists::source_directory_name(const std::string&& v) {
    source_directory_name_ = std::move(v);
}

const std::string& cmakelists::header_file_extension() const {
    return header_file_extension_;
}

std::string& cmakelists::header_file_extension() {
    return header_file_extension_;
}

void cmakelists::header_file_extension(const std::string& v) {
    header_file_extension_ = v;
}

void cmakelists::header_file_extension(const std::string&& v) {
    header_file_extension_ = std::move(v);
}

const std::string& cmakelists::implementation_file_extension() const {
    return implementation_file_extension_;
}

std::string& cmakelists::implementation_file_extension() {
    return implementation_file_extension_;
}

void cmakelists::implementation_file_extension(const std::string& v) {
    implementation_file_extension_ = v;
}

void cmakelists::implementation_file_extension(const std::string&& v) {
    implementation_file_extension_ = std::move(v);
}

const masd::dogen::generation::cpp::fabric::odb_targets& cmakelists::odb_targets() const {
    return odb_targets_;
}

masd::dogen::generation::cpp::fabric::odb_targets& cmakelists::odb_targets() {
    return odb_targets_;
}

void cmakelists::odb_targets(const masd::dogen::generation::cpp::fabric::odb_targets& v) {
    odb_targets_ = v;
}

void cmakelists::odb_targets(const masd::dogen::generation::cpp::fabric::odb_targets&& v) {
    odb_targets_ = std::move(v);
}

const std::string& cmakelists::tests_directory_name() const {
    return tests_directory_name_;
}

std::string& cmakelists::tests_directory_name() {
    return tests_directory_name_;
}

void cmakelists::tests_directory_name(const std::string& v) {
    tests_directory_name_ = v;
}

void cmakelists::tests_directory_name(const std::string&& v) {
    tests_directory_name_ = std::move(v);
}

}
