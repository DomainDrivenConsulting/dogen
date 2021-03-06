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
#ifndef DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_CONTEXT_HPP
#define DOGEN_ORCHESTRATION_TYPES_TRANSFORMS_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen.text/types/transforms/context.hpp"
#include "dogen.codec/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.physical/types/transforms/context.hpp"
#include "dogen.variability/types/transforms/context.hpp"

namespace dogen::orchestration::transforms {

class context final {
public:
    context() = default;
    context(const context&) = default;
    context(context&&) = default;
    ~context() = default;

public:
    context(
        const dogen::variability::transforms::context& variability_context,
        const dogen::codec::transforms::context& codec_context,
        const dogen::logical::transforms::context& logical_context,
        const dogen::text::transforms::context& text_context,
        const dogen::physical::transforms::context& physical_context);

public:
    const dogen::variability::transforms::context& variability_context() const;
    dogen::variability::transforms::context& variability_context();
    void variability_context(const dogen::variability::transforms::context& v);
    void variability_context(const dogen::variability::transforms::context&& v);

    const dogen::codec::transforms::context& codec_context() const;
    dogen::codec::transforms::context& codec_context();
    void codec_context(const dogen::codec::transforms::context& v);
    void codec_context(const dogen::codec::transforms::context&& v);

    const dogen::logical::transforms::context& logical_context() const;
    dogen::logical::transforms::context& logical_context();
    void logical_context(const dogen::logical::transforms::context& v);
    void logical_context(const dogen::logical::transforms::context&& v);

    const dogen::text::transforms::context& text_context() const;
    dogen::text::transforms::context& text_context();
    void text_context(const dogen::text::transforms::context& v);
    void text_context(const dogen::text::transforms::context&& v);

    const dogen::physical::transforms::context& physical_context() const;
    dogen::physical::transforms::context& physical_context();
    void physical_context(const dogen::physical::transforms::context& v);
    void physical_context(const dogen::physical::transforms::context&& v);

public:
    bool operator==(const context& rhs) const;
    bool operator!=(const context& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(context& other) noexcept;
    context& operator=(context other);

private:
    dogen::variability::transforms::context variability_context_;
    dogen::codec::transforms::context codec_context_;
    dogen::logical::transforms::context logical_context_;
    dogen::text::transforms::context text_context_;
    dogen::physical::transforms::context physical_context_;
};

}

namespace std {

template<>
inline void swap(
    dogen::orchestration::transforms::context& lhs,
    dogen::orchestration::transforms::context& rhs) {
    lhs.swap(rhs);
}

}

#endif
