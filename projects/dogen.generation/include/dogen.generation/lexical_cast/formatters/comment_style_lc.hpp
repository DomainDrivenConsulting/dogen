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
#ifndef DOGEN_GENERATION_LEXICAL_CAST_FORMATTERS_COMMENT_STYLE_LC_HPP
#define DOGEN_GENERATION_LEXICAL_CAST_FORMATTERS_COMMENT_STYLE_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.generation/types/formatters/comment_style.hpp"

namespace boost {

template<>
std::string lexical_cast(const dogen::generation::formatters::comment_style& v) {
    using dogen::generation::formatters::comment_style;

    switch (v) {
    case comment_style::invalid:
        return "comment_style::invalid";
    case comment_style::c_style:
        return "comment_style::c_style";
    case comment_style::cpp_style:
        return "comment_style::cpp_style";
    case comment_style::csharp_style:
        return "comment_style::csharp_style";
    case comment_style::shell_style:
        return "comment_style::shell_style";
    case comment_style::sql_style:
        return "comment_style::sql_style";
    case comment_style::xml_style:
        return "comment_style::xml_style";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
dogen::generation::formatters::comment_style lexical_cast(const std::string & s) {
    using dogen::generation::formatters::comment_style;

    if (s == "invalid" || s == "comment_style::invalid")
        return comment_style::invalid;
    if (s == "c_style" || s == "comment_style::c_style")
        return comment_style::c_style;
    if (s == "cpp_style" || s == "comment_style::cpp_style")
        return comment_style::cpp_style;
    if (s == "csharp_style" || s == "comment_style::csharp_style")
        return comment_style::csharp_style;
    if (s == "shell_style" || s == "comment_style::shell_style")
        return comment_style::shell_style;
    if (s == "sql_style" || s == "comment_style::sql_style")
        return comment_style::sql_style;
    if (s == "xml_style" || s == "comment_style::xml_style")
        return comment_style::xml_style;
    throw boost::bad_lexical_cast();
}

}

#endif
