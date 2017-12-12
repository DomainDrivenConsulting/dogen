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
#include "dogen.quilt.cpp/types/formatters/hash/date_helper.hpp"
#include "dogen.quilt.cpp/types/formattables/helper_properties.hpp"
#include "dogen.quilt.cpp/types/formatters/assistant.hpp"
#include "dogen.quilt.cpp/types/formatters/hash/traits.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace hash {

std::string date_helper::id() const {
    static auto r(std::string("<") + traits::facet() + std::string(">") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string date_helper::family() const {
    static std::string r("BoostDate");
    return r;
}

std::list<std::string>
date_helper::owning_formatters() const {
    static auto r(std::list<std::string> {
        traits::class_implementation_archetype(),
        traits::primitive_implementation_archetype()
    });
    return r;
}

std::list<std::string>
date_helper::owning_facets() const {
    static auto r(std::list<std::string> {
        traits::facet()
    });
    return r;
}

std::string date_helper::helper_name() const {
    static std::string r("date_helper");
    return r;
}

bool date_helper::is_enabled(const assistant& /*a*/,
    const formattables::helper_properties& /*hp*/) const {
    return true;
}

void date_helper::
format(assistant& a, const formattables::helper_properties& hp) const {
    const auto d(hp.current());
    const auto qn(d.name_tree_qualified());
    const auto ident(d.name_tree_identifiable());
a.stream() << std::endl;
a.stream() << "inline std::size_t hash_" << ident << "(const " << qn << "& v) {" << std::endl;
a.stream() << "    std::size_t seed(0);" << std::endl;
a.stream() << "    combine(seed, v.modjulian_day());" << std::endl;
a.stream() << "    return seed;" << std::endl;
a.stream() << "}" << std::endl;
}
} } } } }
