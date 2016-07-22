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
#include "dogen/quilt.cpp/types/properties/helper_properties.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/domain_type_helper_stitch.hpp"
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace test_data {

std::string domain_type_helper::id() const {
    static auto r(std::string("<") + traits::facet_name() + std::string(">") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string domain_type_helper::family() const {
    static std::string r("Default");
    return r;
}

std::list<std::string>
domain_type_helper::owning_formatters() const {
    static auto r(std::list<std::string> {
        test_data::traits::class_implementation_formatter_name()
    });
    return r;
}

std::list<std::string>
domain_type_helper::owning_facets() const {
    static auto r(std::list<std::string> {
        test_data::traits::facet_name()
    });
    return r;
}

bool domain_type_helper::requires_explicit_call() const {
    return false;
}

bool domain_type_helper::is_enabled(const assistant& a,
    const properties::helper_properties& hp) const {
    return a.is_streaming_enabled(hp);
}

std::string domain_type_helper::function_name() const {
    static std::string r("operator==");
    return r;
}

std::string domain_type_helper::helper_name() const {
    static std::string r("domain_type_helper");
    return r;
}

void domain_type_helper::
format(assistant& a, const properties::helper_properties& hp) const {
    const auto d(hp.current());
    const auto qn(d.name_tree_qualified());
    const auto ident(d.name_tree_identifiable());
    const bool is_pointer(false);
    const bool is_recursive(false);

    if (is_recursive) {
a.stream() << std::endl;
a.stream() << qn << (is_pointer ? "*" : "") << std::endl;
a.stream() << "create_" << ident << (is_pointer ? "_ptr" : "") << "(const unsigned int) {" << std::endl;
        if (is_pointer) {
a.stream() << "    return nullptr;" << std::endl;
        } else {
a.stream() << "    return " << qn << "();" << std::endl;
        }
a.stream() << "}" << std::endl;
    } else {
a.stream() << std::endl;
a.stream() << qn << (is_pointer ? "*" : "") << std::endl;
a.stream() << "create_" << ident << (is_pointer ? "_ptr" : "") << "(const unsigned int position) {" << std::endl;
a.stream() << "    return " << qn << "_generator::create" << (is_pointer ? "_ptr" : "") << "(position);" << std::endl;
a.stream() << "}" << std::endl;
    }
}

void domain_type_helper_stitch(
    nested_type_formatting_assistant& a,
    const properties::nested_type_info& t,
    const bool as_pointer) {
a.stream() << std::endl;
a.stream() << t.complete_name() << (as_pointer ? "*" : "") << std::endl;
a.stream() << "create_" << t.complete_identifiable_name() << (as_pointer ? "_ptr" : "") << "(const unsigned int position) {" << std::endl;
a.stream() << "    return " << t.complete_name() << "_generator::create" << (as_pointer ? "_ptr" : "") << "(position);" << std::endl;
a.stream() << "}" << std::endl;
}
} } } } }
