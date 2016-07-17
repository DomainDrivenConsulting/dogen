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
#include "dogen/quilt.cpp/types/formatters/hash/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/time_duration_helper_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace hash {


std::string time_duration_helper::id() const {
    static auto r(std::string("<") + traits::facet_name() + std::string(">") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string time_duration_helper::family() const {
    static std::string r("AssociativeContainer");
    return r;
}

std::list<std::string>
time_duration_helper::owning_formatters() const {
    static auto r(std::list<std::string> {
        hash::traits::class_implementation_formatter_name()
    });
    return r;
}

std::list<std::string>
time_duration_helper::owning_facets() const {
    static auto r(std::list<std::string> {
        hash::traits::facet_name()
    });
    return r;
}

bool time_duration_helper::requires_explicit_call() const {
    return false;
}

std::string time_duration_helper::function_name() const {
    static std::string r("operator==");
    return r;
}

std::string time_duration_helper::helper_name() const {
    static std::string r("time_duration_helper");
    return r;
}

bool time_duration_helper::is_enabled(const assistant& /*a*/,
    const properties::helper_properties& /*hp*/) const {
    return true;
}

void time_duration_helper::
format(assistant& a, const properties::helper_properties& hp) const {
    const auto d(hp.current());
    const auto qn(d.name_tree_qualified());
    const auto ident(d.name_tree_identifiable());
    const auto key(hp.direct_descendants().front());
    const auto value(hp.direct_descendants().back());
a.stream() << std::endl;
a.stream() << "inline std::size_t hash_" << ident << "(const " << qn << "& v) {" << std::endl;
a.stream() << "    std::size_t seed(0);" << std::endl;
a.stream() << "    seed = static_cast<std::size_t>(v.total_seconds());" << std::endl;
a.stream() << "    return seed;" << std::endl;
a.stream() << "}" << std::endl;
}

void time_duration_helper_stitch(
    nested_type_formatting_assistant& a,
    const properties::nested_type_info& t) {
a.stream() << std::endl;
a.stream() << "inline std::size_t hash_" << t.complete_identifiable_name() << "(const " << t.complete_name() << "& v) {" << std::endl;
a.stream() << "    std::size_t seed(0);" << std::endl;
a.stream() << "    seed = static_cast<std::size_t>(v.total_seconds());" << std::endl;
a.stream() << "    return seed;" << std::endl;
a.stream() << "}" << std::endl;
}
} } } } }
