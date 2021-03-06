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
#include "dogen.logical/types/entities/helper_properties.hpp"
#include "dogen.text/types/transforms/cpp/hash/variant_helper_transform.hpp"

namespace dogen::text::transforms::cpp::hash {
std::string variant_helper_transform::id() const {
    static auto r(std::string("<masd.cpp.hash>") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string variant_helper_transform::family() const {
    static std::string r("BoostVariant");
    return r;
}

std::list<std::string>
variant_helper_transform::owning_formatters() const {
    static auto r(std::list<std::string> {
        "masd.cpp.hash.class_implementation",
        "masd.cpp.hash.primitive_implementation"
    });
    return r;
}

std::list<std::string>
variant_helper_transform::owning_facets() const {
    static auto r(std::list<std::string> {
        "masd.cpp.hash"
    });
    return r;
}

std::string variant_helper_transform::helper_name() const {
    static std::string r("variant_helper_transform");
    return r;
}

bool variant_helper_transform::is_enabled(
    const physical::entities::model& /*m*/,
    const logical::entities::element& /*e*/,
    const physical::entities::artefact& /*a*/,
    const logical::entities::helper_properties& /*hp*/) const {
    return true;
}

void variant_helper_transform::
apply(std::ostream& os, const logical::entities::model& /*m*/,
    const logical::entities::helper_properties& hp) const {
    const auto d(hp.current());
    const auto qn(d.name_tree_qualified());
    const auto ident(d.name_tree_identifiable());
    const auto key(hp.direct_descendants().front());
    const auto value(hp.direct_descendants().back());
os << std::endl;
os << "struct " << ident << "_visitor : public boost::static_visitor<> {" << std::endl;
os << "    " << ident << "_visitor() : hash(0) {}" << std::endl;
    for (const auto& dd : hp.direct_descendants()) {
os << "    void operator()(const " << dd.name_qualified() << (dd.is_simple_type() ? "" : "&") << " v) const {" << std::endl;
        if (!dd.requires_hashing_helper())
os << "        combine(hash, v);" << std::endl;
        else
os << "        combine(hash, hash_" << dd.name_tree_identifiable() << "(v));" << std::endl;
os << "    }" << std::endl;
os << std::endl;
    }
os << "    mutable std::size_t hash;" << std::endl;
os << "};" << std::endl;
os << std::endl;
os << "inline std::size_t hash_" << ident << "(const " << qn << "& v) {" << std::endl;
os << "    " << ident << "_visitor vis;" << std::endl;
os << "    boost::apply_visitor(vis, v);" << std::endl;
os << "    return vis.hash;" << std::endl;
os << "}" << std::endl;
}
}
