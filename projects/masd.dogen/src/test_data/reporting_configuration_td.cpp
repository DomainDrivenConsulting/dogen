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
#include "masd.dogen/test_data/reporting_style_td.hpp"
#include "masd.dogen/test_data/reporting_configuration_td.hpp"

namespace {

masd::dogen::reporting_style
create_masd_dogen_reporting_style(const unsigned int position) {
    return masd::dogen::reporting_style_generator::create(position);
}

boost::filesystem::path
create_boost_filesystem_path(const unsigned int position) {
    std::ostringstream s;
    s << "/a/path/number_" << position;
    return boost::filesystem::path(s.str());
}

}

namespace masd::dogen {

reporting_configuration_generator::reporting_configuration_generator() : position_(0) { }

void reporting_configuration_generator::
populate(const unsigned int position, result_type& v) {
    v.style(create_masd_dogen_reporting_style(position + 0));
    v.output_directory(create_boost_filesystem_path(position + 1));
}

reporting_configuration_generator::result_type
reporting_configuration_generator::create(const unsigned int position) {
    reporting_configuration r;
    reporting_configuration_generator::populate(position, r);
    return r;
}

reporting_configuration_generator::result_type*
reporting_configuration_generator::create_ptr(const unsigned int position) {
    reporting_configuration* p = new reporting_configuration();
    reporting_configuration_generator::populate(position, *p);
    return p;
}

reporting_configuration_generator::result_type
reporting_configuration_generator::operator()() {
    return create(position_++);
}

}
