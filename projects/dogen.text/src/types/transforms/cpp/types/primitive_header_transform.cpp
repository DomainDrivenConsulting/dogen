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
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.text/types/formatters/assistant.hpp"
#include "dogen.text/types/transforms/cpp/types/primitive_header_transform.hpp"
#include "dogen.text/types/transforms/cpp/types/primitive_header_factory.hpp"

namespace dogen::text::transforms::cpp::types {
namespace {

const std::string transform_id("text.transforms.types.primitive_header_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& primitive_header_transform::static_archetype() {
    static auto r(primitive_header_factory::make());
    return r;
}

const physical::entities::archetype& primitive_header_transform::archetype() const {
    return static_archetype();
}

void primitive_header_transform::
apply(const text::transforms::context& ctx, const text::entities::model& lps,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "primitive header",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    text::formatters::assistant ast(lps, e, a, true/*requires_header_guard*/);
    const auto& p(ast.as<logical::entities::structural::primitive>(e));

    const auto sn(p.name().simple());
    const auto qn(ast.get_qualified_name(p.name()));
    {

        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(ast.make_namespaces(p.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
            const auto attr(p.value_attribute());

            ast.comment(p.documentation());
ast.stream() << "class " << sn << " final {" << std::endl;
ast.stream() << "public:" << std::endl;
            /*
             * Compiler generated constructors and destructors.
             */
            if (!ast.requires_manual_default_constructor())
ast.stream() << "    " << sn << "() = default;" << std::endl;
ast.stream() << "    " << sn << "(const " << sn << "&) = default;" << std::endl;
            if (!ast.requires_manual_move_constructor())
ast.stream() << "    " << sn << "(" << sn << "&&) = default;" << std::endl;
ast.stream() << "    ~" << sn << "() = default;" << std::endl;
            if (p.is_immutable())
ast.stream() << "    " << sn << "& operator=(const " << sn << "&) = delete;" << std::endl;
            /*
             * Manually generated default constructor.
             */
            if (ast.requires_manual_default_constructor()) {
ast.stream() << "public:" << std::endl;
ast.stream() << "    " << sn << "();" << std::endl;
ast.stream() << std::endl;
            }

            /*
             * Manually generated move constructor.
             */
            if (ast.requires_manual_move_constructor()) {
ast.stream() << "public:" << std::endl;
ast.stream() << "    " << sn << "(" << sn << "&& rhs);" << std::endl;
ast.stream() << std::endl;
            }

            /*
             * Manually generated complete constructor.
             */
ast.stream() << "public:" << std::endl;
ast.stream() << "    explicit " << sn << "(const " << ast.get_qualified_name(attr.parsed_type()) << ast.make_by_ref_text(attr) << " " << attr.name().simple() << ");" << std::endl;
ast.stream() << std::endl;
            /*
             * Serialisaton Friends
             */
            if (ast.is_serialization_enabled()) {
ast.stream() << "private:" << std::endl;
ast.stream() << "    template<typename Archive>" << std::endl;
ast.stream() << "    friend void boost::serialization::save(Archive& ar, const " << qn << "& v, unsigned int version);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    template<typename Archive>" << std::endl;
ast.stream() << "    friend void boost::serialization::load(Archive& ar, " << qn << "& v, unsigned int version);" << std::endl;
ast.stream() << std::endl;
            }

            /*
             * Getters and setters.
             */
ast.stream() << "public:" << std::endl;
            ast.comment_start_method_group(attr.documentation(), !attr.is_immutable());
            if (attr.parsed_type().is_current_simple_type()) {
ast.stream() << "    " << ast.get_qualified_name(attr.parsed_type()) << " " << attr.name().simple() << "() const;" << std::endl;
                if (attr.is_immutable()) {
ast.stream() << std::endl;

                } else {
ast.stream() << "    " << ast.make_setter_return_type(sn, attr) << " " << attr.name().simple() << "(const " << ast.get_qualified_name(attr.parsed_type()) << ast.make_by_ref_text(attr) << " v);" << std::endl;
                }
            } else {
ast.stream() << "    const " << ast.get_qualified_name(attr.parsed_type()) << "& " << attr.name().simple() << "() const;" << std::endl;
                if (attr.is_immutable()) {
ast.stream() << std::endl;
                } else {
ast.stream() << "    " << ast.get_qualified_name(attr.parsed_type()) << ast.make_by_ref_text(attr) << " " << attr.name().simple() << "();" << std::endl;
ast.stream() << "    " << ast.make_setter_return_type(sn, attr) << " " << attr.name().simple() << "(const " << ast.get_qualified_name(attr.parsed_type()) << ast.make_by_ref_text(attr) << " v);" << std::endl;
ast.stream() << "    " << ast.make_setter_return_type(sn, attr) << " " << attr.name().simple() << "(const " << ast.get_qualified_name(attr.parsed_type()) << "&& v);" << std::endl;
                }
            }
            ast.comment_end_method_group(attr.documentation(), !attr.is_immutable());

            /*
             * Explicit cast.
             */
ast.stream() << std::endl;
ast.stream() << "public:" << std::endl;
ast.stream() << "    explicit operator " << ast.get_qualified_name(attr.parsed_type()) << "() const {" << std::endl;
ast.stream() << "        return " << attr.member_variable_name() << ";" << std::endl;
ast.stream() << "    }" << std::endl;
            /*
             * Equality.
             */
ast.stream() << std::endl;
ast.stream() << "public:" << std::endl;
ast.stream() << "    bool operator==(const " << sn << "& rhs) const;" << std::endl;
ast.stream() << "    bool operator!=(const " << sn << "& rhs) const {" << std::endl;
ast.stream() << "        return !this->operator==(rhs);" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << std::endl;
            /*
             * Swap and assignment.
             */
ast.stream() << "public:" << std::endl;
ast.stream() << "    void swap(" << sn << "& other)" << ast.make_noexcept_keyword_text() << ";" << std::endl;
            if (!p.is_immutable()) {
ast.stream() << "    " << sn << "& operator=(" << sn << " other);" << std::endl;
            }

            /*
             * Member variables.
             */
ast.stream() << std::endl;
ast.stream() << "private:" << std::endl;
ast.stream() << "    " << ast.get_qualified_name(attr.parsed_type()) << " " << attr.member_variable_name() << ";" << std::endl;
ast.stream() << "};" << std::endl;
ast.stream() << std::endl;
        } // snf

        if (!p.is_immutable()) {
ast.stream() << std::endl;
ast.stream() << "namespace std {" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template<>" << std::endl;
ast.stream() << "inline void swap(" << std::endl;
ast.stream() << "    " << qn << "& lhs," << std::endl;
ast.stream() << "    " << qn << "& rhs) {" << std::endl;
ast.stream() << "    lhs.swap(rhs);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "}" << std::endl;
        }
ast.stream() << std::endl;
    } //ah  sbf
    ast.update_artefact();
    stp.end_transform(a);
}

}
