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
#ifndef DOGEN_CODING_TYPES_TRANSFORMS_TECHNICAL_SPACE_TRANSFORM_HPP
#define DOGEN_CODING_TYPES_TRANSFORMS_TECHNICAL_SPACE_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "dogen.variability/types/meta_model/feature.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.variability/types/meta_model/feature_model.hpp"
#include "dogen.coding/types/meta_model/technical_space.hpp"
#include "dogen.coding/types/meta_model/model.hpp"
#include "dogen.coding/types/transforms/context_fwd.hpp"

namespace dogen::coding::transforms {

/**
 * @brief Updates the technical space fields of the model and its
 * elements.
 */
class technical_space_transform final {
private:
    static meta_model::technical_space to_technical_space(const std::string& s);

private:
    struct feature_group {
        variability::meta_model::feature output_technical_space;
    };

    static feature_group make_feature_group(
        const variability::meta_model::feature_model& fm);

    static std::list<meta_model::technical_space>
    make_output_technical_space(const feature_group& fg,
        const variability::meta_model::configuration& cfg);

private:
    /**
     * @brief Sets up the intrinsic technical space for all model
     * elements.
     */
    static void setup_intrinsic_technical_space(meta_model::model& m);

public:
    static void apply(const context& ctx, meta_model::model& m);
};

}

#endif
