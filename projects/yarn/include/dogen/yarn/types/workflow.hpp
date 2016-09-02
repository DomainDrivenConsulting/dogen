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
#ifndef DOGEN_YARN_TYPES_WORKFLOW_HPP
#define DOGEN_YARN_TYPES_WORKFLOW_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <boost/filesystem/path.hpp>
#include "dogen/dynamic/types/repository.hpp"
#include "dogen/config/types/input_options.hpp"
#include "dogen/yarn/types/descriptor.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/model.hpp"

namespace dogen {
namespace yarn {

class workflow {
private:
    /**
     * @brief Obtain the model descriptors.
     */
    std::list<descriptor> obtain_descriptors_activity(
        const std::list<boost::filesystem::path>& dirs,
        const config::input_options& io) const;

    /**
     * @brief Obtains all intermediate models.
     */
    std::list<intermediate_model> obtain_intermediate_models_activity(
        const dynamic::repository& drp, const std::list<descriptor>& d) const;

    /**
     * @brief Executes the expansion workflow.
     */
    void expand_intermediate_models_activity(
        const dynamic::repository& drp,
        std::list<intermediate_model>& m) const;

    /**
     * @brief Executes the assembling workflow.
     */
    intermediate_model assemble_intermediate_models_activity(
        const std::list<intermediate_model>& m) const;

    /**
     * @brief Transforms the intermediate model to the final
     * representation.
     */
    model transform_intermediate_model_activity(
        const intermediate_model& m) const;

public:
    model execute(const dynamic::repository& drp,
        const std::list<boost::filesystem::path>& dirs,
        const config::input_options& io) const;
};

} }

#endif
