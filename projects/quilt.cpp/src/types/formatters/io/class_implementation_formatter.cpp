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
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/io/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/io/class_implementation_formatter_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/io/class_implementation_formatter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.formatters.io.class_implementation_formatter"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace io {

namespace {

class provider final : public properties::provider_interface<yarn::object> {
public:
    std::string formatter_name() const override;

    std::list<std::string> provide_inclusion_dependencies(
        const properties::inclusion_dependencies_builder_factory& f,
        const yarn::object& o) const override;

    properties::path_derivatives provide_path_derivatives(
        const properties::path_derivatives_factory& f,
        const yarn::name& n) const override;
};

std::string provider::formatter_name() const {
    return class_implementation_formatter::static_formatter_name();
}

std::list<std::string> provider::provide_inclusion_dependencies(
    const properties::inclusion_dependencies_builder_factory& f,
    const yarn::object& o) const {
    auto builder(f.make());
    const auto ch_fn(traits::class_header_formatter_name());
    builder.add(o.name(), ch_fn);

    builder.add(o.opaque_associations(), ch_fn);

    const auto io_fctn(formatters::io::traits::facet_name());
    const auto self_fn(class_implementation_formatter::static_formatter_name());
    const bool io_enabled(builder.is_enabled(o.name(), self_fn));

    if (!io_enabled)
        return builder.build();

    const auto os(inclusion_constants::std::ostream());
    builder.add(os);

    const auto si(builder.make_special_includes(o));
    if (si.requires_stream_manipulators)
        builder.add(inclusion_constants::boost::io::ios_state());

    if (si.has_std_string)
        builder.add(inclusion_constants::boost::algorithm::string());

    if (si.has_ptree) {
        builder.add(inclusion_constants::std::sstream());
        builder.add(inclusion_constants::boost::algorithm::string());
    }

    if (si.has_variant)
        builder.add(inclusion_constants::boost::visitor::apply_visitor());

    const auto io_fn(formatters::io::traits::class_header_formatter_name());
    builder.add(o.transparent_associations(), io_fn);
    builder.add(o.opaque_associations(), io_fn);
    builder.add(o.parent(), io_fn);

    return builder.build();
}

properties::path_derivatives provider::provide_path_derivatives(
    const properties::path_derivatives_factory& f,
    const yarn::name& n) const {
    const auto r(f.make_cpp_implementation(n, formatter_name()));
    return r;
}

}

std::string class_implementation_formatter::static_formatter_name() {
    return traits::class_implementation_formatter_name();
}

std::string class_implementation_formatter::id() const {
    static auto r(ownership_hierarchy().formatter_name());
    return r;
}

dynamic::ownership_hierarchy
class_implementation_formatter::ownership_hierarchy() const {
    static dynamic::ownership_hierarchy
        r(formatters::traits::model_name(), traits::facet_name(),
            class_implementation_formatter::static_formatter_name(),
            formatters::traits::implementation_formatter_group_name());
    return r;
}

file_types class_implementation_formatter::file_type() const {
    return file_types::cpp_implementation;
}

properties::origin_types
class_implementation_formatter::formattable_origin_type() const {
    return properties::origin_types::external;
}

void class_implementation_formatter::register_inclusion_dependencies_provider(
    properties::registrar& rg) const {
    rg.register_provider(boost::make_shared<provider>());
}

dogen::formatters::file class_implementation_formatter::
format(const context& ctx, const yarn::object& o) const {
    assistant a(ctx, ownership_hierarchy(), file_type(), o.name().id());
    const auto r(class_implementation_formatter_stitch(a, o));
    return r;
}

} } } } }
