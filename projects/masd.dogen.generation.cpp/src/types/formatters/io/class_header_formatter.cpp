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
#include "masd.dogen.generation.cpp/types/formatters/io/class_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/assistant.hpp"
#include "masd.dogen.generation.cpp/types/formatters/inclusion_constants.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/io/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/traits.hpp"
#include "masd.dogen.generation.cpp/types/traits.hpp"
#include "masd.dogen.modeling/types/helpers/meta_name_factory.hpp"
#include "masd.dogen.modeling/types/meta_model/object.hpp"
#include "masd.dogen.formatting/types/sequence_formatter.hpp"

namespace dogen::generation::cpp::formatters::io {

std::string class_header_formatter::static_id() {
    return traits::class_header_archetype();
}

std::string class_header_formatter::id() const {
    return static_id();
}

annotations::archetype_location
class_header_formatter::archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::facet(),
          class_header_formatter::static_id());
    return r;
}

const modeling::meta_model::name& class_header_formatter::meta_name() const {
    using modeling::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_object_name());
    return r;
}

std::string class_header_formatter::family() const {
    return cpp::traits::header_family();
}

inclusion_support_types class_header_formatter::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path class_header_formatter::inclusion_path(
    const formattables::locator& l, const modeling::meta_model::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path class_header_formatter::full_path(
    const formattables::locator& l, const modeling::meta_model::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> class_header_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const modeling::meta_model::element& e) const {
    auto builder(f.make());
    builder.add(inclusion_constants::std::iosfwd());

    using traits = formatters::types::traits;
    builder.add(e.name(), traits::canonical_archetype());

    return builder.build();
}

modeling::meta_model::artefact class_header_formatter::
format(const context& ctx, const modeling::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& o(a.as<modeling::meta_model::object>(e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(a.make_namespaces(o.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
            const auto qn(a.get_qualified_name(o.name()));
a.stream() << std::endl;
a.stream() << "std::ostream&" << std::endl;
a.stream() << "operator<<(std::ostream& s," << std::endl;
a.stream() << "     const " << qn << "& v);" << std::endl;
a.stream() << std::endl;
        } // snf
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}
}
