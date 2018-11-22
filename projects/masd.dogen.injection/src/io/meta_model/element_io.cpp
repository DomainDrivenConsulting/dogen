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
#include <boost/io/ios_state.hpp>
#include <boost/algorithm/string.hpp>
#include "masd.dogen.injection/io/meta_model/element_io.hpp"
#include "masd.dogen.injection/io/meta_model/attribute_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::pair<std::string, std::string>& v) {
    s << "{ " << "\"__type__\": " << "\"std::pair\"" << ", ";

    s << "\"first\": " << "\"" << tidy_up_string(v.first) << "\"" << ", ";
    s << "\"second\": " << "\"" << tidy_up_string(v.second) << "\"";
    s << " }";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<std::pair<std::string, std::string> >& v) {
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

inline std::ostream& operator<<(std::ostream& s, const std::list<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::list<masd::dogen::injection::meta_model::attribute>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << *i;
    }
    s << "] ";
    return s;
}

}

namespace masd::dogen::injection::meta_model {

std::ostream& operator<<(std::ostream& s, const element& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"masd::dogen::injection::meta_model::element\"" << ", "
      << "\"name\": " << "\"" << tidy_up_string(v.name()) << "\"" << ", "
      << "\"documentation\": " << "\"" << tidy_up_string(v.documentation()) << "\"" << ", "
      << "\"tagged_values\": " << v.tagged_values() << ", "
      << "\"stereotypes\": " << v.stereotypes() << ", "
      << "\"parents\": " << v.parents() << ", "
      << "\"attributes\": " << v.attributes() << ", "
      << "\"fallback_element_type\": " << "\"" << tidy_up_string(v.fallback_element_type()) << "\"" << ", "
      << "\"can_be_primitive_underlier\": " << v.can_be_primitive_underlier() << ", "
      << "\"in_global_module\": " << v.in_global_module() << ", "
      << "\"can_be_enumeration_underlier\": " << v.can_be_enumeration_underlier() << ", "
      << "\"is_default_enumeration_type\": " << v.is_default_enumeration_type() << ", "
      << "\"is_associative_container\": " << v.is_associative_container() << ", "
      << "\"is_floating_point\": " << v.is_floating_point()
      << " }";
    return(s);
}

}
