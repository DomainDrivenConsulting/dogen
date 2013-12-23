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
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/dia_to_sml/types/all.hpp"
#include "dogen/dia_to_sml/io/all_io.hpp"
#include "dogen/dia_to_sml/test_data/all_td.hpp"
#include "dogen/dia_to_sml/serialization/all_ser.hpp"
#include "dogen/dia_to_sml/serialization/registrar_ser.hpp"

template<typename Archive> void register_types(Archive& ar) {
    dogen::dia_to_sml::register_types<Archive>(ar);
}

namespace {

const std::string empty;
const std::string test_module("dia_to_sml");
const std::string test_suite("serialization_spec");

}

using namespace dogen::dia_to_sml;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(serialization)

BOOST_AUTO_TEST_CASE(validate_serialization) {
    SETUP_TEST_LOG("validate_serialization");

    roundtrip_type<context_generator>();
    roundtrip_type<node_generator>();
    roundtrip_type<profile_generator>();
    roundtrip_type<object_types_generator>();
    roundtrip_type<processed_object_generator>();
    roundtrip_type<processed_property_generator>();
}

BOOST_AUTO_TEST_SUITE_END()
