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
#include "dogen/test_data/configuration_td.hpp"
#include "dogen/test_data/diffing_configuration_td.hpp"
#include "dogen/test_data/tracing_configuration_td.hpp"
#include "dogen/test_data/reporting_configuration_td.hpp"
#include "dogen/test_data/model_processing_configuration_td.hpp"

namespace {

dogen::model_processing_configuration
create_dogen_model_processing_configuration(const unsigned int position) {
    return dogen::model_processing_configuration_generator::create(position);
}

dogen::tracing_configuration
create_dogen_tracing_configuration(const unsigned int position) {
    return dogen::tracing_configuration_generator::create(position);
}

boost::optional<dogen::tracing_configuration>
create_boost_optional_dogen_tracing_configuration(unsigned int position) {
    boost::optional<dogen::tracing_configuration> r(
        create_dogen_tracing_configuration(position));
    return r;
}

dogen::diffing_configuration
create_dogen_diffing_configuration(const unsigned int position) {
    return dogen::diffing_configuration_generator::create(position);
}

boost::optional<dogen::diffing_configuration>
create_boost_optional_dogen_diffing_configuration(unsigned int position) {
    boost::optional<dogen::diffing_configuration> r(
        create_dogen_diffing_configuration(position));
    return r;
}

dogen::reporting_configuration
create_dogen_reporting_configuration(const unsigned int position) {
    return dogen::reporting_configuration_generator::create(position);
}

boost::optional<dogen::reporting_configuration>
create_boost_optional_dogen_reporting_configuration(unsigned int position) {
    boost::optional<dogen::reporting_configuration> r(
        create_dogen_reporting_configuration(position));
    return r;
}

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

}

namespace dogen {

configuration_generator::configuration_generator() : position_(0) { }

void configuration_generator::
populate(const unsigned int position, result_type& v) {
    v.model_processing(create_dogen_model_processing_configuration(position + 0));
    v.tracing(create_boost_optional_dogen_tracing_configuration(position + 1));
    v.diffing(create_boost_optional_dogen_diffing_configuration(position + 2));
    v.reporting(create_boost_optional_dogen_reporting_configuration(position + 3));
    v.byproduct_directory(create_boost_filesystem_path(position + 4));
}

configuration_generator::result_type
configuration_generator::create(const unsigned int position) {
    configuration r;
    configuration_generator::populate(position, r);
    return r;
}

configuration_generator::result_type*
configuration_generator::create_ptr(const unsigned int position) {
    configuration* p = new configuration();
    configuration_generator::populate(position, *p);
    return p;
}

configuration_generator::result_type
configuration_generator::operator()() {
    return create(position_++);
}

}