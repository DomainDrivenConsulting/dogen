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
#ifndef DOGEN_ASSETS_TYPES_TRANSFORMS_PRIMITIVES_TRANSFORM_HPP
#define DOGEN_ASSETS_TYPES_TRANSFORMS_PRIMITIVES_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <iosfwd>
#include "dogen.variability/types/meta_model/feature_model.hpp"
#include "dogen.assets/types/meta_model/model.hpp"
#include "dogen.assets/types/meta_model/attribute.hpp"
#include "dogen.assets/types/meta_model/structural/primitive.hpp"
#include "dogen.assets/types/transforms/context_fwd.hpp"

namespace dogen::assets::transforms {

/**
 * @brief Expands all primitives in model.
 */
class primitives_transform final {
private:
    static std::string obtain_value_attribute_simple_name(
        const meta_model::technical_space ts);

    static meta_model::attribute create_attribute_for_underlying_element(
        const meta_model::name& owner, const meta_model::technical_space ts,
        std::string underlying_element);

public:
    static void apply(const context& ctx, meta_model::model& m);
};

}

#endif
