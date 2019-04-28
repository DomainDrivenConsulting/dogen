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
#ifndef MASD_DOGEN_GENERATION_CSHARP_TYPES_FABRIC_VISUAL_STUDIO_FACTORY_HPP
#define MASD_DOGEN_GENERATION_CSHARP_TYPES_FABRIC_VISUAL_STUDIO_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <boost/shared_ptr.hpp>
#include "masd.dogen.variability/types/type.hpp"
#include "masd.dogen.variability/types/annotation.hpp"
#include "masd.dogen.variability/types/type_repository.hpp"
#include "masd.dogen.variability/types/meta_model/feature.hpp"
#include "masd.dogen.variability/types/meta_model/configuration.hpp"
#include "masd.dogen.variability/types/meta_model/feature_model.hpp"
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.generation/types/meta_model/model.hpp"
#include "masd.dogen.generation.csharp/types/fabric/visual_studio_configuration.hpp"

namespace masd::dogen::generation::csharp::fabric {

class visual_studio_factory final {
private:
    struct type_group {
        variability::type project_solution_guid;
        variability::type project_guid;
    };

    type_group make_type_group(const variability::type_repository& atrp) const;

    visual_studio_configuration make_configuration(const type_group& tg,
        const variability::annotation& ra) const;

    visual_studio_configuration make_configuration(
        const variability::type_repository& atrp,
        const variability::annotation& ra) const;

private:
    struct feature_group {
        variability::meta_model::feature project_solution_guid;
        variability::meta_model::feature project_guid;
    };

    feature_group make_feature_group(
        const variability::meta_model::feature_model& fm) const;

    visual_studio_configuration make_configuration(
        const feature_group& fg,
        const variability::meta_model::configuration& cfg) const;

    visual_studio_configuration make_configuration(
        const variability::meta_model::feature_model& fm,
        const variability::meta_model::configuration& cfg) const;

private:
    std::string obtain_project_name(
        const generation::meta_model::model& m) const;

private:
    boost::shared_ptr<coding::meta_model::element>
    make_solution(const visual_studio_configuration cfg,
        const std::string& project_name,
        const generation::meta_model::model& m) const;

    boost::shared_ptr<coding::meta_model::element>
    make_project(const visual_studio_configuration cfg,
        const std::string& project_name,
        const generation::meta_model::model& m) const;

public:
    std::list<boost::shared_ptr<coding::meta_model::element>>
    make(const variability::type_repository& atrp,
        const variability::meta_model::feature_model& fm,
        const bool use_configuration,
        const generation::meta_model::model& m) const;
};

}

#endif
