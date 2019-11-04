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
#include "dogen.generation/types/formatters/sequence_formatter.hpp"
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.assets/types/meta_model/structural/object.hpp"
#include "dogen.assets/types/helpers/meta_name_factory.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/traits.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "dogen.generation.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen.generation.cpp/types/formatters/serialization/traits.hpp"
#include "dogen.generation.cpp/types/formatters/serialization/class_implementation_formatter.hpp"

namespace dogen::generation::cpp::formatters::serialization {

std::string class_implementation_formatter::static_id() {
    return traits::class_implementation_archetype();
}

std::string class_implementation_formatter::id() const {
    return static_id();
}

archetypes::location
class_implementation_formatter::archetype_location() const {
    static archetypes::location
        r(cpp::traits::kernel(),  cpp::traits::backend(),
          traits::facet(),
          class_implementation_formatter::static_id());
    return r;
}

const assets::meta_model::name& class_implementation_formatter::meta_name() const {
    using assets::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_object_name());
    return r;
}

std::string class_implementation_formatter::family() const {
    return cpp::traits::implementation_family();
}

inclusion_support_types class_implementation_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path class_implementation_formatter::inclusion_path(
    const formattables::locator& /*l*/, const assets::meta_model::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(class_implementation_formatter::static_id()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path class_implementation_formatter::full_path(
    const formattables::locator& l, const assets::meta_model::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, static_id());
}

std::list<std::string> class_implementation_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const assets::meta_model::element& e) const {
    const auto& o(assistant::as<assets::meta_model::structural::object>(e));
    auto builder(f.make());

    const auto ch_fn(traits::class_header_archetype());
    builder.add(o.name(), ch_fn);

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
    builder.add(o.transparent_associations(), carch);
    builder.add(o.opaque_associations(), carch);
    builder.add(o.parents(), carch);
    builder.add(o.leaves(), carch);

    return builder.build();
}

extraction::meta_model::artefact class_implementation_formatter::
format(const context& ctx, const assets::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& o(a.as<assets::meta_model::structural::object>(e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        a.add_helper_methods(o.name().qualified().dot());

        const auto qn(a.get_qualified_name(o.name()));
        const bool has_attributes(!o.local_attributes().empty());
        const bool has_parent(!o.parents().empty());
        const bool has_attributes_or_parent(has_attributes || has_parent);

        if (o.is_parent() || !o.parents().empty()) {
a.stream() << std::endl;
a.stream() << "BOOST_CLASS_TRACKING(" << std::endl;
a.stream() << "    " << qn << "," << std::endl;
a.stream() << "    boost::serialization::track_selectively)" << std::endl;
        }
a.stream() << std::endl;
a.stream() << "namespace boost {" << std::endl;
a.stream() << "namespace serialization {" << std::endl;

        /*
         * Save function
         */
a.stream() << std::endl;
a.stream() << "template<typename Archive>" << std::endl;
a.stream() << "void save(Archive& " << (has_attributes_or_parent ? "ar" : "/*ar*/") << "," << std::endl;
a.stream() << "    const " << qn << "& " << (has_attributes_or_parent ? "v" : "/*v*/") << "," << std::endl;
a.stream() << "    const unsigned int /*version*/) {" << std::endl;
        if (!o.parents().empty()) {
            const auto& pn(o.parents().front());
            const auto pqn(a.get_qualified_name(pn));
a.stream() << "    ar << make_nvp(\"" << pn.simple() << "\", base_object<" << pqn << ">(v));" << std::endl;
        }

        if (has_attributes && has_parent)
a.stream() << std::endl;
        for (const auto attr : o.local_attributes()) {
a.stream() << "    ar << make_nvp(\"" << attr.name().simple() << "\", v." << a.make_member_variable_name(attr) << ");" << std::endl;
        }
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        /*
         * Load function
         */
a.stream() << "template<typename Archive>" << std::endl;
a.stream() << "void load(Archive& " << (has_attributes_or_parent ? "ar," : "/*ar*/,") << std::endl;
a.stream() << "    " << qn << "& " << (has_attributes_or_parent ? "v" : "/*v*/") << "," << std::endl;
a.stream() << "    const unsigned int /*version*/) {" << std::endl;
        if (!o.parents().empty()) {
            const auto& pn(o.parents().front());
            const auto pqn(a.get_qualified_name(pn));
a.stream() << "    ar >> make_nvp(\"" << pn.simple() << "\", base_object<" << pqn << ">(v));" << std::endl;
            if (has_attributes && has_parent)
a.stream() << std::endl;
        }

        for (const auto attr : o.local_attributes()) {
a.stream() << "    ar >> make_nvp(\"" << attr.name().simple() << "\", v." << a.make_member_variable_name(attr) << ");" << std::endl;
        }
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
