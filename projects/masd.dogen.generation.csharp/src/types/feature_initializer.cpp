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
#include "masd.dogen.generation.csharp/types/feature_initializer.hpp"
#include "masd.dogen.generation.csharp/types/formatters/io/features.hpp"
#include "masd.dogen.generation.csharp/types/formatters/facet_features.hpp"
#include "masd.dogen.generation.csharp/types/formatters/types/features.hpp"
#include "masd.dogen.generation.csharp/types/formatters/global_features.hpp"
#include "masd.dogen.generation.csharp/types/formatters/archetype_features.hpp"
#include "masd.dogen.generation.csharp/types/formatters/test_data/features.hpp"

namespace masd::dogen::generation::csharp {

void feature_initializer::
register_templates(variability::helpers::feature_template_registrar& rg) {
    rg.register_templates(masd::dogen::generation::csharp::formatters::archetype_features::make_templates());
    rg.register_templates(masd::dogen::generation::csharp::formatters::facet_features::make_templates());
    rg.register_templates(masd::dogen::generation::csharp::formatters::global_features::make_templates());
    rg.register_templates(masd::dogen::generation::csharp::formatters::io::features::make_templates());
    rg.register_templates(masd::dogen::generation::csharp::formatters::test_data::features::make_templates());
    rg.register_templates(masd::dogen::generation::csharp::formatters::types::features::make_templates());

}

}
