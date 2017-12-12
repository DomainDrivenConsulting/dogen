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
#include "dogen.yarn/types/meta_model/element.hpp"
#include "dogen.quilt.csharp/types/formattables/formattable.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::yarn::meta_model::element>& lhs,
const boost::shared_ptr<dogen::yarn::meta_model::element>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen {
namespace quilt {
namespace csharp {
namespace formattables {

formattable::formattable(
    const dogen::quilt::csharp::formattables::element_properties& element_properties,
    const boost::shared_ptr<dogen::yarn::meta_model::element>& element)
    : element_properties_(element_properties),
      element_(element) { }

void formattable::swap(formattable& other) noexcept {
    using std::swap;
    swap(element_properties_, other.element_properties_);
    swap(element_, other.element_);
}

bool formattable::operator==(const formattable& rhs) const {
    return element_properties_ == rhs.element_properties_ &&
        element_ == rhs.element_;
}

formattable& formattable::operator=(formattable other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const dogen::quilt::csharp::formattables::element_properties& formattable::element_properties() const {
    return element_properties_;
}

dogen::quilt::csharp::formattables::element_properties& formattable::element_properties() {
    return element_properties_;
}

void formattable::element_properties(const dogen::quilt::csharp::formattables::element_properties& v) {
    element_properties_ = v;
}

void formattable::element_properties(const dogen::quilt::csharp::formattables::element_properties&& v) {
    element_properties_ = std::move(v);
}

const boost::shared_ptr<dogen::yarn::meta_model::element>& formattable::element() const {
    return element_;
}

boost::shared_ptr<dogen::yarn::meta_model::element>& formattable::element() {
    return element_;
}

void formattable::element(const boost::shared_ptr<dogen::yarn::meta_model::element>& v) {
    element_ = v;
}

void formattable::element(const boost::shared_ptr<dogen::yarn::meta_model::element>&& v) {
    element_ = std::move(v);
}

} } } }
