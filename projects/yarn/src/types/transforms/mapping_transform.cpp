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
#include "dogen/yarn/types/helpers/mapper.hpp"
#include "dogen/yarn/types/transforms/context.hpp"
#include "dogen/yarn/types/transforms/mapping_transform.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

bool mapping_transform::is_mappable(const meta_model::languages from,
    const meta_model::languages to) {
    return helpers::mapper::is_mappable(from, to);
}

meta_model::intermediate_model mapping_transform::transform(const context& ctx,
    const meta_model::intermediate_model& src, const meta_model::languages to) {
    const helpers::mapper mp(ctx.mapping_repository());
    return mp.map(src.input_language(), to, src);
}

} } }
