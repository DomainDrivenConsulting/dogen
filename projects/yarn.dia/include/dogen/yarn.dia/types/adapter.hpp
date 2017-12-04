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
#ifndef DOGEN_YARN_DIA_TYPES_ADAPTER_HPP
#define DOGEN_YARN_DIA_TYPES_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/yarn/types/meta_model/exoelement.hpp"
#include "dogen/yarn/types/meta_model/exoattribute.hpp"
#include "dogen/yarn.dia/types/processed_object.hpp"
#include "dogen/yarn.dia/types/processed_attribute.hpp"

namespace dogen {
namespace yarn {
namespace dia {

/**
 * @brief Transforms Dia objects into their yarn counterpart.
 */
class adapter final {
private:
    /**
     * @brief Ensure the dia name is valid.
     */
    static void validate_dia_name(const std::string& n);

    /**
     * @brief Constructs a qualified name, taking into account the
     * contents of the contained by parameter.
     */
    static std::string qualified_name(const std::string& contained_by,
        const std::string& simple_name);

    /**
     * @brief Processes the stereotypes field.
     */
    static void process_stereotypes(const processed_object& po,
        meta_model::exoelement& ee);

private:
    /**
     * @brief Adapts a processed attribute into a yarn exoattribute.
     */
    static meta_model::exoattribute adapt(const processed_attribute& a);

public:
    /**
     * @brief Adapts a processed object into a yarn exoelement.
     */
    static meta_model::exoelement
    adapt(const processed_object& po, const std::string& contained_by,
        const std::list<std::string>& parents);
};

} } }

#endif
