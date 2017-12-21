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
#include "dogen.quilt.csharp/types/formatters/test_data/class_formatter.hpp"
#include "dogen.quilt.csharp/types/formatters/assistant.hpp"
#include "dogen.quilt.csharp/types/formatters/test_data/traits.hpp"
#include "dogen.quilt.csharp/types/traits.hpp"
#include "dogen.formatting/types/sequence_formatter.hpp"
#include "dogen.modeling/types/helpers/meta_name_factory.hpp"
#include "dogen.modeling/types/meta_model/object.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {
namespace test_data {

std::string class_formatter::static_id() {
    return traits::class_archetype();
}

std::string class_formatter::id() const {
    return static_id();
}

annotations::archetype_location class_formatter::archetype_location() const {
    static annotations::archetype_location
        r(csharp::traits::kernel(), csharp::traits::backend(),
          traits::facet(),
          class_formatter::static_id());
    return r;
}

const modeling::meta_model::name& class_formatter::meta_name() const {
    using modeling::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_object_name());
    return r;
}

std::string class_formatter::family() const {
    return csharp::traits::csharp_family();
}

boost::filesystem::path class_formatter::full_path(
    const formattables::locator& l, const modeling::meta_model::name& n) const {
    return l.make_full_path(n, static_id());
}

std::list<std::string> class_formatter::
inclusion_dependencies(const modeling::meta_model::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

modeling::meta_model::artefact class_formatter::format(
    const context& ctx, const modeling::meta_model::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), id);
    const auto& o(a.as<modeling::meta_model::object>(static_id(), e));
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
            const bool has_attributes(!o.all_attributes().empty());
            const bool is_parent_or_has_attributes(
                !o.parents().empty() || has_attributes);
a.stream() << "    /// <summary>" << std::endl;
a.stream() << "    /// Generates sequences of " << sn << "." << std::endl;
a.stream() << "    /// </summary>" << std::endl;
a.stream() << "    public static class " << sn << "SequenceGenerator" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        static internal void Populate(" << sn << " value, uint position)" << std::endl;
a.stream() << "        {" << std::endl;
                if (!is_parent_or_has_attributes) {
a.stream() << "            // nothing to populate" << std::endl;
                } else {
                    unsigned int count(0);
                    if (!o.parents().empty()) {
                        const auto& pn(o.parents().front());
                        const auto pqn(a.get_qualified_name(pn));
a.stream() << "            " << pqn << "SequenceGenerator.Populate(value, position);" << std::endl;
                    }

                    for (const auto& attr : o.local_attributes()) {
                        const auto oap(a.get_assistant_properties(attr));
                        if (oap && oap->requires_assistance()) {
a.stream() << "            value." << attr.name().simple() << " = AssistantSequenceGenerator.Create" << oap->method_postfix() << "(position + " << count++ << ");" << std::endl;
                        } else {
                            const auto attr_qn(a.get_qualified_name(attr.parsed_type().current()));
a.stream() << "            value." << attr.name().simple() << " = " << attr_qn << "SequenceGenerator.Create(position + " << count++ << ");" << std::endl;
                        }
                    }
                }
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        static internal " << sn << " Create(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
            if (!o.is_parent()) {
a.stream() << "            var result = new " << sn << "();" << std::endl;
                if (has_attributes) {
a.stream() << "            Populate(result, position);" << std::endl;
                }
a.stream() << "            return result;" << std::endl;
            } else {
                auto leaves(o.leaves());
                const auto front(leaves.front());
                leaves.pop_front();
                unsigned int i(0);
                unsigned int total(leaves.size());
                for (const auto& l : leaves) {
a.stream() << "            if ((position % " << total << ") == " << i++ << ")" << std::endl;
a.stream() << "                return " << a.get_qualified_name(l) << "SequenceGenerator.Create(position);" << std::endl;
                }
a.stream() << "            return " << a.get_qualified_name(front) << "SequenceGenerator.Create(position);" << std::endl;
            }
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
} } } } }
