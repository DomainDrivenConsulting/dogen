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
#include "masd.dogen.injection/types/meta_model/model.hpp"
#include "masd.dogen.injection/types/transforms/context.hpp"
#include "masd.dogen.injection/types/transforms/transformation_error.hpp"
#include "masd.dogen.injection/types/transforms/model_production_chain.hpp"
#include "masd.dogen.injection/types/transforms/model_to_model_chain.hpp"

namespace {

const std::string transform_id("injection.transforms.model_to_model_chain");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string transform_not_supported("Cannot transform into: ");

}

namespace masd::dogen::injection::transforms {

using boost::filesystem::path;

boost::tuple<decoding_transform&, encoding_transform&>
model_to_model_chain::obtain_transforms(const path& src, const path& dst) {
    /*
     * Start by ensuring the registrar is in a good place.
     */
    auto& rg(model_production_chain::registrar());
    rg.validate();

    /*
     * Now ensure we have the required support for the two
     * transformations we intend to do. If not, there is no point
     * continuing.
     */
    return boost::tie(
        rg.decoding_transform_for_path(src),
        rg.encoding_transform_for_path(dst));
}

void model_to_model_chain::apply(const transforms::context& ctx,
    const path& src, const path& dst) {
    tracing::scoped_chain_tracer stp(lg, "model to model chain",
        transform_id, *ctx.tracer());

    /*
     * Obtain a tuple containing the source and destination
     * transforms.
     */
    BOOST_LOG_SEV(lg, info) << " Transforming: " << src.generic_string()
                            << " to: " << dst.generic_string();
    auto tuple(obtain_transforms(src, dst));
    auto src_model(tuple.get<0>().apply(ctx, src));

    /*
     * Transform the model to the requested representation.
     */
    tuple.get<1>().apply(ctx, src_model, dst);
}

}
