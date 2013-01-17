/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_DRIVER_PROGRAM_OPTIONS_PARSER_HPP
#define DOGEN_DRIVER_PROGRAM_OPTIONS_PARSER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <functional>
#include <boost/optional.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/program_options.hpp>
#include "dogen/config/types/archive_types.hpp"
#include "dogen/config/types/settings.hpp"

namespace dogen {
namespace driver {

/**
 * @brief Creates the code generator settings given command line
 * arguments.
 */
class program_options_parser {
public:
    program_options_parser() = delete;
    program_options_parser& operator=(const program_options_parser&) = delete;
    program_options_parser(const program_options_parser&) = delete;

public:
    program_options_parser(program_options_parser&& rhs)
    : settings_(std::move(rhs.settings_)),
      verbose_(std::move(rhs.verbose_)),
      arguments_(std::move(rhs.arguments_)),
      help_function_(std::move(rhs.help_function_)),
      version_function_(std::move(rhs.version_function_)),
      current_path_(std::move(rhs.current_path_)) { }

    explicit program_options_parser(std::vector<std::string> arguments);
    program_options_parser(int argc, char** argv);

private:
    void throw_project_dir_with_split() const;
    void throw_include_source_without_split() const;
    void throw_missing_include_source() const;
    void throw_missing_target() const;

private:
    typedef boost::program_options::options_description options_description;

    options_description general_options_factory() const;
    options_description troubleshooting_options_factory() const;
    options_description modeling_options_factory() const;
    options_description output_options_factory() const;
    options_description cpp_options_factory() const;
    options_description options_factory() const;

private:
    typedef boost::program_options::variables_map variables_map;
    boost::optional<variables_map> variables_map_factory() const;

public:
    static config::archive_types parse_archive_type(const std::string& s);
    static config::cpp_facet_types parse_facet_types(const std::string& s);

private:
    config::modeling_settings
    transform_modeling_settings(const variables_map& vm) const;
    config::cpp_settings transform_cpp_settings(const variables_map& vm) const;
    config::troubleshooting_settings
    transform_troubleshooting_settings(const variables_map& vm) const;
    config::output_settings transform_output_settings(const variables_map& vm) const;

public:
    void help_function(std::function<void(std::string)> value);
    void version_function(std::function<void()> value);

public:
    boost::optional<config::settings> parse();

private:
    config::settings settings_;
    bool verbose_;
    const std::vector<std::string> arguments_;
    std::function<void(const std::string&)> help_function_;
    std::function<void()>  version_function_;
    const boost::filesystem::path current_path_;
};

} }

#endif
