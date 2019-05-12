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
#include "masd.dogen.variability/types/helpers/value_factory.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/features.hpp"

namespace masd::dogen::generation::cpp::formatters::test_data {

masd::dogen::variability::meta_model::feature_template
make_masd_generation_cpp_test_data_directory() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("directory");
    r.name().qualified("masd.generation.cpp.test_data.directory");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    masd::dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "test_data" }));

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_generation_cpp_test_data_postfix() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.test_data.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    masd::dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "td" }));

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_generation_cpp_test_data_class_header_postfix() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.test_data.class_header.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    masd::dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_generation_cpp_test_data_class_implementation_postfix() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.test_data.class_implementation.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    masd::dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_generation_cpp_test_data_enum_header_postfix() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.test_data.enum_header.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    masd::dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_generation_cpp_test_data_enum_implementation_postfix() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.test_data.enum_implementation.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    masd::dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_generation_cpp_test_data_primitive_header_postfix() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.test_data.primitive_header.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    masd::dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_generation_cpp_test_data_primitive_implementation_postfix() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.test_data.primitive_implementation.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    masd::dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_generation_cpp_test_data_master_header_postfix() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.test_data.master_header.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    masd::dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

masd::dogen::variability::meta_model::feature_template
make_masd_generation_cpp_test_data_builtin_header_postfix() {
    using namespace masd::dogen::variability::meta_model;
    feature_template r;
    r.name().simple("postfix");
    r.name().qualified("masd.generation.cpp.test_data.builtin_header.postfix");
    const auto vt(value_type::text);
    r.value_type(vt);
    r.binding_point(binding_point::global);
    r.kind(template_kind::instance);
    masd::dogen::variability::helpers::value_factory f;
    r.default_value(f.make(vt, std::list<std::string>{ "" }));

    archetypes::location al;
    al.kernel("masd");

     r.location(al);
     return r;
}

std::list<masd::dogen::variability::meta_model::feature_template>
features::make_templates() {
    using namespace masd::dogen::variability::meta_model;
    std::list<feature_template> r;
    r.push_back(make_masd_generation_cpp_test_data_directory());
    r.push_back(make_masd_generation_cpp_test_data_postfix());
    r.push_back(make_masd_generation_cpp_test_data_class_header_postfix());
    r.push_back(make_masd_generation_cpp_test_data_class_implementation_postfix());
    r.push_back(make_masd_generation_cpp_test_data_enum_header_postfix());
    r.push_back(make_masd_generation_cpp_test_data_enum_implementation_postfix());
    r.push_back(make_masd_generation_cpp_test_data_primitive_header_postfix());
    r.push_back(make_masd_generation_cpp_test_data_primitive_implementation_postfix());
    r.push_back(make_masd_generation_cpp_test_data_master_header_postfix());
    r.push_back(make_masd_generation_cpp_test_data_builtin_header_postfix());
    return r;
}

}
