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
#include "dogen.generation/types/features/formatting.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"

namespace dogen::generation::features {

namespace {

dogen::variability::meta_model::feature_template
make_formatting_style() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("formatting_style");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    r.kind(template_kind::archetype_template);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

dogen::variability::meta_model::feature_template
make_formatting_input() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("formatting_input");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    r.kind(template_kind::archetype_template);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

}

std::list<dogen::variability::meta_model::feature_template>
formatting::make_templates() {
    using namespace dogen::variability::meta_model;
    std::list<feature_template> r;
    r.push_back(make_formatting_style());
    r.push_back(make_formatting_input());
    return r;
}

}