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
#include "dogen/quilt.cpp/types/formatters/msbuild_targets_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/fabric/msbuild_targets.hpp"
#include "dogen/quilt.cpp/types/fabric/meta_name_factory.hpp"
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/utility/log/logger.hpp"
#include <boost/make_shared.hpp>

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

std::string msbuild_targets_formatter::static_artefact() {
    return traits::msbuild_targets_archetype();
}

std::string msbuild_targets_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location
msbuild_targets_formatter::archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::family(), cpp::traits::kernel(),
          traits::msbuild_facet(),
          msbuild_targets_formatter::static_artefact());
    return r;
}

const yarn::meta_model::name& msbuild_targets_formatter::meta_name() const {
    static auto r(fabric::meta_name_factory::make_msbuild_targets_name());
    return r;
}

inclusion_support_types
msbuild_targets_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path msbuild_targets_formatter::inclusion_path(
    const formattables::locator& /*l*/, const yarn::meta_model::name& n) const {
    
    using namespace dogen::utility::log;
    using namespace dogen::quilt::cpp::formatters;
    static logger lg(logger_factory(static_artefact()));

    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.id();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.id()));
}

boost::filesystem::path msbuild_targets_formatter::full_path(
    const formattables::locator& l, const yarn::meta_model::name& n) const {
    return l.make_full_path_for_msbuild_targets(n, static_artefact());
}

std::list<std::string> msbuild_targets_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const yarn::meta_model::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

dogen::formatters::artefact msbuild_targets_formatter::
format(const context& ctx, const yarn::meta_model::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), false/*requires_header_guard*/, id);
    const auto& c(a.as<fabric::msbuild_targets>(static_artefact(), e));

    {
        const auto cs(dogen::formatters::comment_styles::xml_style);
        a.make_decoration_preamble(cs, e);
        const auto model_name(a.get_identifiable_model_name(c.name()));
        const auto product_name(a.get_product_name(c.name()));
        const auto targets(c.odb_targets());
a.stream() << "<Project DefaultTargets=\"Build\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\" ToolsVersion=\"4.0\">" << std::endl;
a.stream() << std::endl;
a.stream() << "    <!--[" << std::endl;
a.stream() << "        .NAME: odb.targets" << std::endl;
a.stream() << std::endl;
a.stream() << "        .SYNOPSIS:" << std::endl;
a.stream() << "            Generates all of the ODB files for this project." << std::endl;
a.stream() << std::endl;
a.stream() << "        .DESCRIPTION:" << std::endl;
a.stream() << "            Calls the ODB compiler against each of the files in this Dogen model that require" << std::endl;
a.stream() << "            ODB compilation. Also moves the generated files to their correct location." << std::endl;
a.stream() << std::endl;
a.stream() << "        .INPUTS:" << std::endl;
a.stream() << std::endl;
a.stream() << "        .OUTPUTS:" << std::endl;
a.stream() << "    ]-->" << std::endl;
a.stream() << "    <Target Name=\"" << targets.main_target_name() << "\"" << std::endl;
            dogen::formatters::sequence_formatter sf(targets.targets().size());
            sf.prefix_configuration().first("          DependsOnTargets=\"")
                                     .not_first("                            ");
            sf.postfix_configuration().last("\">");
            sf.element_separator(";");
            for (const auto& target : targets.targets()) {
a.stream() << sf.prefix() << target.name() << sf.postfix() << std::endl;
                sf.next();
            }
a.stream() << "        <Message Importance=\"high\" Text=\"ODB " << model_name << " \"/>" << std::endl;
a.stream() << "    </Target>" << std::endl;
a.stream() << std::endl;
            for (const auto& target : targets.targets()) {
                
a.stream() << "    <Target Name=\"" << target.name() << "\">" << std::endl;
a.stream() << "        <Message Importance=\"high\" Text=\"" << target.comment() << "\"/>" << std::endl;
a.stream() << "        <Exec WorkingDirectory=\"$(OutputDirectory)\" Command=\"&quot;$(OdbPath)&quot; -D_SECURE_SCL=0 $(OdbIncludeDirectories) --options-file $(MSBuildThisFileDirectory)" << targets.common_odb_options() << " --options-file $(MSBuildThisFileDirectory)" << target.object_odb_options() << " --output-dir $(MSBuildThisFileDirectory)" << target.output_directory() << " $(MSBuildThisFileDirectory)" << target.types_file() << "\" />" << std::endl;
                for (const auto& pair : target.move_parameters()) {
a.stream() << "        <Move" << std::endl;
a.stream() << "            SourceFiles=\"$(MSBuildThisFileDirectory)" << pair.first << "\"" << std::endl;
a.stream() << "            DestinationFolder=\"$(MSBuildThisFileDirectory)" << pair.second << "\" />" << std::endl;
                }
a.stream() << "    </Target>" << std::endl;
            }
a.stream() << "</Project>" << std::endl;
    } // sbf
    return a.make_artefact();
}
} } } }
