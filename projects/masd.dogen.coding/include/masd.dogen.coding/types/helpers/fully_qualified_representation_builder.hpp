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
#ifndef MASD_DOGEN_CODING_TYPES_HELPERS_FULLY_QUALIFIED_REPRESENTATION_BUILDER_HPP
#define MASD_DOGEN_CODING_TYPES_HELPERS_FULLY_QUALIFIED_REPRESENTATION_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.coding/types/meta_model/name.hpp"
#include "masd.dogen.coding/types/meta_model/name_tree.hpp"
#include "masd.dogen.coding/types/helpers/pretty_printer.hpp"
#include "masd.dogen.coding/types/meta_model/fully_qualified_representation.hpp"

namespace masd::dogen::coding::helpers {

/**
 * @brief Builds a fully qualified representation of a qualifiable
 * model element such as a name or a name tree.
 */
class fully_qualified_representation_builder final {
public:
    fully_qualified_representation_builder();

public:
    /**
     * @brief Adds the qualifiable model element to the pretty printers.
     */
    /**@{*/
    void add(const meta_model::name& n);
    void add(const meta_model::name_tree& nt);
    /**@}*/

public:
    /**
     * @brief Builds the representation.
     *
     * @pre Add must have been called at least once.
     */
    meta_model::fully_qualified_representation build();

    /**
     * @brief Builds the representation for the supplied name.
     */
    meta_model::fully_qualified_representation
    build(const meta_model::name& n, const bool model_name_mode);

private:
    pretty_printer dot_printer_;
    pretty_printer colon_printer_;
};

}

#endif
