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
#include "masd.dogen.generation.cpp/types/formatters/tests/cmakelists_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "masd.dogen.generation.cpp/types/formatters/tests/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/assistant.hpp"
#include "masd.dogen.generation.cpp/types/fabric/cmakelists.hpp"
#include "masd.dogen.generation.cpp/types/fabric/meta_name_factory.hpp"
#include "masd.dogen.generation.cpp/types/formatters/traits.hpp"
#include "masd.dogen.generation.cpp/types/traits.hpp"
#include "masd.dogen.generation/types/formatters/sequence_formatter.hpp"
#include "masd.dogen.utility/types/log/logger.hpp"
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/throw_exception.hpp>
#include <boost/make_shared.hpp>

namespace masd::dogen::generation::cpp::formatters::tests {

std::string cmakelists_formatter::static_id() {
    return tests::traits::cmakelists_archetype();
}

std::string cmakelists_formatter::id() const {
    return static_id();
}

archetypes::archetype_location cmakelists_formatter::
archetype_location() const {
    static archetypes::archetype_location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::facet(),
          cmakelists_formatter::static_id());
    return r;
}

const coding::meta_model::name& cmakelists_formatter::meta_name() const {
    static auto r(fabric::meta_name_factory::make_cmakelists_name());
    return r;
}

std::string cmakelists_formatter::family() const {
    return cpp::traits::cmake_family();
}

inclusion_support_types cmakelists_formatter::
inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path cmakelists_formatter::inclusion_path(
    const formattables::locator& /*l*/, const coding::meta_model::name& n) const {

    using namespace masd::dogen::utility::log;
    using namespace masd::dogen::generation::cpp::formatters;
    static logger lg(logger_factory(cmakelists_formatter::static_id()));

    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path cmakelists_formatter::full_path(
    const formattables::locator& l, const coding::meta_model::name& n) const {
    return l.make_full_path_for_tests_cmakelists(n, static_id());
}

std::list<std::string> cmakelists_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const coding::meta_model::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

extraction::meta_model::artefact cmakelists_formatter::
format(const context& ctx, const coding::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& c(a.as<fabric::cmakelists>(e));

    {
        a.make_decoration_preamble(e);
        const auto model_name(a.get_identifiable_model_name(c.name()));
        const auto product_name(a.get_product_name(c.name()));
a.stream() << "set(name \"" << model_name << "\")" << std::endl;
a.stream() << "set(lib_target_name ${name}) # .lib" << std::endl;
a.stream() << "set(tests_binary_name ${name}.tests)" << std::endl;
a.stream() << "set(tests_target_name ${name}.tests)" << std::endl;
a.stream() << std::endl;
a.stream() << "set(files \"\")" << std::endl;
a.stream() << "file(GLOB_RECURSE files RELATIVE" << std::endl;
a.stream() << "    \"${CMAKE_CURRENT_SOURCE_DIR}/\"" << std::endl;
a.stream() << "    \"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp\")" << std::endl;
a.stream() << std::endl;
a.stream() << "add_executable(${tests_target_name} ${files})" << std::endl;
a.stream() << std::endl;
a.stream() << "set_target_properties(${tests_target_name}" << std::endl;
a.stream() << "    PROPERTIES OUTPUT_NAME ${tests_binary_name})" << std::endl;
a.stream() << std::endl;
a.stream() << "target_link_libraries(${tests_target_name}" << std::endl;
a.stream() << "    ${lib_target_name}" << std::endl;
a.stream() << "    ${Boost_LIBRARIES}" << std::endl;
a.stream() << "    ${CMAKE_REQUIRED_LIBRARIES}" << std::endl;
a.stream() << "    ${CMAKE_THREAD_LIBS_INIT})" << std::endl;
a.stream() << std::endl;
a.stream() << "set(command $<TARGET_FILE:${tests_target_name}> ${boost_test_parameters})" << std::endl;
a.stream() << std::endl;
a.stream() << "add_custom_target(run_${tests_target_name}" << std::endl;
a.stream() << "    COMMENT \"Running ${tests_target_name}\" VERBATIM" << std::endl;
a.stream() << "    COMMAND ${command}" << std::endl;
a.stream() << "    WORKING_DIRECTORY ${stage_bin_dir}" << std::endl;
a.stream() << "    DEPENDS ${tests_target_name})" << std::endl;
a.stream() << std::endl;
a.stream() << "add_dependencies(run_all_tests run_${tests_target_name})" << std::endl;
a.stream() << std::endl;
a.stream() << "if(WITH_BENCHMARKS)" << std::endl;
a.stream() << "    set(benchmark_file" << std::endl;
a.stream() << "        ${benchmark_directory}/${benchmark_prefix}${tests_target_name}.csv)" << std::endl;
a.stream() << "    add_custom_target(benchmark_${tests_target_name}" << std::endl;
a.stream() << "        COMMENT \"Benchmarking testing ${tests_target_name}\" VERBATIM" << std::endl;
a.stream() << "        COMMAND ${benchmark_command} ${benchmark_repeats} ${benchmark_file}" << std::endl;
a.stream() << "        ${command}" << std::endl;
a.stream() << "        WORKING_DIRECTORY ${stage_bin_dir}" << std::endl;
a.stream() << "        DEPENDS ${tests_target_name})" << std::endl;
a.stream() << std::endl;
a.stream() << "    add_dependencies(benchmark_all benchmark_${tests_target_name})" << std::endl;
a.stream() << "endif()" << std::endl;
a.stream() << std::endl;
a.stream() << "add_boost_tests(${tests_binary_name} ${files})" << std::endl;
a.stream() << std::endl;
a.stream() << "install(TARGETS ${tests_target_name} RUNTIME DESTINATION bin COMPONENT tests)" << std::endl;
    } // sbf
        return a.make_artefact();
}
}
