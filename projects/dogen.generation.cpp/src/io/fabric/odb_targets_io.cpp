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
#include <ostream>
#include <boost/algorithm/string.hpp>
#include "dogen.generation.cpp/io/fabric/odb_target_io.hpp"
#include "dogen.generation.cpp/io/fabric/odb_targets_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<dogen::generation::cpp::fabric::odb_target>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen::generation::cpp::fabric {

std::ostream& operator<<(std::ostream& s, const odb_targets& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::generation::cpp::fabric::odb_targets\"" << ", "
      << "\"main_target_name\": " << "\"" << tidy_up_string(v.main_target_name()) << "\"" << ", "
      << "\"common_odb_options\": " << "\"" << tidy_up_string(v.common_odb_options()) << "\"" << ", "
      << "\"targets\": " << v.targets()
      << " }";
    return(s);
}

}
