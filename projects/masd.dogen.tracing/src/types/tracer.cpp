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
#include <sstream>
#include <iomanip>
#include <boost/throw_exception.hpp>
#include <boost/filesystem/convenience.hpp>
#include "masd.dogen/io/tracing_configuration_io.hpp"
#include "masd.dogen.utility/types/io/optional_io.hpp"
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/filesystem/file.hpp"
#include "masd.dogen.annotations/io/type_repository_io.hpp"
#include "masd.dogen.annotations/io/archetype_location_repository_io.hpp"
#include "masd.dogen.tracing/types/tracing_error.hpp"
#include "masd.dogen.tracing/types/metrics.hpp"
#include "masd.dogen.tracing/types/metrics_printer.hpp"
#include "masd.dogen.tracing/types/tracer.hpp"

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("tracing.tracer"));

const char zero('0');
const std::string empty;
const unsigned int leading_zeros(3);
const std::string delimiter("-");
const std::string extension(".json");

const std::string chain_directory_exists(
    "Directory for chain already exists: ");
const std::string directory_missing("Tracing data directory must be supplied.");
const std::string failed_delete("Failed to delete tracer data directory.");
const std::string failed_create("Failed to create tracer data directory.");
const std::string unexpected_empty("The stack must not be empty.");

}

namespace masd::dogen::tracing {

tracer::tracer(const annotations::archetype_location_repository& alrp,
    const annotations::type_repository& atrp,
    const boost::filesystem::path& tracing_directory,
    const boost::optional<tracing_configuration>& cfg) :
    configuration_(cfg),
    tracing_directory_(tracing_directory),
    builder_(configuration_ ?
        configuration_->logging_impact() : empty,
        detailed_tracing_enabled()),
    current_directory_(tracing_directory) {

    validate();

    if (!tracing_enabled())
        return;

    handle_tracing_directory();

    if (!detailed_tracing_enabled())
        return;

    transform_position_.push(0);
    write_initial_inputs(alrp, atrp);
}

void tracer::validate() const {
    /*
     * If data tracing was requested, we must have a directory in
     * which to place the data.
     */
    if (tracing_enabled() && tracing_directory_.empty()) {
        BOOST_LOG_SEV(lg, error) << directory_missing;
        BOOST_THROW_EXCEPTION(tracing_error(directory_missing));
    }

    BOOST_LOG_SEV(lg, debug) << "Tracer initialised. Configuration: "
                             << configuration_;
    BOOST_LOG_SEV(lg, debug) << "Tracing directory: '"
                             << tracing_directory_.generic_string() << "'";
}

bool tracer::tracing_enabled() const {
    // double-bang by design.
    return !!configuration_;
}

bool tracer::detailed_tracing_enabled() const {
    return tracing_enabled() &&
        configuration_->level() == tracing_level::detail;
}

void tracer::handle_tracing_directory() const {
    BOOST_LOG_SEV(lg, debug) << "Handling tracing directory.";

    if (boost::filesystem::exists(tracing_directory_)) {
        BOOST_LOG_SEV(lg, debug) << "Tracing directory already exists: "
                                 << tracing_directory_.generic_string();

        boost::system::error_code ec;
        boost::filesystem::remove_all(tracing_directory_, ec);
        if (ec) {
            BOOST_LOG_SEV(lg, error) << failed_delete;
            BOOST_THROW_EXCEPTION(tracing_error(failed_delete));
        }
        BOOST_LOG_SEV(lg, debug) << "Deleted tracer data directory.";
    }

    boost::system::error_code ec;
    boost::filesystem::create_directories(tracing_directory_, ec);
    if (ec) {
        BOOST_LOG_SEV(lg, error) << failed_create;
        BOOST_THROW_EXCEPTION(tracing_error(failed_create));
    }
    BOOST_LOG_SEV(lg, debug) << "Created tracer data directory: "
                             << tracing_directory_.generic_string();
}

void tracer::handle_current_directory() const {
    BOOST_LOG_SEV(lg, debug) << "Handling current directory change.";

    ensure_transform_position_not_empty();

    const auto id(builder_.current()->transform_id());
    std::ostringstream s;
    s << std::setfill(zero) << std::setw(leading_zeros)
      << transform_position_.top();

    if (configuration_ && !configuration_->use_short_names())
        s << delimiter << id;

    current_directory_ /= s.str();

    if (boost::filesystem::exists(current_directory_)) {
        const auto gs(current_directory_.generic_string());
        BOOST_LOG_SEV(lg, error) << chain_directory_exists << gs;
        BOOST_THROW_EXCEPTION(tracing_error(chain_directory_exists + gs));
    }

    boost::system::error_code ec;
    boost::filesystem::create_directories(current_directory_, ec);
    if (ec) {
        BOOST_LOG_SEV(lg, error) << failed_create;
        BOOST_THROW_EXCEPTION(tracing_error(failed_create));
    }
    BOOST_LOG_SEV(lg, debug) << "Created current directory: "
                             << current_directory_.generic_string();
}

void tracer::ensure_transform_position_not_empty() const {
    if (transform_position_.empty()) {
        BOOST_LOG_SEV(lg, error) << unexpected_empty;
        BOOST_THROW_EXCEPTION(tracing_error(unexpected_empty));
    }
}

boost::filesystem::path
tracer::full_path_for_writing(const std::string& filename) const {
    std::ostringstream s;
    s << std::setfill(zero) << std::setw(leading_zeros)
      << transform_position_.top();

    if (configuration_ && !configuration_->use_short_names())
        s << delimiter << filename;

    s << extension;

    return current_directory_ / s.str();
}

boost::filesystem::path tracer::full_path_for_writing(
    const std::string& transform_id, const std::string& type) const {
    ensure_transform_position_not_empty();

    std::ostringstream s;
    s << std::setfill(zero) << std::setw(leading_zeros)
      << transform_position_.top();

    if (configuration_ && !configuration_->use_short_names()) {
        s << delimiter << transform_id << delimiter
          << builder_.current()->guid();
    }

    s << delimiter << type << extension;

    return current_directory_ / s.str();
}

void tracer::write_initial_inputs(
    const annotations::archetype_location_repository& alrp,
    const annotations::type_repository& atrp) const {

    BOOST_LOG_SEV(lg, debug) << "Writing initial inputs.";

    ensure_transform_position_not_empty();
    auto path(full_path_for_writing("archetype_location_repository"));
    BOOST_LOG_SEV(lg, debug) << "Writing: " << path.generic_string();
    utility::filesystem::write(path, alrp);

    ++transform_position_.top();
    path = full_path_for_writing("type_repository");
    BOOST_LOG_SEV(lg, debug) << "Writing: " << path.generic_string();
    utility::filesystem::write(path, atrp);

    BOOST_LOG_SEV(lg, debug) << "Finish writing initial inputs.";
}

void tracer::start_transform(const std::string& transform_id) const {
    if (!tracing_enabled())
        return;

    start_transform(transform_id, empty);
}

void tracer::start_chain(const std::string& transform_id) const {
    if (!tracing_enabled())
        return;

    start_chain(transform_id, empty);
}

void tracer::start_chain(const std::string& transform_id,
    const std::string& model_id) const {
    if (!tracing_enabled())
        return;

    BOOST_LOG_SEV(lg, debug) << "Starting: " << transform_id
                             << " (" << builder_.current()->guid() << ")";
    builder_.start(transform_id, model_id);

    if (!detailed_tracing_enabled())
        return;

    ++transform_position_.top();
    handle_current_directory();
    transform_position_.push(0);
}

void tracer::start_transform(const std::string& transform_id,
    const std::string& model_id) const {
    if (!tracing_enabled())
        return;

    builder_.start(transform_id, model_id);
    BOOST_LOG_SEV(lg, debug) << "Starting: " << transform_id
                             << " (" << builder_.current()->guid() << ")";
}

void tracer::end_chain() const {
    if (!tracing_enabled())
        return;

    BOOST_LOG_SEV(lg, debug) << "Ending: " << builder_.current()->transform_id()
                             << " (" << builder_.current()->guid() << ")";
    builder_.end();

    if (!detailed_tracing_enabled())
        return;

    ensure_transform_position_not_empty();
    transform_position_.pop();
    current_directory_ = current_directory_.parent_path();
    BOOST_LOG_SEV(lg, debug) << "Current directory is now: "
                             << current_directory_.generic_string();
}

void tracer::end_transform() const {
    if (!tracing_enabled())
        return;

    BOOST_LOG_SEV(lg, debug) << "Ending: " << builder_.current()->transform_id()
                             << " (" << builder_.current()->guid() << ")";
    builder_.end();
}

void tracer::end_tracing() const {
    BOOST_LOG_SEV(lg, debug) << "Finished tracing.";

    if (!tracing_enabled())
        return;

    const auto tm(builder_.build());
    const bool uom(configuration_->format() == tracing_format::org_mode);
    const bool dgis(configuration_->guids_enabled());
    const auto s(metrics_printer::print(dgis, uom, tm));
    BOOST_LOG_SEV(lg, debug) << "Writing to tracing directory: '"
                             << tracing_directory_.generic_string() << "'";
    const auto fn(uom ? "transform_stats.org" : "transform_stats.txt");
    utility::filesystem::write(tracing_directory_ / fn, s);
}

}
