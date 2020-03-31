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
#include "dogen.physical/types/helpers/name_factory.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/test_data/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/test_data/enum_header_transform.hpp"

namespace dogen::m2t::cpp::transforms::test_data {

std::string enum_header_transform::static_id() {
    return traits::enum_header_archetype_qn();
}

std::string enum_header_transform::id() const {
    return static_id();
}

physical::entities::name
enum_header_transform::physical_name() const {
    using physical::helpers::name_factory;
    static auto r(name_factory::make(cpp::traits::backend_qn(),
        traits::facet_qn(), enum_header_transform::static_id()));
    return r;
}

const logical::entities::name& enum_header_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_enumeration_name());
    return r;
}

inclusion_support_types enum_header_transform::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path enum_header_transform::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path enum_header_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> enum_header_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {
    auto builder(f.make());

    builder.add(e.name(), types::traits::enum_header_archetype_qn());
    return builder.build();
}

physical::entities::artefact enum_header_transform::
apply(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, physical_name(), true/*requires_header_guard*/);
    const auto& ye(a.as<logical::entities::structural::enumeration>(e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(a.make_namespaces(ye.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
a.stream() << "class " << ye.name().simple() << "_generator {" << std::endl;
a.stream() << "public:" << std::endl;
a.stream() << "    " << ye.name().simple() << "_generator();" << std::endl;
a.stream() << std::endl;
a.stream() << "public:" << std::endl;
a.stream() << "    typedef " << a.get_qualified_name(ye.name()) << " result_type;" << std::endl;
a.stream() << std::endl;
a.stream() << "public:" << std::endl;
a.stream() << "    static void populate(const unsigned int position, result_type& v);" << std::endl;
a.stream() << "    static result_type create(const unsigned int position);" << std::endl;
a.stream() << "    result_type operator()();" << std::endl;
a.stream() << std::endl;
a.stream() << "private:" << std::endl;
a.stream() << "    unsigned int position_;" << std::endl;
a.stream() << "};" << std::endl;
a.stream() << std::endl;
         } // snf
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}

}
