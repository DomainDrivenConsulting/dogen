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
#ifndef MASD_DOGEN_GENERATION_CSHARP_TYPES_MODEL_TO_EXTRACTION_MODEL_TRANSFORM_HPP
#define MASD_DOGEN_GENERATION_CSHARP_TYPES_MODEL_TO_EXTRACTION_MODEL_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <vector>
#include <string>
#include <memory>
#include <forward_list>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "masd.dogen.variability/types/annotation.hpp"
#include "masd.dogen.variability/types/type_repository.hpp"
#include "masd.dogen.variability/types/annotation_factory.hpp"
#include "masd.dogen.generation/types/meta_model/model.hpp"
#include "masd.dogen.generation/types/transforms/context.hpp"
#include "masd.dogen.generation/types/transforms/model_to_extraction_model_transform_interface.hpp"
#include "masd.dogen.generation.csharp/types/formatters/repository.hpp"
#include "masd.dogen.generation.csharp/types/formattables/locator.hpp"
#include "masd.dogen.generation.csharp/types/formattables/model.hpp"

namespace masd::dogen::generation::csharp {

/**
 * @brief Manages the c# backend.
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
    formattables::model create_formattables_model(
        const variability::type_repository& atrp,
        const variability::annotation& ra,
        const formatters::repository& frp, const formattables::locator & l,
        const generation::meta_model::model& m) const;

    std::list<extraction::meta_model::artefact>
    format(const variability::type_repository& atrp,
        const variability::annotation_factory& af,
        const formattables::model& fm) const;

public:
    std::string id() const override;

    const std::forward_list<variability::archetype_location>&
        archetype_locations() const override;

    const std::unordered_map<std::string,
                             variability::archetype_locations_group>&
    archetype_locations_by_meta_name() const override;

    const std::unordered_map<std::string,
                             std::list<variability::archetype_location>>&
    archetype_locations_by_family() const override;

    const variability::archetype_location_repository_parts&
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
