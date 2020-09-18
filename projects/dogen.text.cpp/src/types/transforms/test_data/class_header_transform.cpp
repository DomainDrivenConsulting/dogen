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
#include "dogen.utility/types/io/shared_ptr_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.physical/io/entities/artefact_io.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/transforms/test_data/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/test_data/class_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/test_data/class_header_factory.hpp"

namespace dogen::text::cpp::transforms::test_data {
namespace {

const std::string transform_id("text.cpp.transforms.test_data.class_header_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& class_header_transform::static_archetype() {
    static auto r(class_header_factory::make());
    return r;
}

const physical::entities::archetype& class_header_transform::archetype() const {
    return static_archetype();
}

inclusion_support_types class_header_transform::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path class_header_transform::inclusion_path(
    const formattables::locator& l, const identification::entities::logical_name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, archetype().meta_name().id().value());
}

boost::filesystem::path class_header_transform::full_path(
    const formattables::locator& l, const identification::entities::logical_name& n) const {
    return l.make_full_path_for_cpp_header(n, archetype().meta_name().id().value());
}

std::list<std::string> class_header_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {
    auto builder(f.make());
    builder.add(e.name(), types::traits::class_header_archetype_qn());
    return builder.build();
}

void class_header_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "class header",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    assistant ast(ctx, e, archetype().meta_name(), true/*requires_header_guard*/, a);
    const auto& o(ast.as<logical::entities::structural::object>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
            const auto sn(o.name().simple());
            const auto qn(ast.get_qualified_name(o.name()));
            const auto ns(ast.make_namespaces(o.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
ast.stream() << std::endl;
ast.stream() << "class " << sn << "_generator {" << std::endl;
            if (!o.is_parent()) {
ast.stream() << "public:" << std::endl;
ast.stream() << "    " << sn << "_generator();" << std::endl;
ast.stream() << std::endl;
            }
ast.stream() << "public:" << std::endl;
ast.stream() << "    typedef " << qn << " result_type;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "public:" << std::endl;
            if (!o.is_immutable())
ast.stream() << "    static void populate(const unsigned int position, result_type& v);" << std::endl;
            if (!o.is_parent()) {
ast.stream() << "    static result_type create(const unsigned int position);" << std::endl;
ast.stream() << "    result_type operator()();" << std::endl;
ast.stream() << std::endl;
ast.stream() << "private:" << std::endl;
ast.stream() << "    unsigned int position_;" << std::endl;
            }
ast.stream() << "public:" << std::endl;
ast.stream() << "    static result_type* create_ptr(const unsigned int position);" << std::endl;
ast.stream() << "};" << std::endl;
ast.stream() << std::endl;
        } // snf
ast.stream() << std::endl;
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}
}
