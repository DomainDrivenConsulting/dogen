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
#ifndef MASD_DOGEN_VARIABILITY_TYPES_TRANSFORMS_PROFILE_BINDING_TRANSFORM_HPP
#define MASD_DOGEN_VARIABILITY_TYPES_TRANSFORMS_PROFILE_BINDING_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>
#include "masd.dogen.variability/types/meta_model/binding_point.hpp"
#include "masd.dogen.variability/types/meta_model/feature.hpp"
#include "masd.dogen.variability/types/meta_model/feature_model.hpp"
#include "masd.dogen.variability/types/meta_model/profile_repository.hpp"
#include "masd.dogen.variability/types/meta_model/configuration_model.hpp"
#include "masd.dogen.variability/types/transforms/context.hpp"

namespace masd::dogen::variability::transforms {

/**
 * @brief Binds configurations to profiles.
 */
class profile_binding_transform final {
private:
    struct feature_group {
        meta_model::feature profile;
    };

    static feature_group
    make_feature_group(const meta_model::feature_model& fm);

    static std::string obtain_profile_name(const feature_group& fg,
        const meta_model::configuration& cfg);

private:
    /**
     * @brief Given a binding point, returns the well-known name of
     * its the default profile.
     */
    static std::string get_default_profile_name_for_binding_point(
        const meta_model::binding_point bp);

private:
    static void bind(const meta_model::profile_repository& prp,
        const feature_group& fg, meta_model::configuration& cfg);

public:
    static void apply(const context& ctx,
        const meta_model::profile_repository& prp,
        const meta_model::feature_model& fm,
        meta_model::configuration_model& cm);
};

}

#endif
