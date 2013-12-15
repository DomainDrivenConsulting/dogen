/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <array>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/types/model.hpp"
#include "dogen/sml/types/indexing_error.hpp"
#include "dogen/sml/types/object.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/sml/io/qname_io.hpp"
#include "dogen/sml/io/object_io.hpp"
#include "dogen/utility/test/exception_checkers.hpp"
#include "dogen/sml/test/mock_model_factory.hpp"
#include "dogen/sml/types/concept_indexer.hpp"

namespace {

const std::string test_module("sml");
const std::string test_suite("concept_indexer_spec");

const std::string concept_not_found("Concept not found");
const std::string object_not_found("Object not found in model");

using dogen::sml::test::mock_model_factory;

/* @note tagging should make no difference to tests, and not having tags
 * makes the model dumps easier to understand.
 *
 * However, strictly speaking, tagging happens before indexing so it
 * would be more truthful to use a tagged model in the tests.
 */
const mock_model_factory::flags flags(false/*tagged*/, false/*resolved*/,
    false/*merged*/, false/*concepts_indexed*/, false/*properties_indexed*/);

const mock_model_factory factory(flags);

}

using dogen::utility::test::contains_checker;
using dogen::sml::indexing_error;
using dogen::utility::test::asserter;
using object_types = dogen::sml::test::mock_model_factory::object_types;
using property_types = dogen::sml::test::mock_model_factory::property_types;

BOOST_AUTO_TEST_SUITE(concept_indexer)

BOOST_AUTO_TEST_CASE(empty_model_is_untouched_by_concept_indexer) {
    SETUP_TEST_LOG_SOURCE("empty_model_is_untouched_by_concept_indexer");

    auto a(factory.build_empty_model());
    const auto e(factory.build_empty_model());
    BOOST_REQUIRE(a.objects().empty());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << a;

    dogen::sml::concept_indexer i;
    i.index(a);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_single_type_and_no_properties_is_untouched_by_concept_indexer) {
    SETUP_TEST_LOG_SOURCE("model_with_single_type_and_no_properties_is_untouched_by_concept_indexer");

    auto a(factory.build_single_type_model());
    const auto e(factory.build_single_type_model());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << a;
    BOOST_REQUIRE(a.objects().size() == 1);

    dogen::sml::concept_indexer ind;
    ind.index(a);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_type_with_property_is_untouched_by_concept_indexer) {
    SETUP_TEST_LOG_SOURCE("model_with_type_with_property_is_untouched_by_concept_indexer");

    const auto pt(property_types::unsigned_int);
    auto a(factory.object_with_property(object_types::value_object, pt));
    const auto e(factory.object_with_property(object_types::value_object, pt));

    BOOST_LOG_SEV(lg, debug) << "before indexing: " << a;

    BOOST_REQUIRE(a.concepts().empty());
    BOOST_REQUIRE(a.enumerations().empty());
    BOOST_REQUIRE(a.primitives().size() == 1);

    BOOST_REQUIRE(a.objects().size() == 1);
    const auto& o(a.objects().begin()->second);
    BOOST_REQUIRE(o.local_properties().size() == 1);
    BOOST_REQUIRE(o.inherited_properties().empty());
    BOOST_REQUIRE(o.all_properties().empty());
    BOOST_REQUIRE(o.relationships().empty());

    dogen::sml::concept_indexer ind;
    ind.index(a);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_single_concept_is_untouched_by_concept_indexer) {
    SETUP_TEST_LOG_SOURCE("model_with_single_concept_is_untouched_by_concept_indexer");

    auto a(factory.build_single_concept_model());
    const auto e(factory.build_single_concept_model());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << a;
    BOOST_REQUIRE(a.objects().size() == 1);

    const auto& o(a.objects().begin()->second);
    using dogen::sml::relationship_types;
    const auto rt(relationship_types::modeled_concepts);
    const auto i(o.relationships().find(rt));
    BOOST_REQUIRE(i != o.relationships().end());
    BOOST_REQUIRE(i->second.size() == 1);

    BOOST_REQUIRE(a.concepts().size() == 1);
    const auto& c(a.concepts().begin()->second);
    BOOST_REQUIRE(c.refines().empty());

    dogen::sml::concept_indexer ind;
    ind.index(a);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_one_level_of_concept_inheritance_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_one_level_of_concept_inheritance_results_in_expected_indices");

    using dogen::sml::relationship_types;
    const auto mc(relationship_types::modeled_concepts);
    const auto par(relationship_types::parents);

    auto m(factory.build_first_degree_concepts_model());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;
    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        const auto& o(pair.second);

        auto i(o.relationships().find(mc));
        BOOST_REQUIRE(i != o.relationships().end());
        if (factory.is_type_name_n(0, qn)) {
            BOOST_REQUIRE(i->second.size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(0, i->second.front()));
        } else if (factory.is_type_name_n(1, qn)) {
            BOOST_REQUIRE(i->second.size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(1, i->second.front()));
        } else
            BOOST_FAIL("Unexpected object: " << qn);

        i = o.relationships().find(par);
        BOOST_REQUIRE(i == o.relationships().end());
    }

    BOOST_REQUIRE(m.concepts().size() == 2);
    for (const auto& pair : m.concepts()) {
        const auto& qn(pair.first);
        const auto& c(pair.second);

        if (factory.is_concept_name_n(0, qn))
            BOOST_REQUIRE(c.refines().empty());
        else if (factory.is_concept_name_n(1, qn)) {
            BOOST_REQUIRE(c.refines().size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(0, c.refines().front()));
        } else
            BOOST_FAIL("Unexpected concept: " << qn);
    }

    dogen::sml::concept_indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

    for (const auto& pair : m.concepts()) {
        const auto& qn(pair.first);
        const auto& c(pair.second);

        if (factory.is_concept_name_n(0, qn)) {
            BOOST_CHECK(c.refines().empty());
        } else if (factory.is_concept_name_n(1, qn)) {
            BOOST_CHECK(c.refines().size() == 1);
        } else
            BOOST_FAIL("Unexpected concept: " << qn);
    }

    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        const auto& o(pair.second);

        const auto i(o.relationships().find(mc));
        BOOST_REQUIRE(i != o.relationships().end());

        if (factory.is_type_name_n(0, qn))
            BOOST_CHECK(i->second.size() == 1);
        else if (factory.is_type_name_n(1, qn)) {
            BOOST_CHECK(i->second.size() == 2);
        } else
            BOOST_FAIL("Unexpected object: " << qn);
    }
}

BOOST_AUTO_TEST_CASE(model_with_two_levels_of_concept_inheritance_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_two_levels_of_concept_inheritance_results_in_expected_indices");

    using dogen::sml::relationship_types;
    const auto mc(relationship_types::modeled_concepts);
    const auto par(relationship_types::parents);

    auto m(factory.build_second_degree_concepts_model());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;
    BOOST_REQUIRE(m.objects().size() == 3);
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        const auto& o(pair.second);

        auto i(o.relationships().find(mc));
        BOOST_REQUIRE(i != o.relationships().end());
        if (factory.is_type_name_n(0, qn)) {
            BOOST_REQUIRE(i->second.size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(0, i->second.front()));
        } else if (factory.is_type_name_n(1, qn)) {
            BOOST_REQUIRE(i->second.size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(1, i->second.front()));
        } else if (factory.is_type_name_n(2, qn)) {
            BOOST_REQUIRE(i->second.size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(2, i->second.front()));
        } else
            BOOST_FAIL("Unexpected object: " << qn);

        i = o.relationships().find(par);
        BOOST_REQUIRE(i == o.relationships().end());
    }

    BOOST_REQUIRE(m.concepts().size() == 3);
    for (const auto& pair : m.concepts()) {
        const auto& qn(pair.first);
        const auto& c(pair.second);

        if (factory.is_concept_name_n(0, qn))
            BOOST_REQUIRE(c.refines().empty());
        else if (factory.is_concept_name_n(1, qn)) {
            BOOST_REQUIRE(c.refines().size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(0, c.refines().front()));
        } else if (factory.is_concept_name_n(2, qn)) {
            BOOST_REQUIRE(c.refines().size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(1, c.refines().front()));
        } else
            BOOST_FAIL("Unexpected concept: " << qn);
    }

    dogen::sml::concept_indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

    for (const auto& pair : m.concepts()) {
        const auto& qn(pair.first);
        const auto& c(pair.second);

        if (factory.is_concept_name_n(0, qn)) {
            BOOST_CHECK(c.refines().empty());
        } else if (factory.is_concept_name_n(1, qn)) {
            BOOST_CHECK(c.refines().size() == 1);
        } else if (factory.is_concept_name_n(2, qn)) {
            BOOST_CHECK(c.refines().size() == 2);
        } else
            BOOST_FAIL("Unexpected concept: " << qn);
    }

    BOOST_REQUIRE(m.objects().size() == 3);
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        const auto& o(pair.second);

        const auto i(o.relationships().find(mc));
        BOOST_REQUIRE(i != o.relationships().end());

        if (factory.is_type_name_n(0, qn))
            BOOST_CHECK(i->second.size() == 1);
        else if (factory.is_type_name_n(1, qn)) {
            BOOST_CHECK(i->second.size() == 2);
        } else if (factory.is_type_name_n(2, qn)) {
                BOOST_CHECK(i->second.size() == 3);
        } else
            BOOST_FAIL("Unexpected object: " << qn);
    }
}

BOOST_AUTO_TEST_CASE(model_with_diamond_concept_inheritance_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_diamond_concept_inheritance_results_in_expected_indices");

    auto m(factory.build_diamond_inheritance_concepts_model());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

    using dogen::sml::relationship_types;
    const auto mc(relationship_types::modeled_concepts);
    const auto par(relationship_types::parents);
    BOOST_REQUIRE(m.objects().size() == 1);
    {
        const auto& qn(m.objects().begin()->first);
        const auto& o(m.objects().begin()->second);

        if (factory.is_type_name_n(0, qn)) {

            auto i(o.relationships().find(mc));
            BOOST_REQUIRE(i != o.relationships().end());
            BOOST_REQUIRE(i->second.size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(3, i->second.front()));

            i = o.relationships().find(par);
            BOOST_REQUIRE(i == o.relationships().end());
        } else
            BOOST_FAIL("Unexpected object: " << qn);
    }

    BOOST_REQUIRE(m.concepts().size() == 4);
    for (const auto& pair : m.concepts()) {
        const auto& qn(pair.first);
        const auto& c(pair.second);

        if (factory.is_concept_name_n(0, qn))
            BOOST_REQUIRE(c.refines().empty());
        else if (factory.is_concept_name_n(1, qn)) {
            BOOST_REQUIRE(c.refines().size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(0, c.refines().front()));
        } else if (factory.is_concept_name_n(2, qn)) {
            BOOST_REQUIRE(c.refines().size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(0, c.refines().front()));
        } else if (factory.is_concept_name_n(3, qn)) {
            BOOST_REQUIRE(c.refines().size() == 2);
            BOOST_REQUIRE(
                factory.is_concept_name_n(1, c.refines().front()) ||
                factory.is_concept_name_n(2, c.refines().front()));
            BOOST_REQUIRE(
                factory.is_concept_name_n(1, c.refines().back()) ||
                factory.is_concept_name_n(2, c.refines().back()));
        } else
            BOOST_FAIL("Unexpected concept: " << qn);
    }

    dogen::sml::concept_indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;
    BOOST_CHECK(m.concepts().size() == 4);
    for (const auto& pair : m.concepts()) {
        const auto& qn(pair.first);
        const auto& c(pair.second);

        if (factory.is_concept_name_n(0, qn)) {
            BOOST_CHECK(c.refines().empty());
        } else if (factory.is_concept_name_n(1, qn)) {
            BOOST_CHECK(c.refines().size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(0, c.refines().front()));
        } else if (factory.is_concept_name_n(2, qn)) {
            BOOST_CHECK(c.refines().size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(0, c.refines().front()));
        } else if (factory.is_concept_name_n(3, qn)) {
            BOOST_CHECK(c.refines().size() == 3);
            bool found_zero(false), found_one(false), found_two(false);
            for (const auto& qn : c.refines()) {
                found_zero = found_zero || factory.is_concept_name_n(0, qn);
                found_one = found_one || factory.is_concept_name_n(1, qn);
                found_two = found_two || factory.is_concept_name_n(2, qn);
            }
            BOOST_CHECK(found_zero);
            BOOST_CHECK(found_one);
            BOOST_CHECK(found_two);
        } else
            BOOST_FAIL("Unexpected concept: " << qn);
    }

    BOOST_REQUIRE(m.objects().size() == 1);
    {
        const auto& qn(m.objects().begin()->first);
        const auto& o(m.objects().begin()->second);

        const auto i(o.relationships().find(mc));
        BOOST_REQUIRE(i != o.relationships().end());

        BOOST_CHECK(factory.is_type_name_n(0, qn));
        BOOST_CHECK(i->second.size() == 4);
    }
}

BOOST_AUTO_TEST_CASE(model_with_single_parent_that_does_not_model_concepts_is_untouched_by_concept_indexer) {
    SETUP_TEST_LOG_SOURCE("model_with_single_parent_that_does_not_model_concepts_is_untouched_by_concept_indexer");

    auto a(factory.object_with_parent_in_the_same_model());
    const auto e(factory.object_with_parent_in_the_same_model());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << a;

    BOOST_REQUIRE(a.objects().size() == 2);
    BOOST_REQUIRE(a.concepts().empty());

    dogen::sml::concept_indexer ind;
    ind.index(a);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_third_degree_inheritance_that_does_not_model_concepts_is_untouched_by_concept_indexer) {
    SETUP_TEST_LOG_SOURCE("model_with_third_degree_inheritance_that_does_not_model_concepts_is_untouched_by_concept_indexer");

    auto a(factory.object_with_third_degree_parent_in_same_model());
    const auto e(factory.object_with_third_degree_parent_in_same_model());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << a;

    BOOST_REQUIRE(a.objects().size() == 4);
    BOOST_REQUIRE(a.concepts().empty());

    dogen::sml::concept_indexer ind;
    ind.index(a);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_containing_object_with_parent_that_models_concept_is_untouched_by_concept_indexer) {
    SETUP_TEST_LOG_SOURCE("model_containing_object_with_parent_that_models_concept_is_untouched_by_concept_indexer");

    auto a(factory.build_object_with_parent_that_models_concept());
    const auto e(factory.build_object_with_parent_that_models_concept());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << a;

    BOOST_REQUIRE(a.concepts().size() == 1);
    for (const auto& pair : a.concepts()) {
        const auto& qn(pair.first);
        const auto& c(pair.second);

        if (factory.is_concept_name_n(0, qn))
            BOOST_REQUIRE(c.refines().empty());
        else
            BOOST_FAIL("Unexpected object: " << qn);
    }

    using dogen::sml::relationship_types;
    const auto mc(relationship_types::modeled_concepts);
    const auto par(relationship_types::parents);

    BOOST_REQUIRE(a.objects().size() == 2);
    for (const auto& pair : a.objects()) {
        const auto& qn(pair.first);
        const auto& o(pair.second);

        auto i(o.relationships().find(mc));
        if (factory.is_type_name_n(0, qn)) {
            BOOST_REQUIRE(i != o.relationships().end());
            BOOST_REQUIRE(i->second.size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(0, i->second.front()));
        } else if (factory.is_type_name_n(1, qn)) {
            BOOST_REQUIRE(i == o.relationships().end());

            i = o.relationships().find(par);
            BOOST_REQUIRE(i != o.relationships().end());
            BOOST_REQUIRE(i->second.size() == 1);
            BOOST_REQUIRE(factory.is_type_name_n(0, i->second.front()));
        } else
            BOOST_FAIL("Unexpected object: " << qn);
    }

    dogen::sml::concept_indexer ind;
    ind.index(a);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << a;
    BOOST_CHECK(asserter::assert_object(e, a));
}

BOOST_AUTO_TEST_CASE(model_with_containing_object_with_parent_that_models_a_refined_concept_results_in_expected_indices) {
    SETUP_TEST_LOG_SOURCE("model_with_containing_object_with_parent_that_models_a_refined_concept_results_in_expected_indices");

    auto m(factory.build_object_with_parent_that_models_a_refined_concept());
    BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

    BOOST_REQUIRE(m.concepts().size() == 2);
    for (const auto& pair : m.concepts()) {
        const auto& qn(pair.first);
        const auto& c(pair.second);

        if (factory.is_concept_name_n(0, qn))
            BOOST_REQUIRE(c.refines().empty());
        else if (factory.is_concept_name_n(1, qn)) {
            BOOST_REQUIRE(c.refines().size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(0, c.refines().front()));
        } else
            BOOST_FAIL("Unexpected object: " << qn);
    }

    using dogen::sml::relationship_types;
    const auto mc(relationship_types::modeled_concepts);
    const auto par(relationship_types::parents);

    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        const auto& o(pair.second);

        auto i(o.relationships().find(mc));
        if (factory.is_type_name_n(0, qn)) {
            BOOST_REQUIRE(i != o.relationships().end());
            BOOST_REQUIRE(i->second.size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(1, i->second.front()));
        } else if (factory.is_type_name_n(1, qn)) {
            BOOST_REQUIRE(i == o.relationships().end());

            i = o.relationships().find(par);
            BOOST_REQUIRE(i != o.relationships().end());
            BOOST_REQUIRE(i->second.size() == 1);
            BOOST_REQUIRE(factory.is_type_name_n(0, i->second.front()));
        } else
            BOOST_FAIL("Unexpected object: " << qn);
    }

    dogen::sml::concept_indexer ind;
    ind.index(m);
    BOOST_LOG_SEV(lg, debug) << "after indexing: " << m;

    BOOST_CHECK(m.concepts().size() == 2);
    for (const auto& pair : m.concepts()) {
        const auto& qn(pair.first);
        const auto& c(pair.second);

        if (factory.is_concept_name_n(0, qn)) {
            BOOST_CHECK(c.refines().empty());
        } else if (factory.is_concept_name_n(1, qn)) {
            BOOST_CHECK(c.refines().size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(0, c.refines().front()));
        } else
            BOOST_FAIL("Unexpected concept: " << qn);
    }

    BOOST_REQUIRE(m.objects().size() == 2);
    for (const auto& pair : m.objects()) {
        const auto& qn(pair.first);
        const auto& o(pair.second);

        auto i(o.relationships().find(mc));
        if (factory.is_type_name_n(0, qn)) {
            BOOST_REQUIRE(i->second.size() == 2);
            BOOST_REQUIRE(
                factory.is_concept_name_n(0, i->second.front()) ||
                factory.is_concept_name_n(1, i->second.front()));
            BOOST_REQUIRE(
                factory.is_concept_name_n(0, i->second.back()) ||
                factory.is_concept_name_n(1, i->second.back()));
        } else if (factory.is_type_name_n(1, qn)) {
            BOOST_REQUIRE(i == o.relationships().end());

            i = o.relationships().find(par);
            BOOST_REQUIRE(i != o.relationships().end());
            BOOST_REQUIRE(i->second.size() == 1);
            BOOST_REQUIRE(factory.is_type_name_n(0, i->second.front()));
        } else
            BOOST_FAIL("Unexpected object: " << qn);
    }
}

BOOST_AUTO_TEST_CASE(model_with_concept_that_refines_missing_concept_throws) {
    SETUP_TEST_LOG_SOURCE("model_with_concept_that_refines_missing_concept_throws");

    auto m(factory.build_concept_that_refines_missing_concept());
    BOOST_REQUIRE(m.objects().empty());
    BOOST_REQUIRE(m.concepts().size() == 1);
    {
        const auto& qn(m.concepts().begin()->first);
        const auto& c(m.concepts().begin()->second);

        if (factory.is_concept_name_n(1, qn)) {
            BOOST_REQUIRE(c.refines().size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(0, c.refines().front()));
        } else
            BOOST_FAIL("Unexpected object: " << qn);
    }

    BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

    dogen::sml::concept_indexer i;
    using dogen::sml::indexing_error;
    contains_checker<indexing_error> c(concept_not_found);
    BOOST_CHECK_EXCEPTION(i.index(m), indexing_error, c);
}

BOOST_AUTO_TEST_CASE(model_with_object_that_models_missing_concept_throws) {
    SETUP_TEST_LOG_SOURCE("model_with_object_that_models_missing_concept_throws");

    auto m(factory.build_object_that_models_missing_concept());
    BOOST_REQUIRE(m.concepts().empty());
    BOOST_REQUIRE(m.objects().size() == 1);
    {
        const auto& qn(m.objects().begin()->first);
        if (!factory.is_type_name_n(0, qn))
            BOOST_FAIL("Unexpected object: " << qn);

        const auto& o(m.objects().begin()->second);
        using dogen::sml::relationship_types;
        const auto mc(relationship_types::modeled_concepts);
        auto i(o.relationships().find(mc));

        BOOST_REQUIRE(i != o.relationships().end());
        BOOST_REQUIRE(i->second.size() == 1);
        BOOST_REQUIRE(factory.is_concept_name_n(0, i->second.front()));
    }

    BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

    dogen::sml::concept_indexer i;
    using dogen::sml::indexing_error;
    contains_checker<indexing_error> c(concept_not_found);
    BOOST_CHECK_EXCEPTION(i.index(m), indexing_error, c);
}

BOOST_AUTO_TEST_CASE(model_with_object_with_missing_parent_throws) {
    SETUP_TEST_LOG_SOURCE("build_object_that_models_concept_with_missing_parent");

    auto m(factory.build_object_that_models_concept_with_missing_parent());
    BOOST_REQUIRE(m.concepts().size() == 1);
    {
        const auto& qn(m.concepts().begin()->first);
        const auto& c(m.concepts().begin()->second);

        if (factory.is_concept_name_n(0, qn))
            BOOST_REQUIRE(c.refines().empty());
        else
            BOOST_FAIL("Unexpected object: " << qn);
    }

    BOOST_REQUIRE(m.objects().size() == 1);
    {
        const auto& qn(m.objects().begin()->first);
        const auto& o(m.objects().begin()->second);

        using dogen::sml::relationship_types;
        const auto mc(relationship_types::modeled_concepts);

        auto i(o.relationships().find(mc));
        if (factory.is_type_name_n(1, qn)) {
            BOOST_REQUIRE(i != o.relationships().end());
            BOOST_REQUIRE(i->second.size() == 1);
            BOOST_REQUIRE(factory.is_concept_name_n(0, i->second.front()));

            const auto par(relationship_types::parents);
            i = o.relationships().find(par);
            BOOST_REQUIRE(i != o.relationships().end());
            BOOST_REQUIRE(i->second.size() == 1);
            BOOST_REQUIRE(factory.is_type_name_n(0, i->second.front()));
        } else
            BOOST_FAIL("Unexpected object: " << qn);
    }

    BOOST_LOG_SEV(lg, debug) << "before indexing: " << m;

    dogen::sml::concept_indexer i;
    using dogen::sml::indexing_error;
    contains_checker<indexing_error> c(object_not_found);
    BOOST_CHECK_EXCEPTION(i.index(m), indexing_error, c);
}

BOOST_AUTO_TEST_SUITE_END()
