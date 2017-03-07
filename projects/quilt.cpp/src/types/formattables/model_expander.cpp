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
#include "dogen/quilt.cpp/types/formattables/streaming_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/enablement_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/canonical_archetype_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/inclusion_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/decoration_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/aspect_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/helper_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/reducer.hpp"
#include "dogen/quilt.cpp/types/formattables/file_path_and_guard_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/odb_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/facet_directory_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/formatting_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/cmakelists_expander.hpp"
#include "dogen/quilt.cpp/types/formattables/model_expander.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

void model_expander::
expand_streaming(const annotations::type_repository& atrp, model& fm) const {
    streaming_expander ex;
    ex.expand(atrp, fm);
}

void model_expander::expand_enablement(const annotations::type_repository& atrp,
    const annotations::annotation& ra,
    const formatters::repository& frp, model& fm) const {
    enablement_expander ex;
    ex.expand(atrp, ra, frp, fm);
}

void model_expander::expand_canonical_archetypes(
    const formatters::repository& frp, model& fm) const {
    canonical_archetype_expander ex;
    ex.expand(frp, fm);
}

void model_expander::expand_inclusion(
    const annotations::type_repository& atrp, const formatters::repository& frp,
    const locator& l, model& fm) const {
    inclusion_expander ex;
    ex.expand(atrp, frp, l, fm);
}

void model_expander::expand_decoration(
    const dogen::formatters::decoration_properties_factory& dpf,
    model& fm) const {
    decoration_expander ex;
    ex.expand(dpf, fm);
}

void model_expander::expand_aspects(const annotations::type_repository& atrp,
    model& fm) const {
    aspect_expander ex;
    ex.expand(atrp, fm);
}

void model_expander::expand_helpers(const annotations::type_repository& atrp,
    const formatters::repository& frp, model& fm) const {
    helper_expander ex;
    ex.expand(atrp, frp, fm);
}

void model_expander::reduce(model& fm) const {
    reducer rd;
    rd.reduce(fm);
}

void model_expander::expand_file_paths_and_guards(
    const formatters::repository& frp, const locator& l, model& fm) const {
    file_path_and_guard_expander ex;
    ex.expand(frp, l, fm);
}

void model_expander::
expand_odb(const annotations::type_repository& atrp, model& fm) const {
    odb_expander ex;
    ex.expand(atrp, fm);
}

void model_expander::
expand_facet_directories(const locator& l,model& fm) const {
    facet_directory_expander ex;
    ex.expand(l, fm);
}

void model_expander::expand_formatting_properties(
    const annotations::type_repository& atrp, const formatters::repository& frp,
    model& fm) const {
    formatting_expander ex;
    ex.expand(atrp, frp, fm);
}

void model_expander::expand_cmakelists(const locator& l, model& fm) const {
    cmakelists_expander ex;
    ex.expand(l, fm);
}

void model_expander::expand(
    const annotations::type_repository& atrp, const annotations::annotation& ra,
    const dogen::formatters::decoration_properties_factory& dpf,
    const formatters::repository& frp, const locator& l, model& fm) const {

    /*
     * Streaming expansion must be done before helper expansion as the
     * helpers need the streaminging properties.
     */
    expand_streaming(atrp, fm);

    /*
     * Enablement expansion must be done before inclusion because
     * inclusion relies on it to know which formatters are enabled.
     */
    expand_enablement(atrp, ra, frp, fm);

    /*
     * Canonical formatter expansion must be done before inclusion
     * because we use the canonical formatter notation to find
     * inclusion directives.
     */
    expand_canonical_archetypes(frp, fm);

    expand_inclusion(atrp, frp, l, fm);
    expand_decoration(dpf, fm);
    expand_aspects(atrp, fm);
    expand_helpers(atrp, frp, fm);

    /*
     * All of the above expansions must be performed prior to
     * reduction because we require types from external models.
     */
    reduce(fm);

    expand_file_paths_and_guards(frp, l, fm);
    expand_odb(atrp, fm);
    expand_facet_directories(l, fm);
    expand_formatting_properties(atrp, frp, fm);
    expand_cmakelists(l, fm);
}

} } } }
