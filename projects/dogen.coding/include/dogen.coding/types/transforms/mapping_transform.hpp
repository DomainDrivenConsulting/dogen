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
#ifndef DOGEN_CODING_TYPES_TRANSFORMS_MAPPING_TRANSFORM_HPP
#define DOGEN_CODING_TYPES_TRANSFORMS_MAPPING_TRANSFORM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen.coding/types/helpers/mapping.hpp"
#include "dogen.coding/types/helpers/mapping_set.hpp"
#include "dogen.coding/types/helpers/mapping_value.hpp"
#include "dogen.coding/types/helpers/mapping_set_repository.hpp"
#include "dogen.coding/types/meta_model/model.hpp"
#include "dogen.coding/types/meta_model/model_set.hpp"
#include "dogen.coding/types/meta_model/technical_space.hpp"
#include "dogen.coding/types/transforms/context_fwd.hpp"

namespace dogen::coding::transforms {

class mapping_transform final {
private:
    /**
     * @brief Retrieve all extensible mappables in the model set.
     */
    static std::unordered_map<std::string,
                       boost::shared_ptr<
                           meta_model::mapping::extensible_mappable>
                       >
    obtain_mappables(const coding::meta_model::model_set& ms);

    /**
     * @brief Creates all of the element id mappings from the
     * mappables.
     */
    static std::unordered_map<std::string, std::list<helpers::mapping>>
    create_mappings(const std::unordered_map<std::string,
        boost::shared_ptr<meta_model::mapping::extensible_mappable>>&
        mappables);

    /**
     * @brief Ensures the mappings are valid.
     */
    static void validate_mappings(const std::unordered_map<std::string,
        std::list<helpers::mapping>>& mappings);

private:
    static void insert(const std::string& lam_id, const meta_model::name& n,
        const meta_model::technical_space ts,
        std::unordered_map<meta_model::technical_space,
        std::unordered_map<std::string, meta_model::name>>& map);

    static void populate_mapping_set(
        const std::list<helpers::mapping>& mappings,
        helpers::mapping_set& ms);

    static helpers::mapping_set_repository create_repository(
        const std::unordered_map<std::string,
        std::list<helpers::mapping>>& mappings_by_set_name);

private:
    static bool is_mappable(const meta_model::technical_space from,
        const meta_model::technical_space to);

    static meta_model::model apply(const context& ctx,
        const helpers::mapping_set_repository& msrp,
        const meta_model::model& src, const meta_model::technical_space to);

public:
    static coding::meta_model::model_set apply(const context& ctx,
        const coding::meta_model::model_set& src,
        const meta_model::technical_space to);
};

}

#endif
