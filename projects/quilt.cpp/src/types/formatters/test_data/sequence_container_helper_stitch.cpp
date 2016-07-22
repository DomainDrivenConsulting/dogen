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
#include "dogen/quilt.cpp/types/formatters/test_data/sequence_container_helper_stitch.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace test_data {

std::string sequence_container_helper::id() const {
    static auto r(std::string("<") + traits::facet_name() + std::string(">") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string sequence_container_helper::family() const {
    static std::string r("SequenceContainer");
    return r;
}

std::list<std::string>
sequence_container_helper::owning_formatters() const {
    static auto r(std::list<std::string> {
        test_data::traits::class_implementation_formatter_name()
    });
    return r;
}

std::list<std::string>
sequence_container_helper::owning_facets() const {
    static auto r(std::list<std::string> {
        test_data::traits::facet_name()
    });
    return r;
}

bool sequence_container_helper::requires_explicit_call() const {
    return false;
}

bool sequence_container_helper::is_enabled(const assistant& /*a*/,
    const properties::helper_properties& /*hp*/) const {
    return true;
}

std::string sequence_container_helper::function_name() const {
    static std::string r("operator==");
    return r;
}

std::string sequence_container_helper::helper_name() const {
    static std::string r("sequence_container_helper");
    return r;
}

void sequence_container_helper::
format(assistant& a, const properties::helper_properties& hp) const {
    const auto d(hp.current());
    const auto qn(d.name_tree_qualified());
    const auto ident(d.name_tree_identifiable());
    const auto containee(hp.direct_descendants().front());
a.stream() << std::endl;
a.stream() << qn << " create_" << ident << "(unsigned int position) {" << std::endl;
a.stream() << "    " << qn << " r;" << std::endl;
a.stream() << "    for (unsigned int i(0); i < 4; ++i) {" << std::endl;
a.stream() << "        r.push_back(create_" << containee.name_tree_identifiable() << "(position + i));" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << "    return r;" << std::endl;
a.stream() << "}" << std::endl;
}

void sequence_container_helper_stitch(
    nested_type_formatting_assistant& a,
    const properties::nested_type_info& t) {

    const auto containee(t.children().front());
a.stream() << std::endl;
a.stream() << t.complete_name() << " create_" << t.complete_identifiable_name() << "(unsigned int position) {" << std::endl;
a.stream() << "    " << t.complete_name() << " r;" << std::endl;
a.stream() << "    for (unsigned int i(0); i < 4; ++i) {" << std::endl;
a.stream() << "        r.push_back(create_" << containee.complete_identifiable_name() << "(position + i));" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << "    return r;" << std::endl;
a.stream() << "}" << std::endl;
}
} } } } }
