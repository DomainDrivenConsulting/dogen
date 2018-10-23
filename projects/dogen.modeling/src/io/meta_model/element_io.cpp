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
#include "dogen.annotations/io/annotation_io.hpp"
#include "dogen.modeling/io/meta_model/name_io.hpp"
#include "dogen.modeling/io/meta_model/element_io.hpp"
#include "dogen.formatting/io/decoration_properties_io.hpp"
#include "dogen.modeling/io/meta_model/origin_types_io.hpp"
#include "dogen.modeling/io/meta_model/opaque_properties_io.hpp"
#include "dogen.modeling/io/meta_model/static_stereotypes_io.hpp"
#include "dogen.modeling/io/meta_model/artefact_properties_io.hpp"
#include "dogen.modeling/io/meta_model/local_archetype_location_properties_io.hpp"

namespace dogen::modeling::meta_model {

std::ostream& operator<<(std::ostream& s, const element& v) {
    v.to_stream(s);
    return(s);
}

}
