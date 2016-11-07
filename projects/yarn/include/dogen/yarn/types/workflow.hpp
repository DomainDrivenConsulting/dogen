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

#include <vector>
#include <boost/filesystem/path.hpp>
#include "dogen/annotations/types/annotation_groups_factory.hpp"
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/options/types/input_options.hpp"
#include "dogen/yarn/types/frontend_registrar.hpp"
#include "dogen/yarn/types/injector_registrar.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"
#include "dogen/yarn/types/model.hpp"

namespace dogen {
namespace yarn {

class workflow {
public:
    workflow();

public:
    /**
    p * @brief Returns the frontend registrar. If it has not yet been
     * initialised, initialises it.
     */
    static yarn::frontend_registrar& frontend_registrar();

    /**
     * @brief Returns the injector registrar. If it has not yet been
     * initialised, initialises it.
     */
    static yarn::injector_registrar& injector_registrar();

private:
    void validate() const;

    /**
     * @brief Obtains all intermediate models.
     */
    std::vector<intermediate_model> obtain_intermediate_models(
        const std::vector<boost::filesystem::path>& data_dirs,
        const annotations::annotation_groups_factory& agf,
        const annotations::type_repository& atrp,
        const options::input_options& io) const;

    /**
     * @brief Obtains the final model.
     */
    model obtain_final_model(const annotations::type_repository& atrp,
        const std::vector<intermediate_model>& ims) const;

public:
    model execute(const std::vector<boost::filesystem::path>& data_dirs,
        const annotations::annotation_groups_factory& agf,
        const annotations::type_repository& atrp,
        const options::input_options& io) const;

private:
    static std::shared_ptr<yarn::frontend_registrar> frontend_registrar_;
    static std::shared_ptr<yarn::injector_registrar> injector_registrar_;
};

} }

#endif
