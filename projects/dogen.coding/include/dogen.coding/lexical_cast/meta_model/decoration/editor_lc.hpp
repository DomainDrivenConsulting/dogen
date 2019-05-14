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
#ifndef DOGEN_CODING_LEXICAL_CAST_META_MODEL_DECORATION_EDITOR_LC_HPP
#define DOGEN_CODING_LEXICAL_CAST_META_MODEL_DECORATION_EDITOR_LC_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include "dogen.coding/types/meta_model/decoration/editor.hpp"

namespace boost {

template<>
std::string lexical_cast(const dogen::coding::meta_model::decoration::editor& v) {
    using dogen::coding::meta_model::decoration::editor;

    switch (v) {
    case editor::invalid:
        return "editor::invalid";
    case editor::emacs:
        return "editor::emacs";
    case editor::vi:
        return "editor::vi";
    case editor::vim:
        return "editor::vim";
    case editor::ex:
        return "editor::ex";
    default:
        throw boost::bad_lexical_cast();
    }
}

template<>
dogen::coding::meta_model::decoration::editor lexical_cast(const std::string & s) {
    using dogen::coding::meta_model::decoration::editor;

    if (s == "invalid" || s == "editor::invalid")
        return editor::invalid;
    if (s == "emacs" || s == "editor::emacs")
        return editor::emacs;
    if (s == "vi" || s == "editor::vi")
        return editor::vi;
    if (s == "vim" || s == "editor::vim")
        return editor::vim;
    if (s == "ex" || s == "editor::ex")
        return editor::ex;
    throw boost::bad_lexical_cast();
}

}

#endif
