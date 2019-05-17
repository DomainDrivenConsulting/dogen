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
#include "dogen.variability/types/meta_model/feature_model.hpp"

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::variability::meta_model::feature_model>& lhs,
const boost::shared_ptr<dogen::variability::meta_model::feature_model>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::archetypes::location_repository>& lhs,
const boost::shared_ptr<dogen::archetypes::location_repository>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace boost {

inline bool operator==(const boost::shared_ptr<dogen::tracing::tracer>& lhs,
const boost::shared_ptr<dogen::tracing::tracer>& rhs) {
    return (!lhs && !rhs) ||(lhs && rhs && (*lhs == *rhs));
}

}

namespace dogen::injection::transforms {

context::context()
    : compatibility_mode_(static_cast<bool>(0)) { }

context::context(
    const std::vector<boost::filesystem::path>& data_directories,
    const boost::shared_ptr<dogen::variability::meta_model::feature_model>& feature_model,
    const boost::shared_ptr<dogen::archetypes::location_repository>& archetype_location_repository,
    const boost::shared_ptr<dogen::tracing::tracer>& tracer,
    const bool compatibility_mode)
    : data_directories_(data_directories),
      feature_model_(feature_model),
      archetype_location_repository_(archetype_location_repository),
      tracer_(tracer),
      compatibility_mode_(compatibility_mode) { }

void context::swap(context& other) noexcept {
    using std::swap;
    swap(data_directories_, other.data_directories_);
    swap(feature_model_, other.feature_model_);
    swap(archetype_location_repository_, other.archetype_location_repository_);
    swap(tracer_, other.tracer_);
    swap(compatibility_mode_, other.compatibility_mode_);
}

bool context::operator==(const context& rhs) const {
    return data_directories_ == rhs.data_directories_ &&
        feature_model_ == rhs.feature_model_ &&
        archetype_location_repository_ == rhs.archetype_location_repository_ &&
        tracer_ == rhs.tracer_ &&
        compatibility_mode_ == rhs.compatibility_mode_;
}

context& context::operator=(context other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::vector<boost::filesystem::path>& context::data_directories() const {
    return data_directories_;
}

std::vector<boost::filesystem::path>& context::data_directories() {
    return data_directories_;
}

void context::data_directories(const std::vector<boost::filesystem::path>& v) {
    data_directories_ = v;
}

void context::data_directories(const std::vector<boost::filesystem::path>&& v) {
    data_directories_ = std::move(v);
}

const boost::shared_ptr<dogen::variability::meta_model::feature_model>& context::feature_model() const {
    return feature_model_;
}

boost::shared_ptr<dogen::variability::meta_model::feature_model>& context::feature_model() {
    return feature_model_;
}

void context::feature_model(const boost::shared_ptr<dogen::variability::meta_model::feature_model>& v) {
    feature_model_ = v;
}

void context::feature_model(const boost::shared_ptr<dogen::variability::meta_model::feature_model>&& v) {
    feature_model_ = std::move(v);
}

const boost::shared_ptr<dogen::archetypes::location_repository>& context::archetype_location_repository() const {
    return archetype_location_repository_;
}

boost::shared_ptr<dogen::archetypes::location_repository>& context::archetype_location_repository() {
    return archetype_location_repository_;
}

void context::archetype_location_repository(const boost::shared_ptr<dogen::archetypes::location_repository>& v) {
    archetype_location_repository_ = v;
}

void context::archetype_location_repository(const boost::shared_ptr<dogen::archetypes::location_repository>&& v) {
    archetype_location_repository_ = std::move(v);
}

const boost::shared_ptr<dogen::tracing::tracer>& context::tracer() const {
    return tracer_;
}

boost::shared_ptr<dogen::tracing::tracer>& context::tracer() {
    return tracer_;
}

void context::tracer(const boost::shared_ptr<dogen::tracing::tracer>& v) {
    tracer_ = v;
}

void context::tracer(const boost::shared_ptr<dogen::tracing::tracer>&& v) {
    tracer_ = std::move(v);
}

bool context::compatibility_mode() const {
    return compatibility_mode_;
}

void context::compatibility_mode(const bool v) {
    compatibility_mode_ = v;
}

}
