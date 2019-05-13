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
#ifndef DOGEN_INJECTION_JSON_TYPES_DEHYDRATOR_HPP
#define DOGEN_INJECTION_JSON_TYPES_DEHYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <map>
#include <string>
#include <iosfwd>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.injection/types/meta_model/element.hpp"
#include "dogen.injection/types/meta_model/attribute.hpp"
#include "dogen.injection/types/meta_model/model.hpp"

namespace dogen::injection::json {

class dehydrator final {
private:
    static std::string tidy_up_string(std::string s);

private:
    static void insert_documentation(std::ostream& s, const std::string& d);
    static void insert_tagged_values(std::ostream& s,
        const std::list<std::pair<std::string, std::string>>& tv);
    static void insert_stereotypes(std::ostream& s,
        const std::list<std::string>& st);
    static void insert_parents(std::ostream& s,
        const std::list<std::string>& parents);
    static void insert_attribute(std::ostream& s,
        const injection::meta_model::attribute& a);
    static void insert_element(std::ostream& s,
        const injection::meta_model::element& e);

public:
    static std::string dehydrate(const injection::meta_model::model& m);
    static void dehydrate(const injection::meta_model::model& m,
        const boost::filesystem::path& p);
};

}

#endif
