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
#ifndef MASD_DOGEN_GENERATION_TYPES_TRANSFORMS_DYNAMIC_TRANSFORMS_CHAIN_HPP
#define MASD_DOGEN_GENERATION_TYPES_TRANSFORMS_DYNAMIC_TRANSFORMS_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.variability/types/annotation.hpp"
#include "masd.dogen.variability/types/type_repository.hpp"
#include "masd.dogen.generation/types/meta_model/model.hpp"
#include "masd.dogen.generation/types/transforms/dynamic_transform_registrar.hpp"
#include "masd.dogen.generation/types/transforms/context_fwd.hpp"

namespace masd::dogen::generation::transforms {

class dynamic_transforms_chain final {
public:
    /**
     * @brief Registrar that keeps track of the available external
     * transforms.
     */
    static dynamic_transform_registrar& registrar();

public:
    static void apply(const context& ctx, meta_model::model& m);

private:
    static std::shared_ptr<dynamic_transform_registrar> registrar_;
};

/*
 * Helper method to register external transforms.
 */
template<typename ExternalTransform>
inline void register_dynamic_transform() {
    auto t(std::make_shared<ExternalTransform>());
    auto& rg(dynamic_transforms_chain::registrar());
    rg.register_dynamic_transform(t);
}

}

#endif
