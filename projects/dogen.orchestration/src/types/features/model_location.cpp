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
#include "dogen.variability/types/helpers/value_factory.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.orchestration/types/features/model_location.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace dogen::orchestration::features {

namespace {

dogen::variability::entities::feature
make_masd_codec_external_modules() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("external_modules");
    r.name().qualified("masd.codec.external_modules");
    r.description(R"(External modules containing this model.

External modules contribute to the namespace of the model but not the model
name.)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    return r;
}

dogen::variability::entities::feature
make_masd_codec_model_modules() {
    using namespace dogen::variability::entities;
    feature r;
    r.name().simple("model_modules");
    r.name().qualified("masd.codec.model_modules");
    r.description(R"(Model modules containing this model.

The model modules result in a top-level name separated by dots, e.g. a.b.c.)");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    return r;
}

}

model_location::feature_group
model_location::make_feature_group(const dogen::variability::entities::feature_model& fm) {
    feature_group r;
    const dogen::variability::helpers::feature_selector s(fm);

    r.external_modules = s.get_by_name("masd.codec.external_modules");
    r.model_modules = s.get_by_name("masd.codec.model_modules");

    return r;
}

model_location::static_configuration model_location::make_static_configuration(
    const feature_group& fg,
    const dogen::variability::entities::configuration& cfg) {

    static_configuration r;
    const dogen::variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.external_modules))
        r.external_modules = s.get_text_content(fg.external_modules);
    r.model_modules = s.get_text_content(fg.model_modules);
    return r;
}

std::list<dogen::variability::entities::feature>
model_location::make_features() {
    using namespace dogen::variability::entities;
    std::list<dogen::variability::entities::feature> r;
    r.push_back(make_masd_codec_external_modules());
    r.push_back(make_masd_codec_model_modules());
    return r;
}

}
