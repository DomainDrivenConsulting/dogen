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
#include <boost/algorithm/string/predicate.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/io/set_io.hpp"
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.utility/types/io/vector_io.hpp"
#include "masd.dogen.utility/types/filesystem/file.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.variability/io/meta_model/feature_template_repository_io.hpp"
#include "masd.dogen.variability/types/helpers/feature_template_hydrator.hpp"
#include "masd.dogen.variability/types/transforms/feature_template_hydration_transform.hpp"

namespace {

const std::string transform_id(
    "variability.transforms.feature_template_hydration_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string variability_dir("variability");
const std::string features_prefix("masd.variability.feature_templates.");

}

namespace masd::dogen::variability::transforms {
std::vector<boost::filesystem::path>
feature_template_hydration_transform::to_template_directories(
    const std::vector<boost::filesystem::path>& data_dirs) {

    std::vector<boost::filesystem::path> r;
    r.reserve(data_dirs.size());
    for (const auto& dir : data_dirs)
        r.push_back(dir / variability_dir);

    return r;
}

std::list<boost::filesystem::path>
feature_template_hydration_transform::obtain_template_filenames(
    const std::vector<boost::filesystem::path>& template_dirs) {

    BOOST_LOG_SEV(lg, trace) << "Finding all files in: " << template_dirs;
    const auto files(dogen::utility::filesystem::find_files(template_dirs));
    BOOST_LOG_SEV(lg, trace) << "Files found: " << files;

    std::list<boost::filesystem::path> r;
    for (const auto& f : files) {
        const auto fn(f.filename().generic_string());
        if (boost::starts_with(fn, features_prefix)) {
            BOOST_LOG_SEV(lg, trace) << "Adding file: " << fn;
            r.push_back(f);
        } else
            BOOST_LOG_SEV(lg, trace) << "Ignoring file: " << fn;
    }
    return r;
}

meta_model::feature_template_repository
feature_template_hydration_transform::hydrate_templates(
    const std::list<boost::filesystem::path>& fns) {

    helpers::feature_template_hydrator h;
    std::list<meta_model::feature_template> fts;
    for (const auto& fn : fns)
        fts.splice(fts.end(), h.hydrate(fn));

    const meta_model::feature_template_repository r(fts);
    return r;
}

meta_model::feature_template_repository
feature_template_hydration_transform::apply(const context& ctx) {
    tracing::scoped_transform_tracer stp(lg,
        "feature template hydration transform", transform_id, transform_id,
        *ctx.tracer());

    BOOST_LOG_SEV(lg, debug) << "Obtaining feature templates.";

    /*
     * First we obtain the set of directories that contain feature
     * templates, by looking into the supplied data directories at a
     * well-known location.
     */
    const auto template_dirs(to_template_directories(ctx.data_directories()));

    /*
     * We then get a list of all templates in these directories.
     */
    const auto tfns(obtain_template_filenames(template_dirs));

    /*
     * Now we can hydrate all files with templates.
     */
    const auto r(hydrate_templates(tfns));

    stp.end_transform(r);
    BOOST_LOG_SEV(lg, debug) << "Finished obtaining feature templates.";
    return r;
}

}
