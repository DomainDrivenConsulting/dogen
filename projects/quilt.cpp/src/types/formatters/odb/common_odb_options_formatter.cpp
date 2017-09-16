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
#include "dogen/quilt.cpp/types/formatters/odb/common_odb_options_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/fabric/common_odb_options.hpp"
#include "dogen/quilt.cpp/types/fabric/meta_name_factory.hpp"
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/utility/log/logger.hpp"
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/throw_exception.hpp>
#include <boost/make_shared.hpp>

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace odb {

std::string common_odb_options_formatter::static_artefact() {
    return traits::common_odb_options_archetype();
}

std::string common_odb_options_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location
common_odb_options_formatter::archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::family(), cpp::traits::kernel(),
          traits::facet(), common_odb_options_formatter::static_artefact());
    return r;
}

const yarn::meta_model::name& common_odb_options_formatter::meta_name() const {
    static auto r(fabric::meta_name_factory::make_common_odb_options_name());
    return r;
}

inclusion_support_types
common_odb_options_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path common_odb_options_formatter::inclusion_path(
    const formattables::locator& /*l*/, const yarn::meta_model::name& n) const {
    using namespace dogen::utility::log;
    static logger
        lg(logger_factory("quilt.cpp.formatters.odb.common_odb_options_formatter"));

        const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.id();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.id()));
}

boost::filesystem::path common_odb_options_formatter::full_path(
    const formattables::locator& l, const yarn::meta_model::name& n) const {
    return l.make_full_path_for_odb_options(n, static_artefact());
}

std::list<std::string> common_odb_options_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const yarn::meta_model::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

dogen::formatters::artefact common_odb_options_formatter::
format(const context& ctx, const yarn::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& o(a.as<fabric::common_odb_options>(static_artefact(), e));

    {
        const auto cs(dogen::formatters::comment_styles::shell_style);
        a.make_decoration_preamble(cs, e);

        if (!a.is_cpp_standard_98()) {
a.stream() << "# enable C++11" << std::endl;
a.stream() << "--std c++11" << std::endl;
a.stream() << std::endl;
        }

        if (!o.sql_name_case().empty()) {
a.stream() << "# casing" << std::endl;
a.stream() << "--sql-name-case " << o.sql_name_case() << std::endl;
a.stream() << std::endl;
        }

        if (o.databases().size() > 1) {
a.stream() << "# enable multi-database support" << std::endl;
a.stream() << "--multi-database static" << std::endl;
a.stream() << std::endl;
        }

        if (!o.databases().empty()) {
a.stream() << "# target databases" << std::endl;

            for (const auto& d : o.databases())
a.stream() << "--database " << d << std::endl;
a.stream() << std::endl;
        }
a.stream() << "# use the boost profile" << std::endl;
a.stream() << "--profile boost" << std::endl;
a.stream() << std::endl;
a.stream() << "# generate queries and embedded schemas" << std::endl;
a.stream() << "--generate-query" << std::endl;
a.stream() << "--generate-schema" << std::endl;
a.stream() << "--schema-format embedded" << std::endl;
a.stream() << std::endl;
a.stream() << "# force odb extensions to be different from dogen ones just in case." << std::endl;
a.stream() << "--ixx-suffix .ixx" << std::endl;
a.stream() << "--hxx-suffix .hxx" << std::endl;
a.stream() << "--cxx-suffix .cxx" << std::endl;
a.stream() << std::endl;
a.stream() << "# debug regexes" << std::endl;
a.stream() << "# --include-regex-trace" << std::endl;
    } // sbf
    return a.make_artefact();
}
} } } } }
