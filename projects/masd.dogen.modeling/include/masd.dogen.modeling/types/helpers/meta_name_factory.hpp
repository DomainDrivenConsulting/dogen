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
#ifndef MASD_DOGEN_MODELING_TYPES_HELPERS_META_NAME_FACTORY_HPP
#define MASD_DOGEN_MODELING_TYPES_HELPERS_META_NAME_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "masd.dogen.modeling/types/meta_model/name.hpp"

namespace masd::dogen::modeling::helpers {

class meta_name_factory final {
private:
    static meta_model::location make_location();
    static meta_model::name make_name(const std::string& sn);

public:
    static meta_model::name make_exomodel_name();
    static meta_model::name make_endomodel_name();
    static meta_model::name make_model_name();

    static meta_model::name make_module_name();
    static meta_model::name make_object_template_name();
    static meta_model::name make_builtin_name();
    static meta_model::name make_enumeration_name();
    static meta_model::name make_primitive_name();
    static meta_model::name make_object_name();
    static meta_model::name make_exception_name();
    static meta_model::name make_visitor_name();
};

}

#endif
