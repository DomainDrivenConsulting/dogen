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
#include <sstream>
#include <boost/test/unit_test.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/cpp/types/formatters/cpp_indenter.hpp"

namespace {

const std::string empty;
const std::string test_module("generator");
const std::string test_suite("indenter_spec");

}

BOOST_AUTO_TEST_SUITE(indenter)

BOOST_AUTO_TEST_CASE(default_indenter_does_not_indent) {
    SETUP_TEST_LOG_SOURCE("default_indenter_does_not_indent");
    dogen::cpp::formatters::cpp_indenter indenter;
    std::ostringstream stream;
    stream << indenter;
    BOOST_CHECK(stream.str().empty());
    BOOST_CHECK(indenter.empty());
    BOOST_LOG_SEV(lg, debug) << "zero indent: '" << indenter << "'";
}

BOOST_AUTO_TEST_CASE(indenting_increases_indentation_level) {
    SETUP_TEST_LOG_SOURCE("indenting_increases_indentation_level");
    dogen::cpp::formatters::cpp_indenter indenter;
    std::ostringstream stream;
    stream << (++indenter);
    BOOST_CHECK(!stream.str().empty());
    BOOST_CHECK(!indenter.empty());
    BOOST_LOG_SEV(lg, debug) << "one indent: '" << indenter << "'";

    unsigned int one_indent_size(stream.str().length());
    stream.str(empty);
    stream << (++indenter);
    BOOST_CHECK(!indenter.empty());
    BOOST_CHECK(stream.str().length() == 2 * one_indent_size);
    BOOST_LOG_SEV(lg, debug) << "two indent: '" << indenter << "'";

    stream.str(empty);
    stream << (++indenter);
    BOOST_CHECK(!indenter.empty());
    BOOST_CHECK(stream.str().length() == 3 * one_indent_size);
    BOOST_LOG_SEV(lg, debug)  << "three indent: '" << indenter << "'";
}

BOOST_AUTO_TEST_CASE(unindenting_decreases_indentation_level) {
    SETUP_TEST_LOG_SOURCE("unindenting_decreases_indentation_level");
    dogen::cpp::formatters::cpp_indenter indenter;
    BOOST_CHECK(indenter.empty());

    std::ostringstream stream;
    stream << (++indenter);
    BOOST_CHECK(!stream.str().empty());
    BOOST_CHECK(!indenter.empty());

    unsigned int one_indent_size(stream.str().length());
    ++indenter;

    stream.str(empty);
    stream << (++indenter);
    BOOST_CHECK(stream.str().length() == 3 * one_indent_size);
    BOOST_LOG_SEV(lg, debug) << "three indent: '" << indenter << "'";

    stream.str(empty);
    stream << (--indenter);
    BOOST_CHECK(stream.str().length() == 2 * one_indent_size);
    BOOST_LOG_SEV(lg, debug) << "two indent: '" << indenter << "'";

    stream.str(empty);
    stream << (--indenter);
    BOOST_CHECK(stream.str().length() == one_indent_size);
    BOOST_LOG_SEV(lg, debug) << "one indent: '" << indenter << "'";

    stream.str(empty);
    stream << (--indenter);
    BOOST_CHECK(stream.str().empty());
    BOOST_CHECK(indenter.empty());
    BOOST_LOG_SEV(lg, debug) << "zero indent: '" << indenter << "'";
}

BOOST_AUTO_TEST_CASE(unindenting_at_zero_indentation_level_does_nothing) {
    SETUP_TEST_LOG("unindenting_at_zero_indentation_level_does_nothing");
    dogen::cpp::formatters::cpp_indenter indenter;

    std::ostringstream stream;
    stream << (--indenter);
    BOOST_CHECK(stream.str().empty());

    stream << (++indenter);
    BOOST_CHECK(!stream.str().empty());
}

BOOST_AUTO_TEST_CASE(cpp_positive_indenter_scope_correctly_increases_and_decreases_indentation_level) {
    SETUP_TEST_LOG("cpp_positive_indenter_scope_correctly_increases_and_decreases_indentation_level");
    using namespace dogen::cpp::formatters;
    cpp_indenter indenter;

    std::ostringstream stream;
    stream << indenter;
    BOOST_CHECK(stream.str().empty());
    {
        cpp_positive_indenter_scope s(indenter);
        stream << indenter;
        BOOST_CHECK(!stream.str().empty());
        unsigned int one_indent_size(stream.str().length());
        {
            cpp_positive_indenter_scope s(indenter);
            stream.str(empty);
            stream << indenter;
            BOOST_CHECK(stream.str().length() == 2 * one_indent_size);
        }
        stream.str(empty);
        stream << indenter;
        BOOST_CHECK(stream.str().length() == one_indent_size);
    }
    stream.str(empty);
    stream << indenter;
    BOOST_CHECK(stream.str().empty());
}

BOOST_AUTO_TEST_CASE(cpp_negative_indenter_scope_correctly_decreases_and_increases_indentation_level) {
    SETUP_TEST_LOG_SOURCE("cpp_negative_indenter_scope_correctly_decreases_and_increases_indentation_level");
    using namespace dogen::cpp::formatters;
    cpp_indenter indenter;

    std::ostringstream stream;
    stream << indenter;
    BOOST_CHECK(stream.str().empty());

    stream << (++indenter);
    BOOST_CHECK(!stream.str().empty());
    unsigned int one_indent_size(stream.str().length());
    ++indenter;
    {
        cpp_negative_indenter_scope s(indenter);
        stream.str(empty);
        stream << indenter;
        BOOST_CHECK(stream.str().length() == one_indent_size);
        {
            cpp_negative_indenter_scope s(indenter);
            stream.str(empty);
            stream << indenter;
            BOOST_CHECK(stream.str().empty());
        }
        stream.str(empty);
        stream << indenter;
        BOOST_CHECK(stream.str().length() == one_indent_size);
    }
    stream.str(empty);
    stream << indenter;
    BOOST_CHECK(stream.str().length() == 2 * one_indent_size);
}

BOOST_AUTO_TEST_CASE(cpp_negative_indenter_scope_correctly_handles_zero_indentation_level) {
    SETUP_TEST_LOG("cpp_negative_indenter_scope_correctly_handles_zero_indentation_level");
    using namespace dogen::cpp::formatters;
    cpp_indenter indenter;

    std::ostringstream stream;
    stream << indenter;
    BOOST_CHECK(stream.str().empty());
    {
        cpp_negative_indenter_scope s(indenter);
        stream.str(empty);
        stream << indenter;
        BOOST_CHECK(stream.str().empty());
    }
    stream.str(empty);
    stream << indenter;
    BOOST_CHECK(stream.str().empty());
}

BOOST_AUTO_TEST_SUITE_END()
