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
#include "dogen/quilt.cpp/types/formattables/helper_properties.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/io/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/io/associative_container_helper.hpp"
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace io {

std::string associative_container_helper::id() const {
    static auto r(std::string("<") + traits::facet() + std::string(">") +
        std::string("<") + helper_name() + std::string(">"));
    return r;
}

std::string associative_container_helper::family() const {
    static std::string r("AssociativeContainer");
    return r;
}

std::list<std::string>
associative_container_helper::owning_formatters() const {
    static auto r(std::list<std::string> {
        io::traits::class_implementation_archetype(),
        io::traits::primitive_implementation_archetype(),
        types::traits::class_implementation_archetype(),
        types::traits::primitive_implementation_archetype()
    });
    return r;
}

std::list<std::string>
associative_container_helper::owning_facets() const {
    static auto r(std::list<std::string> {
        io::traits::facet(), types::traits::facet()
    });
    return r;
}

std::string associative_container_helper::helper_name() const {
    static std::string r("associative_container_helper");
    return r;
}

bool associative_container_helper::is_enabled(const assistant& a,
    const formattables::helper_properties& hp) const {
    return a.is_streaming_enabled(hp);
}

void associative_container_helper::
format(assistant& a, const formattables::helper_properties& hp) const {
    {
        const auto d(hp.current());
        const auto qn(d.name_tree_qualified());
        auto snf(a.make_scoped_namespace_formatter(d.namespaces()));

        if (hp.direct_descendants().size() == 2) {
            const auto key(hp.direct_descendants().front());
            const auto value(hp.direct_descendants().back());
a.stream() << std::endl;
a.stream() << "inline std::ostream& operator<<(std::ostream& s, const " << qn << "& v) {" << std::endl;
a.stream() << "    s << \"[\";" << std::endl;
a.stream() << "    for (auto i(v.begin()); i != v.end(); ++i) {" << std::endl;
a.stream() << "        if (i != v.begin()) s << \", \";" << std::endl;
a.stream() << "        s << \"[ { \" << \"\\\"__type__\\\": \" << \"\\\"key\\\"\" << \", \" << \"\\\"data\\\": \";" << std::endl;
a.stream() << "        s << " << a.streaming_for_type(key, "i->first") << ";" << std::endl;
a.stream() << "        s << \" }, { \" << \"\\\"__type__\\\": \" << \"\\\"value\\\"\" << \", \" << \"\\\"data\\\": \";" << std::endl;
a.stream() << "        s << " << a.streaming_for_type(value, "i->second") << ";" << std::endl;
a.stream() << "        s << \" } ]\";" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << "    s << \" ] \";" << std::endl;
a.stream() << "    return s;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        } else {
        const auto containee(hp.direct_descendants().front());
a.stream() << std::endl;
a.stream() << "inline std::ostream& operator<<(std::ostream& s, const " << qn << "& v) {" << std::endl;
a.stream() << "    s << \"[ \";" << std::endl;
a.stream() << "    for (auto i(v.begin()); i != v.end(); ++i) {" << std::endl;
a.stream() << "        if (i != v.begin()) s << \", \";" << std::endl;
a.stream() << "        s << " << a.streaming_for_type(containee, "*i") << ";" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << "    s << \"] \";" << std::endl;
a.stream() << "    return s;" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        }
    }
a.stream() << std::endl;
}
} } } } }
