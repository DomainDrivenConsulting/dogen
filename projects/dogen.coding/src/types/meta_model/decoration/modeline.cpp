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
#include "dogen.coding/io/meta_model/element_io.hpp"
#include "dogen.coding/io/meta_model/technical_space_io.hpp"
#include "dogen.coding/types/meta_model/element_visitor.hpp"
#include "dogen.coding/io/meta_model/decoration/editor_io.hpp"
#include "dogen.coding/types/meta_model/decoration/modeline.hpp"
#include "dogen.coding/io/meta_model/decoration/modeline_field_io.hpp"
#include "dogen.coding/io/meta_model/decoration/modeline_location_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::coding::meta_model::decoration::modeline_field>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::coding::meta_model::decoration {

modeline::modeline()
    : editor_(static_cast<dogen::coding::meta_model::decoration::editor>(0)),
      location_(static_cast<dogen::coding::meta_model::decoration::modeline_location>(0)),
      technical_space_(static_cast<dogen::coding::meta_model::technical_space>(0)) { }

modeline::modeline(
    const dogen::coding::meta_model::name& name,
    const std::string& documentation,
    const dogen::coding::meta_model::origin_types origin_type,
    const std::string& contained_by,
    const bool in_global_module,
    const std::list<dogen::coding::meta_model::static_stereotypes>& static_stereotypes,
    const std::list<std::string>& dynamic_stereotypes,
    const dogen::coding::meta_model::name& meta_name,
    const dogen::coding::meta_model::technical_space intrinsic_technical_space,
    const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
    const bool is_element_extension,
    const std::unordered_map<std::string, dogen::coding::meta_model::artefact_properties>& artefact_properties,
    const std::unordered_map<std::string, dogen::coding::meta_model::local_archetype_location_properties>& archetype_location_properties,
    const boost::optional<dogen::coding::meta_model::decoration::element_properties>& decoration,
    const dogen::coding::meta_model::decoration::editor editor,
    const dogen::coding::meta_model::decoration::modeline_location location,
    const std::list<dogen::coding::meta_model::decoration::modeline_field>& fields,
    const dogen::coding::meta_model::technical_space technical_space)
    : dogen::coding::meta_model::element(
      name,
      documentation,
      origin_type,
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
      editor_(editor),
      location_(location),
      fields_(fields),
      technical_space_(technical_space) { }

void modeline::accept(const element_visitor& v) const {
    v.visit(*this);
}

void modeline::accept(element_visitor& v) const {
    v.visit(*this);
    }

void modeline::accept(const element_visitor& v) {
    v.visit(*this);
}

void modeline::accept(element_visitor& v) {
    v.visit(*this);
}

void modeline::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::coding::meta_model::decoration::modeline\"" << ", "
      << "\"__parent_0__\": ";
    dogen::coding::meta_model::element::to_stream(s);
    s << ", "
      << "\"editor\": " << editor_ << ", "
      << "\"location\": " << location_ << ", "
      << "\"fields\": " << fields_ << ", "
      << "\"technical_space\": " << technical_space_
      << " }";
}

void modeline::swap(modeline& other) noexcept {
    dogen::coding::meta_model::element::swap(other);

    using std::swap;
    swap(editor_, other.editor_);
    swap(location_, other.location_);
    swap(fields_, other.fields_);
    swap(technical_space_, other.technical_space_);
}

bool modeline::equals(const dogen::coding::meta_model::element& other) const {
    const modeline* const p(dynamic_cast<const modeline* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool modeline::operator==(const modeline& rhs) const {
    return dogen::coding::meta_model::element::compare(rhs) &&
        editor_ == rhs.editor_ &&
        location_ == rhs.location_ &&
        fields_ == rhs.fields_ &&
        technical_space_ == rhs.technical_space_;
}

modeline& modeline::operator=(modeline other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

dogen::coding::meta_model::decoration::editor modeline::editor() const {
    return editor_;
}

void modeline::editor(const dogen::coding::meta_model::decoration::editor v) {
    editor_ = v;
}

dogen::coding::meta_model::decoration::modeline_location modeline::location() const {
    return location_;
}

void modeline::location(const dogen::coding::meta_model::decoration::modeline_location v) {
    location_ = v;
}

const std::list<dogen::coding::meta_model::decoration::modeline_field>& modeline::fields() const {
    return fields_;
}

std::list<dogen::coding::meta_model::decoration::modeline_field>& modeline::fields() {
    return fields_;
}

void modeline::fields(const std::list<dogen::coding::meta_model::decoration::modeline_field>& v) {
    fields_ = v;
}

void modeline::fields(const std::list<dogen::coding::meta_model::decoration::modeline_field>&& v) {
    fields_ = std::move(v);
}

dogen::coding::meta_model::technical_space modeline::technical_space() const {
    return technical_space_;
}

void modeline::technical_space(const dogen::coding::meta_model::technical_space v) {
    technical_space_ = v;
}

}
