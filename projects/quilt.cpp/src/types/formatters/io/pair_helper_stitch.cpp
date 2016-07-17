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
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/io/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/io/pair_helper_stitch.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace io {

std::string pair_helper::id() const {
    static auto r(std::string("<") + traits::facet_name() + std::string(">") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string pair_helper::family() const {
    static std::string r("Pair");
    return r;
}

std::list<std::string> pair_helper::owning_formatters() const {
    static auto r(std::list<std::string> {
        io::traits::class_implementation_formatter_name(),
        types::traits::class_implementation_formatter_name()
    });
    return r;
}

std::list<std::string> pair_helper::owning_facets() const {
    static auto r(std::list<std::string> {
        io::traits::facet_name(),
        types::traits::facet_name()
    });
    return r;
}

bool pair_helper::requires_explicit_call() const {
    return false;
}

std::string pair_helper::function_name() const {
    static std::string r("operator==");
    return r;
}

std::string pair_helper::helper_name() const {
    static std::string r("pair_helper");
    return r;
}

bool pair_helper::is_enabled(const assistant& a,
    const properties::helper_properties& hp) const {
    return a.is_streaming_enabled(hp);
}

void pair_helper::
format(assistant& a, const properties::helper_properties& hp) const {
    {
        const auto d(hp.current());
        const auto nt_qn(d.name_tree_qualified());
        const auto n_qn(d.name_qualified());
        auto snf(a.make_scoped_namespace_formatter(d.namespaces()));
        const auto first(hp.direct_descendants().front());
        const auto second(hp.direct_descendants().back());
a.stream() << std::endl;
a.stream() << "inline std::ostream& operator<<(std::ostream& s, const " << nt_qn << "& v) {" << std::endl;
a.stream() << "    s << \"{ \" << \"\\\"__type__\\\": \" << \"\\\"" << n_qn << "\\\"\" << \", \";" << std::endl;
a.stream() << std::endl;
a.stream() << "    s << \"\\\"first\\\": \" << " << a.streaming_for_type(first, "v.first") << " << \", \";" << std::endl;
a.stream() << "    s << \"\\\"second\\\": \" << " << a.streaming_for_type(second, "v.second") << ";" << std::endl;
a.stream() << "    s << \" }\";" << std::endl;
a.stream() << "    return s;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
    }
a.stream() << std::endl;
}
} } } } }
