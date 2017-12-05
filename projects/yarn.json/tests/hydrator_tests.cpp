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
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem/fstream.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/test/mock_type_factory.hpp"
#include "dogen/annotations/test/mock_type_repository_factory.hpp"
#include "dogen/annotations/types/type.hpp"
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/module.hpp"
#include "dogen/yarn/types/meta_model/builtin.hpp"
#include "dogen/yarn/types/meta_model/exomodel.hpp"
#include "dogen/yarn/io/meta_model/exomodel_io.hpp"
#include "dogen/yarn.json/types/hydration_error.hpp"
#include "dogen/yarn.json/types/hydrator.hpp"
#include "dogen/utility/test/exception_checkers.hpp"

namespace {

const std::string test_module("yarn.json");
const std::string test_suite("hydrator_tests");

const std::string documentation("a_doc");
const std::string type_name("a_type");
const std::string attribute_name("some_attr");
const std::string attribute_type("std::string");
const std::string some_key("some_key");
const std::string some_value("some_value");
const std::string first_parent("a::b::c");
const std::string second_parent("a");
const std::string a_stereotype("some stereotype");
const std::string another_stereotype("another");

const std::string cpp_std_model_path("library/cpp.std.json");
const std::string cpp_std_model_name("std");
const std::string cpp_boost_model_name("boost");
const std::string cpp_boost_model_path("library/cpp.boost.json");
const std::string hardware_model_path("library/cpp.builtins.json");
const std::string hardware_model_name_front("cpp");
const std::string hardware_model_name_back("builtins");

const std::string missing_elements("Missing mandatory elements");

const std::string one_object_model(R"({
    "documentation" : "a_doc",
    "stereotypes" : [ "some stereotype", "another" ],
    "tagged_values" : {
        "some_key" : "some_value"
    },
    "elements" : [
        {
            "name" : "a_type",
            "documentation" : "a_doc",
            "parents" : [ "a::b::c", "a" ],
            "stereotypes" : [ "yarn::object", "some stereotype" ],
            "tagged_values" : {
                "some_key" : "some_value"
            }
        }
    ]
}
)");

const std::string object_with_attribute_model(R"({
    "elements" : [
        {
            "name" : "a_type",
            "parents" : [ "a::b::c" ],
            "attributes" : [
                {
                    "name" : "some_attr",
                    "type" : "std::string",
                    "documentation" : "a_doc",
                    "stereotypes" : [ "some stereotype", "yarn::fluent" ],
                    "tagged_values" : {
                        "some_key" : "some_value"
                    }
                }
            ]
        }
    ]
}
)");

const std::string missing_elements_model(R"({
    "documentation" : "a_doc",
    "stereotypes" : [ "some stereotype", "another" ]
}
)");

const std::string empty_elements_model(R"({
    "documentation" : "a_doc",
    "stereotypes" : [ "some stereotype", "another" ],
    "elements" : []
}
)");


dogen::yarn::meta_model::exomodel hydrate(std::istream& s) {
    dogen::yarn::json::hydrator h;
    return h.hydrate(s);
}
/*
dogen::yarn::meta_model::exomodel
hydrate(const boost::filesystem::path& p) {
    boost::filesystem::ifstream s(p);
    return hydrate(s);
}
*/
dogen::yarn::meta_model::exomodel
hydrate(const std::string& content) {
    std::istringstream s(content);
    return hydrate(s);
}

}

using dogen::utility::test::contains_checker;
using dogen::yarn::json::hydration_error;

BOOST_AUTO_TEST_SUITE(hydrator_tests)

BOOST_AUTO_TEST_CASE(one_object_model_hydrates_into_expected_model) {
    SETUP_TEST_LOG_SOURCE("one_object_model_hydrates_into_expected_model");

    BOOST_LOG_SEV(lg, debug) << "input: " << one_object_model;
    const auto m(hydrate(one_object_model));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    BOOST_CHECK(m.documentation() == documentation);
    BOOST_REQUIRE(m.stereotypes().size() == 2);
    BOOST_CHECK(m.stereotypes().front() == a_stereotype);
    BOOST_CHECK(m.stereotypes().back() == another_stereotype);

    BOOST_REQUIRE(m.tagged_values().size() == 1);
    BOOST_CHECK(m.tagged_values().front().first == some_key);
    BOOST_CHECK(m.tagged_values().front().second == some_value);

    BOOST_REQUIRE(m.elements().size() == 1);
    const auto& e(m.elements().front());
    BOOST_CHECK(e.name() == type_name);
    BOOST_CHECK(e.documentation() == documentation);

    BOOST_REQUIRE(e.parents().size() == 2);
    BOOST_CHECK(e.parents().front() == first_parent);
    BOOST_CHECK(e.parents().back() == second_parent);

    BOOST_REQUIRE(e.tagged_values().size() == 1);
    BOOST_CHECK(e.tagged_values().front().first == some_key);
    BOOST_CHECK(e.tagged_values().front().second == some_value);

    BOOST_REQUIRE(e.stereotypes().size() == 2);
    BOOST_CHECK(e.stereotypes().back() == a_stereotype);
    BOOST_CHECK(e.stereotypes().front() == "yarn::object");

    BOOST_CHECK(e.attributes().empty());
}

BOOST_AUTO_TEST_CASE(object_with_attribute_model_hydrates_into_expected_model) {
    SETUP_TEST_LOG_SOURCE("object_with_attribute_model_hydrates_into_expected_model");

    BOOST_LOG_SEV(lg, debug) << "input: " << object_with_attribute_model;
    const auto m(hydrate(object_with_attribute_model));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    BOOST_CHECK(m.documentation().empty());
    BOOST_CHECK(m.stereotypes().empty());
    BOOST_CHECK(m.stereotypes().empty());
    BOOST_CHECK(m.tagged_values().empty());

    BOOST_REQUIRE(m.elements().size() == 1);
    const auto& e(m.elements().front());
    BOOST_CHECK(e.name() == type_name);
    BOOST_CHECK(e.documentation().empty());

    BOOST_REQUIRE(e.parents().size() == 1);
    BOOST_CHECK(e.parents().front() == first_parent);

    BOOST_REQUIRE(e.attributes().size() == 1);
    const auto& a(e.attributes().front());
    BOOST_CHECK(a.name() == attribute_name);
    BOOST_CHECK(a.type() == attribute_type);
    BOOST_CHECK(a.documentation() == documentation);

    BOOST_REQUIRE(a.tagged_values().size() == 1);
    BOOST_CHECK(a.tagged_values().front().first == some_key);
    BOOST_CHECK(a.tagged_values().front().second == some_value);

    BOOST_CHECK(a.stereotypes().size() == 2);
    BOOST_CHECK(a.stereotypes().front() == a_stereotype);
    BOOST_CHECK(a.stereotypes().back() == "yarn::fluent");
}

BOOST_AUTO_TEST_CASE(empty_elements_model_results_in_empty_model) {
    SETUP_TEST_LOG_SOURCE("empty_elements_model_results_in_empty_model");

    BOOST_LOG_SEV(lg, debug) << "input: " << empty_elements_model;
    const auto m(hydrate(empty_elements_model));
    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    BOOST_CHECK(m.elements().empty());
    BOOST_CHECK(m.documentation() == documentation);
    BOOST_REQUIRE(m.stereotypes().size() == 2);
    BOOST_CHECK(m.stereotypes().front() == a_stereotype);
    BOOST_CHECK(m.stereotypes().back() == another_stereotype);
}

BOOST_AUTO_TEST_CASE(missing_elements_model_throws) {
    SETUP_TEST_LOG_SOURCE("missing_elements_model_throws");

    BOOST_LOG_SEV(lg, debug) << "input: " << missing_elements_model;
    contains_checker<hydration_error> c(missing_elements);
    BOOST_CHECK_EXCEPTION(hydrate(missing_elements_model), hydration_error, c);
}
/*
BOOST_AUTO_TEST_CASE(cpp_boost_model_hydrates_into_expected_model) {
    SETUP_TEST_LOG_SOURCE("cpp_boost_model_hydrates_into_expected_model");

    using namespace dogen::utility::filesystem;
    boost::filesystem::path p(data_files_directory() / cpp_boost_model_path);
    const auto m(hydrate(p));

    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    const auto& elements(m.elements());
    BOOST_CHECK(!elements.empty());
    for (const auto& e : elements) {
        const auto n(e.name());
        BOOST_REQUIRE(!n.empty());
    }
}
*/
/*

BOOST_AUTO_TEST_CASE(cpp_std_model_hydrates_into_expected_model) {
    SETUP_TEST_LOG_SOURCE("cpp_std_model_hydrates_into_expected_model");

    using namespace dogen::utility::filesystem;
    boost::filesystem::path p(data_files_directory() / cpp_std_model_path);
    const auto m(hydrate(p));

    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    const auto& objects(m.objects());
    BOOST_CHECK(!objects.empty());
    for (const auto& pair : objects) {
        const auto& o(*pair.second);
        const auto n(o.name());

        BOOST_REQUIRE(!n.simple().empty());
        BOOST_CHECK(n.location().model_modules().empty());
        BOOST_CHECK(n.location().internal_modules().empty());
        BOOST_CHECK(n.location().external_modules().empty());
    }

    const auto builtins(m.builtins());
    BOOST_CHECK(!m.builtins().empty());
    for (const auto& pair : builtins) {
        const auto p(*pair.second);
        const auto n(p.name());

        BOOST_REQUIRE(!n.simple().empty());
        BOOST_CHECK(n.location().model_modules().empty());
        BOOST_CHECK(n.location().internal_modules().empty());
        BOOST_CHECK(n.location().external_modules().empty());
    }

    BOOST_CHECK(m.enumerations().empty());
    BOOST_REQUIRE(m.modules().empty());
}

BOOST_AUTO_TEST_CASE(hardware_model_hydrates_into_expected_model) {
    SETUP_TEST_LOG_SOURCE("hardware_model_hydrates_into_expected_model");
    using namespace dogen::utility::filesystem;
    boost::filesystem::path p(data_files_directory() / hardware_model_path);
    const auto m(hydrate(p));

    BOOST_LOG_SEV(lg, debug) << "model: " << m;

    BOOST_CHECK(m.objects().empty());
    const auto builtins(m.builtins());
    BOOST_CHECK(!builtins.empty());
    for (const auto& pair : builtins) {
        const auto& p(*pair.second);
        const auto n(p.name());
        BOOST_REQUIRE(!n.simple().empty());
        BOOST_CHECK(n.location().model_modules().empty());
        BOOST_CHECK(n.location().internal_modules().empty());
        BOOST_CHECK(n.location().external_modules().empty());
    }

    BOOST_CHECK(m.enumerations().empty());
    BOOST_CHECK(m.modules().empty());
}
*/
BOOST_AUTO_TEST_SUITE_END()
