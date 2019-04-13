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
#include "masd.dogen.generation.cpp/types/formatters/visual_studio_solution_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "masd.dogen.generation.cpp/types/formatters/assistant.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/traits.hpp"
#include "masd.dogen.generation.cpp/types/fabric/visual_studio_solution.hpp"
#include "masd.dogen.generation.cpp/types/fabric/meta_name_factory.hpp"
#include "masd.dogen.generation.cpp/types/traits.hpp"
#include "masd.dogen.generation/types/formatters/sequence_formatter.hpp"
#include "masd.dogen.utility/types/log/logger.hpp"
#include <boost/make_shared.hpp>

namespace masd::dogen::generation::cpp::formatters {

std::string visual_studio_solution_formatter::static_id() {
    return traits::visual_studio_solution_archetype();
}

std::string visual_studio_solution_formatter::id() const {
    static auto r(archetype_location().archetype());
    return r;
}

archetypes::location
visual_studio_solution_formatter::archetype_location() const {
    static archetypes::location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::visual_studio_facet(),
          visual_studio_solution_formatter::static_id());
    return r;
}

const coding::meta_model::name&
visual_studio_solution_formatter::meta_name() const {
    using fabric::meta_name_factory;
    static auto r(meta_name_factory::make_visual_studio_solution_name());
    return r;
}

std::string visual_studio_solution_formatter::family() const {
    return cpp::traits::visual_studio_project_family();
}

inclusion_support_types
visual_studio_solution_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path visual_studio_solution_formatter::inclusion_path(
    const formattables::locator& /*l*/, const coding::meta_model::name& n) const {

    using namespace masd::dogen::utility::log;
    using namespace masd::dogen::generation::cpp::formatters;
    static logger lg(logger_factory(static_id()));

    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path visual_studio_solution_formatter::
full_path(const formattables::locator& l, const coding::meta_model::name& n) const {
    return l.make_full_path_for_solution(n, static_id());
}

std::list<std::string> visual_studio_solution_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const coding::meta_model::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

extraction::meta_model::artefact visual_studio_solution_formatter::
format(const context& ctx, const coding::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& vsl(a.as<fabric::visual_studio_solution>(e));
a.stream() << "Microsoft Visual Studio Solution File, Format Version 12.00" << std::endl;
a.stream() << "# Visual Studio 2012" << std::endl;
a.stream() << "Project(\"{" << vsl.project_solution_guid() << "}\") = \"" << vsl.project_name() << "\", \"" << vsl.project_name() << ".csproj\", \"{" << vsl.project_guid() << "}\"" << std::endl;
a.stream() << "EndProject" << std::endl;
a.stream() << "Global" << std::endl;
a.stream() << "    GlobalSection(SolutionConfigurationPlatforms) = preSolution" << std::endl;
a.stream() << "        Debug|Any CPU = Debug|Any CPU" << std::endl;
a.stream() << "        Release|Any CPU = Release|Any CPU" << std::endl;
a.stream() << "    EndGlobalSection" << std::endl;
a.stream() << "    GlobalSection(ProjectConfigurationPlatforms) = postSolution" << std::endl;
a.stream() << "        {" << vsl.project_guid() << "}.Debug|Any CPU.ActiveCfg = Debug|Any CPU" << std::endl;
a.stream() << "        {" << vsl.project_guid() << "}.Debug|Any CPU.Build.0 = Debug|Any CPU" << std::endl;
a.stream() << "        {" << vsl.project_guid() << "}.Release|Any CPU.ActiveCfg = Release|Any CPU" << std::endl;
a.stream() << "        {" << vsl.project_guid() << "}.Release|Any CPU.Build.0 = Release|Any CPU" << std::endl;
a.stream() << "    EndGlobalSection" << std::endl;
a.stream() << "    GlobalSection(MonoDevelopProperties) = preSolution" << std::endl;
a.stream() << "        StartupItem = CppModel.vcxroj" << std::endl;
a.stream() << "    EndGlobalSection" << std::endl;
a.stream() << "EndGlobal" << std::endl;
    return a.make_artefact();
}
}
