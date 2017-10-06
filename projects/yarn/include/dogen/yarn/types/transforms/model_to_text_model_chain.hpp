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
#ifndef DOGEN_YARN_TYPES_TRANSFORMS_MODEL_TO_TEXT_MODEL_CHAIN_HPP
#define DOGEN_YARN_TYPES_TRANSFORMS_MODEL_TO_TEXT_MODEL_CHAIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>
#include "dogen/annotations/types/type.hpp"
#include "dogen/annotations/types/annotation.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/formatters/types/decoration_properties_factory.hpp"
#include "dogen/yarn/types/meta_model/text_model.hpp"
#include "dogen/yarn/types/transforms/model_to_text_model_transform_registrar.hpp"
#include "dogen/yarn/types/transforms/configuration.hpp"
#include "dogen/yarn/types/transforms/context_fwd.hpp"

namespace dogen {
namespace yarn {
namespace transforms {

class model_to_text_model_chain final {
private:
    struct type_group {
        annotations::type enable_kernel_directories;
        std::list<annotations::type> enabled;
    };

    static type_group make_type_group(const annotations::type_repository& atrp,
        const std::list<annotations::archetype_location>& als);

    static std::unordered_set<std::string> obtain_enabled_kernels(
        const type_group& tg, const annotations::annotation& ra);

    static bool obtain_enable_kernel_directories(const type_group& tg,
        const annotations::annotation& ra);

    static configuration make_configuration(const context& ctx,
        const std::list<annotations::archetype_location>& als,
        const annotations::annotation& ra);

public:
    /**
     * @brief Registrar that keeps track of the available transforms.
     */
    static model_to_text_model_transform_registrar& registrar();

private:
    /*
     * Merges source into destination.
     */
    static void merge(meta_model::text_model&& src,
        meta_model::text_model& dst);

public:
    static meta_model::text_model
    transform(const context& ctx, const meta_model::model& m);
    static meta_model::text_model
    transform(const context& ctx, const std::list<meta_model::model>& models);

private:
    static std::shared_ptr<model_to_text_model_transform_registrar> registrar_;
};

/*
 * Helper method to register transforms.
 */
template<typename Transform>
inline void register_transform() {
    auto t(std::make_shared<Transform>());
    auto& rg(model_to_text_model_chain::registrar());
    rg.register_transform(t);
}

} } }

#endif
