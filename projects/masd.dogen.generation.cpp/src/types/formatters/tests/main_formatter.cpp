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
#include "masd.dogen.generation.cpp/types/formatters/tests/main_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/tests/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "masd.dogen.generation.cpp/types/formatters/inclusion_constants.hpp"
#include "masd.dogen.generation.cpp/types/formatters/traits.hpp"
#include "masd.dogen.generation.cpp/types/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/assistant.hpp"
#include "masd.dogen.generation/types/formatters/sequence_formatter.hpp"
#include "masd.dogen.generation.cpp/types/fabric/meta_name_factory.hpp"
#include "masd.dogen.generation.cpp/types/fabric/entry_point.hpp"
#include "masd.dogen.utility/types/log/logger.hpp"
#include <boost/throw_exception.hpp>

namespace masd::dogen::generation::cpp::formatters::tests {

std::string main_formatter::static_id() {
    return traits::main_archetype();
}

std::string main_formatter::id() const {
    return static_id();
}

variability::archetype_location
main_formatter::archetype_location() const {
    static variability::archetype_location
        r(cpp::traits::kernel(),  cpp::traits::backend(),
          traits::facet(),
          main_formatter::static_id());
    return r;
}

const coding::meta_model::name& main_formatter::meta_name() const {
    static auto r(fabric::meta_name_factory::make_entry_point_name());
    return r;
}

std::string main_formatter::family() const {
    return cpp::traits::implementation_family();
}

inclusion_support_types main_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path main_formatter::inclusion_path(
    const formattables::locator& /*l*/, const coding::meta_model::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(
        logger_factory(main_formatter::static_id()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path main_formatter::full_path(
    const formattables::locator& l, const coding::meta_model::name& n) const {
    return l.make_full_path_for_tests_cpp_main(n, static_id());
}

std::list<std::string> main_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const coding::meta_model::element& /*e*/) const {

    using coding::meta_model::object;
    auto builder(f.make());

    using ic = inclusion_constants;
    builder.add(ic::boost::test::unit_test());
    builder.add(ic::boost::test::unit_test_monitor());
    builder.add(ic::boost::exception::info());
    builder.add(ic::std::iostream());
    builder.add(ic::boost::exception::diagnostic_information());

    return builder.build();
}

extraction::meta_model::artefact main_formatter::
format(const context& ctx, const coding::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    const auto& ep(a.as<fabric::entry_point>(e));
    const auto qn(a.get_qualified_name(ep.name()));
a.stream() << "#define BOOST_TEST_MODULE " << qn << std::endl;
a.stream() << std::endl;
    {
        auto sbf(a.make_scoped_boilerplate_formatter(ep));
a.stream() << std::endl;
a.stream() << "namespace  {" << std::endl;
a.stream() << std::endl;
a.stream() << "const std::string error_msg(\"Error during test.\");" << std::endl;
a.stream() << std::endl;
a.stream() << "inline void translate(const boost::exception& e) {" << std::endl;
a.stream() << "    std::cerr << std::endl << boost::diagnostic_information(e);" << std::endl;
a.stream() << "    throw std::runtime_error(error_msg);" << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "struct exception_fixture {" << std::endl;
a.stream() << "    exception_fixture() {" << std::endl;
a.stream() << "        using boost::exception;" << std::endl;
a.stream() << "        using boost::unit_test::unit_test_monitor;" << std::endl;
a.stream() << "        unit_test_monitor.register_exception_translator<exception>(&translate);" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << "};" << std::endl;
a.stream() << std::endl;
a.stream() << "}" << std::endl;
a.stream() << std::endl;
a.stream() << "BOOST_GLOBAL_FIXTURE(exception_fixture);" << std::endl;
    } // sbf
    return a.make_artefact();
}
}
