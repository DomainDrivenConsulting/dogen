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
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/filesystem/path.hpp"
#include "masd.dogen.utility/types/filesystem/file.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.extraction/io/meta_model/model_io.hpp"
#include "masd.dogen.extraction/io/meta_model/operation_type_io.hpp"
#include "masd.dogen.extraction/io/helpers/files_by_status_io.hpp"
#include "masd.dogen.extraction/types/helpers/file_status_collector.hpp"
#include "masd.dogen.extraction/types/transforms/transform_exception.hpp"
#include "masd.dogen.extraction/types/transforms/operation_transform.hpp"

namespace {

const std::string transform_id(
    "extraction.transforms.operation_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string unexpected_operation(
    "Operation not expected by transform: ");

}

namespace masd::dogen::extraction::transforms {

void operation_transform::
transform(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg,
        "operation transform", transform_id, m.name(),
        *ctx.tracer(), m);

    for (auto& a : m.artefacts()) {
        const auto gs(a.path().generic());
        BOOST_LOG_SEV(lg, trace) << "Processing: " << gs;

        // HACK: we seemt to have some blank artefacts atm.
        if (a.path().empty())
            continue;

        /*
         * We only expect artefacts with a limited range of operation
         * types. If this artefact is aksing for anything else, throw.
         */
        using extraction::meta_model::operation_type;
        const auto ot(a.operation().type());
        if (ot != operation_type::create_only && ot != operation_type::write) {
            const auto s(boost::lexical_cast<std::string>(ot));
            BOOST_LOG_SEV(lg, error) << unexpected_operation << ot;
            BOOST_THROW_EXCEPTION(
                transform_exception(unexpected_operation + s));
        }

        /*
         * If the file does not yet exist, it must be a newly
         * generated file. If the user requested create only, we can
         * safely bump it to write.
         */
        using extraction::meta_model::operation_reason;
        if (!boost::filesystem::exists(a.path())) {
            a.operation().type(operation_type::write);
            a.operation().reason(operation_reason::newly_generated);
            BOOST_LOG_SEV(lg, trace) << "File does not yet exist for artefact.";
            continue;
        }

        /*
         * The file already exists. Check to see if the user requested
         * to create it only if it doesn't yet exist; if so, we are
         * now safe to ignore it.
         */
        if (ot == operation_type::create_only) {
            a.operation().type(operation_type::ignore);
            a.operation().reason(operation_reason::already_exists);
            BOOST_LOG_SEV(lg, trace) << "Ignoring file as it is create only.";
            continue;
        }

        /*
         * If the user requested force write, we should always write
         * regardlesss of contents. However, note that this does not
         * apply to create only, which has already been handled above.
         */
        if (m.force_write()) {
            a.operation().reason(operation_reason::force_write);
            BOOST_LOG_SEV(lg, trace) << "Force write is on so writing.";
            continue;
        }

        /*
         * Check if there is a need to write or not. For this we
         * perform a binary diff of the file content; if it has
         * changed, we need to write.
         */
        using masd::dogen::utility::filesystem::read_file_content;
        const std::string c(read_file_content(a.path()));
        if (c == a.content()) {
            a.operation().type(operation_type::ignore);
            a.operation().reason(operation_reason::unchanged_generated);
            BOOST_LOG_SEV(lg, trace) << "File contents have not changed.";
            continue;
        }

        /*
         * The last scenario is a generated file which has been
         * changed.
         */
        BOOST_LOG_SEV(lg, trace) << "File contents have changed.";
        a.operation().reason(operation_reason::changed_generated);
    }

    stp.end_transform(m);
}

}
