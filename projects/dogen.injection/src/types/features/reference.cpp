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
#include "dogen.injection/types/features/reference.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::injection::features {

namespace {

dogen::variability::meta_model::feature_template
make_masd_injection_reference() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("reference");
    r.name().qualified("masd.injection.reference");
    const auto vt(value_type::text_collection);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

}

reference::feature_group
reference::make_feature_group(const dogen::variability::meta_model::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.reference = s.get_by_name("masd.injection.reference");

    return r;
}

reference::static_configuration reference::make_static_configuration(
    const feature_group& fg,
   const dogen::variability::meta_model::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.reference))
        r.reference = s.get_text_collection_content(fg.reference);

    return r;
}

std::list<dogen::variability::meta_model::feature_template>
reference::make_templates() {
    using namespace dogen::variability::meta_model;
    std::list<dogen::variability::meta_model::feature_template> r;
    r.push_back(make_masd_injection_reference());
    return r;
}

}
