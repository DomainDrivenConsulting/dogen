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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/dynamic/types/repository_workflow.hpp"
#include "dogen/config/types/knitting_options_validator.hpp"
#include "dogen/config/io/knitting_options_io.hpp"
#include "dogen/yarn/types/workflow.hpp"
#include "dogen/formatters/types/formatting_error.hpp"
#include "dogen/formatters/types/filesystem_writer.hpp"
#include "dogen/quilt/types/workflow.hpp"
#include "dogen/knit/types/workflow_error.hpp"
#include "dogen/knit/types/housekeeper.hpp"
#include "dogen/knit/types/workflow.hpp"

typedef boost::error_info<struct tag_workflow, std::string> errmsg_workflow;

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("knit.workflow"));

const std::string xml_extension(".xml");
const std::string text_extension(".txt");
const std::string binary_extension(".bin");
const std::string target_postfix("_target");
const std::string library_dir("library");
const std::string merged("merged_");
const std::string fields_dir("fields");
const std::string invalid_archive_type("Invalid or unexpected archive type");
const std::string incorrect_stdout_config(
    "Configuration for output to stdout is incorrect");
const std::string code_generation_failure("Code generation failure.");

}

namespace dogen {
namespace knit {

workflow::workflow(workflow&& rhs)
    : knitting_options_(std::move(rhs.knitting_options_)) { }

workflow::
workflow(const config::knitting_options& o) : knitting_options_(o) {
    config::knitting_options_validator v;
    v.validate(knitting_options_);
}

bool workflow::housekeeping_required() const {
    return knitting_options_.output().delete_extra_files();
}

std::forward_list<dynamic::ownership_hierarchy> workflow::
obtain_ownership_hierarchy_activity() const {
    std::forward_list<dynamic::ownership_hierarchy> r;
    const auto& rg(quilt::workflow::registrar());
    for (const auto b : rg.backends())
        r.splice_after(r.before_begin(), b->ownership_hierarchy());

    return r;
}

dynamic::repository workflow::setup_dynamic_repository_activity(
    const std::forward_list<dynamic::ownership_hierarchy>& oh) const {
    using namespace dogen::utility::filesystem;
    const auto dir(data_files_directory() / fields_dir);
    dynamic::repository_workflow w;
    return w.execute(oh, std::forward_list<boost::filesystem::path> { dir });
}

std::list<yarn::input_descriptor>
workflow::obtain_input_descriptors_activity() const {
    std::list<yarn::input_descriptor> r;
    using namespace dogen::utility::filesystem;
    const auto dir(data_files_directory() / library_dir);

    const auto files(find_files(dir));
    BOOST_LOG_SEV(lg, debug) << "Found " << files.size()
                             << " paths to library models.";

    for (const auto& f : files) {
        BOOST_LOG_SEV(lg, debug) << "Library model: " << f.filename();
        yarn::input_descriptor id;
        id.path(f);
        id.is_target(false);
        r.push_back(id);
    }
    BOOST_LOG_SEV(lg, debug) << "Done creating paths to library models.";

    const auto input_options(knitting_options_.input());
    BOOST_LOG_SEV(lg, debug) << "Found " << input_options.references().size()
                             << " paths to reference models.";

    for (const auto ref : input_options.references()) {
        BOOST_LOG_SEV(lg, debug) << "Reference model: "
                                 << ref.path().filename();
        yarn::input_descriptor id;
        id.path(ref.path());
        id.external_modules(ref.external_modules());
        id.is_target(false);
        r.push_back(id);
    }
    BOOST_LOG_SEV(lg, debug) << "Done creating paths to reference models.";

    yarn::input_descriptor target;
    target.path(input_options.target().path());
    target.is_target(true);
    target.external_modules(input_options.target().external_modules());
    r.push_back(target);
    BOOST_LOG_SEV(lg, debug) << "Added target model: "
                             << input_options.target().path();

    return r;
}

yarn::model workflow::obtain_yarn_model_activity(
    const dynamic::repository& rp,
    const std::list<yarn::input_descriptor>& id) const {
    const auto w = yarn::workflow();
    return w.execute(rp, id);
}

void workflow::perform_housekeeping_activity(
    const std::forward_list<formatters::file>& files,
    const std::forward_list<boost::filesystem::path>& dirs) const {

    std::set<boost::filesystem::path> expected_files;
    for (const auto file : files)
        expected_files.insert(file.path().generic_string());

    const auto& ip(knitting_options_.output().ignore_patterns());
    std::forward_list<std::string> ignore_patterns(ip.begin(), ip.end());
    housekeeper hk(ignore_patterns, dirs, expected_files);
    hk.tidy_up();
}


std::shared_ptr<dogen::formatters::file_writer_interface>
workflow::obtain_file_writer_activity() const {
    const config::output_options& options(knitting_options_.output());
    const auto fw(options.force_write());

    using dogen::formatters::filesystem_writer;
    return std::make_shared<filesystem_writer>(fw);
}

void workflow::write_files_activity(
    std::shared_ptr<dogen::formatters::file_writer_interface> writer,
    const std::forward_list<formatters::file>& files) const {

    if (files.empty()) {
        BOOST_LOG_SEV(lg, warn) << "No files were generated, so no output.";
        return;
    }

    writer->write(files);
}

void workflow::execute() const {
    BOOST_LOG_SEV(lg, info) << "Starting.";
    BOOST_LOG_SEV(lg, info) << "Knitting options: " << knitting_options_;

    try {
        const auto oh(obtain_ownership_hierarchy_activity());
        const auto rp(setup_dynamic_repository_activity(oh));
        const auto id(obtain_input_descriptors_activity());
        const auto m(obtain_yarn_model_activity(rp, id));

        if (!m.has_generatable_types()) {
            BOOST_LOG_SEV(lg, warn) << "No generatable types found.";
            return;
        }

        quilt::workflow w(knitting_options_, rp);
        const auto files(w.execute(m));

        const auto writer(obtain_file_writer_activity());
        write_files_activity(writer, files);

        if (housekeeping_required()) {
            const auto md(w.managed_directories(m));
            perform_housekeeping_activity(files, md);
        }
    } catch(const dogen::formatters::formatting_error& e) {
        BOOST_THROW_EXCEPTION(workflow_error(e.what()));
    } catch (boost::exception& e) {
        e << errmsg_workflow(code_generation_failure);
        throw;
    }
    BOOST_LOG_SEV(lg, info) << "Finished.";
}

} }
