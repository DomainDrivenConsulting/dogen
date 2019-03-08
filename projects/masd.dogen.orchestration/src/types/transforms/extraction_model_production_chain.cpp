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
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.injection/types/transforms/model_set_production_chain.hpp"
#include "masd.dogen.coding/types/transforms/model_production_chain.hpp"
#include "masd.dogen.generation/types/transforms/model_generation_chain.hpp"
#include "masd.dogen.generation/types/transforms/model_to_extraction_model_chain.hpp"
#include "masd.dogen.extraction/io/meta_model/model_io.hpp"
#include "masd.dogen.extraction/types/transforms/model_production_chain.hpp"
#include "masd.dogen.orchestration/types/transforms/injection_model_set_to_coding_model_set_transform.hpp"
#include "masd.dogen.orchestration/types/transforms/coding_model_to_generation_model_transform.hpp"
#include "masd.dogen.orchestration/types/transforms/context.hpp"
#include "masd.dogen.orchestration/types/transforms/extraction_model_production_chain.hpp"

namespace {

const std::string
transform_id("orchestration.transforms.extraction_model_production_chain");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

}


namespace masd::dogen::orchestration::transforms {

extraction::meta_model::model extraction_model_production_chain::
transform(const context& ctx,
    const boost::filesystem::path& target) {
    BOOST_LOG_SEV(lg, info) << "Starting extraction model production.";
    BOOST_LOG_SEV(lg, debug) << "Target: " << target.generic();

    const auto model_name(target.filename().string());
    const auto& tracer(*ctx.injection_context().tracer());
    tracing::scoped_chain_tracer stp(lg, "extraction model production chain",
        transform_id, model_name, tracer);

    /*
     * Obtain the injection model set.
     */
    using injection::transforms::model_set_production_chain;
    const auto ims(model_set_production_chain::transform(
            ctx.injection_context(), target));

    /*
     * Convert the injection model set into a coding model set.
     */
    const auto cmset(injection_model_set_to_coding_model_set_transform::
        transform(ctx.coding_context(), ims));

    /*
     * Run all the coding transforms against the model set.
     */
    const auto cms(coding::transforms::model_production_chain::
        transform(ctx.coding_context(), cmset));

    /*
     * Obtain the generation models.
     */

    auto gms(transforms::coding_model_to_generation_model_transform::
        transform(ctx.generation_context(), cms));

    /*
     * Run all the generation transforms agains the generation models.
     */
    generation::transforms::model_generation_chain::
        transform(ctx.generation_context(), gms);

    /*
     * Obtain the extraction models.
     */
    using generation::transforms::model_to_extraction_model_chain;
    auto r(model_to_extraction_model_chain::transform(
            ctx.generation_context(), gms));

    /*
     * Runn all of the extraction transforms against the extraction models.
     */
    extraction::transforms::model_production_chain::transform(
        ctx.extraction_context(), r);

    stp.end_chain(r);
    BOOST_LOG_SEV(lg, info) << "Finished extraction model production.";

    return r;
}


}
