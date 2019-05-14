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
#ifndef DOGEN_EXTRACTION_LEXICAL_CAST_META_MODEL_OPERATION_REASON_LC_HPP
#define DOGEN_EXTRACTION_LEXICAL_CAST_META_MODEL_OPERATION_REASON_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.extraction/types/meta_model/operation_reason.hpp"

namespace boost {

template<>
std::string lexical_cast(const dogen::extraction::meta_model::operation_reason& v) {
    using dogen::extraction::meta_model::operation_reason;

    switch (v) {
    case operation_reason::invalid:
        return "operation_reason::invalid";
    case operation_reason::newly_generated:
        return "operation_reason::newly_generated";
    case operation_reason::changed_generated:
        return "operation_reason::changed_generated";
    case operation_reason::unchanged_generated:
        return "operation_reason::unchanged_generated";
    case operation_reason::already_exists:
        return "operation_reason::already_exists";
    case operation_reason::ignore_generated:
        return "operation_reason::ignore_generated";
    case operation_reason::force_write:
        return "operation_reason::force_write";
    case operation_reason::unexpected:
        return "operation_reason::unexpected";
    case operation_reason::ignore_unexpected:
        return "operation_reason::ignore_unexpected";
    case operation_reason::ignore_regex:
        return "operation_reason::ignore_regex";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
dogen::extraction::meta_model::operation_reason lexical_cast(const std::string & s) {
    using dogen::extraction::meta_model::operation_reason;

    if (s == "invalid" || s == "operation_reason::invalid")
        return operation_reason::invalid;
    if (s == "newly_generated" || s == "operation_reason::newly_generated")
        return operation_reason::newly_generated;
    if (s == "changed_generated" || s == "operation_reason::changed_generated")
        return operation_reason::changed_generated;
    if (s == "unchanged_generated" || s == "operation_reason::unchanged_generated")
        return operation_reason::unchanged_generated;
    if (s == "already_exists" || s == "operation_reason::already_exists")
        return operation_reason::already_exists;
    if (s == "ignore_generated" || s == "operation_reason::ignore_generated")
        return operation_reason::ignore_generated;
    if (s == "force_write" || s == "operation_reason::force_write")
        return operation_reason::force_write;
    if (s == "unexpected" || s == "operation_reason::unexpected")
        return operation_reason::unexpected;
    if (s == "ignore_unexpected" || s == "operation_reason::ignore_unexpected")
        return operation_reason::ignore_unexpected;
    if (s == "ignore_regex" || s == "operation_reason::ignore_regex")
        return operation_reason::ignore_regex;
    throw boost::bad_lexical_cast();
}

}

#endif
