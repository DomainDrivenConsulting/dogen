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
#include "dogen.generation.cpp/types/formatters/types/enum_header_formatter.hpp"
#include "dogen.generation.cpp/types/formatters/types/enum_header_formatter.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/traits.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation/types/formatters/sequence_formatter.hpp"
#include "dogen.coding/types/helpers/meta_name_factory.hpp"
#include "dogen.coding/types/meta_model/structural/enumeration.hpp"

namespace dogen::generation::cpp::formatters::types {

std::string enum_header_formatter::static_id() {
    return traits::enum_header_archetype();
}

std::string enum_header_formatter::id() const {
    return static_id();
}

archetypes::location
enum_header_formatter::archetype_location() const {
    static archetypes::location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::facet(),
          enum_header_formatter::static_id());
    return r;
}

const coding::meta_model::name& enum_header_formatter::meta_name() const {
    using coding::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_enumeration_name());
    return r;
}

std::string enum_header_formatter::family() const {
    return cpp::traits::header_family();
}

inclusion_support_types enum_header_formatter::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path enum_header_formatter::inclusion_path(
    const formattables::locator& l, const coding::meta_model::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path enum_header_formatter::full_path(
    const formattables::locator& l, const coding::meta_model::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> enum_header_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const coding::meta_model::element& e) const {

    using coding::meta_model::structural::enumeration;
    const auto& en(assistant::as<enumeration>(e));
    auto builder(f.make());
    const auto arch(traits::canonical_archetype());
    builder.add(en.underlying_element(), arch);
    return builder.build();
}

extraction::meta_model::artefact enum_header_formatter::
format(const context& ctx, const coding::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), true/*requires_header_guard*/);
    const auto& ye(a.as<coding::meta_model::structural::enumeration>(e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(a.make_namespaces(e.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
            a.comment(e.documentation());
            if (a.is_cpp_standard_98()) {
a.stream() << "enum " << ye.name().simple() << " {" << std::endl;
            } else {
                if (ye.use_implementation_defined_underlying_element())
a.stream() << "enum class " << ye.name().simple() << " {" << std::endl;
                else
a.stream() << "enum class " << ye.name().simple() << " : " << a.get_qualified_name(ye.underlying_element()) << " {" << std::endl;
            }

            generation::formatters::sequence_formatter sf(ye.enumerators().size());
            for (const auto& en : ye.enumerators()) {
                if (ye.use_implementation_defined_enumerator_values())
a.stream() << "    " << en.name().simple() << sf.postfix() << a.comment_inline(en.documentation()) << std::endl;
                else
a.stream() << "    " << en.name().simple() << " = " << en.value() << sf.postfix() << a.comment_inline(en.documentation()) << std::endl;
                sf.next();
            }
a.stream() << "};" << std::endl;
a.stream() << std::endl;
        } // snf
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}

}
