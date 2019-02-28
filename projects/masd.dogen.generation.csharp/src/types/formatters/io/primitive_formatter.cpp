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
#include "masd.dogen.generation.csharp/types/formatters/io/primitive_formatter.hpp"
#include "masd.dogen.generation.csharp/types/formatters/assistant.hpp"
#include "masd.dogen.generation.csharp/types/formatters/io/traits.hpp"
#include "masd.dogen.generation.csharp/types/traits.hpp"
#include "masd.dogen.extraction/types/sequence_formatter.hpp"
#include "masd.dogen.coding/types/helpers/meta_name_factory.hpp"
#include "masd.dogen.coding/types/meta_model/primitive.hpp"

namespace masd::dogen::generation::csharp::formatters::io {

std::string primitive_formatter::static_id() {
    return traits::primitive_archetype();
}

std::string primitive_formatter::id() const {
    return static_id();
}

annotations::archetype_location primitive_formatter::archetype_location() const {
    static annotations::archetype_location
        r(csharp::traits::kernel(), csharp::traits::backend(),
          traits::facet(),
          primitive_formatter::static_id());
    return r;
}

const coding::meta_model::name& primitive_formatter::meta_name() const {
    using coding::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_primitive_name());
    return r;
}

std::string primitive_formatter::family() const {
    return csharp::traits::csharp_family();
}

boost::filesystem::path primitive_formatter::full_path(
    const formattables::locator& l, const coding::meta_model::name& n) const {
    return l.make_full_path(n, static_id());
}

std::list<std::string> primitive_formatter::
inclusion_dependencies(const coding::meta_model::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

extraction::meta_model::artefact primitive_formatter::
format(const context& ctx, const coding::meta_model::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), id);
    const auto& p(a.as<coding::meta_model::primitive>(static_id(), e));
    {
        const auto sn(e.name().simple());
        const auto qn(a.get_qualified_name(e.name()));
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
a.stream() << "using System;" << std::endl;
a.stream() << std::endl;
            const auto ns(a.make_namespaces(e.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << "    /// <summary>" << std::endl;
a.stream() << "    /// Generates sequences of " << sn << "." << std::endl;
a.stream() << "    /// </summary>" << std::endl;
a.stream() << "    public static class " << sn << "Dumper" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        static internal void Dump(AssistantDumper assistant, " << sn << " value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            assistant.IncrementDepth();" << std::endl;
a.stream() << "            if (assistant.MaximumDepthExceeded())" << std::endl;
a.stream() << "                return;" << std::endl;
a.stream() << std::endl;
a.stream() << "            assistant.AddStartObject();" << std::endl;
a.stream() << "            assistant.AddType(\"" << qn << "\", true/*withSeparator*/);" << std::endl;
a.stream() << "            if (value == null)" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                assistant.Add(\"data\", \"<null>\");" << std::endl;
a.stream() << "                assistant.AddEndObject();" << std::endl;
a.stream() << "                return;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            assistant.AddKey(\"data\");" << std::endl;
a.stream() << "            assistant.AddPairSeparator();" << std::endl;
a.stream() << "            assistant.AddStartObject();" << std::endl;
            const auto attr(p.value_attribute());
            const auto oap(a.get_assistant_properties(attr));
            if (oap && oap->requires_assistance()) {
a.stream() << "            assistant.Add(\"" << attr.name().simple() << "\", value." << attr.name().simple() << ");" << std::endl;
            } else {
                const auto attr_qn(a.get_qualified_name(attr.parsed_type().current()));
a.stream() << "            assistant.AddKey(\"" << attr.name().simple() << "\");" << std::endl;
a.stream() << "            assistant.AddPairSeparator();" << std::endl;
a.stream() << "            " << attr_qn << "Dumper.Dump(assistant, value." << attr.name().simple() << ";" << std::endl;
            }
a.stream() << "            assistant.AddEndObject(); // data" << std::endl;
a.stream() << "            assistant.AddEndObject(); // main object" << std::endl;
a.stream() << "            assistant.HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << std::endl;
a.stream() << "            assistant.DecrementDepth();" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static string Dump(" << sn << " value)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            var assistant = new AssistantDumper();" << std::endl;
a.stream() << "            Dump(assistant, value);" << std::endl;
a.stream() << "            return assistant.ToString();" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << "    }" << std::endl;
        }
    } // sbf
    return a.make_artefact();
}
}
