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
#include <set>
#include <array>
#include <boost/test/unit_test.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "masd.dogen.utility/types/test/logging.hpp"
#include "masd.dogen.utility/types/test/exception_checkers.hpp"
#include "masd.dogen.coding/types/meta_model/name.hpp"
#include "masd.dogen.coding/io/meta_model/name_io.hpp"
#include "masd.dogen.coding/types/meta_model/model.hpp"
#include "masd.dogen.coding/io/meta_model/model_io.hpp"
#include "masd.dogen.coding/types/meta_model/structural/object.hpp"
#include "masd.dogen.coding/types/transforms/transformation_error.hpp"
#include "masd.dogen.coding/test/mock_context_factory.hpp"
#include "masd.dogen.coding/test/mock_model_factory.hpp"
#include "masd.dogen.coding/types/transforms/merge_transform.hpp"

namespace {

const std::string test_module("masd.dogen.coding.tests");
const std::string test_suite("merge_transform_tests");

using masd::dogen::coding::test::mock_model_factory;
const mock_model_factory::flags flags;
const mock_model_factory factory(flags);

const std::string invalid_id("INVALID");
const std::string invalid_model_name("INVALID");

const std::string double_merging("Attempt to merge more than once");
const std::string inconsistent_kvp("Inconsistency between key and value");

const std::string missing_target("Target model not present");
const std::string too_many_targets("Only one target expected.");

}

using masd::dogen::utility::test::contains_checker;
using masd::dogen::coding::meta_model::origin_types;
using masd::dogen::coding::meta_model::model;
using masd::dogen::coding::transforms::merge_transform;
using masd::dogen::coding::test::mock_context_factory;

BOOST_AUTO_TEST_SUITE(merge_transform_tests)

BOOST_AUTO_TEST_CASE(merging_n_distinct_models_with_one_object_each_results_in_n_objects_in_merged_model) {
    SETUP_TEST_LOG_SOURCE("merging_n_distinct_models_with_one_object_each_results_in_n_objects_in_merged_model");

    const auto tg(origin_types::target);
    const auto target(factory.make_single_type_model(tg, 0));

    const unsigned int n(5);
    std::list<model> ims;
    const auto npr(origin_types::non_proxy_reference);
    for (unsigned int i(1); i < n; ++i) {
        const auto m(factory.make_single_type_model(npr, i));
        ims.push_back(m);
    }

    const auto ctx(mock_context_factory::make());
    const auto combined(merge_transform::apply(ctx, target, ims));

    BOOST_LOG_SEV(lg, debug) << "Merged model: " << combined;

    BOOST_CHECK(combined.structural_elements().objects().size() == n);
    BOOST_CHECK(combined.structural_elements().builtins().empty());
    BOOST_CHECK(combined.structural_elements().enumerations().empty());
    BOOST_CHECK(combined.structural_elements().object_templates().empty());
    BOOST_CHECK(combined.structural_elements().modules().empty());
    BOOST_CHECK(combined.references().size() == 4);

    for (const auto pair : combined.references())
        BOOST_CHECK(pair.second == npr);

    std::set<std::string> object_names;
    std::set<std::string> model_names;
    for (const auto& pair : combined.structural_elements().objects()) {
        const auto& n(pair.second->name());
        BOOST_REQUIRE(n.location().model_modules().size() == 1);
        object_names.insert(n.location().model_modules().front() + "_" +
            n.simple());
        model_names.insert(n.location().model_modules().front());
    }

    BOOST_REQUIRE(object_names.size() == n);
    BOOST_REQUIRE(model_names.size() == n);

    auto object_i(object_names.cbegin());
    auto model_i(model_names.cbegin());
    for (unsigned int i(0); i < n; ++i) {
        BOOST_REQUIRE(object_i != object_names.cend());
        BOOST_REQUIRE(model_i != model_names.cend());

        BOOST_LOG_SEV(lg, debug) << "object name: " << *object_i;
        BOOST_LOG_SEV(lg, debug) << "model name: " << *model_i;

        const auto expected_model_name(factory.simple_model_name(i));
        const auto expected_object_name(factory.simple_type_name(0));
        BOOST_LOG_SEV(lg, debug) << "expected object name: "
                                 << expected_object_name;
        BOOST_LOG_SEV(lg, debug) << "expected model name: "
                                 << expected_model_name;

        BOOST_CHECK(boost::ends_with(*object_i, expected_object_name));
        BOOST_CHECK(boost::starts_with(*object_i, expected_model_name));
        BOOST_CHECK(*model_i == expected_model_name);
        ++object_i;
        ++model_i;
    }
}

BOOST_AUTO_TEST_CASE(merging_empty_model_results_in_empty_merged_model) {
    SETUP_TEST_LOG_SOURCE("merging_empty_model_results_in_empty_merged_model");
    const auto tg(origin_types::target);
    const auto m(factory.make_empty_model(tg));

    const std::list<model> ims;
    const auto ctx(mock_context_factory::make());
    const auto combined(merge_transform::apply(ctx, m, ims));
    BOOST_LOG_SEV(lg, debug) << "Merged model: " << combined;

    BOOST_CHECK(combined.structural_elements().objects().empty());
    BOOST_CHECK(combined.structural_elements().builtins().empty());
    BOOST_CHECK(combined.structural_elements().enumerations().empty());
    BOOST_CHECK(combined.structural_elements().modules().empty());
}

BOOST_AUTO_TEST_SUITE_END()
