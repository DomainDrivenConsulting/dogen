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
#include "dogen.tracing/types/tracer.hpp"
#include "dogen.injection/types/transforms/context.hpp"
#include "dogen.archetypes/types/location_repository.hpp"

namespace dogen::injection::transforms {

context::context()
    : compatibility_mode_(false) {}

context::context(
    const std::vector<boost::filesystem::path>& data_directories,
    const bool compatibility_mode,
    const boost::shared_ptr<dogen::variability::meta_model::feature_model>& feature_model,
    const boost::shared_ptr<dogen::archetypes::location_repository>& archetype_location_repository,
    const boost::shared_ptr<dogen::tracing::tracer>& tracer)
    : data_directories_(data_directories),
      compatibility_mode_(compatibility_mode),
      feature_model_(feature_model),
      archetype_location_repository_(archetype_location_repository),
      tracer_(tracer) { }

const std::vector<boost::filesystem::path>& context::data_directories() const {
    return data_directories_;
}

void context::data_directories(const std::vector<boost::filesystem::path>& v) {
    data_directories_ = v;
}

bool context::compatibility_mode() const {
    return compatibility_mode_;
}

void context::compatibility_mode(const bool v) {
    compatibility_mode_ = v;
}

const boost::shared_ptr<dogen::variability::meta_model::feature_model>& context::feature_model() const {
    return feature_model_;
}

void context::feature_model(const boost::shared_ptr<dogen::variability::meta_model::feature_model>& v) {
    feature_model_ = v;
}

const boost::shared_ptr<dogen::archetypes::location_repository>& context::archetype_location_repository() const {
    return archetype_location_repository_;
}

void context::archetype_location_repository(const boost::shared_ptr<dogen::archetypes::location_repository>& v) {
    archetype_location_repository_ = v;
}

const boost::shared_ptr<dogen::tracing::tracer>& context::tracer() const {
    return tracer_;
}

void context::tracer(const boost::shared_ptr<dogen::tracing::tracer>& v) {
    tracer_ = v;
}

}
