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
#ifndef DOGEN_CODING_TYPES_TRANSFORMS_ENDOASSEMBLY_CHAIN_HPP
#define DOGEN_CODING_TYPES_TRANSFORMS_ENDOASSEMBLY_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include "dogen.coding/types/meta_model/technical_space.hpp"
#include "dogen.coding/types/meta_model/model.hpp"
#include "dogen.coding/types/transforms/context_fwd.hpp"

namespace dogen::coding::transforms {

/**
 * @brief Merges target and references and post-processes the result.
 */
class assembly_chain final {
public:
    static meta_model::model apply(const context& ctx,
        const meta_model::technical_space ts,
        const meta_model::model& target,
        const std::list<meta_model::model>& refs);
};

}

#endif