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
#include "dogen.assets/io/meta_model/element_io.hpp"
#include "dogen.assets/types/meta_model/element_visitor.hpp"
#include "dogen.assets/types/meta_model/mapping/fixed_mappable.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace dogen::assets::meta_model::mapping {

fixed_mappable::fixed_mappable(
    const dogen::assets::meta_model::name& name,
    const std::string& documentation,
    const dogen::assets::meta_model::origin_types origin_type,
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
    const std::string& destination)
    : dogen::assets::meta_model::element(
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
      destination_(destination) { }

void fixed_mappable::accept(const element_visitor& v) const {
    v.visit(*this);
}

void fixed_mappable::accept(element_visitor& v) const {
    v.visit(*this);
    }

void fixed_mappable::accept(const element_visitor& v) {
    v.visit(*this);
}

void fixed_mappable::accept(element_visitor& v) {
    v.visit(*this);
}

void fixed_mappable::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::assets::meta_model::mapping::fixed_mappable\"" << ", "
      << "\"__parent_0__\": ";
    dogen::assets::meta_model::element::to_stream(s);
    s << ", "
      << "\"destination\": " << "\"" << tidy_up_string(destination_) << "\""
      << " }";
}

void fixed_mappable::swap(fixed_mappable& other) noexcept {
    dogen::assets::meta_model::element::swap(other);

    using std::swap;
    swap(destination_, other.destination_);
}

bool fixed_mappable::equals(const dogen::assets::meta_model::element& other) const {
    const fixed_mappable* const p(dynamic_cast<const fixed_mappable* const>(&other));
    if (!p) return false;
    return *this == *p;
}

bool fixed_mappable::operator==(const fixed_mappable& rhs) const {
    return dogen::assets::meta_model::element::compare(rhs) &&
        destination_ == rhs.destination_;
}

fixed_mappable& fixed_mappable::operator=(fixed_mappable other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& fixed_mappable::destination() const {
    return destination_;
}

std::string& fixed_mappable::destination() {
    return destination_;
}

void fixed_mappable::destination(const std::string& v) {
    destination_ = v;
}

void fixed_mappable::destination(const std::string&& v) {
    destination_ = std::move(v);
}

}
