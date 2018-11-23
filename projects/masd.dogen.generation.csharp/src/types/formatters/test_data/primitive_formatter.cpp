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
#include "masd.dogen.generation.csharp/types/formatters/test_data/primitive_formatter.hpp"
#include "masd.dogen.generation.csharp/types/formatters/assistant.hpp"
#include "masd.dogen.generation.csharp/types/formatters/test_data/traits.hpp"
#include "masd.dogen.generation.csharp/types/traits.hpp"
#include "masd.dogen.extraction/types/sequence_formatter.hpp"
#include "masd.dogen.coding/types/helpers/meta_name_factory.hpp"
#include "masd.dogen.coding/types/meta_model/primitive.hpp"

namespace masd::dogen::generation::csharp::formatters::test_data {

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

coding::meta_model::artefact primitive_formatter::
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
a.stream() << "using System.Collections;" << std::endl;
a.stream() << "using System.Collections.Generic;" << std::endl;
a.stream() << std::endl;
            const auto ns(a.make_namespaces(e.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));

a.stream() << "    /// <summary>" << std::endl;
a.stream() << "    /// Generates sequences of " << sn << "." << std::endl;
a.stream() << "    /// </summary>" << std::endl;
a.stream() << "    public static class " << sn << "SequenceGenerator" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        static internal void Populate(" << sn << " value, uint position)" << std::endl;
a.stream() << "        {" << std::endl;
            const auto attr(p.value_attribute());
            const auto oap(a.get_assistant_properties(attr));
            if (oap && oap->requires_assistance()) {
a.stream() << "            value." << attr.name().simple() << " = AssistantSequenceGenerator.Create" << oap->method_postfix() << "(position);" << std::endl;
            } else {
                const auto attr_qn(a.get_qualified_name(attr.parsed_type().current()));
a.stream() << "            value." << attr.name().simple() << " = " << attr_qn << "SequenceGenerator.Create(position);" << std::endl;
            }
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        static internal " << sn << " Create(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            var result = new " << sn << "();" << std::endl;
a.stream() << "            Populate(result, position);" << std::endl;
a.stream() << "            return result;" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        #region Enumerator" << std::endl;
a.stream() << "        private class " << sn << "Enumerator : IEnumerator, IEnumerator<" << sn << ">, IDisposable" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            #region Properties" << std::endl;
a.stream() << "            private uint _position;" << std::endl;
a.stream() << "            private " << sn << " _current;" << std::endl;
a.stream() << "            #endregion" << std::endl;
a.stream() << std::endl;
a.stream() << "            private void PopulateCurrent()" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                _current = " << sn << "SequenceGenerator.Create(_position);" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            #region IDisposable" << std::endl;
a.stream() << "            public void Dispose()" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "            #endregion" << std::endl;
a.stream() << std::endl;
a.stream() << "            #region IEnumerator implementation" << std::endl;
a.stream() << "            public bool MoveNext()" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                ++_position;" << std::endl;
a.stream() << "                PopulateCurrent();" << std::endl;
a.stream() << "                return true;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            public void Reset()" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                _position = 0;" << std::endl;
a.stream() << "                PopulateCurrent();" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            public object Current {" << std::endl;
a.stream() << "                get" << std::endl;
a.stream() << "                {" << std::endl;
a.stream() << "                    return _current;" << std::endl;
a.stream() << "                }" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            " << sn << " IEnumerator<" << sn << ">.Current" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                get" << std::endl;
a.stream() << "                {" << std::endl;
a.stream() << "                    return _current;" << std::endl;
a.stream() << "                }" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "            #endregion" << std::endl;
a.stream() << std::endl;
a.stream() << "            public " << sn << "Enumerator()" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                PopulateCurrent();" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << "        #endregion" << std::endl;
a.stream() << std::endl;
a.stream() << "        #region Enumerable" << std::endl;
a.stream() << "        private class " << sn << "Enumerable : IEnumerable, IEnumerable<" << sn << ">" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            #region IEnumerable implementation" << std::endl;
a.stream() << "            public IEnumerator GetEnumerator()" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                return new " << sn << "Enumerator();" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            IEnumerator<" << sn << "> IEnumerable<" << sn << ">.GetEnumerator()" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                return new " << sn << "Enumerator();" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "            #endregion" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << "        #endregion" << std::endl;
a.stream() << std::endl;
a.stream() << "        static public IEnumerable<" << sn << "> Sequence()" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return new " << sn << "Enumerable();" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << "    }" << std::endl;
        }
    } // sbf
    return a.make_artefact();
}
}
