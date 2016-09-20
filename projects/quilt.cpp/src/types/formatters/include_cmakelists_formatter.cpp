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
#include <boost/make_shared.hpp>
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/include_cmakelists_formatter_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/include_cmakelists_formatter.hpp"

namespace {

const std::string empty;

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

namespace {

class provider final :
        public properties::provider_interface<fabric::cmakelists> {
public:
    std::string facet_name() const override;
    std::string formatter_name() const override;

    std::list<std::string> provide_inclusion_dependencies(
        const properties::inclusion_dependencies_builder_factory& f,
        const fabric::cmakelists& p) const override;

    properties::inclusion_path_support inclusion_path_support() const override;

    boost::filesystem::path provide_inclusion_path(const properties::locator& l,
        const yarn::name& n) const override;

    boost::filesystem::path provide_full_path(const properties::locator& l,
        const yarn::name& n) const override;
};

std::string provider::facet_name() const {
    return empty;
}

std::string provider::formatter_name() const {
    return include_cmakelists_formatter::static_formatter_name();
}

std::list<std::string> provider::provide_inclusion_dependencies(
    const properties::inclusion_dependencies_builder_factory& /*f*/,
    const fabric::cmakelists& /*c*/) const {

    static std::list<std::string> r;
    return r;
}

properties::inclusion_path_support provider::
inclusion_path_support() const {
    return properties::inclusion_path_support::is_default;
}

boost::filesystem::path
provider::provide_inclusion_path(const properties::locator& /*l*/,
    const yarn::name& /*n*/) const {
    static boost::filesystem::path r;
    return r;
}

boost::filesystem::path
provider::provide_full_path(const properties::locator& l,
    const yarn::name& n) const {
    return l.make_full_path_for_include_cmakelists(n, formatter_name());
}

}

std::string include_cmakelists_formatter::static_formatter_name() {
    return traits::include_cmakelists_formatter_name();
}

std::string include_cmakelists_formatter::id() const {
    static auto r(ownership_hierarchy().formatter_name());
    return r;
}

dynamic::ownership_hierarchy include_cmakelists_formatter::
ownership_hierarchy() const {
    static dynamic::ownership_hierarchy
        r(formatters::traits::model_name(), traits::cmake_facet_name(),
            include_cmakelists_formatter::static_formatter_name(),
            empty/*group name*/);
    return r;
}

file_types include_cmakelists_formatter::file_type() const {
    return file_types::cmakefile;
}

properties::origin_types
include_cmakelists_formatter::formattable_origin_type() const {
    return properties::origin_types::external;
}

void include_cmakelists_formatter::
register_provider(properties::registrar& rg) const {
    rg.register_provider(boost::make_shared<provider>());
}

dogen::formatters::file include_cmakelists_formatter::
format(const context& ctx, const fabric::cmakelists& c) const {
    assistant a(ctx, ownership_hierarchy(), file_type(), c.name().id());
    const auto r(include_cmakelists_formatter_stitch(a, c));
    return r;
}

} } } }
