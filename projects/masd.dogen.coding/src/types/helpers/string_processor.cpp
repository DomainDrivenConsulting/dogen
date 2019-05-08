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
#include <boost/algorithm/string.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.coding/types/helpers/string_processor.hpp"

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("coding.helpers.string_processor"));

const std::string empty;
const std::string comma(",");
const std::string space(" ");
const std::string less_than("<");
const std::string more_than(">");
const std::string separator("_");
const std::string scope_operator("::");

}

namespace masd::dogen::coding::helpers {

std::string string_processor::to_identifiable(const std::string& s) {
    std::string r(s);
    BOOST_LOG_SEV(lg, trace) << "Input string: " << r;

    boost::replace_all(r, scope_operator, separator);
    boost::replace_all(r, less_than, separator);

    boost::replace_all(r, comma, empty);
    boost::replace_all(r, more_than, empty);
    boost::trim(r);

    boost::replace_all(r, space, separator);

    BOOST_LOG_SEV(lg, trace) << "Result: " << r;
    return r;
}

}
