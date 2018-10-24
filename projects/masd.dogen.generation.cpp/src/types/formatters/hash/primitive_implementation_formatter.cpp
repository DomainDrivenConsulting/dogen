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
#include "masd.dogen.generation.cpp/types/formatters/hash/primitive_implementation_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/hash/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "masd.dogen.generation.cpp/types/formatters/inclusion_constants.hpp"
#include "masd.dogen.generation.cpp/types/formatters/traits.hpp"
#include "masd.dogen.generation.cpp/types/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/assistant.hpp"
#include "masd.dogen.formatting/types/sequence_formatter.hpp"
#include "masd.dogen.modeling/types/helpers/meta_name_factory.hpp"
#include "masd.dogen.modeling/types/meta_model/primitive.hpp"
#include "masd.dogen.utility/log/logger.hpp"
#include <boost/throw_exception.hpp>

namespace dogen::generation::cpp::formatters::hash {

std::string primitive_implementation_formatter::static_id() {
    return traits::primitive_implementation_archetype();
}

std::string primitive_implementation_formatter::id() const {
    return static_id();
}

annotations::archetype_location
primitive_implementation_formatter::archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::kernel(),  cpp::traits::backend(),
          traits::facet(),
          primitive_implementation_formatter::static_id());
    return r;
}

const modeling::meta_model::name& primitive_implementation_formatter::meta_name() const {
    using modeling::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_primitive_name());
    return r;
}

std::string primitive_implementation_formatter::family() const {
    return cpp::traits::implementation_family();
}

inclusion_support_types primitive_implementation_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path primitive_implementation_formatter::inclusion_path(
    const formattables::locator& /*l*/, const modeling::meta_model::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(primitive_implementation_formatter::static_id()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.id();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.id()));
}

boost::filesystem::path primitive_implementation_formatter::full_path(
    const formattables::locator& l, const modeling::meta_model::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_id());
}

std::list<std::string>
primitive_implementation_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const modeling::meta_model::element& e) const {

    using modeling::meta_model::primitive;
    const auto& p(assistant::as<primitive>(e));
    const auto carch(traits::canonical_archetype());
    auto builder(f.make());
    builder.add(p.name(), carch);

    return builder.build();
}

modeling::meta_model::artefact primitive_implementation_formatter::
format(const context& ctx, const modeling::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& p(a.as<modeling::meta_model::primitive>(e));

    const auto sn(p.name().simple());
    const auto qn(a.get_qualified_name(p.name()));
    {
        auto sbf(a.make_scoped_boilerplate_formatter(e));
a.stream() << std::endl;
a.stream() << "namespace {" << std::endl;
a.stream() << std::endl;
a.stream() << "template <typename HashableType>" << std::endl;
a.stream() << "inline void combine(std::size_t& seed, const HashableType& value) {" << std::endl;
a.stream() << "    std::hash<HashableType> hasher;" << std::endl;
a.stream() << "    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);" << std::endl;
a.stream() << "}" << std::endl;

        a.add_helper_methods(p.name().id());
a.stream() << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        {
            const auto ns(a.make_namespaces(p.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
            const auto sn(p.name().simple());
            const auto qn(a.get_qualified_name(p.name()));
            const auto attr(p.value_attribute());
a.stream() << std::endl;
a.stream() << "std::size_t " << sn << "_hasher::hash(const " << sn << "& v) {" << std::endl;
a.stream() << "    std::size_t seed(0);" << std::endl;
            if (a.requires_hashing_helper_method(attr))
a.stream() << "    combine(seed, hash_" << attr.parsed_type().identifiable() << "(v." << attr.name().simple() << "()));" << std::endl;
            else
a.stream() << "    combine(seed, v." << attr.name().simple() << "());" << std::endl;
a.stream() << "    return seed;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        } // snf
    } // sbf
    return a.make_artefact();
}
}
