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
#ifndef DOGEN_ENGINE_TYPES_TRANSFORMS_CONTEXT_HPP
#define DOGEN_ENGINE_TYPES_TRANSFORMS_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen.variability/types/transforms/context.hpp"
#include "dogen.assets/types/transforms/context.hpp"
#include "dogen.injection/types/transforms/context.hpp"
#include "dogen.generation/types/transforms/context.hpp"
#include "dogen.extraction/types/transforms/context.hpp"

namespace dogen::engine::transforms {

class context final {
public:
    context() = default;
    context(const context&) = default;
    context(context&&) = default;
    ~context() = default;

public:
    context(
        const dogen::variability::transforms::context& variability_context,
        const dogen::injection::transforms::context& injection_context,
        const dogen::assets::transforms::context& assets_context,
        const dogen::generation::transforms::context& generation_context,
        const dogen::extraction::transforms::context& extraction_context);

public:
    const dogen::variability::transforms::context& variability_context() const;
    dogen::variability::transforms::context& variability_context();
    void variability_context(const dogen::variability::transforms::context& v);
    void variability_context(const dogen::variability::transforms::context&& v);

    const dogen::injection::transforms::context& injection_context() const;
    dogen::injection::transforms::context& injection_context();
    void injection_context(const dogen::injection::transforms::context& v);
    void injection_context(const dogen::injection::transforms::context&& v);

    const dogen::assets::transforms::context& assets_context() const;
    dogen::assets::transforms::context& assets_context();
    void assets_context(const dogen::assets::transforms::context& v);
    void assets_context(const dogen::assets::transforms::context&& v);

    const dogen::generation::transforms::context& generation_context() const;
    dogen::generation::transforms::context& generation_context();
    void generation_context(const dogen::generation::transforms::context& v);
    void generation_context(const dogen::generation::transforms::context&& v);

    const dogen::extraction::transforms::context& extraction_context() const;
    dogen::extraction::transforms::context& extraction_context();
    void extraction_context(const dogen::extraction::transforms::context& v);
    void extraction_context(const dogen::extraction::transforms::context&& v);

private:
    dogen::variability::transforms::context variability_context_;
    dogen::injection::transforms::context injection_context_;
    dogen::assets::transforms::context assets_context_;
    dogen::generation::transforms::context generation_context_;
    dogen::extraction::transforms::context extraction_context_;
};

}

#endif
