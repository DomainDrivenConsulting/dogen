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
#include "dogen.assets/types/meta_model/templating/element_repository.hpp"
#include "dogen.assets/types/meta_model/templating/logic_less_template.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::assets::meta_model::templating::logic_less_template>& lhs,
const boost::shared_ptr<dogen::assets::meta_model::templating::logic_less_template>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::assets::meta_model::templating {

element_repository::element_repository(const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::templating::logic_less_template> >& logic_less_templates)
    : logic_less_templates_(logic_less_templates) { }

void element_repository::swap(element_repository& other) noexcept {
    using std::swap;
    swap(logic_less_templates_, other.logic_less_templates_);
}

bool element_repository::operator==(const element_repository& rhs) const {
    return logic_less_templates_ == rhs.logic_less_templates_;
}

element_repository& element_repository::operator=(element_repository other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::templating::logic_less_template> >& element_repository::logic_less_templates() const {
    return logic_less_templates_;
}

std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::templating::logic_less_template> >& element_repository::logic_less_templates() {
    return logic_less_templates_;
}

void element_repository::logic_less_templates(const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::templating::logic_less_template> >& v) {
    logic_less_templates_ = v;
}

void element_repository::logic_less_templates(const std::unordered_map<std::string, boost::shared_ptr<dogen::assets::meta_model::templating::logic_less_template> >&& v) {
    logic_less_templates_ = std::move(v);
}

}