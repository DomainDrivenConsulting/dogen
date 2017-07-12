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
#include "dogen/yarn/io/meta_model/name_io.hpp"
#include "dogen/yarn/io/meta_model/name_tree_io.hpp"
#include "dogen/yarn/io/helpers/decomposition_result_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::pair<std::string, dogen::yarn::meta_model::name>& v) {
    s << "{ " << "\"__type__\": " << "\"std::pair\"" << ", ";

    s << "\"first\": " << "\"" << tidy_up_string(v.first) << "\"" << ", ";
    s << "\"second\": " << v.second;
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::pair<std::string, dogen::yarn::meta_model::name> >& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::pair<std::string, dogen::yarn::meta_model::name_tree>& v) {
    s << "{ " << "\"__type__\": " << "\"std::pair\"" << ", ";

    s << "\"first\": " << "\"" << tidy_up_string(v.first) << "\"" << ", ";
    s << "\"second\": " << v.second;
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::pair<std::string, dogen::yarn::meta_model::name_tree> >& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace yarn {
namespace helpers {

std::ostream& operator<<(std::ostream& s, const decomposition_result& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::yarn::helpers::decomposition_result\"" << ", "
      << "\"names\": " << v.names() << ", "
      << "\"name_trees\": " << v.name_trees()
      << " }";
    return(s);
}

} } }
