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
#include <boost/date_time/posix_time/posix_time.hpp>
#include "dogen.formatting/types/code_generation_marker_factory.hpp"

namespace {

const std::string default_message("This file was generated by Dogen.");
const std::string default_warning("WARNING: do not edit this file.");
const std::string generation_timestamp("Generation timestamp: ");

}


namespace dogen::formatting {

code_generation_marker_factory::code_generation_marker_factory()
    : add_date_time_(false), add_warning_(false) { }

code_generation_marker_factory::
code_generation_marker_factory(const bool add_date_time,
    const bool add_warning, const std::string& message)
    : add_date_time_(add_date_time), add_warning_(add_warning),
      message_(message) { }

std::string code_generation_marker_factory::make() const {
    std::ostringstream s;

    if (message_.empty())
        s << default_message << std::endl;
    else
        s << message_ << std::endl;

    if (add_date_time_) {
        using namespace boost::posix_time;
        ptime now(second_clock::local_time());
        s << generation_timestamp << to_iso_extended_string(now) << std::endl;
    }

    if (add_warning_)
        s << default_warning << std::endl;

    return s.str();
}

}
