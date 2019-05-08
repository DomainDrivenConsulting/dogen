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
#include "masd.dogen.generation.cpp/types/formatters/serialization/primitive_implementation_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/serialization/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/inclusion_constants.hpp"
#include "masd.dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "masd.dogen.generation.cpp/types/formatters/assistant.hpp"
#include "masd.dogen.generation.cpp/types/formatters/traits.hpp"
#include "masd.dogen.generation.cpp/types/traits.hpp"
#include "masd.dogen.coding/types/helpers/meta_name_factory.hpp"
#include "masd.dogen.coding/types/meta_model/structural/primitive.hpp"
#include "masd.dogen.utility/types/log/logger.hpp"
#include <boost/throw_exception.hpp>
#include "masd.dogen.generation/types/formatters/sequence_formatter.hpp"

namespace masd::dogen::generation::cpp::formatters::serialization {

std::string primitive_implementation_formatter::static_id() {
    return traits::primitive_implementation_archetype();
}

std::string primitive_implementation_formatter::id() const {
    return static_id();
}

archetypes::location
primitive_implementation_formatter::archetype_location() const {
    static archetypes::location
        r(cpp::traits::kernel(),  cpp::traits::backend(),
          traits::facet(),
          primitive_implementation_formatter::static_id());
    return r;
}

const coding::meta_model::name& primitive_implementation_formatter::meta_name() const {
    using coding::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_primitive_name());
    return r;
}

std::string primitive_implementation_formatter::family() const {
    return cpp::traits::implementation_family();
}

inclusion_support_types primitive_implementation_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path primitive_implementation_formatter::inclusion_path(
    const formattables::locator& /*l*/, const coding::meta_model::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(primitive_implementation_formatter::static_id()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path primitive_implementation_formatter::full_path(
    const formattables::locator& l, const coding::meta_model::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_id());
}

std::list<std::string>
primitive_implementation_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const coding::meta_model::element& e) const {
    using coding::meta_model::structural::primitive;
    const auto& p(assistant::as<primitive>(e));
    auto builder(f.make());

    const auto ph_fn(traits::primitive_header_archetype());
    builder.add(p.name(), ph_fn);

    using ic = inclusion_constants;
    builder.add(ic::boost::archive::text_iarchive());
    builder.add(ic::boost::archive::text_oarchive());
    builder.add(ic::boost::archive::binary_iarchive());
    builder.add(ic::boost::archive::binary_oarchive());
    builder.add(ic::boost::archive::polymorphic_iarchive());
    builder.add(ic::boost::archive::polymorphic_oarchive());

    // XML serialisation
    builder.add(ic::boost::serialization::nvp());
    builder.add(ic::boost::archive::xml_iarchive());
    builder.add(ic::boost::archive::xml_oarchive());

    const auto carch(traits::canonical_archetype());
    builder.add(p.value_attribute().parsed_type().current(), carch);

    return builder.build();
}

extraction::meta_model::artefact primitive_implementation_formatter::
format(const context& ctx, const coding::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& p(a.as<coding::meta_model::structural::primitive>(e));

    const auto sn(p.name().simple());
    const auto qn(a.get_qualified_name(p.name()));
    {
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        const auto attr(p.value_attribute());
a.stream() << std::endl;
a.stream() << "namespace boost {" << std::endl;
a.stream() << "namespace serialization {" << std::endl;

        /*
         * Save function
         */
a.stream() << std::endl;
a.stream() << "template<typename Archive>" << std::endl;
a.stream() << "void save(Archive& ar, const " << qn << "& v, const unsigned int /*version*/) {" << std::endl;
a.stream() << "    ar << make_nvp(\"" << attr.name().simple() << "\", v." << a.make_member_variable_name(attr) << ");" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        /*
         * Load function
         */
a.stream() << "template<typename Archive>" << std::endl;
a.stream() << "void load(Archive& ar, " << qn << "& v, const unsigned int /*version*/) {" << std::endl;
a.stream() << "    ar >> make_nvp(\"" << attr.name().simple() << "\", v." << a.make_member_variable_name(attr) << ");" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "} }" << std::endl;
a.stream() << std::endl;
a.stream() << "namespace boost {" << std::endl;
a.stream() << "namespace serialization {" << std::endl;
a.stream() << std::endl;
a.stream() << "template void save(archive::polymorphic_oarchive& ar, const " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << "template void load(archive::polymorphic_iarchive& ar, " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << std::endl;
a.stream() << "template void save(archive::text_oarchive& ar, const " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << "template void load(archive::text_iarchive& ar, " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << std::endl;
a.stream() << "template void save(archive::binary_oarchive& ar, const " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << "template void load(archive::binary_iarchive& ar, " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << std::endl;
a.stream() << "template void save(archive::xml_oarchive& ar, const " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << "template void load(archive::xml_iarchive& ar, " << qn << "& v, unsigned int version);" << std::endl;
a.stream() << std::endl;
a.stream() << "} }" << std::endl;
    } // sbf
    return a.make_artefact();
}

}
