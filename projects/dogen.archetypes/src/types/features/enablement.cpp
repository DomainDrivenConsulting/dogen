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
#include "dogen.archetypes/types/features/enablement.hpp"
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::archetypes::features {

namespace {

dogen::variability::meta_model::feature_template
make_enabled() {
    using namespace dogen::variability::meta_model;
    feature_template r;
    r.name().simple("enabled");
    const auto vt(value_type::boolean);
    r.value_type(vt);
    r.binding_point(binding_point::any);
    r.kind(template_kind::recursive_template);
    dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "true" }));

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

}

enablement::feature_group
enablement::make_feature_group(const dogen::variability::meta_model::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.enabled = s.get_by_name("enabled");

    return r;
}

enablement::static_configuration enablement::make_static_configuration(
    const feature_group& fg,
   const dogen::variability::meta_model::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
        r.enabled = s.get_boolean_content(fg.enabled);
    return r;
}

std::list<dogen::variability::meta_model::feature_template>
enablement::make_templates() {
    using namespace dogen::variability::meta_model;
    std::list<dogen::variability::meta_model::feature_template> r;
    r.push_back(make_enabled());
    return r;
}

}
