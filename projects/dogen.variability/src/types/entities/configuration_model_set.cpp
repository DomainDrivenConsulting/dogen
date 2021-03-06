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
#include "dogen.variability/types/entities/configuration_model_set.hpp"

namespace dogen::variability::entities {

configuration_model_set::configuration_model_set(const std::list<dogen::variability::entities::configuration_model>& models)
    : models_(models) { }

void configuration_model_set::swap(configuration_model_set& other) noexcept {
    using std::swap;
    swap(models_, other.models_);
}

bool configuration_model_set::operator==(const configuration_model_set& rhs) const {
    return models_ == rhs.models_;
}

configuration_model_set& configuration_model_set::operator=(configuration_model_set other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::list<dogen::variability::entities::configuration_model>& configuration_model_set::models() const {
    return models_;
}

std::list<dogen::variability::entities::configuration_model>& configuration_model_set::models() {
    return models_;
}

void configuration_model_set::models(const std::list<dogen::variability::entities::configuration_model>& v) {
    models_ = v;
}

void configuration_model_set::models(const std::list<dogen::variability::entities::configuration_model>&& v) {
    models_ = std::move(v);
}

}
