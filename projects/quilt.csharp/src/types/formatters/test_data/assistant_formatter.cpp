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
#include "dogen/quilt.csharp/types/formatters/test_data/assistant_formatter.hpp"
#include "dogen/quilt.csharp/types/formatters/assistant.hpp"
#include "dogen/quilt.csharp/types/formatters/test_data/traits.hpp"
#include "dogen/quilt.csharp/types/fabric/meta_name_factory.hpp"
#include "dogen/quilt.csharp/types/fabric/assistant.hpp"
#include "dogen/quilt.csharp/types/traits.hpp"
#include "dogen/formatters/types/sequence_formatter.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {
namespace test_data {

std::string assistant_formatter::static_artefact() {
    return traits::assistant_archetype();
}

std::string assistant_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location assistant_formatter::archetype_location() const {
    static annotations::archetype_location
        r(csharp::traits::kernel(), csharp::traits::backend(),
          traits::facet(),
          assistant_formatter::static_artefact());
    return r;
}

const yarn::meta_model::name& assistant_formatter::meta_name() const {
    using fabric::meta_name_factory;
    static auto r(meta_name_factory::make_assistant_name());
    return r;
}

boost::filesystem::path assistant_formatter::full_path(
    const formattables::locator& l, const yarn::meta_model::name& n) const {
    return l.make_full_path(n, static_artefact());
}

std::list<std::string> assistant_formatter::
inclusion_dependencies(const yarn::meta_model::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

dogen::formatters::artefact assistant_formatter::format(
    const context& ctx, const yarn::meta_model::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), id);
    {
        const auto sn(e.name().simple());
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
a.stream() << "using System;" << std::endl;
a.stream() << "using System.Collections;" << std::endl;
a.stream() << "using System.Collections.Specialized;" << std::endl;
a.stream() << std::endl;
            const auto ns(a.make_namespaces(e.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << "    /// <summary>" << std::endl;
a.stream() << "    /// Provides helper methods for the sequence generators." << std::endl;
a.stream() << "    /// </summary>" << std::endl;
a.stream() << "    static class " << sn << "SequenceGenerator" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        private const int SequenceSize = 10;" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static object CreateObject(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return \"this is an object: \" + Convert.ToString(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static string CreateString(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return \"this is a string: \" + Convert.ToString(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static byte CreateByte(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return Convert.ToByte(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static sbyte CreateShortByte(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return Convert.ToSByte(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static int CreateInt(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return Convert.ToInt32(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static uint CreateUInt(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return position;" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static short CreateShort(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return Convert.ToInt16(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static ushort CreateUShort(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return Convert.ToUInt16(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static long CreateLong(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return Convert.ToInt64(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static ulong CreateULong(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return Convert.ToUInt64(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static float CreateFloat(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return Convert.ToSingle(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static double CreateDouble(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return Convert.ToDouble(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static char CreateChar(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return Convert.ToChar(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static bool CreateBool(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return position % 2 == 0;" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static decimal CreateDecimal(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return Convert.ToDecimal(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static IEnumerable CreateIEnumerable(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return CreateArrayList(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static ICollection CreateICollection(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return CreateArrayList(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static IList CreateIList(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return CreateArrayList(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static ArrayList CreateArrayList(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            var result = new ArrayList();" << std::endl;
a.stream() << "            for (uint i = 0; i < SequenceSize; i++)" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                switch((position + i) % 5)" << std::endl;
a.stream() << "                {" << std::endl;
a.stream() << "                case 0: result.Add(CreateString(position + i)); break;" << std::endl;
a.stream() << "                case 1: result.Add(CreateByte(position + i)); break;" << std::endl;
a.stream() << "                case 2: result.Add(CreateInt(position + i)); break;" << std::endl;
a.stream() << "                case 3: result.Add(CreateLong(position + i)); break;" << std::endl;
a.stream() << "                case 4: result.Add(CreateFloat(position + i)); break;" << std::endl;
a.stream() << "                case 5: result.Add(CreateDecimal(position + i)); break;" << std::endl;
a.stream() << "                default: result.Add(CreateBool(position + i)); break;" << std::endl;
a.stream() << "                }" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "            return result;" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static IDictionary CreateIDictionary(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return CreateHashtable(position);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static Hashtable CreateHashtable(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            var result = new Hashtable();" << std::endl;
a.stream() << "            for (uint i = 0; i < SequenceSize; i++)" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                result.Add(\"key_\" + position + i, \"value_\" + position + i);" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "            return result;" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static HybridDictionary CreateHybridDictionary(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            var result = new HybridDictionary();" << std::endl;
a.stream() << "            for (uint i = 0; i < SequenceSize; i++)" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                result.Add(\"key_\" + position + i, \"value_\" + position + i);" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "            return result;" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static NameValueCollection CreateNameValueCollection(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            var result = new NameValueCollection();" << std::endl;
a.stream() << "            for (uint i = 0; i < SequenceSize; i++)" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                result.Add(\"key_\" + position + i, \"value_\" + position + i);" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "            return result;" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static BitArray CreateBitArray(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            var result = new BitArray(SequenceSize);" << std::endl;
a.stream() << "            for (int i = 0; i < SequenceSize; i++)" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                result[i] = position % 2 == 0;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "            return result;" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static Queue CreateQueue(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            var result = new Queue();" << std::endl;
a.stream() << "            for (int i = 0; i < SequenceSize; i++)" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                result.Enqueue(\"value_\" + position + i);" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "            return result;" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static Stack CreateStack(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            var result = new Stack();" << std::endl;
a.stream() << "            for (int i = 0; i < SequenceSize; i++)" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                result.Push(\"value_\" + position + i);" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "            return result;" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static SortedList CreateSortedList(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            var result = new SortedList();" << std::endl;
a.stream() << "            for (int i = 0; i < SequenceSize; i++)" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                result.Add(\"key_\" + position + i, \"value_\" + position + i);" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "            return result;" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << "    }" << std::endl;
        }
    } // sbf
    return a.make_artefact();
}
} } } } }
