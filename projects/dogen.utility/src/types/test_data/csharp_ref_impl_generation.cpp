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
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/environment/variable_reader.hpp"
#include "dogen.utility/types/test_data/test_data_exception.hpp"
#include "dogen.utility/types/test_data/csharp_ref_impl_generation.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("utility.csharp_ref_impl_generation"));

const std::string csharp_ref_impl_project_directory_env(
    "CSHARP_REF_IMPL_PROJECTS_DIRECTORY");

const std::string project_dir_not_found(
    "Could not find project directory: ");
const std::string not_initialized("Test data set is not initialized");
const std::string failed_delete("Failed to delete output directory.");
const std::string failed_create("Failed to create output directory.");

const std::string output_dir("masd.csharp_ref_impl.code_generation_test_output");

const std::string models_dia_dir("CSharpRefImpl.Models/dia");
const std::string models_json_dir("CSharpRefImpl.Models/json");

const std::string path_csharprefimpl_csharpmodel_dia(
    "CSharpRefImpl.CSharpModel.dia");
const std::string path_csharprefimpl_directorysettings_dia(
    "CSharpRefImpl.DirectorySettings.dia");
const std::string path_csharprefimpl_lammodel_dia(
    "CSharpRefImpl.LamModel.dia");

const std::string path_csharprefimpl_csharpmodel_json(
    "CSharpRefImpl.CSharpModel.json");
const std::string path_csharprefimpl_directorysettings_json(
    "CSharpRefImpl.DirectorySettings.json");
const std::string path_csharprefimpl_lammodel_json(
    "CSharpRefImpl.LamModel.json");

}

using boost::filesystem::path;

namespace dogen::utility::test_data {

path csharp_ref_impl_generation::project_directory_;
path csharp_ref_impl_generation::dia_models_directory_;
path csharp_ref_impl_generation::json_models_directory_;
path csharp_ref_impl_generation::output_directory_;

void csharp_ref_impl_generation::initialize() {
        using environment::variable_reader;
    const std::string proj_dir_env(
        variable_reader::strict_read_environment_variable(
            csharp_ref_impl_project_directory_env));

    project_directory_ = path(proj_dir_env);
    BOOST_LOG_SEV(lg, debug) << "Project directory: "
                             << project_directory_.generic_string();
    if (!boost::filesystem::exists(project_directory_)) {
        BOOST_LOG_SEV(lg, error) << project_dir_not_found
                                 << proj_dir_env;
        BOOST_THROW_EXCEPTION(
            test_data_exception(project_dir_not_found + proj_dir_env));
    }

    dia_models_directory_ = project_directory_ / models_dia_dir;
    json_models_directory_ = project_directory_ / models_json_dir;
    BOOST_LOG_SEV(lg, debug) << "Dia models: "
                             << dia_models_directory_.generic_string()
                             << " JSON models: "
                             << json_models_directory_.generic_string();

    output_directory_ = boost::filesystem::absolute(output_dir);
    if (boost::filesystem::exists(output_directory_)) {
        BOOST_LOG_SEV(lg, debug) << "Output directory already exists: "
                                 << output_directory_.generic_string();

        boost::system::error_code ec;
        boost::filesystem::remove_all(output_directory_, ec);
        if (ec) {
            BOOST_LOG_SEV(lg, error) << failed_delete;
            BOOST_THROW_EXCEPTION(test_data_exception(failed_delete));
        }
        BOOST_LOG_SEV(lg, debug) << "Deleted output data directory.";
    }

    boost::system::error_code ec;
    boost::filesystem::create_directories(output_directory_, ec);
    if (ec) {
        BOOST_LOG_SEV(lg, error) << failed_create;
        BOOST_THROW_EXCEPTION(test_data_exception(failed_create));
    }
    BOOST_LOG_SEV(lg, debug) << "Created output data directory: "
                             << output_directory_.generic_string();
}

void csharp_ref_impl_generation::ensure_initialized() {
    if (project_directory_.empty())
        BOOST_THROW_EXCEPTION(test_data_exception(not_initialized));
}

path csharp_ref_impl_generation::project_directory() {
    ensure_initialized();
    return project_directory_;
}

path csharp_ref_impl_generation::output_directory() {
    ensure_initialized();
    return output_directory_;
}

path csharp_ref_impl_generation::input_csharprefimpl_csharpmodel_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_csharprefimpl_csharpmodel_dia;
}

path csharp_ref_impl_generation::
input_csharprefimpl_directorysettings_dia() {
    ensure_initialized();
    return dia_models_directory_ /
        path_csharprefimpl_directorysettings_dia;
}

path csharp_ref_impl_generation::input_csharprefimpl_lammodel_dia() {
    ensure_initialized();
    return dia_models_directory_ / path_csharprefimpl_lammodel_dia;
}

path csharp_ref_impl_generation::input_csharprefimpl_csharpmodel_json() {
    ensure_initialized();
    return json_models_directory_ / path_csharprefimpl_csharpmodel_json;
}

path csharp_ref_impl_generation::
input_csharprefimpl_directorysettings_json() {
    ensure_initialized();
    return json_models_directory_ /
        path_csharprefimpl_directorysettings_json;
}

path csharp_ref_impl_generation::input_csharprefimpl_lammodel_json() {
    ensure_initialized();
    return json_models_directory_ / path_csharprefimpl_lammodel_json;
}

}
