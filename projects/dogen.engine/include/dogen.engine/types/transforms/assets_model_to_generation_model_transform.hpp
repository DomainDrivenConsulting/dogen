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
#ifndef DOGEN_ENGINE_TYPES_TRANSFORMS_ASSETS_MODEL_TO_GENERATION_MODEL_TRANSFORM_HPP
#define DOGEN_ENGINE_TYPES_TRANSFORMS_ASSETS_MODEL_TO_GENERATION_MODEL_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "dogen.assets/types/meta_model/model.hpp"
#include "dogen.generation/types/meta_model/model.hpp"
#include "dogen.generation/types/transforms/context.hpp"

namespace dogen::engine::transforms {

class assets_model_to_generation_model_transform final {
private:
    static std::size_t
    compute_total_size(const assets::meta_model::model& em);

    static generation::meta_model::model
    apply(const assets::meta_model::model& m);

public:
    static std::list<generation::meta_model::model>
    apply(const generation::transforms::context& ctx,
        const std::list<assets::meta_model::model>& cms);
};

}

#endif
