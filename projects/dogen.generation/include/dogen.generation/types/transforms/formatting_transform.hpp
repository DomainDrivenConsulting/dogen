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
#ifndef DOGEN_GENERATION_TYPES_TRANSFORMS_FORMATTING_TRANSFORM_HPP
#define DOGEN_GENERATION_TYPES_TRANSFORMS_FORMATTING_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen.variability/types/meta_model/feature.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.variability/types/meta_model/feature_model.hpp"
#include "dogen.generation/types/transforms/context.hpp"
#include "dogen.generation/types/meta_model/model.hpp"
#include "dogen.coding/types/meta_model/formatting_styles.hpp"
#include "dogen.generation/types/transforms/formatting_configuration.hpp"

namespace dogen::generation::transforms {

class formatting_transform final {
private:
    static meta_model::formatting_styles
    to_formatting_style(const std::string& s);

private:
    struct feature_group {
        variability::meta_model::feature formatting_style;
        variability::meta_model::feature formatting_input;
    };

    static std::unordered_map<std::string, feature_group>
    make_feature_groups(const variability::meta_model::feature_model& fm,
        const std::list<archetypes::location>& als);

    static std::unordered_map<std::string, formatting_configuration>
    make_formatting_configuration(
        const std::unordered_map<std::string, feature_group>& fgs,
        const variability::meta_model::configuration& cfg);

    static void apply(const std::unordered_map<std::string, feature_group> fgs,
        coding::meta_model::element& e);

public:
    static void apply(const context& ctx, meta_model::model& m);
};

}

#endif
