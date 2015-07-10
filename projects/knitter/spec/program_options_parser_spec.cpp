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
#include <vector>
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/config/io/knitting_options_io.hpp"
#include "dogen/knitter/program_options_parser.hpp"
#include "dogen/knitter/parser_validation_error.hpp"

using namespace dogen::utility::log;

namespace {

const std::string empty;
const std::string test_module("knitter");
const std::string test_suite("program_options_parser_spec");
const std::string help_sanity_line("General options");
const std::string missing_target("Mandatory parameter target is missing");
const std::string invalid_facet_type("Invalid facet type");
const std::string invalid_archive_type("Invalid archive type");
const std::string unknown_option("invalid-argument");
const std::string source_include_error(
    "You must supply both source-dir and include-dir");
const std::string split_project_dir_error(
    "Argument project-dir cannot be used in conjunction with project splitting");
const std::string source_include_without_split(
    "Arguments source-dir and include-dir require project splitting");

const std::string help_arg("--help");
const std::string version_arg("--version");
const std::string invalid_arg("--invalid-argument");
const std::string invalid_value_arg("invalid-value");

const std::string verbose_arg("--verbose");
const std::string debug_dir_arg("--debug-dir");
const std::string debug_dir_value_arg("some_dir");
const std::string save_dia_model_arg("--save-dia-model");
const std::string save_dia_model_value_arg("xml");
const std::string save_sml_model_arg("--save-sml-model");
const std::string save_sml_model_value_arg("text");
const std::string stop_after_merging_arg("--stop-after-merging");
const std::string stop_after_formatting_arg("--stop-after-formatting");

const std::string target_arg("--target");
const std::string target_value_arg("some_target");
const std::string external_module_path_arg("--external-module-path");
const std::string external_module_path_value_arg("a module");
const std::string reference_arg("--reference");
const std::string reference_value_1_arg("some reference");
const std::string reference_value_2_arg("another reference");
const std::string reference_value_3_arg("a reference,module path 3");
const std::string reference_value_4_arg("another reference,module path 4");

const std::string reference_value_3_diagram("a reference");
const std::string reference_value_3_module_path("module path 3");
const std::string reference_value_4_diagram("another reference");
const std::string reference_value_4_module_path("module path 4");

const std::string cpp_split_project_arg("--cpp-split-project");
const std::string cpp_project_dir_arg("--cpp-project-dir");
const std::string cpp_project_dir_value_arg("a project dir");
const std::string cpp_source_arg("--cpp-source-dir");
const std::string cpp_source_value_arg("some_source");
const std::string cpp_include_arg("--cpp-include-dir");
const std::string cpp_include_value_arg("some_include");
const std::string cpp_disable_cmakelists_arg("--cpp-disable-cmakelists");

const std::string delete_extra_files_arg("--delete-extra-files");
const std::string force_write_arg("--force-write");

class help_mock {
public:
    explicit help_mock(bool& called) : called_(called) { }

    void operator()(const std::string& description) {
        logger lg(logger_factory(test_suite));
        BOOST_LOG_SEV(lg, debug) << "description: " << description;
        BOOST_CHECK(!description.empty());
        BOOST_CHECK(boost::contains(description, help_sanity_line));
        called_ = true;
    }

    bool& called_;
};

help_mock help_mock_factory(bool& called) {
    return help_mock(called);
}

class version_mock {
public:
    explicit version_mock(bool& called) : called_(called) { }
    void operator()() { called_ = true; }
    bool& called_;
};

version_mock version_mock_factory(bool& called) {
    return version_mock(called);
}

dogen::knitter::program_options_parser setup_parser(
    std::vector<std::string> options,
    bool& help_called,
    bool& version_called) {

    logger lg(logger_factory(test_suite));
    BOOST_LOG_SEV(lg, debug) << "options: " << options;
    dogen::knitter::program_options_parser r(options);
    r.help_function(help_mock_factory(help_called));
    r.version_function(version_mock_factory(version_called));
    return r;
}

void check_exception(std::vector<std::string> options, std::string expected) {
    bool help(false);
    bool version(false);
    auto parser(setup_parser(options, help, version));

    using dogen::knitter::parser_validation_error;
    auto lambda([&](const parser_validation_error& e) -> bool {
            const std::string msg(e.what());
            logger lg(logger_factory(test_suite));

            BOOST_LOG_SEV(lg, debug) << "Caught an exception: '" << msg;
            if (!boost::contains(msg, expected)) {
                BOOST_LOG_SEV(lg, error)
                    << "Unexpected exception text. Expected: '" << expected;
                return false;
            }
            BOOST_LOG_SEV(lg, debug) << "Text is the expected message";
            return true;
        });

    BOOST_CHECK_EXCEPTION(parser.parse(), parser_validation_error, lambda);
    BOOST_CHECK(!help);
    BOOST_CHECK(!version);
}

dogen::config::knitting_options
check_valid_arguments(std::vector<std::string> options) {
    bool help(false);
    bool version(false);
    auto parser(setup_parser(options, help, version));

    const auto r(parser.parse());

    BOOST_CHECK(r);
    BOOST_CHECK(!help);
    BOOST_CHECK(!version);
    return r.get();
}

void check_help(std::vector<std::string> options) {
    bool help(false);
    bool version(false);
    auto parser(setup_parser(options, help, version));

    const auto r(parser.parse());

    BOOST_CHECK(!r);
    BOOST_CHECK(help);
    BOOST_CHECK(!version);
}

void check_version(std::vector<std::string> options) {
    bool help(false);
    bool version(false);
    auto parser(setup_parser(options, help, version));

    const auto r(parser.parse());

    BOOST_CHECK(!r);
    BOOST_CHECK(!help);
    BOOST_CHECK(version);
}

}

BOOST_AUTO_TEST_SUITE(program_options_parser)

BOOST_AUTO_TEST_CASE(supplying_help_argument_results_in_help) {
    SETUP_TEST_LOG("supplying_help_argument_results_in_help");
    check_help(std::vector<std::string> { help_arg });
}

BOOST_AUTO_TEST_CASE(supplying_help_argument_with_no_help_function_results_in_no_op) {
    SETUP_TEST_LOG_SOURCE("supplying_help_argument_with_no_help_function_results_in_no_op");
    bool version(false);
    const std::vector<std::string> o = { help_arg };
    BOOST_LOG_SEV(lg, debug) << "options: " << o;

    dogen::knitter::program_options_parser parser(o);
    parser.version_function(version_mock_factory(version));
    const auto r(parser.parse());

    BOOST_CHECK(!r);
    BOOST_CHECK(!version);
}

BOOST_AUTO_TEST_CASE(supplying_version_argument_results_in_just_printing_version) {
    SETUP_TEST_LOG("supplying_version_argument_results_in_just_printing_version");
    check_version(std::vector<std::string> { version_arg });
}

BOOST_AUTO_TEST_CASE(supplying_version_argument_with_no_version_function_results_in_no_op) {
    SETUP_TEST_LOG_SOURCE("supplying_version_argument_with_no_version_function_results_in_no_op");
    bool help(false);
    const std::vector<std::string> o = { version_arg };
    BOOST_LOG_SEV(lg, debug) << "options: " << o;

    dogen::knitter::program_options_parser parser(o);
    parser.help_function(help_mock_factory(help));
    const auto r(parser.parse());

    BOOST_CHECK(!r);
    BOOST_CHECK(!help);
}

BOOST_AUTO_TEST_CASE(supplying_no_arguments_throws) {
    SETUP_TEST_LOG("supplying_no_arguments_throws");
    check_exception(std::vector<std::string> {}, missing_target);
}

BOOST_AUTO_TEST_CASE(supplying_modeling_options_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("supplying_modeling_options_results_in_expected_options");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        external_module_path_arg,
        external_module_path_value_arg,
        reference_arg,
        reference_value_1_arg,
        reference_arg,
        reference_value_2_arg
    };

    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;

    const auto io(ko.input());
    BOOST_CHECK(io.target().string() == target_value_arg);
    BOOST_CHECK(io.external_module_path() == external_module_path_value_arg);

    const auto refs(io.references());
    BOOST_REQUIRE(refs.size() == 2);
    BOOST_CHECK(refs[0].path().string() == reference_value_1_arg);
    BOOST_CHECK(refs[1].path().string() == reference_value_2_arg);
}

BOOST_AUTO_TEST_CASE(supplying_module_path_for_references_results_in_correct_module_path) {
    SETUP_TEST_LOG_SOURCE("supplying_module_path_for_references_results_in_correct_module_path");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        external_module_path_arg,
        external_module_path_value_arg,
        reference_arg,
        reference_value_3_arg,
        reference_arg,
        reference_value_4_arg
    };

    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;

    const auto io(ko.input());
    const auto refs(io.references());
    BOOST_REQUIRE(refs.size() == 2);

    BOOST_CHECK(refs[0].path().string() == reference_value_3_diagram);
    BOOST_CHECK(
        refs[0].external_module_path() == reference_value_3_module_path);
    BOOST_CHECK(refs[1].path().string() == reference_value_4_diagram);
    BOOST_CHECK(
        refs[1].external_module_path() == reference_value_4_module_path);
}

BOOST_AUTO_TEST_CASE(not_supplying_modeling_options_other_than_target_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("not_supplying_modeling_options_other_than_target_results_in_expected_options");

    const std::vector<std::string> o = {
        target_arg, target_value_arg,
    };

    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;

    const auto is(ko.input());
    BOOST_CHECK(is.target().string() == target_value_arg);
    BOOST_CHECK(is.external_module_path().empty());
    BOOST_REQUIRE(is.references().empty());
}

BOOST_AUTO_TEST_CASE(supplying_arguments_without_target_throws) {
    SETUP_TEST_LOG("supplying_arguments_without_target_throws");
    const std::vector<std::string> o = {
        cpp_split_project_arg,
        cpp_source_arg, cpp_source_value_arg,
        cpp_include_arg, cpp_include_value_arg
    };
    check_exception(o, missing_target);
}

BOOST_AUTO_TEST_CASE(supplying_cpp_arguments_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("supplying_cpp_arguments_results_in_expected_options");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        cpp_split_project_arg,
        cpp_source_arg, cpp_source_value_arg,
        cpp_include_arg, cpp_include_value_arg,
        cpp_disable_cmakelists_arg,
    };

    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;

    const auto co(ko.cpp());
    BOOST_CHECK(co.source_directory_path().string() == cpp_source_value_arg);
    BOOST_CHECK(co.include_directory_path().string() == cpp_include_value_arg);
    BOOST_CHECK(co.disable_cmakelists());
}

BOOST_AUTO_TEST_CASE(supplying_invalid_archive_type_throws) {
    SETUP_TEST_LOG_SOURCE("supplying_invalid_archive_type_throws");
    const std::vector<std::string> o1 = {
        target_arg, target_value_arg,
        save_dia_model_arg, invalid_value_arg,
    };
    check_exception(o1, invalid_archive_type);

    const std::vector<std::string> o2 = {
        target_arg, target_value_arg,
        save_sml_model_arg, invalid_value_arg,
    };
    check_exception(o2, invalid_archive_type);
}

BOOST_AUTO_TEST_CASE(not_supplying_cpp_arguments_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("not_supplying_cpp_arguments_results_in_expected_options");
    const std::vector<std::string> o = { target_arg, target_value_arg };

    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;

    const auto co(ko.cpp());
    BOOST_CHECK(!co.split_project());
    BOOST_CHECK(!co.project_directory_path().empty());
    BOOST_CHECK(co.source_directory_path().empty());
    BOOST_CHECK(co.include_directory_path().empty());
    BOOST_CHECK(!co.disable_cmakelists());
}

BOOST_AUTO_TEST_CASE(supplying_an_invalid_argument_throws) {
    SETUP_TEST_LOG("supplying_an_invalid_argument_throws");
    typedef std::vector<std::string> vector;
    check_exception(vector { invalid_arg }, unknown_option);
    check_exception(vector { invalid_arg, help_arg }, unknown_option);
    check_exception(vector { help_arg, invalid_arg }, unknown_option);
    check_exception(vector { invalid_arg, version_arg }, unknown_option);
    check_exception(vector { version_arg, invalid_arg }, unknown_option);
}

BOOST_AUTO_TEST_CASE(supplying_valid_arguments_with_help_results_in_help) {
    SETUP_TEST_LOG("supplying_valid_arguments_with_help_results_in_help");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        cpp_include_arg, cpp_include_value_arg,
        help_arg
    };
    check_help(o);
}

BOOST_AUTO_TEST_CASE(supplying_valid_arguments_with_version_results_in_version) {
    SETUP_TEST_LOG("supplying_valid_arguments_with_version_results_in_version");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        cpp_include_arg, cpp_include_value_arg,
        version_arg
    };
    check_version(o);
}

BOOST_AUTO_TEST_CASE(supplying_project_directory_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("supplying_project_directory_results_in_expected_options");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        cpp_project_dir_arg, cpp_project_dir_value_arg
    };

    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;

    const auto co(ko.cpp());
    BOOST_CHECK(co.project_directory_path() == cpp_project_dir_value_arg);
}

BOOST_AUTO_TEST_CASE(supplying_split_without_source_and_include_defaults_them) {
    SETUP_TEST_LOG_SOURCE("supplying_split_without_source_and_include_defaults_them");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        cpp_split_project_arg
    };

    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;

    const auto co(ko.cpp());
    BOOST_CHECK(!co.source_directory_path().empty());
    BOOST_CHECK(!co.include_directory_path().empty());
}

BOOST_AUTO_TEST_CASE(supplying_source_or_include_without_split_throws) {
    SETUP_TEST_LOG("supplying_source_or_include_without_split_throws");
    const std::vector<std::string> o0 = {
        target_arg, target_value_arg,
        cpp_source_arg, cpp_source_value_arg
    };
    check_exception(o0, source_include_without_split);

    const std::vector<std::string> o1 = {
        target_arg, target_value_arg,
        cpp_include_arg, cpp_include_value_arg
    };
    check_exception(o1, source_include_without_split);

    const std::vector<std::string> o2 = {
        target_arg, target_value_arg,
        cpp_source_arg, cpp_source_value_arg,
        cpp_include_arg, cpp_include_value_arg
    };
    check_exception(o2, source_include_without_split);
}

BOOST_AUTO_TEST_CASE(supplying_project_dir_with_split_throws) {
    SETUP_TEST_LOG("supplying_project_dir_with_split_throws");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        cpp_split_project_arg,
        cpp_project_dir_arg, cpp_project_dir_value_arg
    };
    check_exception(o, split_project_dir_error);
}

BOOST_AUTO_TEST_CASE(supplying_source_and_no_include_throws) {
    SETUP_TEST_LOG("supplying_source_and_no_include_throws");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        cpp_split_project_arg,
        cpp_source_arg, cpp_source_value_arg
    };
    check_exception(o, source_include_error);
}

BOOST_AUTO_TEST_CASE(supplying_include_and_no_source_throws) {
    SETUP_TEST_LOG("supplying_include_and_no_source_throws");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        cpp_split_project_arg,
        cpp_include_arg, cpp_include_value_arg
    };
    check_exception(o, source_include_error);
}

BOOST_AUTO_TEST_CASE(not_supplying_troubleshooting_options_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("not_supplying_troubleshooting_options_results_in_expected_options");
    const std::vector<std::string> o = {
        target_arg, target_value_arg
    };
    const auto s(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << s;

    const auto ts(s.troubleshooting());
    BOOST_CHECK(ts.debug_dir().empty());

    using dogen::config::archive_types;
    BOOST_CHECK(ts.save_dia_model() == archive_types::invalid);
    BOOST_CHECK(ts.save_dia_model() == archive_types::invalid);

    BOOST_CHECK(!ts.stop_after_merging());
    BOOST_CHECK(!ts.stop_after_merging());
}

BOOST_AUTO_TEST_CASE(supplying_troubleshooting_options_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("supplying_troubleshooting_options_results_in_expected_options");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        debug_dir_arg, debug_dir_value_arg,
        save_dia_model_arg, save_dia_model_value_arg,
        save_sml_model_arg, save_sml_model_value_arg,
        stop_after_merging_arg, stop_after_formatting_arg
    };
    const auto s(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << s;

    const auto ts(s.troubleshooting());
    BOOST_CHECK(ts.debug_dir().string() == debug_dir_value_arg);

    using dogen::config::archive_types;
    BOOST_CHECK(ts.save_dia_model() == archive_types::xml);
    BOOST_CHECK(ts.save_sml_model() == archive_types::text);

    BOOST_CHECK(ts.stop_after_merging());
    BOOST_CHECK(ts.stop_after_formatting());
}

BOOST_AUTO_TEST_CASE(supplying_save_sml_or_dia_results_in_options_with_debug_dir) {
    SETUP_TEST_LOG_SOURCE("supplying_save_sml_or_dia_results_in_options_with_debug_dir");
    typedef std::vector<std::string> vector;
    auto lambda([&](vector o) {
            const auto s(check_valid_arguments(o));
            BOOST_LOG_SEV(lg, debug) << "options: " << s;

            const auto ts(s.troubleshooting());
            BOOST_CHECK(!ts.debug_dir().empty());
        });

    const vector o1 = {
        target_arg, target_value_arg,
        save_dia_model_arg, save_dia_model_value_arg
    };
    lambda(o1);

    const vector o2 = {
        target_arg, target_value_arg,
        save_sml_model_arg, save_sml_model_value_arg
    };
    lambda(o2);
}

BOOST_AUTO_TEST_CASE(not_supplying_output_options_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("not_supplying_output_options_results_in_expected_options");
    const std::vector<std::string> o = { target_arg, target_value_arg };
    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;

    const auto oo(ko.output());
    BOOST_CHECK(!oo.delete_extra_files());
    BOOST_CHECK(!oo.force_write());
}

BOOST_AUTO_TEST_CASE(supplying_output_options_results_in_expected_options) {
    SETUP_TEST_LOG_SOURCE("supplying_output_options_results_in_expected_options");
    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        delete_extra_files_arg,
        force_write_arg
    };
    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;

    const auto oo(ko.output());
    BOOST_CHECK(oo.delete_extra_files());
    BOOST_CHECK(oo.force_write());
}

BOOST_AUTO_TEST_CASE(supplying_verobose_flag_results_in_options_with_verbose_on) {
    SETUP_TEST_LOG_SOURCE("supplying_verobose_flag_results_in_options_with_verbose_on");

    const std::vector<std::string> o = {
        target_arg, target_value_arg,
        verbose_arg
    };
    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;
    BOOST_CHECK(ko.verbose());
}

BOOST_AUTO_TEST_CASE(not_supplying_verobose_flag_results_in_options_with_verbose_off) {
    SETUP_TEST_LOG_SOURCE("not_supplying_verobose_flag_results_in_options_with_verbose_off");

    const std::vector<std::string> o = { target_arg, target_value_arg };
    const auto ko(check_valid_arguments(o));
    BOOST_LOG_SEV(lg, debug) << "options: " << ko;
    BOOST_CHECK(!ko.verbose());
}

BOOST_AUTO_TEST_SUITE_END()
