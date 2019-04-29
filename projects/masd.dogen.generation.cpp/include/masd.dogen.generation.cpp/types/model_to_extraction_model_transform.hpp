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
#ifndef MASD_DOGEN_GENERATION_CPP_TYPES_MODEL_TO_EXTRACTION_MODEL_TRANSFORM_HPP
#define MASD_DOGEN_GENERATION_CPP_TYPES_MODEL_TO_EXTRACTION_MODEL_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "masd.dogen.variability/types/helpers/configuration_factory.hpp"
#include "masd.dogen.variability/types/meta_model/feature.hpp"
#include "masd.dogen.variability/types/meta_model/configuration.hpp"
#include "masd.dogen.variability/types/meta_model/feature_model.hpp"
#include "masd.dogen.generation/types/meta_model/model.hpp"
#include "masd.dogen.generation/types/transforms/model_to_extraction_model_transform_interface.hpp"
#include "masd.dogen.generation.cpp/types/formatters/repository.hpp"
#include "masd.dogen.generation.cpp/types/formattables/locator.hpp"
#include "masd.dogen.generation.cpp/types/formattables/model.hpp"

namespace masd::dogen::generation::cpp {

/**
 * @brief Implements a C++ model to text transform.
 */
class model_to_extraction_model_transform final
    : public generation::transforms::model_to_extraction_model_transform_interface {
public:
    model_to_extraction_model_transform() = default;
    model_to_extraction_model_transform(
        const model_to_extraction_model_transform&) = delete;
    model_to_extraction_model_transform(
        model_to_extraction_model_transform&&) = default;

public:

    ~model_to_extraction_model_transform() noexcept;

private:
    /**
     * @brief Get the formatters repository.
     */
    const formatters::repository& formatters_repository() const;

    /**
     * @brief Create the formattables representation of the yarn model.
     */
    formattables::model create_formattables_model(
        const variability::meta_model::feature_model& feature_model,
        const variability::meta_model::configuration& rcfg,
        const formatters::repository& frp, const formattables::locator& l,
        const generation::meta_model::model& m) const;

    /**
     * @brief Creates a file locator.
     */
    formattables::locator make_locator(
        const boost::filesystem::path& output_directory_path,
        const variability::meta_model::feature_model& fm,
        const variability::meta_model::configuration& cfg,
        const formatters::repository& frp,
        const bool enable_backend_directories,
        const generation::meta_model::model& m) const;

    /**
     * @brief Create the files representation of the formattables model.
     */
    std::list<extraction::meta_model::artefact>
    format(const std::unordered_set<generation::meta_model::element_archetype>&
        enabled_archetype_for_element,
        const variability::meta_model::feature_model& feature_model,
        const variability::helpers::configuration_factory& cf,
        const formattables::model& fm) const;

    /**
     * @brief Creates a list of all the managed directories.
     */
    std::list<boost::filesystem::path>
    managed_directories(const formattables::locator& l) const;

public:
    std::string id() const override;

    const std::forward_list<archetypes::location>&
    archetype_locations() const override;

    const std::unordered_map<std::string,
                             archetypes::locations_group>&
    archetype_locations_by_meta_name() const override;

    const std::unordered_map<std::string,
                             std::list<archetypes::location>>&
    archetype_locations_by_family() const override;

    const archetypes::location_repository_parts&
    archetype_location_repository_parts() const override;

    coding::meta_model::technical_space technical_space() const override;

    std::unordered_map<std::string,
                       generation::meta_model::intra_backend_segment_properties>
    intra_backend_segment_properties() const override;

    extraction::meta_model::model
    apply(const generation::transforms::context& ctx,
        const bool enable_backend_directories,
        const generation::meta_model::model& m) const override;
};

}

#endif
