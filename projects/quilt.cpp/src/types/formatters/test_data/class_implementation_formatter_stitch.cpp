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
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/class_implementation_formatter_stitch.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace test_data {

dogen::formatters::file
class_implementation_formatter_stitch(assistant& a, const yarn::object& o) {

    {
        const auto sn(o.name().simple());
        const auto qn(a.get_qualified_name(o.name()));
        auto sbf(a.make_scoped_boilerplate_formatter());
        if (!o.local_attributes().empty()) {
a.stream() << "namespace {" << std::endl;
        a.add_helper_methods();
a.stream() << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        }

        {
            const auto ns(a.make_namespaces(o.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));

            /*
             * Default constructor.
             */
            if (!o.is_parent()) {
a.stream() << std::endl;
a.stream() << sn << "_generator::" << sn << "_generator() : position_(0) { }" << std::endl;
            }

            /*
             * Populate method.
             */
            if (!o.is_immutable()) {
                bool no_args(o.local_attributes().empty() && !o.parent());
                if (no_args) {
a.stream() << std::endl;
a.stream() << "void " << sn << "_generator::" << std::endl;
a.stream() << "populate(const unsigned int /*position*/, result_type& /*v*/) {" << std::endl;
                } else {
a.stream() << std::endl;
a.stream() << "void " << sn << "_generator::" << std::endl;
a.stream() << "populate(const unsigned int position, result_type& v) {" << std::endl;
                }

                if (o.parent()) {
                    const auto& pn(*o.parent());
                    const auto pqn(a.get_qualified_name(pn));
a.stream() << "    " << pqn << "_generator::populate(position, v);" << std::endl;
                }
                unsigned int i(0);
                for (const auto attr : o.local_attributes()) {
a.stream() << "    v." << attr.name().simple() << "(create_" << attr.parsed_type().identifiable() << "(position + " << i << "));" << std::endl;
                    ++i;
                }
a.stream() << "}" << std::endl;
            }

            /*
             * Create method.
             */
            if (!o.is_parent()) {
                 const bool no_arg(o.all_attributes().empty());
a.stream() << std::endl;
a.stream() << sn << "_generator::result_type" << std::endl;
a.stream() << sn << "_generator::create(const unsigned int" << (no_arg ? "/*position*/" : " position") << ") {" << std::endl;
                if (o.is_immutable()) {
a.stream() << "    return " << sn << "(" << std::endl;
                    // FIXME: hack
                    if (o.local_attributes().empty())
a.stream() << std::endl;
                    else {
                        dogen::formatters::sequence_formatter sf(o.local_attributes().size());
                        for (const auto attr : o.local_attributes()) {
a.stream() << "        create_" << attr.parsed_type().identifiable() << "(position + " << sf.current_position() << ")" << sf.postfix() << std::endl;
                            sf.next();
                        }
                    }
a.stream() << "        );" << std::endl;
                } else {
a.stream() << "    " << sn << " r;" << std::endl;
                    if (!o.all_attributes().empty())
a.stream() << "    " << sn << "_generator::populate(position, r);" << std::endl;
a.stream() << "    return r;" << std::endl;
                }
a.stream() << "}" << std::endl;
            }

            /*
             * Create method ptr.
             */
a.stream() << std::endl;
a.stream() << sn << "_generator::result_type*" << std::endl;
a.stream() << sn << "_generator::create_ptr(const unsigned int position) {" << std::endl;
            if (o.leaves().empty()) {
                if (o.is_immutable())
a.stream() << "    return new " << sn << "(create(position));" << std::endl;
                else {
a.stream() << "    " << sn << "* p = new " << sn << "();" << std::endl;
a.stream() << "    " << sn << "_generator::populate(position, *p);" << std::endl;
a.stream() << "    return p;" << std::endl;
                }
            } else {
                auto leaves(o.leaves());
                const auto front(leaves.front());
                leaves.pop_front();
                unsigned int i(0);
                unsigned int total(leaves.size());
                for (const auto& l : leaves) {
a.stream() << "    if ((position % " << total << ") == " << i++ << ")" << std::endl;
a.stream() << "        return " << a.get_qualified_name(l) << "_generator::create_ptr(position);" << std::endl;
                }
a.stream() << "    return " << a.get_qualified_name(front) << "_generator::create_ptr(position);" << std::endl;
            }
a.stream() << "}" << std::endl;
            /*
             * Function operator
             */
             if (!o.is_parent()) {
a.stream() << std::endl;
a.stream() << sn << "_generator::result_type" << std::endl;
a.stream() << sn << "_generator::operator()() {" << std::endl;
a.stream() << "    return create(position_++);" << std::endl;
a.stream() << "}" << std::endl;
            }
a.stream() << std::endl;
        } // snf
    } // sbf
    return a.make_file();
}
} } } } }
