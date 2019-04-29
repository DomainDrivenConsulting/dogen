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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/io/unordered_map_io.hpp"
#include "masd.dogen.generation.cpp/types/traits.hpp"
#include "masd.dogen.variability/types/helpers/feature_selector.hpp"
#include "masd.dogen.variability/types/helpers/configuration_selector.hpp"
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.generation.cpp/io/formattables/streaming_properties_io.hpp"
#include "masd.dogen.generation.cpp/types/formattables/streaming_expander.hpp"

namespace {

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(
        "generation.cpp.formattables.streaming_expander"));

}

namespace masd::dogen::generation::cpp::formattables {

streaming_expander::feature_group
streaming_expander::make_feature_group(
    const variability::meta_model::feature_model& fm) const {
    BOOST_LOG_SEV(lg, debug) << "Creating feature group.";

    feature_group r;

    const variability::helpers::feature_selector s(fm);
    const auto scm(traits::cpp::streaming::string_conversion_method());
    r.string_conversion_method = s.get_by_name(scm);

    const auto rq(traits::cpp::streaming::requires_quoting());
    r.requires_quoting = s.get_by_name(rq);

    const auto ruc(traits::cpp::streaming::remove_unprintable_characters());
    r.remove_unprintable_characters = s.get_by_name(ruc);

    BOOST_LOG_SEV(lg, debug) << "Created type group.";

    return r;
}

boost::optional<streaming_properties>
streaming_expander::
make_streaming_properties(const feature_group& fg,
    const variability::meta_model::configuration& cfg) const {

    BOOST_LOG_SEV(lg, debug) << "Creating streaming properties.";
    bool found_any(false);
    streaming_properties r;
    const variability::helpers::configuration_selector s(cfg);

    const auto& rq(fg.requires_quoting);
    if (s.has_configuration_point(rq)) {
        r.requires_quoting(s.get_boolean_content_or_default(rq));
        found_any = true;
    }

    const auto& scm(fg.string_conversion_method);
    if (s.has_configuration_point(scm)) {
        r.string_conversion_method(s.get_text_content_or_default(scm));
        found_any = true;
    }

    const auto& ruc(fg.remove_unprintable_characters);
    if (s.has_configuration_point(ruc)) {
        r.remove_unprintable_characters(s.get_boolean_content_or_default(ruc));
        found_any = true;
    }

    if (!found_any)
        return boost::optional<streaming_properties>();

    BOOST_LOG_SEV(lg, debug) << "Created streaming properties. "
                             << "Result: " << r;
    return r;
}


void streaming_expander::
expand(const variability::meta_model::feature_model& feature_model,
    model& fm) const {

    BOOST_LOG_SEV(lg, debug) << "Started expanding streaming properties.";
    const auto fg(make_feature_group(feature_model));
    for (auto& pair : fm.formattables()) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);

        /*
         * We only want to process the master segment; the element
         * extensions can be ignored.
         */
        auto segment(formattable.master_segment());
        const auto& e(*segment);
        const auto sp(make_streaming_properties(fg, *e.configuration()));
        if (!sp)
            continue;

        fm.streaming_properties()[id] = *sp;
    }

    BOOST_LOG_SEV(lg, debug) << "Finished expanding streaming properties. "
                             << "Result: "<< fm.streaming_properties();
}

}
