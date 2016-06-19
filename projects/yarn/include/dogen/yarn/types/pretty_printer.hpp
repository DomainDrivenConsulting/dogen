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
#ifndef DOGEN_YARN_TYPES_PRETTY_PRINTER_HPP
#define DOGEN_YARN_TYPES_PRETTY_PRINTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <sstream>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/name_tree.hpp"
#include "dogen/yarn/types/separators.hpp"

namespace dogen {
namespace yarn {

class pretty_printer {
public:
    pretty_printer();
    explicit pretty_printer(const separators s);

private:
    std::list<std::string> to_list(const name& n,
        const bool skip_simple_name) const;

private:
    void print_scoped(const std::string& separator,
        const std::list<std::string>& l);
    void print_enclosed(const std::list<std::string>& l);

public:
    void add(const name& n, const bool skip_simple_name = false);
    void add(const name_tree& nt);

public:
    std::string print();

private:
    bool has_name_trees_;
    bool last_name_tree_had_children_;
    std::ostringstream stream_;
    const separators separator_;
};

} }

#endif
