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
#ifndef DOGEN_TEMPLATING_LEXICAL_CAST_STITCH_BLOCK_TYPES_LC_HPP
#define DOGEN_TEMPLATING_LEXICAL_CAST_STITCH_BLOCK_TYPES_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.templating/types/stitch/block_types.hpp"

namespace boost {

template<>
std::string lexical_cast(const dogen::templating::stitch::block_types& v) {
    using dogen::templating::stitch::block_types;

    switch (v) {
    case block_types::invalid:
        return "block_types::invalid";
    case block_types::text_block:
        return "block_types::text_block";
    case block_types::standard_control_block:
        return "block_types::standard_control_block";
    case block_types::expression_block:
        return "block_types::expression_block";
    case block_types::variable_block:
        return "block_types::variable_block";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
dogen::templating::stitch::block_types lexical_cast(const std::string & s) {
    using dogen::templating::stitch::block_types;

    if (s == "invalid" || s == "block_types::invalid")
        return block_types::invalid;
    if (s == "text_block" || s == "block_types::text_block")
        return block_types::text_block;
    if (s == "standard_control_block" || s == "block_types::standard_control_block")
        return block_types::standard_control_block;
    if (s == "expression_block" || s == "block_types::expression_block")
        return block_types::expression_block;
    if (s == "variable_block" || s == "block_types::variable_block")
        return block_types::variable_block;
    throw boost::bad_lexical_cast();
}

}

#endif
