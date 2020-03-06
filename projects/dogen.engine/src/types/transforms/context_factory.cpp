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
#include <boost/make_shared.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/filesystem/path.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.tracing/types/tracer.hpp"
#include "dogen.archetypes/types/features/initializer.hpp"
#include "dogen.archetypes/io/location_repository_io.hpp"
#include "dogen.archetypes/types/location_repository_builder.hpp"
#include "dogen.variability/types/transforms/context.hpp"
#include "dogen.variability/types/features/initializer.hpp"
#include "dogen.variability/types/helpers/registrar.hpp"
#include "dogen.variability/types/meta_model/feature_template_repository.hpp"
#include "dogen.variability/types/transforms/feature_model_production_chain.hpp"
#include "dogen.templating/types/initializer.hpp"
#include "dogen.injection/types/transforms/context.hpp"
#include "dogen.injection/types/features/initializer.hpp"
#include "dogen.assets/types/features/initializer.hpp"
#include "dogen.generation/types/features/initializer.hpp"
#include "dogen.generation/types/transforms/model_to_extraction_model_chain.hpp"
#include "dogen.generation/types/transforms/model_to_extraction_model_transform_registrar.hpp"
#include "dogen.generation.cpp/types/feature_initializer.hpp"
#include "dogen.generation.csharp/types/feature_initializer.hpp"
#include "dogen.extraction/types/features/initializer.hpp"
#include "dogen.engine/types/features/initializer.hpp"
#include "dogen.engine/types/transforms/factory_exception.hpp"
#include "dogen.engine/types/transforms/context_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("engine.transforms.context_factory"));

const std::string alrp_input_id("archetype_location_repository");
const std::string fm_input_id("feature_model");

const std::string duplicate_segment("Duplicat segment: ");

}

namespace dogen::engine::transforms {

using generation::transforms::model_to_extraction_model_transform_registrar;

std::unordered_map<std::string,
                   generation::meta_model::intra_backend_segment_properties>
create_intra_backend_segment_properties(
    const model_to_extraction_model_transform_registrar& rg) {
    std::unordered_map<
        std::string,
        generation::meta_model::intra_backend_segment_properties> r;

    /*
     * Obtain the intra-backend segment properties of each registered
     * model-to-text transform. Notice that the segment names must be
     * unique globally. Then merge them all into a single container of
     * segment properties.
     */
    for (const auto& pair : rg.transforms_by_technical_space()) {
        const auto& t(*pair.second);
        for (const auto& pair : t.intra_backend_segment_properties()) {
            const auto inserted(r.insert(pair).second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, error) << duplicate_segment << pair.first;
                BOOST_THROW_EXCEPTION(
                    factory_exception(duplicate_segment + pair.first));
            }
        }
    }
    return r;
}

boost::shared_ptr<archetypes::location_repository>
create_archetype_location_repository(
    const model_to_extraction_model_transform_registrar& rg) {

    archetypes::location_repository_builder b;
    for (const auto& pair : rg.transforms_by_technical_space()) {
        const auto& t(*pair.second);
        b.add(t.archetype_locations_by_meta_name());
        b.add(t.archetype_locations_by_family());
        b.add(t.archetype_location_repository_parts());
    }
    return boost::make_shared<archetypes::location_repository>(b.build());
}

variability::meta_model::feature_template_repository
make_feature_template_repository() {
    variability::helpers::registrar rg;
    injection::features::initializer::register_templates(rg);
    assets::features::initializer::register_templates(rg);
    generation::features::initializer::register_templates(rg);
    templating::initializer::register_templates(rg);
    variability::features::initializer::register_templates(rg);
    archetypes::features::initializer::register_templates(rg);
    extraction::features::initializer::register_templates(rg);
    generation::cpp::feature_initializer::register_templates(rg);
    generation::csharp::feature_initializer::register_templates(rg);
    features::initializer::register_templates(rg);
    const auto r(rg.feature_template_repository());
    return r;
}

variability::meta_model::feature_repository
make_feature_repository() {
    variability::helpers::registrar rg;
    const auto r(rg.feature_repository());
    return r;
}

injection::transforms::context context_factory::
make_injection_context(const configuration& cfg,
    const std::string& activity) {
    BOOST_LOG_SEV(lg, debug) << "Creating the context. Activity: " << activity;

    /*
     * Obtain the transform registrar and ensure it has been setup.
     */
    using generation::transforms::model_to_extraction_model_chain;
    const auto& rg = model_to_extraction_model_chain::registrar();
    rg.validate();

    /*
     * Obtain the share directory.
     */
    injection::transforms::context r;
    const auto lib_dir(utility::filesystem::library_directory());
    const auto lib_dirs(std::vector<boost::filesystem::path>{ lib_dir });
    r.data_directories(lib_dirs);

    /*
     * Setup the archetypes data structures.
     */
    const auto alrp(create_archetype_location_repository(rg));
    r.archetype_location_repository(alrp);

    /*
     * Setup the tracer. Note that we do it regardless of whether
     * tracing is enabled or not - its the tracer job to handle that.
     */
    const auto tracer(boost::make_shared<tracing::tracer>(cfg, activity));
    r.tracer(tracer);

    return r;

}

context context_factory::
make_context(const configuration& cfg, const std::string& activity,
    const boost::filesystem::path& output_directory) {
    BOOST_LOG_SEV(lg, debug) << "Creating the top-level context. Activity: "
                             << activity;

    /*
     * First we create the variability context, needed to create the
     * feature model.
     */
    variability::transforms::context vctx;

    /*
     * Obtain the data directories.
     */
    const auto lib_dir(utility::filesystem::library_directory());
    const auto lib_dirs(std::vector<boost::filesystem::path>{ lib_dir });
    vctx.data_directories(lib_dirs);

    /*
     * Obtain the transform registrar and ensure it has been setup.
     */
    using generation::transforms::model_to_extraction_model_chain;
    const auto& rg = model_to_extraction_model_chain::registrar();
    rg.validate();

    /*
     * Obtain the archetype location repository.
     */
    const auto alrp(create_archetype_location_repository(rg));
    vctx.archetype_location_repository(alrp);

    /*
     * Handle the compatibility mode.
     */
    const bool cm(cfg.model_processing().compatibility_mode_enabled());
    vctx.compatibility_mode(cm);

    /*
     * Setup the tracer. Note that we do it regardless of whether
     * tracing is enabled or not - its the tracer job to handle that.
     */
    const auto tracer(boost::make_shared<tracing::tracer>(cfg, activity));
    vctx.tracer(tracer);
    tracer->start_run(alrp_input_id, *alrp);

    /*
     * Create the top-level context and all of its sub-contexts.
     */
    engine::transforms::context r;
    r.variability_context(vctx);

    /*
     * Now we can create the feature model.
     */
    const auto ftrp(make_feature_template_repository());
    const auto frp(make_feature_repository());
    using variability::transforms::feature_model_production_chain;
    const auto fm(feature_model_production_chain::apply(vctx, ftrp, frp));
    r.injection_context().feature_model(fm);
    r.assets_context().feature_model(fm);
    r.generation_context().feature_model(fm);
    r.extraction_context().feature_model(fm);

    /*
     * Handle the compatibility mode for all other contexts.
     */
    r.injection_context().compatibility_mode(cm);

    /*
     * Populate the output directory.
     */
    r.generation_context().output_directory_path(output_directory);

    /*
     * Populate the data directories.
     */
    r.injection_context().data_directories(lib_dirs);

    /*
     * Setup the archetype location repository.
     */
    r.injection_context().archetype_location_repository(alrp);
    r.assets_context().archetype_location_repository(alrp);
    r.generation_context().archetype_location_repository(alrp);

    /*
     * Setup the intrabackend segment properties.
     */
    const auto ibsp(create_intra_backend_segment_properties(rg));
    r.generation_context().intra_backend_segment_properties(ibsp);

    /*
     * Setup the tracer.
     */
    r.injection_context().tracer(tracer);
    r.assets_context().tracer(tracer);
    r.generation_context().tracer(tracer);
    r.extraction_context().tracer(tracer);

    /*
     * Setup the diffing and operational reporting configuration.
     */
    r.extraction_context().diffing_configuration(cfg.diffing());
    r.extraction_context().reporting_configuration(cfg.reporting());

    /*
     * Populate dry run mode.
     */
    const auto drm(cfg.model_processing().dry_run_mode_enabled());
    r.extraction_context().dry_run_mode_enabled(drm);

    /*
     * Populate the variability overrides.
     */
    const auto& vo(cfg.model_processing().variability_overrides());
    r.injection_context().variability_overrides(vo);

    /*
     * Populate the generation timestamp.
     */
    using namespace boost::posix_time;
    std::ostringstream s;
    s << to_iso_extended_string(cfg.model_processing().activity_timestamp());
    r.generation_context().generation_timestamp(s.str());

    return r;
}

}
