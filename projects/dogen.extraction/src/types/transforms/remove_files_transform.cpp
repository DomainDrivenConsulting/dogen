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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.extraction/io/meta_model/model_io.hpp"
#include "dogen.extraction/types/transforms/remove_files_transform.hpp"

namespace {

const std::string transform_id("extraction.transforms.remove_files_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::extraction::transforms {

void remove_files_transform::delete_extra_files(const meta_model::model& m) {
    /*
     * If the user did not ask to delete extra files, do nothing.
     */
    if (!m.outputting_properties().delete_extra_files()) {
        BOOST_LOG_SEV(lg, debug) << "Delete extra files is off.";
        return;
    }

    /*
     * Collect all the files to remove across the model.
     */
    std::list<boost::filesystem::path> unexpected;
    for (const auto& a : m.artefacts()) {
        using extraction::meta_model::operation_type;
        if (a.operation().type() == operation_type::remove)
            unexpected.push_back(a.path());
    }

    /*
     * Remove all unwanted files
     */
    if (unexpected.empty()) {
        BOOST_LOG_SEV(lg, debug) << "No files found to remove.";
        return;
    }

    BOOST_LOG_SEV(lg, debug) << "Starting to remove files.";
    utility::filesystem::remove(unexpected);
    BOOST_LOG_SEV(lg, debug) << "Removed files.";
}

void remove_files_transform::
delete_empty_directories(const meta_model::model& m) {
    if (!m.outputting_properties().delete_empty_directories()) {
        BOOST_LOG_SEV(lg, debug) << "Delete empty directories is off.";
        return;
    }

    /*
     * Get rid of any empty directories. Note that this is implemented
     * in a bit of an optimistic way:
     *
     * - we can remove empty directories created by the user that are
     *   not related to code generation.
     *
     * - we are not honouring ignore regexes. We probably should not
     *   remove a directory if it matches a ignore regex.
     *
     * For now this approach is good enough.
     */
    BOOST_LOG_SEV(lg, debug) << "Starting to remove empty directories.";
    utility::filesystem::remove_empty_directories(m.managed_directories());
    BOOST_LOG_SEV(lg, debug) << "Removed empty directories.";
}

void remove_files_transform::
apply(const context& ctx, const meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg,
        "remove files transform", transform_id, m.name(), *ctx.tracer());

    /*
     * If we don't have any artefacts then we're done.
     */
    if (m.artefacts().empty()) {
        BOOST_LOG_SEV(lg, info) << "No artefacts were generated.";
        return;
    }

    /*
     * If the user requested a dry run, do nothng.
     */
    if (ctx.dry_run_mode_enabled()) {
        BOOST_LOG_SEV(lg, info) << "Dry run mode is enabled, not executing.";
        return;
    }

    /*
     * Execute the transform.
     */
    delete_extra_files(m);
    delete_empty_directories(m);
}

}