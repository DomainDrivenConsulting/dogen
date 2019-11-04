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
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string/join.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.assets/types/meta_model/structural/object.hpp"
#include "dogen.assets/types/helpers/meta_name_factory.hpp"
#include "dogen.assets/types/helpers/name_factory.hpp"
#include "dogen.generation/types/formatters/sequence_formatter.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/traits.hpp"
#include "dogen.generation.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/io/traits.hpp"
#include "dogen.generation.cpp/types/formatters/hash/traits.hpp"
#include "dogen.generation.cpp/types/formatters/serialization/traits.hpp"
#include "dogen.generation.cpp/types/formatters/test_data/traits.hpp"
#include "dogen.generation.cpp/types/formatters/tests/traits.hpp"
#include "dogen.generation.cpp/types/formatters/tests/class_implementation_formatter.hpp"

namespace dogen::generation::cpp::formatters::tests {

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
    return l.make_full_path_for_tests_cpp_implementation(n, static_id());
}

std::list<std::string> class_implementation_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const assets::meta_model::element& e) const {

    using assets::meta_model::structural::object;
    const auto& o(assistant::as<object>(e));
    auto builder(f.make());
    builder.add(o.name(), types::traits::class_header_archetype());
    builder.add(o.name(), test_data::traits::class_header_archetype());

    using ic = inclusion_constants;
    builder.add(ic::std::string());
    builder.add(ic::boost::test::unit_test());

    if (o.is_parent())
        builder.add(ic::boost::shared_ptr());

    const auto io_arch(io::traits::class_header_archetype());
    const bool io_enabled(builder.is_enabled(o.name(), io_arch));
    if (io_enabled) {
        builder.add(o.name(), io_arch);
        builder.add(ic::std::sstream());
        builder.add(ic::boost::property_tree::ptree());
        builder.add(ic::boost::property_tree::json_parser());
    }

    using ser = formatters::serialization::traits;
    const auto ser_arch(ser::class_header_archetype());
    const bool ser_enabled(builder.is_enabled(o.name(), ser_arch));
    if (ser_enabled) {
        builder.add(o.name(), ser_arch);

        // FIXME: hack for registrar
        assets::helpers::name_factory nf;
        auto n(o.name());
        n.location().internal_modules().clear();
        const auto rn(nf.build_element_in_model(n, "registrar"));
        builder.add(rn, ser::registrar_header_archetype());

        builder.add(ic::boost::archive::text_iarchive());
        builder.add(ic::boost::archive::text_oarchive());
        builder.add(ic::boost::archive::binary_iarchive());
        builder.add(ic::boost::archive::binary_oarchive());
        builder.add(ic::boost::archive::polymorphic_iarchive());
        builder.add(ic::boost::archive::polymorphic_oarchive());
        builder.add(ic::boost::serialization::nvp());
        builder.add(ic::boost::archive::xml_iarchive());
        builder.add(ic::boost::archive::xml_oarchive());

        if (o.is_parent())
            builder.add(ic::boost::serialization::shared_ptr());
    }

    using hash = formatters::hash::traits;
    const auto hash_arch(hash::class_header_archetype());
    const bool hash_enabled(builder.is_enabled(o.name(), hash_arch));
    if (hash_enabled)
        builder.add(o.name(), hash_arch);

    return builder.build();
}

extraction::meta_model::artefact class_implementation_formatter::
format(const context& ctx, const assets::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& o(a.as<assets::meta_model::structural::object>(e));
    {
        auto sbf(a.make_scoped_boilerplate_formatter(o));
        const auto qn(a.get_qualified_name(o.name()));
        auto list(e.name().location().internal_modules());
        list.push_back(o.name().simple());
        const std::string test_suite_name(boost::join(list, "_"));

        std::string type_name("auto");
        if (a.is_cpp_standard_98())
            type_name = qn;

a.stream() << "BOOST_AUTO_TEST_SUITE(" << test_suite_name << "_tests)" << std::endl;
a.stream() << std::endl;
        /*
         * If we have no attributes at all, we cannot test this
         * type. Similarly, if test data is not enabled, none of the
         * tests can be generated. In either case, we need to insert a
         * fake test for now. The real solution will be to filter
         * based on element state.
         */
        if (o.all_attributes().empty() || !a.is_test_data_enabled()) {
            /*
             * No tests.
             */
a.stream() << "BOOST_AUTO_TEST_CASE(fake_test) {" << std::endl;
a.stream() << "    BOOST_CHECK(true);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
        } else {
            /*
             * Types tests. These cannot be performed to parents as
             * they are abstract.
             */
            if (!o.is_parent()) {
a.stream() << "BOOST_AUTO_TEST_CASE(identical_objects_are_equal) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    const " << type_name << " a(g());" << std::endl;
a.stream() << "    const " << type_name << " b(a);" << std::endl;
a.stream() << std::endl;
a.stream() << "    BOOST_CHECK(a == b);" << std::endl;
a.stream() << "    BOOST_CHECK(b == a);" << std::endl;
a.stream() << "    BOOST_CHECK(!(a != b));" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_CASE(an_object_is_equal_to_itself) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    const " << type_name << " a(g());" << std::endl;
a.stream() << std::endl;
a.stream() << "    BOOST_CHECK(a == a);" << std::endl;
a.stream() << "    BOOST_CHECK(!(a != a));" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_CASE(distinct_objects_are_unequal) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    const " << type_name << " a(g());" << std::endl;
a.stream() << "    const " << type_name << " b(g());" << std::endl;
a.stream() << std::endl;
a.stream() << "    BOOST_CHECK(!(a == b));" << std::endl;
a.stream() << "    BOOST_CHECK(a != b);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
                if (!o.is_immutable()) {
a.stream() << "BOOST_AUTO_TEST_CASE(assigning_an_object_to_itself_results_in_the_same_object) {" << std::endl;
a.stream() << "#if defined(__clang__) && !defined(__apple_build_version__)  && (__clang_major__ >= 7)" << std::endl;
a.stream() << "#pragma clang diagnostic push" << std::endl;
a.stream() << "#pragma clang diagnostic ignored \"-Wself-assign-overloaded\"" << std::endl;
a.stream() << "#endif" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    " << type_name << " a(g());" << std::endl;
a.stream() << "    const " << type_name << " b(a);" << std::endl;
a.stream() << "    const " << type_name << " c(g());" << std::endl;
a.stream() << std::endl;
a.stream() << "    a = a;" << std::endl;
a.stream() << "    BOOST_CHECK(a == b);" << std::endl;
a.stream() << "    BOOST_CHECK(a != c);" << std::endl;
a.stream() << "#if defined(__clang__) && !defined(__apple_build_version__)  && (__clang_major__ >= 7)" << std::endl;
a.stream() << "#pragma clang diagnostic pop" << std::endl;
a.stream() << "#endif" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
                }

                // FIXME: should be 11 or greater.
                if (!a.is_cpp_standard_98()) {
a.stream() << "BOOST_AUTO_TEST_CASE(moved_objects_are_equal) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    g();" << std::endl;
a.stream() << "    " << type_name << " a(g());" << std::endl;
a.stream() << "    const " << type_name << " b = " << qn << "();" << std::endl;
a.stream() << "    const " << type_name << " c(a);" << std::endl;
a.stream() << "    BOOST_CHECK(a != b);" << std::endl;
a.stream() << "    BOOST_CHECK(a == c);" << std::endl;
a.stream() << std::endl;
a.stream() << "    const " << type_name << " d = std::move(a);" << std::endl;
a.stream() << "    BOOST_CHECK(d == c);" << std::endl;
a.stream() << "    BOOST_CHECK(d != b);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
                }

                if (!o.is_immutable()) {
a.stream() << "BOOST_AUTO_TEST_CASE(assigned_objects_are_equal) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    g();" << std::endl;
a.stream() << "    const " << type_name << " a(g());" << std::endl;
a.stream() << "    " << qn << " b;" << std::endl;
a.stream() << "    BOOST_CHECK(a != b);" << std::endl;
a.stream() << std::endl;
a.stream() << "    b = a;" << std::endl;
a.stream() << "    BOOST_CHECK(a == b);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_CASE(copy_constructed_objects_are_equal) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    g();" << std::endl;
a.stream() << "    const " << type_name << " a(g());" << std::endl;
a.stream() << "    " << type_name << " b(a);" << std::endl;
a.stream() << "    BOOST_CHECK(a == b);" << std::endl;
a.stream() << std::endl;
a.stream() << "    b = " << qn << "();" << std::endl;
a.stream() << "    BOOST_CHECK(a != b);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_CASE(swapping_objects_results_in_the_expected_state) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    const " << type_name << " a(g());" << std::endl;
a.stream() << "    const " << type_name << " b(g());" << std::endl;
a.stream() << std::endl;
a.stream() << "    " << type_name << " c(a);" << std::endl;
a.stream() << "    " << type_name << " d(b);" << std::endl;
a.stream() << "    BOOST_CHECK(c == a);" << std::endl;
a.stream() << "    BOOST_CHECK(d == b);" << std::endl;
a.stream() << std::endl;
a.stream() << "    std::swap(c, d);" << std::endl;
a.stream() << "    BOOST_CHECK(c == b);" << std::endl;
a.stream() << "    BOOST_CHECK(d == a);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
                }
            }

            if (a.is_io_enabled()) {
                /*
                 * IO tests.
                 */
a.stream() << "BOOST_AUTO_TEST_CASE(inserter_operator_produces_valid_json) {" << std::endl;
                if (o.is_parent()) {
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    const boost::shared_ptr<" << qn << "> a(g.create_ptr(1));" << std::endl;
a.stream() << "    std::stringstream s;" << std::endl;
a.stream() << "    s << *a;" << std::endl;
a.stream() << std::endl;
a.stream() << "    boost::property_tree::ptree pt;" << std::endl;
a.stream() << "    BOOST_REQUIRE_NO_THROW(read_json(s, pt));" << std::endl;
                } else {
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    const " << type_name << " a(g());" << std::endl;
a.stream() << "    std::stringstream s;" << std::endl;
a.stream() << "    s << a;" << std::endl;
a.stream() << std::endl;
a.stream() << "    boost::property_tree::ptree pt;" << std::endl;
a.stream() << "    BOOST_REQUIRE_NO_THROW(read_json(s, pt));" << std::endl;
                }
a.stream() << "}" << std::endl;
a.stream() << std::endl;
            }

            if (a.is_serialization_enabled()) {
                /*
                 * Serialization tests.
                 */
                // FIXME: hack for register_types
                assets::helpers::name_factory nf;
                auto n(o.name());
                n.location().internal_modules().clear();
                const auto rn(nf.build_element_in_model(n, "register_types"));
                const auto registrar_qn(a.get_qualified_name(rn));

                if (o.is_parent()) {
a.stream() << "BOOST_AUTO_TEST_CASE(xml_roundtrip_produces_the_same_entity) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    const boost::shared_ptr<" << qn << "> a(g.create_ptr(1));" << std::endl;
a.stream() << std::endl;
a.stream() << "    using namespace boost::archive;" << std::endl;
a.stream() << "    std::ostringstream os;" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        xml_oarchive oa(os);" << std::endl;
a.stream() << "        " << registrar_qn << "<xml_oarchive>(oa);" << std::endl;
a.stream() << "        oa << BOOST_SERIALIZATION_NVP(a);" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "    boost::shared_ptr<" << qn << "> b;" << std::endl;
a.stream() << "    std::istringstream is(os.str());" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        xml_iarchive ia(is);" << std::endl;
a.stream() << "        " << registrar_qn << "<xml_iarchive>(ia);" << std::endl;
a.stream() << "        ia >> BOOST_SERIALIZATION_NVP(b);" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "    BOOST_REQUIRE(a);" << std::endl;
a.stream() << "    BOOST_REQUIRE(b);" << std::endl;
a.stream() << "    BOOST_CHECK(*a == *b);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_CASE(text_roundtrip_produces_the_same_entity) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    const boost::shared_ptr<" << qn << "> a(g.create_ptr(1));" << std::endl;
a.stream() << std::endl;
a.stream() << "    using namespace boost::archive;" << std::endl;
a.stream() << "    std::ostringstream os;" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        text_oarchive oa(os);" << std::endl;
a.stream() << "        " << registrar_qn << "<text_oarchive>(oa);" << std::endl;
a.stream() << "        oa << a;" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "    boost::shared_ptr<" << qn << "> b;" << std::endl;
a.stream() << "    std::istringstream is(os.str());" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        text_iarchive ia(is);" << std::endl;
a.stream() << "        " << registrar_qn << "<text_iarchive>(ia);" << std::endl;
a.stream() << "        ia >> b;" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "    BOOST_REQUIRE(a);" << std::endl;
a.stream() << "    BOOST_REQUIRE(b);" << std::endl;
a.stream() << "    BOOST_CHECK(*a == *b);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_CASE(binary_roundtrip_produces_the_same_entity) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    const boost::shared_ptr<" << qn << "> a(g.create_ptr(1));" << std::endl;
a.stream() << std::endl;
a.stream() << "    using namespace boost::archive;" << std::endl;
a.stream() << "    std::ostringstream os;" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        binary_oarchive oa(os);" << std::endl;
a.stream() << "        " << registrar_qn << "<binary_oarchive>(oa);" << std::endl;
a.stream() << "        oa << a;" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "    boost::shared_ptr<" << qn << "> b;" << std::endl;
a.stream() << "    std::istringstream is(os.str());" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        binary_iarchive ia(is);" << std::endl;
a.stream() << "        " << registrar_qn << "<binary_iarchive>(ia);" << std::endl;
a.stream() << "        ia >> b;" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "    BOOST_REQUIRE(a);" << std::endl;
a.stream() << "    BOOST_REQUIRE(b);" << std::endl;
a.stream() << "    BOOST_CHECK(*a == *b);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
                } else {

a.stream() << "BOOST_AUTO_TEST_CASE(xml_roundtrip_produces_the_same_entity) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    const " << type_name << " a(g());" << std::endl;
a.stream() << std::endl;
a.stream() << "    using namespace boost::archive;" << std::endl;
a.stream() << "    std::ostringstream os;" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        xml_oarchive oa(os);" << std::endl;
a.stream() << "        " << registrar_qn << "<xml_oarchive>(oa);" << std::endl;
a.stream() << "        oa << BOOST_SERIALIZATION_NVP(a);" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "    " << qn << " b = " << qn << "();" << std::endl;
a.stream() << "    std::istringstream is(os.str());" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        xml_iarchive ia(is);" << std::endl;
a.stream() << "        " << registrar_qn << "<xml_iarchive>(ia);" << std::endl;
a.stream() << "        ia >> BOOST_SERIALIZATION_NVP(b);" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "    BOOST_CHECK(a == b);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_CASE(text_roundtrip_produces_the_same_entity) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    const " << type_name << " a(g());" << std::endl;
a.stream() << std::endl;
a.stream() << "    using namespace boost::archive;" << std::endl;
a.stream() << "    std::ostringstream os;" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        text_oarchive oa(os);" << std::endl;
a.stream() << "        " << registrar_qn << "<text_oarchive>(oa);" << std::endl;
a.stream() << "        oa << a;" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "    " << qn << " b = " << qn << "();" << std::endl;
a.stream() << "    std::istringstream is(os.str());" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        text_iarchive ia(is);" << std::endl;
a.stream() << "        " << registrar_qn << "<text_iarchive>(ia);" << std::endl;
a.stream() << "        ia >> b;" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "    BOOST_CHECK(a == b);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_CASE(binary_roundtrip_produces_the_same_entity) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    const " << type_name << " a(g());" << std::endl;
a.stream() << std::endl;
a.stream() << "    using namespace boost::archive;" << std::endl;
a.stream() << "    std::ostringstream os;" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        binary_oarchive oa(os);" << std::endl;
a.stream() << "        " << registrar_qn << "<binary_oarchive>(oa);" << std::endl;
a.stream() << "        oa << a;" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "    " << qn << " b = " << qn << "();" << std::endl;
a.stream() << "    std::istringstream is(os.str());" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        binary_iarchive ia(is);" << std::endl;
a.stream() << "        " << registrar_qn << "<binary_iarchive>(ia);" << std::endl;
a.stream() << "        ia >> b;" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << std::endl;
a.stream() << "    BOOST_CHECK(a == b);" << std::endl;
a.stream() << "}" << std::endl;
                }
            }

            if (a.is_hash_enabled() && !o.is_parent()) {
                /*
                 * hash tests.
                 */
a.stream() << "BOOST_AUTO_TEST_CASE(equal_objects_generate_the_same_hash) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    g();" << std::endl;
a.stream() << "    const " << type_name << " a(g());" << std::endl;
a.stream() << "    const " << type_name << " b(a);" << std::endl;
a.stream() << std::endl;
a.stream() << "    std::hash<" << qn << "> hasher;" << std::endl;
a.stream() << "    BOOST_CHECK(hasher(a) == hasher(b));" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_AUTO_TEST_CASE(different_objects_generate_different_hashes) {" << std::endl;
a.stream() << "    " << qn << "_generator g;" << std::endl;
a.stream() << "    g();" << std::endl;
a.stream() << "    const " << type_name << " a(g());" << std::endl;
a.stream() << "    const " << type_name << " b(g());" << std::endl;
a.stream() << std::endl;
a.stream() << "    std::hash<" << qn << "> hasher;" << std::endl;
a.stream() << "    BOOST_CHECK(hasher(a) != hasher(b));" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
            }
        }
a.stream() << "BOOST_AUTO_TEST_SUITE_END()" << std::endl;
    } // sbf
    return a.make_artefact();
}
}
