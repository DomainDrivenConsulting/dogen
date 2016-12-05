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
#include "dogen/quilt.cpp/types/formatters/types/class_implementation_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/io/inserter_implementation_helper.hpp"
#include "dogen/quilt.cpp/types/formatters/io/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/formatting_error.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/utility/log/logger.hpp"
#include <boost/throw_exception.hpp>
#include <boost/make_shared.hpp>
#include <typeinfo>

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace types {

std::string class_implementation_formatter::static_artefact() {
    return traits::class_implementation_archetype();
}

std::string class_implementation_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location
class_implementation_formatter::archetype_location() const {
    static annotations::archetype_location
        r(formatters::traits::family(),  formatters::traits::kernel(),
          traits::facet(), class_implementation_formatter::static_artefact());
    return r;
}

std::type_index class_implementation_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(yarn::object)));
    return r;
}

inclusion_support_types class_implementation_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path class_implementation_formatter::inclusion_path(
    const formattables::locator& /*l*/, const yarn::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(class_implementation_formatter::static_artefact()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.id();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.id()));
}

boost::filesystem::path class_implementation_formatter::full_path(
    const formattables::locator& l, const yarn::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_artefact());
}

std::list<std::string> class_implementation_formatter::inclusion_dependencies(
    const formattables::inclusion_dependencies_builder_factory& f,
    const yarn::element& e) const {
    const auto& o(assistant::as<yarn::object>(static_artefact(), e));
    auto builder(f.make());

    const auto ch_arch(traits::class_header_archetype());
    builder.add(o.name(), ch_arch);
    builder.add(o.opaque_associations(), ch_arch);

    const auto io_arch(formatters::io::traits::class_header_archetype());
    const bool in_inheritance(o.is_parent() || o.is_child());
    const bool io_enabled(builder.is_enabled(o.name(), io_arch));
    const bool requires_io(io_enabled && in_inheritance);

    if (!requires_io)
        return builder.build();

    const auto os(inclusion_constants::std::ostream());
    builder.add(os);

    const auto si(builder.make_special_includes(o));
    if (si.requires_stream_manipulators)
        builder.add(inclusion_constants::boost::io::ios_state());

    if (si.has_std_string)
        builder.add(inclusion_constants::boost::algorithm::string());

    const auto io_carch(io::traits::canonical_archetype());
    builder.add(o.transparent_associations(), io_carch);
    builder.add(o.opaque_associations(), io_carch);
    builder.add(o.parent(), io_carch);

    if (o.is_visitation_leaf()) {
        /*
         * Only leaves have a visitation implementation. Note that we
         * don't bother including the base if we are already including
         * the derived visitor.
         */
        const auto v_arch(traits::visitor_header_archetype());
        if (o.derived_visitor())
            builder.add(*o.derived_visitor(), v_arch);
        else
            builder.add(*o.base_visitor(), v_arch);
    }

    return builder.build();
}

dogen::formatters::artefact class_implementation_formatter::
format(const context& ctx, const yarn::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), false/*requires_header_guard*/, id);
    const auto& o(a.as<yarn::object>(static_artefact(), e));

    {
        const auto sn(o.name().simple());
        const auto qn(a.get_qualified_name(o.name()));
        auto sbf(a.make_scoped_boilerplate_formatter());
        a.add_helper_methods(o.name().id());

        {
            const auto ns(a.make_namespaces(o.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));

            /*
             * Default constructor.
             */
            if (a.requires_manual_default_constructor()) {
a.stream() << std::endl;
a.stream() << sn << "::" << sn << "()" << std::endl;
                // FIXME: this was just too hard to hack with a sequence.
                // FIXME: indentation is all off too.
                std::ostringstream ss;
                bool is_first(true);
                for (const auto attr : o.local_attributes()) {
                    if (!attr.parsed_type().is_current_simple_type())
                        continue;

                    if (!is_first)
                        ss << "," << std::endl << "      ";

                    ss << a.make_member_variable_name(attr)
                       << "(static_cast<" << a.get_qualified_name(attr.parsed_type())
                       << ">(0))";

                    is_first = false;
                }
                ss << " { }";
                const std::string out(ss.str());
a.stream() << "    : " << out << std::endl;
            }

            /*
             * Move constructor.
             */
            if (a.requires_manual_move_constructor()) {
a.stream() << std::endl;
a.stream() << sn << "::" << sn << "(" << sn << "&& rhs)" << std::endl;
                unsigned int size((o.parent() ? 1 : 0) + o.local_attributes().size());

                dogen::formatters::sequence_formatter sf(size);
                sf.prefix_configuration().first(": ").not_first("  ");
                sf.postfix_configuration().last(" { }");
                if (o.parent()) {
                    const auto& pn(*o.parent());
                    const auto pqn(a.get_qualified_name(pn));
a.stream() << "    " << sf.prefix() << pqn << "(" << std::endl;
a.stream() << "        std::forward<" << pqn << ">(rhs))" << sf.postfix() << std::endl;
                    sf.next();
                }

                for (const auto attr : o.local_attributes()) {
a.stream() << "    " << sf.prefix() << a.make_member_variable_name(attr) << "(std::move(rhs." << a.make_member_variable_name(attr) << "))" << sf.postfix() << std::endl;
                    sf.next();
                }
            }

            /*
             * Complete constructor.
             */
            if (!o.all_attributes().empty()) {
                const auto attr_count(o.all_attributes().size());
                if (attr_count == 1) {
                     const auto attr(*o.all_attributes().begin());
a.stream() << std::endl;
a.stream() << sn << "::" << sn << "(const " << a.get_qualified_name(attr.parsed_type()) << a.make_by_ref_text(attr) << " " << attr.name().simple() << ")" << std::endl;
                } else {
a.stream() << std::endl;
a.stream() << sn << "::" << sn << "(" << std::endl;

                    dogen::formatters::sequence_formatter sf(attr_count);
                    sf.postfix_configuration().last(")");
                    for (const auto attr : o.all_attributes()) {
a.stream() << "    const " << a.get_qualified_name(attr.parsed_type()) << a.make_by_ref_text(attr) << " " << attr.name().simple() << sf.postfix() << std::endl;
                        sf.next();
                    }
                }

                int sequence_size(o.local_attributes().size() + (o.parent() ? 1 : 0));
                for (const auto pair : o.inherited_attributes()) {
                    const auto& pattrs(pair.second);
                    sequence_size += (pattrs.size() > 1 ? pattrs.size() : 0);
                }

                dogen::formatters::sequence_formatter sf(sequence_size);
                sf.postfix_configuration().last(" { }");
                sf.prefix_configuration().first(": ").not_first("  ");
                for (const auto pair : o.inherited_attributes()) {
                    const auto pqn(a.get_qualified_name(pair.first));
                    const auto& pattrs(pair.second);
                    if (pattrs.size() <= 1) {
a.stream() << "    " << sf.prefix() << pqn << "(" << (pattrs.empty() ? "" : pattrs.front().name().simple()) << ")" << sf.postfix() << std::endl;
                        sf.next();
                    } else {
a.stream() << "    " << sf.prefix() << pqn << "(" << sf.postfix(true/*skip*/) << std::endl;
                        sf.next();
                        dogen::formatters::sequence_formatter sf2(pattrs.size());
                        sf2.element_separator("");

                        sf2.prefix_configuration().first("  ").not_first("  ");
                        sf2.postfix_configuration().last(")");
                        for (const auto attr : pattrs) {
a.stream() << "    " << sf2.prefix() << attr.name().simple() << sf2.postfix() << sf.postfix() << std::endl;
                            sf2.next();
                            sf.next();
                        }
                    }
                }

                for (const auto attr : o.local_attributes()) {
a.stream() << "    " << sf.prefix() << a.make_member_variable_name(attr) << "(" << attr.name().simple() << ")" << sf.postfix() << std::endl;
                    sf.next();
                }
            }

            /*
             * Visitation.
             */
            if (o.is_visitation_leaf()) {
                std::string bvn;
                std::string dvn;
                std::string rpn;
                if (o.derived_visitor()) {
                    bvn = a.get_qualified_name(*o.base_visitor());
                    dvn = o.derived_visitor()->simple();
                    rpn = a.get_qualified_name(*o.root_parent());
                } else {
                    bvn = o.base_visitor()->simple();
                    rpn = o.root_parent()->simple();
                }
a.stream() << std::endl;
a.stream() << "void " << sn << "::accept(const " << bvn << "& v) const {" << std::endl;
                if (o.derived_visitor()) {
a.stream() << "    typedef const " << dvn << "* derived_ptr;" << std::endl;
a.stream() << "    const auto dv(dynamic_cast<derived_ptr>(&v));" << std::endl;
a.stream() << "    if (dv)" << std::endl;
a.stream() << "        dv->visit(*this);" << std::endl;
                } else {
a.stream() << "    v.visit(*this);" << std::endl;
                }
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "void " << sn << "::accept(" << bvn << "& v) const {" << std::endl;
                if (o.derived_visitor()) {
a.stream() << "    typedef " << dvn << "* derived_ptr;" << std::endl;
a.stream() << "    const auto dv(dynamic_cast<derived_ptr>(&v));" << std::endl;
a.stream() << "    if (dv)" << std::endl;
a.stream() << "        dv->visit(*this);" << std::endl;
                } else {
a.stream() << "    v.visit(*this);" << std::endl;
                }
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "void " << sn << "::accept(const " << bvn << "& v) {" << std::endl;
                if (o.derived_visitor()) {
a.stream() << "    typedef const " << dvn << "* derived_ptr;" << std::endl;
a.stream() << "    const auto dv(dynamic_cast<derived_ptr>(&v));" << std::endl;
a.stream() << "    if (dv)" << std::endl;
a.stream() << "        dv->visit(*this);" << std::endl;
                } else {
a.stream() << "    v.visit(*this);" << std::endl;
                }
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "void " << sn << "::accept(" << bvn << "& v) {" << std::endl;
                if (o.derived_visitor()) {
a.stream() << "    typedef " << dvn << "* derived_ptr;" << std::endl;
a.stream() << "    const auto dv(dynamic_cast<derived_ptr>(&v));" << std::endl;
a.stream() << "    if (dv)" << std::endl;
a.stream() << "        dv->visit(*this);" << std::endl;
                } else {
a.stream() << "    v.visit(*this);" << std::endl;
                }
a.stream() << "}" << std::endl;
a.stream() << std::endl;
            }

            /*
             * Streaming
             */
            if (a.is_io_enabled()) {
                if (o.in_inheritance_relationship()) {
a.stream() << std::endl;
a.stream() << "void " << sn << "::to_stream(std::ostream& s) const {" << std::endl;
                io::inserter_implementation_helper(a, o, true/*inside_class*/);
a.stream() << "}" << std::endl;
                }
            }

            /*
             * Swap
             */
            if (!o.is_immutable() && (!o.all_attributes().empty() || o.is_parent())) {
                const bool empty(o.all_attributes().empty() && !o.parent());
a.stream() << std::endl;
a.stream() << "void " << sn << "::swap(" << sn << "&" << (empty ? "" : " other") << ") noexcept {" << std::endl;
               if (o.parent()) {
                    const auto& pn(*o.parent());
a.stream() << "    " << pn.simple() << "::swap(other);" << std::endl;
a.stream() << std::endl;

               }

               if (!o.local_attributes().empty()) {
a.stream() << "    using std::swap;" << std::endl;
                   for (const auto attr : o.local_attributes())
a.stream() << "    swap(" << a.make_member_variable_name(attr) << ", other." << a.make_member_variable_name(attr) << ");" << std::endl;
               }
a.stream() << "}" << std::endl;
            }

            /*
             * Equals method
             */
            // FIXME: looking at root_parent as a hack due to service leafs not
            // FIXME: being processed atm.
            if (!o.is_parent() && o.parent() && o.root_parent()) {
                const auto rpn(*o.root_parent());
a.stream() << std::endl;
a.stream() << "bool " << sn << "::equals(const " << a.get_qualified_name(rpn) << "& other) const {" << std::endl;
a.stream() << "    const " << sn << "* const p(dynamic_cast<const " << sn << "* const>(&other));" << std::endl;
a.stream() << "    if (!p) return false;" << std::endl;
a.stream() << "    return *this == *p;" << std::endl;
a.stream() << "}" << std::endl;
            }

            /*
             * Equals operator
             */
            std::string method_name;
            if (o.is_parent())
                method_name = "compare";
            else
                method_name = "operator==";
a.stream() << std::endl;
a.stream() << "bool " << sn << "::" << method_name << "(const " << sn << "& " << (o.all_attributes().empty() ? "/*rhs*/" : "rhs") << ") const {" << std::endl;

            if (o.all_attributes().empty())
a.stream() << "    return true;" << std::endl;
            else {
                dogen::formatters::sequence_formatter sf(o.parent() ? 1 : 0);
                sf.element_separator("");
                sf.prefix_configuration().first("return ").not_first("    ");
                sf.postfix_configuration().not_last(" &&");
                if (o.local_attributes().empty())
                    sf.postfix_configuration().last(";");
                else
                    sf.postfix_configuration().last(" &&");

                if (o.parent()) {
                    const auto& pn(*o.parent());
a.stream() << "    " << sf.prefix() << pn.simple() << "::compare(rhs)" << sf.postfix() << std::endl;
                    sf.next();
                }
                sf.reset(o.local_attributes().size());
                sf.element_separator("");
                if (!o.parent())
                   sf.prefix_configuration().first("return ");
                else
                   sf.prefix_configuration().first("    ");
                sf.prefix_configuration().not_first("    ");
                sf.postfix_configuration().last(";").not_last(" &&");
                for (const auto attr : o.local_attributes()) {
a.stream() << "    " << sf.prefix() << a.make_member_variable_name(attr) << " == rhs." << a.make_member_variable_name(attr) << sf.postfix() << std::endl;
                    sf.next();
                }
            }
a.stream() << "}" << std::endl;

            /*
             * Assignment
             */
            if (!o.all_attributes().empty() && !o.is_parent() && !o.is_immutable()) {
a.stream() << std::endl;
a.stream() << sn << "& " << sn << "::operator=(" << sn << " other) {" << std::endl;
a.stream() << "    using std::swap;" << std::endl;
a.stream() << "    swap(*this, other);" << std::endl;
a.stream() << "    return *this;" << std::endl;
a.stream() << "}" << std::endl;
            }

            /*
             * Getters and setters
             */
             for (const auto attr : o.local_attributes()) {
                 if (attr.parsed_type().is_current_simple_type()) {
a.stream() << std::endl;
a.stream() << a.get_qualified_name(attr.parsed_type()) << " " << sn << "::" << attr.name().simple() << "() const {" << std::endl;
a.stream() << "    return " << a.make_member_variable_name(attr) << ";" << std::endl;
a.stream() << "}" << std::endl;
                    if (!o.is_immutable()) {
a.stream() << std::endl;
a.stream() << (attr.is_fluent() ? sn + "&" : "void") << " " << sn << "::" << attr.name().simple() << "(const " << a.get_qualified_name(attr.parsed_type()) << " v) {" << std::endl;
a.stream() << "    " << a.make_member_variable_name(attr) << " = v;" << std::endl;
                        if (attr.is_fluent()) {
a.stream() << "    return *this;" << std::endl;
                        }
a.stream() << "}" << std::endl;
                    }
                } else {
a.stream() << std::endl;
a.stream() << "const " << a.get_qualified_name(attr.parsed_type()) << "& " << sn << "::" << attr.name().simple() << "() const {" << std::endl;
a.stream() << "    return " << a.make_member_variable_name(attr) << ";" << std::endl;
a.stream() << "}" << std::endl;
                    if (!o.is_immutable()) {
a.stream() << std::endl;
a.stream() << a.get_qualified_name(attr.parsed_type()) << "& " << sn << "::" << attr.name().simple() << "() {" << std::endl;
a.stream() << "    return " << a.make_member_variable_name(attr) << ";" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << (o.is_fluent() ? sn + "&" : "void") << " " << sn << "::" << attr.name().simple() << "(const " << a.get_qualified_name(attr.parsed_type()) << "& v) {" << std::endl;
a.stream() << "    " << a.make_member_variable_name(attr) << " = v;" << std::endl;
                        if (o.is_fluent()) {
a.stream() << "    return *this;" << std::endl;
                        }
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << (o.is_fluent() ? sn + "&" : "void") << " " << sn << "::" << attr.name().simple() << "(const " << a.get_qualified_name(attr.parsed_type()) << "&& v) {" << std::endl;
a.stream() << "    " << a.make_member_variable_name(attr) << " = std::move(v);" << std::endl;
                        if (o.is_fluent()) {
a.stream() << "    return *this;" << std::endl;
                        }
a.stream() << "}" << std::endl;
                    }
                }
            }
a.stream() << std::endl;
        } // snf
    } // sbf
    return a.make_artefact();
}

} } } } }
