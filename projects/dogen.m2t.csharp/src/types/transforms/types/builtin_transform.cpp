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
#include "dogen.logical/types/entities/structural/builtin.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t.csharp/types/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/types/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/assistant.hpp"
#include "dogen.m2t.csharp/types/transforms/types/builtin_transform.hpp"

namespace dogen::m2t::csharp::transforms::types {

std::string builtin_transform::static_id() {
    return traits::builtin_archetype();
}

std::string builtin_transform::id() const {
    return static_id();
}

physical::entities::location builtin_transform::archetype_location() const {
    static physical::entities::location
        r(csharp::traits::backend(), traits::facet(),
          builtin_transform::static_id());
    return r;
}

const logical::entities::name& builtin_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_builtin_name());
    return r;
}

std::string builtin_transform::family() const {
    return csharp::traits::csharp_family();
}

boost::filesystem::path builtin_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path(n, static_id());
}

std::list<std::string> builtin_transform::
inclusion_dependencies(const logical::entities::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

physical::entities::artefact builtin_transform::
format(const context& /*ctx*/, const logical::entities::element& /*e*/) const {
    physical::entities::artefact r;
    return r;
}

}
