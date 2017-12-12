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
#include "dogen.quilt.cpp/types/formatters/types/visitor_header_formatter.hpp"
#include "dogen.quilt.cpp/types/formatters/hash/traits.hpp"
#include "dogen.quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen.quilt.cpp/types/formatters/serialization/traits.hpp"
#include "dogen.quilt.cpp/types/formatters/io/traits.hpp"
#include "dogen.quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen.quilt.cpp/types/formatters/traits.hpp"
#include "dogen.quilt.cpp/types/traits.hpp"
#include "dogen.quilt.cpp/types/formatters/assistant.hpp"
#include "dogen.yarn/types/helpers/meta_name_factory.hpp"
#include "dogen.yarn/types/meta_model/visitor.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace types {

std::string visitor_header_formatter::static_id() {
    return traits::visitor_header_archetype();
}

std::string visitor_header_formatter::id() const {
    return static_id();
}

annotations::archetype_location
visitor_header_formatter::archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::facet(),
          visitor_header_formatter::static_id());
    return r;
}

const yarn::meta_model::name& visitor_header_formatter::meta_name() const {
    using yarn::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_visitor_name());
    return r;
}

std::string visitor_header_formatter::family() const {
    return cpp::traits::header_family();
}

inclusion_support_types visitor_header_formatter::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path visitor_header_formatter::inclusion_path(
    const formattables::locator& l, const yarn::meta_model::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path visitor_header_formatter::full_path(
    const formattables::locator& l, const yarn::meta_model::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> visitor_header_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const yarn::meta_model::element& e) const {
    using yarn::meta_model::visitor;
    const auto& v(assistant::as<visitor>(e));
    auto builder(f.make());
    builder.add(v.visits(), traits::forward_declarations_archetype());

    if (v.parent())
        builder.add(*v.parent(), traits::visitor_header_archetype());

    return builder.build();
}

yarn::meta_model::artefact visitor_header_formatter::
format(const context& ctx, const yarn::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), true/*requires_header_guard*/);
    const auto& v(a.as<yarn::meta_model::visitor>(e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(a.make_namespaces(v.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
            a.comment(v.documentation());
            if (!v.parent())
a.stream() << "class " << v.name().simple() << " {" << std::endl;
            else {
                const auto& pn(*v.parent());
                const auto pqn(a.get_qualified_name(pn));
a.stream() << "class " << v.name().simple() << " : public " << pqn << " {" << std::endl;
            }
a.stream() << "public:" << std::endl;
a.stream() << "    virtual ~" << v.name().simple() << "()" << a.make_noexcept_keyword_text() << " = 0;" << std::endl;
a.stream() << std::endl;
a.stream() << "public:" << std::endl;
            if (v.parent()) {
                const auto& pn(*v.parent());
                const auto pqn(a.get_qualified_name(pn));
a.stream() << "    using " << pqn << "::visit;" << std::endl;
a.stream() << std::endl;
            }

            bool is_first(true);
            for (const auto& t : v.visits()) {
                if (!is_first)
a.stream() << std::endl;
                const auto qn(a.get_qualified_name(t));
                const auto doc("Accept visits for type " + qn);
                a.comment_start_method_group(doc);
a.stream() << "    virtual void visit(const " << qn << "&) const { }" << std::endl;
a.stream() << "    virtual void visit(const " << qn << "&) { }" << std::endl;
a.stream() << "    virtual void visit(" << qn << "&) const { }" << std::endl;
a.stream() << "    virtual void visit(" << qn << "&) { }" << std::endl;
                a.comment_end_method_group(doc);
                is_first = false;
            }
a.stream() << "};" << std::endl;
a.stream() << std::endl;
a.stream() << "inline " << v.name().simple() << "::~" << v.name().simple() << "()" << a.make_noexcept_keyword_text() << " { }" << std::endl;
a.stream() << std::endl;
        } // snf
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}

} } } } }
