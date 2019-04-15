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
#ifndef MASD_DOGEN_VARIABILITY_TYPES_HELPERS_CONFIGURATION_FACTORY_HPP
#define MASD_DOGEN_VARIABILITY_TYPES_HELPERS_CONFIGURATION_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "masd.dogen.archetypes/types/location_repository.hpp"
#include "masd.dogen.variability/types/meta_model/feature.hpp"
#include "masd.dogen.variability/types/meta_model/feature_model.hpp"
#include "masd.dogen.variability/types/meta_model/configuration.hpp"
#include "masd.dogen.variability/types/meta_model/binding_type.hpp"

namespace masd::dogen::variability::helpers {

/**
 * @brief Produces a configuration object from raw data.
 */
class configuration_factory final {
public:
    /**
     * @brief Initialise the configuration factory.
     *
     * @param alrp the archetype location repository.
     * @param fm the feature model.
     * @param compatibility_mode if true, try to ignore some
     * resolution errors.
     */
    configuration_factory(const archetypes::location_repository& alrp,
        const meta_model::feature_model& fm, const bool compatibility_mode);

private:
    /**
     * @brief Returns the feature for the given qualified name, if any
     * such feature exists.
     */
    boost::optional<meta_model::feature>
    try_obtain_feature(const std::string& qn) const;

    /**
     * @brief Ensures the feature can be bound to the supplied binding
     * type.
     */
    void validate_binding(const meta_model::feature& f,
        const meta_model::binding_type bt) const;

    /**
     * @brief Given a binding type, returns the well-known name of its
     * the default configuration.
     */
    std::string get_default_configuration_name_for_binding_type(
        const meta_model::binding_type bt) const;

private:
    /**
     * @brief Converts the raw data into a configuration.
     */
    meta_model::configuration
    create_configuration(const meta_model::binding_type bt,
        const std::unordered_map<std::string, std::list<std::string>>&
        aggregated_entries) const;

    /**
     * @brief Aggregate entry data by key.
     */
    std::unordered_map<std::string, std::list<std::string>>
    aggregate_entries(const std::list<std::pair<std::string, std::string>>&
        entries) const;

public:
    /**
     * @brief Create a configuration.
     */
    meta_model::configuration
    make(const std::list<std::pair<std::string, std::string>>& entries,
        const meta_model::binding_type bt) const;

private:
    const archetypes::location_repository& archetype_location_repository_;
    const meta_model::feature_model& feature_model_;
    const bool compatibility_mode_;
};

}

#endif
