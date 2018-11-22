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
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.generation.cpp/types/formattables/formattable.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<masd::dogen::coding::meta_model::element>& lhs,
const boost::shared_ptr<masd::dogen::coding::meta_model::element>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace masd::dogen::generation::cpp::formattables {

formattable::formattable(
    const boost::shared_ptr<masd::dogen::coding::meta_model::element>& master_segment,
    const std::list<boost::shared_ptr<masd::dogen::coding::meta_model::element> >& all_segments,
    const masd::dogen::generation::cpp::formattables::element_properties& element_properties)
    : master_segment_(master_segment),
      all_segments_(all_segments),
      element_properties_(element_properties) { }

void formattable::swap(formattable& other) noexcept {
    using std::swap;
    swap(master_segment_, other.master_segment_);
    swap(all_segments_, other.all_segments_);
    swap(element_properties_, other.element_properties_);
}

bool formattable::operator==(const formattable& rhs) const {
    return master_segment_ == rhs.master_segment_ &&
        all_segments_ == rhs.all_segments_ &&
        element_properties_ == rhs.element_properties_;
}

formattable& formattable::operator=(formattable other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::shared_ptr<masd::dogen::coding::meta_model::element>& formattable::master_segment() const {
    return master_segment_;
}

boost::shared_ptr<masd::dogen::coding::meta_model::element>& formattable::master_segment() {
    return master_segment_;
}

void formattable::master_segment(const boost::shared_ptr<masd::dogen::coding::meta_model::element>& v) {
    master_segment_ = v;
}

void formattable::master_segment(const boost::shared_ptr<masd::dogen::coding::meta_model::element>&& v) {
    master_segment_ = std::move(v);
}

const std::list<boost::shared_ptr<masd::dogen::coding::meta_model::element> >& formattable::all_segments() const {
    return all_segments_;
}

std::list<boost::shared_ptr<masd::dogen::coding::meta_model::element> >& formattable::all_segments() {
    return all_segments_;
}

void formattable::all_segments(const std::list<boost::shared_ptr<masd::dogen::coding::meta_model::element> >& v) {
    all_segments_ = v;
}

void formattable::all_segments(const std::list<boost::shared_ptr<masd::dogen::coding::meta_model::element> >&& v) {
    all_segments_ = std::move(v);
}

const masd::dogen::generation::cpp::formattables::element_properties& formattable::element_properties() const {
    return element_properties_;
}

masd::dogen::generation::cpp::formattables::element_properties& formattable::element_properties() {
    return element_properties_;
}

void formattable::element_properties(const masd::dogen::generation::cpp::formattables::element_properties& v) {
    element_properties_ = v;
}

void formattable::element_properties(const masd::dogen::generation::cpp::formattables::element_properties&& v) {
    element_properties_ = std::move(v);
}

}
