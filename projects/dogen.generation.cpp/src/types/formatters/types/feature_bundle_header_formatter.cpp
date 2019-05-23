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
#include "dogen.generation.cpp/types/formatters/types/feature_bundle_header_formatter.hpp"
#include "dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/io/inserter_implementation_helper.hpp"
#include "dogen.generation.cpp/types/formatters/io/traits.hpp"
#include "dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "dogen.generation.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/formatters/traits.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation/types/formatters/sequence_formatter.hpp"
#include "dogen.assets/types/helpers/meta_name_factory.hpp"
#include "dogen.assets/types/meta_model/variability/feature_bundle.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include <boost/throw_exception.hpp>

namespace dogen::generation::cpp::formatters::types {

std::string feature_bundle_header_formatter::static_id() {
    return traits::feature_bundle_header_archetype();
}

std::string feature_bundle_header_formatter::id() const {
    return static_id();
}

archetypes::location
feature_bundle_header_formatter::archetype_location() const {
    static archetypes::location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::facet(),
          feature_bundle_header_formatter::static_id());
    return r;
}

const assets::meta_model::name& feature_bundle_header_formatter::meta_name() const {
    using assets::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_variability_feature_bundle_name());
    return r;
}

std::string feature_bundle_header_formatter::family() const {
    return cpp::traits::header_family();
}

inclusion_support_types feature_bundle_header_formatter::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path feature_bundle_header_formatter::inclusion_path(
    const formattables::locator& l, const assets::meta_model::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path feature_bundle_header_formatter::full_path(
    const formattables::locator& l, const assets::meta_model::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> feature_bundle_header_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const assets::meta_model::element& /*e*/) const {
    using assets::meta_model::variability::feature_bundle;

    auto builder(f.make());

    builder.add(inclusion_constants::std::list());
    builder.add("\"dogen.variability/types/meta_model/feature_template.hpp\"");

    return builder.build();
}

extraction::meta_model::artefact feature_bundle_header_formatter::
format(const context& ctx, const assets::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& fb(a.as<assets::meta_model::variability::feature_bundle>(e));

    {
        const auto sn(fb.name().simple());
        const auto qn(a.get_qualified_name(fb.name()));
        auto sbf(a.make_scoped_boilerplate_formatter(fb));
        a.add_helper_methods(fb.name().qualified().dot());

        {
            const auto ns(a.make_namespaces(fb.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
           a.comment(fb.documentation());
a.stream() << "class " << sn << " final {" << std::endl;
a.stream() << "public:" << std::endl;
a.stream() << "    static std::list<dogen::variability::meta_model::feature_template>" << std::endl;
a.stream() << "    make_templates();" << std::endl;
a.stream() << "};" << std::endl;
a.stream() << std::endl;
        } // snf
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}
}
