/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2014 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <iostream>
#include <boost/exception/diagnostic_information.hpp>
#include "dogen/utility/log/life_cycle_manager.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/options/types/knitting_options_validator.hpp"
#include "dogen/version.hpp"
#include "dogen/knitter/program_options_parser.hpp"
#include "dogen/knitter/parser_validation_error.hpp"
#include "dogen/options/types/knitting_options.hpp"
#include "dogen/knit/types/workflow.hpp"
#include "dogen/knitter/workflow.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("knitter"));
const std::string log_file_prefix("log/dogen.knitter.");
const std::string more_information(
    "Try `dogen.knitter --help' for more information.");
const std::string knitter_product("Dogen Knitter v" DOGEN_VERSION);
const std::string usage_error_msg("Usage error: ");
const std::string fatal_error_msg("Fatal Error: " );
const std::string log_file_msg("See the log file for details: ");
const std::string errors_msg(" finished with errors.");

/**
 * @brief Print the program's help text.
 */
void help(const std::string& d) {
    std::cout << "Dogen Knitter." << std::endl
              << "Generates domain objects from a Dia diagram."
              << std::endl << std::endl << d << std::endl;
}

/**
 * @brief Print the program's version details.
 */
void version() {
    std::cout << knitter_product << std::endl
              << "Copyright (C) 2012-2016 Marco Craveiro." << std::endl
              << "License: GPLv3 - GNU GPL version 3 or later "
              << "<http://gnu.org/licenses/gpl.html>."
              << std::endl;
}

}

namespace dogen {
namespace knitter {

workflow::workflow() : can_log_(false) { }

void workflow::
initialise_model_name(const dogen::options::knitting_options& o) {
    const boost::filesystem::path p(o.input().target().path());
    model_name_ = p.stem().filename().string();
}

boost::optional<options::knitting_options> workflow::
generate_knitting_options_activity(const int argc, const char* argv[]) const {
    program_options_parser p(argc, argv);
    p.help_function(help);
    p.version_function(version);

    boost::optional<options::knitting_options> r(p.parse());
    if (!r)
        return r;

    options::knitting_options_validator v;
    v.validate(*r);

    return r;
}

void workflow::initialise_logging_activity(const options::knitting_options& o) {
    const auto sev(o.verbose() ? severity_level::debug : severity_level::info);
    log_file_name_ = log_file_prefix + model_name_ + ".log";
    life_cycle_manager lcm;
    lcm.initialise(log_file_name_, sev);
    can_log_ = true;
}

void workflow::knit_activity(const options::knitting_options& o) const {
    BOOST_LOG_SEV(lg, info) << knitter_product << " started.";
    knit::workflow w(o);
    w.execute();
    BOOST_LOG_SEV(lg, info) << knitter_product << " finished.";
}

void workflow::report_exception_common() const {
    if (can_log_) {
        BOOST_LOG_SEV(lg, warn) << knitter_product << errors_msg;
        std::cerr << log_file_msg << "'" << log_file_name_.string()
                  << "' " << std::endl;
    }

    if (model_name_.empty())
        return;

    std::cerr << "Failed to generate model: '" << model_name_ << "'."
              << std::endl;
}

void workflow::report_exception(const std::exception& e) const {
    /*
     * We must catch by std::exception and cast the boost exception
     * here; if we were to catch boost exception, we would not have
     * access to the what() method and thus could not provide a
     * user-friendly message to the console.
     */
    const auto be(dynamic_cast<const boost::exception* const>(&e));
    if (be && can_log_) {
        BOOST_LOG_SEV(lg, error) << "Error: "
                                 << boost::diagnostic_information(*be);
    }

    std::cerr << "Error: " << e.what() << std::endl;
    report_exception_common();
}

void workflow::report_exception() const {
    std::cerr << "Knitter was forced to terminate." << std::endl;
    report_exception_common();
}

int workflow::execute(const int argc, const char* argv[]) {
    try {
        const auto o(generate_knitting_options_activity(argc, argv));

        /*
         * Can only happen if the options are valid but do not
         * require any action.
         */
        if (!o)
            return 0;

        const auto& s(*o);
        initialise_model_name(s);
        initialise_logging_activity(s);
        knit_activity(s);
    } catch (const knitter::parser_validation_error& e) {
        /*
         * Log known not to be initialised as we are still parsing
         * command line options.
         */
        std::cerr << usage_error_msg << e.what() << std::endl
                  << more_information << std::endl;
        return 1;
    } catch (const std::exception& e) {
        report_exception(e);
        return 1;
    } catch(...) {
        report_exception();
        return 1;
    }
    return 0;
}

} }
