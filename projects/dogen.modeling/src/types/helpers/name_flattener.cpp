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
#include "dogen.modeling/types/helpers/name_flattener.hpp"

namespace dogen {
namespace modeling {
namespace helpers {

name_flattener::name_flattener(const bool detect_model_name)
    : detect_model_name_(detect_model_name) {}

std::list<std::string>
name_flattener::flatten(const meta_model::name& n) const {
    const auto& l(n.location());
    std::list<std::string> r(l.external_modules());

    for (const auto& m : l.model_modules())
        r.push_back(m);

    for (const auto& m : l.internal_modules())
        r.push_back(m);


    if (!detect_model_name_)
        return r;

    /* if the name belongs to the model's module, we need to remove the
     * module's simple name from the module path (it is in both the
     * module path and it is also the module's simple name).
     */
    const bool no_internal_modules(l.internal_modules().empty());
    const bool has_model_modules(!l.model_modules().empty());
    const bool is_model_name(no_internal_modules && has_model_modules &&
        n.simple() == l.model_modules().back());

    if (is_model_name)
        r.pop_back();

    return r;
}

} } }
