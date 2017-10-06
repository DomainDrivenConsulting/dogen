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
#include "dogen/quilt.cpp/types/formatters/types/exception_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/serialization/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/io/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/yarn/types/helpers/meta_name_factory.hpp"
#include "dogen/yarn/types/meta_model/exception.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace types {

std::string exception_header_formatter::static_artefact() {
    return traits::exception_header_archetype();
}

std::string exception_header_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location
exception_header_formatter::archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::facet(),
          exception_header_formatter::static_artefact());
    return r;
}

const yarn::meta_model::name& exception_header_formatter::meta_name() const {
    using yarn::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_exception_name());
    return r;
}

inclusion_support_types exception_header_formatter::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path exception_header_formatter::inclusion_path(
    const formattables::locator& l, const yarn::meta_model::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_artefact());
}

boost::filesystem::path exception_header_formatter::full_path(
    const formattables::locator& l, const yarn::meta_model::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_artefact());
}

std::list<std::string> exception_header_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const yarn::meta_model::element& /*e*/) const {
    auto builder(f.make());
    builder.add(inclusion_constants::std::string());
    builder.add(inclusion_constants::boost::exception::info());
    return builder.build();
}

dogen::formatters::artefact exception_header_formatter::
format(const context& ctx, const yarn::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), true/*requires_header_guard*/);
    const auto& ye(a.as<yarn::meta_model::exception>(e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(a.make_namespaces(ye.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
            a.comment(ye.documentation());
a.stream() << "class " << ye.name().simple() << " : public virtual std::exception, public virtual boost::exception {" << std::endl;
a.stream() << "public:" << std::endl;
            if (a.is_cpp_standard_98()) {
a.stream() << "    " << ye.name().simple() << "() {}" << std::endl;
a.stream() << "    ~" << ye.name().simple() << "() {}" << std::endl;
            } else {
a.stream() << "    " << ye.name().simple() << "() = default;" << std::endl;
a.stream() << "    ~" << ye.name().simple() << "()" << a.make_noexcept_keyword_text() << " = default;" << std::endl;
            }
a.stream() << std::endl;
a.stream() << "public:" << std::endl;
a.stream() << "    explicit " << ye.name().simple() << "(const std::string& message) : message_(message) { }" << std::endl;
a.stream() << std::endl;
a.stream() << "public:" << std::endl;
            if (a.is_cpp_standard_98()) {
                // Note: we are using BOOST_NOEXCEPT here by design. The problem is
                // users may include this header in a C++ 98 project or in a C++ > 11 project;
                // and we need to have different behaviours. Depending on this inclusion.
                // If we do not, we will cause compilation errors when including C++ 98 code
                // on a C++ 11 project. This is because the standard library will have noexcept
                // but we won't (as we were generated for C++ 98), so we'd be weakening the exception
                // guarantees. By using the boost macro we will do the right thing hopefully.
                // And since we already need boost for exception, we should be ok.
a.stream() << "    const char* what() const BOOST_NOEXCEPT { return(message_.c_str()); }" << std::endl;
            } else {
a.stream() << "    const char* what() const" << a.make_noexcept_keyword_text() << " { return(message_.c_str()); }" << std::endl;
            }
a.stream() << std::endl;
a.stream() << "private:" << std::endl;
a.stream() << "    const std::string message_;" << std::endl;
a.stream() << "};" << std::endl;
a.stream() << std::endl;
        } // snf
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}

} } } } }
