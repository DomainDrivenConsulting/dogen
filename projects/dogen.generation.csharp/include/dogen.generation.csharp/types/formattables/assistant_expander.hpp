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
#ifndef DOGEN_GENERATION_CSHARP_TYPES_FORMATTABLES_ASSISTANT_EXPANDER_HPP
#define DOGEN_GENERATION_CSHARP_TYPES_FORMATTABLES_ASSISTANT_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/optional.hpp>
#include "dogen.variability/types/meta_model/feature.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.variability/types/meta_model/feature_model.hpp"
#include "dogen.generation.csharp/types/formattables/model.hpp"
#include "dogen.generation.csharp/types/formattables/assistant_properties.hpp"

namespace dogen::generation::csharp::formattables {

class assistant_expander final {
private:
    struct feature_group {
        variability::meta_model::feature requires_assistance;
        variability::meta_model::feature method_postfix;
    };

    feature_group make_feature_group(
        const variability::meta_model::feature_model& fm) const;

    boost::optional<assistant_properties>
    make_assistant_properties(const feature_group& fg,
        const variability::meta_model::configuration& cfg) const;

public:
    void expand(const variability::meta_model::feature_model& feature_model,
        model& fm) const;
};

}

#endif
