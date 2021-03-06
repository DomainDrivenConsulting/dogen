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
#include "dogen/types/model_processing_configuration.hpp"

namespace dogen {

model_processing_configuration::model_processing_configuration()
    : compatibility_mode_enabled_(static_cast<bool>(0)),
      dry_run_mode_enabled_(static_cast<bool>(0)) { }

model_processing_configuration::model_processing_configuration(
    const bool compatibility_mode_enabled,
    const bool dry_run_mode_enabled,
    const std::vector<std::string>& variability_overrides,
    const boost::posix_time::ptime& activity_timestamp)
    : compatibility_mode_enabled_(compatibility_mode_enabled),
      dry_run_mode_enabled_(dry_run_mode_enabled),
      variability_overrides_(variability_overrides),
      activity_timestamp_(activity_timestamp) { }

void model_processing_configuration::swap(model_processing_configuration& other) noexcept {
    using std::swap;
    swap(compatibility_mode_enabled_, other.compatibility_mode_enabled_);
    swap(dry_run_mode_enabled_, other.dry_run_mode_enabled_);
    swap(variability_overrides_, other.variability_overrides_);
    swap(activity_timestamp_, other.activity_timestamp_);
}

bool model_processing_configuration::operator==(const model_processing_configuration& rhs) const {
    return compatibility_mode_enabled_ == rhs.compatibility_mode_enabled_ &&
        dry_run_mode_enabled_ == rhs.dry_run_mode_enabled_ &&
        variability_overrides_ == rhs.variability_overrides_ &&
        activity_timestamp_ == rhs.activity_timestamp_;
}

model_processing_configuration& model_processing_configuration::operator=(model_processing_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool model_processing_configuration::compatibility_mode_enabled() const {
    return compatibility_mode_enabled_;
}

void model_processing_configuration::compatibility_mode_enabled(const bool v) {
    compatibility_mode_enabled_ = v;
}

bool model_processing_configuration::dry_run_mode_enabled() const {
    return dry_run_mode_enabled_;
}

void model_processing_configuration::dry_run_mode_enabled(const bool v) {
    dry_run_mode_enabled_ = v;
}

const std::vector<std::string>& model_processing_configuration::variability_overrides() const {
    return variability_overrides_;
}

std::vector<std::string>& model_processing_configuration::variability_overrides() {
    return variability_overrides_;
}

void model_processing_configuration::variability_overrides(const std::vector<std::string>& v) {
    variability_overrides_ = v;
}

void model_processing_configuration::variability_overrides(const std::vector<std::string>&& v) {
    variability_overrides_ = std::move(v);
}

const boost::posix_time::ptime& model_processing_configuration::activity_timestamp() const {
    return activity_timestamp_;
}

boost::posix_time::ptime& model_processing_configuration::activity_timestamp() {
    return activity_timestamp_;
}

void model_processing_configuration::activity_timestamp(const boost::posix_time::ptime& v) {
    activity_timestamp_ = v;
}

void model_processing_configuration::activity_timestamp(const boost::posix_time::ptime&& v) {
    activity_timestamp_ = std::move(v);
}

}
