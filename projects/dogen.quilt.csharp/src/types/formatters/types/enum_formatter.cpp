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
#include "dogen/quilt.csharp/types/formatters/types/enum_formatter.hpp"
#include "dogen/quilt.csharp/types/formatters/assistant.hpp"
#include "dogen/quilt.csharp/types/formatters/types/traits.hpp"
#include "dogen/quilt.csharp/types/traits.hpp"
#include "dogen.formatters/types/sequence_formatter.hpp"
#include "dogen/yarn/types/helpers/meta_name_factory.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {
namespace types {

std::string enum_formatter::static_id() {
    return traits::enum_archetype();
}

std::string enum_formatter::id() const {
    return static_id();
}

annotations::archetype_location enum_formatter::archetype_location() const {
    static annotations::archetype_location
        r(csharp::traits::kernel(), csharp::traits::backend(),
          traits::facet(),
          enum_formatter::static_id());
    return r;
}

const yarn::meta_model::name& enum_formatter::meta_name() const {
    using yarn::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_enumeration_name());
    return r;
}

std::string enum_formatter::family() const {
    return csharp::traits::csharp_family();
}

boost::filesystem::path enum_formatter::full_path(
    const formattables::locator& l, const yarn::meta_model::name& n) const {
    return l.make_full_path(n, static_id());
}

std::list<std::string> enum_formatter::
inclusion_dependencies(const yarn::meta_model::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

yarn::meta_model::artefact enum_formatter::
format(const context& ctx, const yarn::meta_model::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), id);
    const auto& ye(a.as<yarn::meta_model::enumeration>(static_id(), e));
    {
        const auto sn(e.name().simple());
        const auto qn(a.get_qualified_name(e.name()));
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
a.stream() << "using System;" << std::endl;
a.stream() << std::endl;
            const auto ns(a.make_namespaces(e.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
            a.comment(e.documentation(), 1/*indent*/);
            if (ye.use_implementation_defined_underlying_element())
a.stream() << "    public enum " << sn << std::endl;
            else
a.stream() << "    public enum " << sn << " : " << a.get_qualified_name(ye.underlying_element()) << std::endl;
a.stream() << "    {" << std::endl;
            dogen::formatters::sequence_formatter sf(ye.enumerators().size());
            for (const auto& en : ye.enumerators()) {
                if (ye.use_implementation_defined_enumerator_values())
a.stream() << "        " << en.name().simple() << sf.postfix() << a.comment_inline(en.documentation()) << std::endl;
                else
a.stream() << "        " << en.name().simple() << " = " << en.value() << sf.postfix() << a.comment_inline(en.documentation()) << std::endl;
                sf.next();
            }
a.stream() << "    }" << std::endl;
        } // snf
    } // sbf
    return a.make_artefact();
}
} } } } }
