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
#include "dogen.text.cpp/io/formattables/model_io.hpp"
#include "dogen.text.cpp/io/formattables/formattable_io.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.text.cpp/io/formattables/cpp_standards_io.hpp"
#include "dogen.identification/io/entities/logical_name_io.hpp"
#include "dogen.logical/io/entities/streaming_properties_io.hpp"

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<dogen::identification::entities::logical_id, dogen::logical::entities::streaming_properties>& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << i->first;
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::formattable>& v) {
    s << "[";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "[ { " << "\"__type__\": " << "\"key\"" << ", " << "\"data\": ";
        s << i->first;
        s << " }, { " << "\"__type__\": " << "\"value\"" << ", " << "\"data\": ";
        s << i->second;
        s << " } ]";
    }
    s << " ] ";
    return s;
}

}

namespace dogen::text::cpp::formattables {

std::ostream& operator<<(std::ostream& s, const model& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::text::cpp::formattables::model\"" << ", "
      << "\"name\": " << v.name() << ", "
      << "\"streaming_properties\": " << v.streaming_properties() << ", "
      << "\"formattables\": " << v.formattables() << ", "
      << "\"cpp_standard\": " << v.cpp_standard()
      << " }";
    return(s);
}

}
