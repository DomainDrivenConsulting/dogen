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
#ifndef MASD_DOGEN_GENERATION_CSHARP_TYPES_FORMATTABLES_MODEL_HPP
#define MASD_DOGEN_GENERATION_CSHARP_TYPES_FORMATTABLES_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "masd.dogen.modeling/types/meta_model/name.hpp"
#include "masd.dogen.generation.csharp/types/formattables/formattable.hpp"
#include "masd.dogen.generation.csharp/types/formattables/aspect_properties.hpp"
#include "masd.dogen.generation.csharp/types/formattables/assistant_properties.hpp"

namespace masd::dogen::generation::csharp::formattables {

class model final {
public:
    model() = default;
    model(const model&) = default;
    model(model&&) = default;
    ~model() = default;

public:
    model(
        const masd::dogen::modeling::meta_model::name& name,
        const std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::formattable>& formattables,
        const std::list<std::string>& project_items,
        const std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::aspect_properties>& aspect_properties,
        const std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::assistant_properties>& assistant_properties);

public:
    const masd::dogen::modeling::meta_model::name& name() const;
    masd::dogen::modeling::meta_model::name& name();
    void name(const masd::dogen::modeling::meta_model::name& v);
    void name(const masd::dogen::modeling::meta_model::name&& v);

    const std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::formattable>& formattables() const;
    std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::formattable>& formattables();
    void formattables(const std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::formattable>& v);
    void formattables(const std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::formattable>&& v);

    const std::list<std::string>& project_items() const;
    std::list<std::string>& project_items();
    void project_items(const std::list<std::string>& v);
    void project_items(const std::list<std::string>&& v);

    const std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::aspect_properties>& aspect_properties() const;
    std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::aspect_properties>& aspect_properties();
    void aspect_properties(const std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::aspect_properties>& v);
    void aspect_properties(const std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::aspect_properties>&& v);

    const std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::assistant_properties>& assistant_properties() const;
    std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::assistant_properties>& assistant_properties();
    void assistant_properties(const std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::assistant_properties>& v);
    void assistant_properties(const std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::assistant_properties>&& v);

public:
    bool operator==(const model& rhs) const;
    bool operator!=(const model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model& other) noexcept;
    model& operator=(model other);

private:
    masd::dogen::modeling::meta_model::name name_;
    std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::formattable> formattables_;
    std::list<std::string> project_items_;
    std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::aspect_properties> aspect_properties_;
    std::unordered_map<std::string, masd::dogen::generation::csharp::formattables::assistant_properties> assistant_properties_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::generation::csharp::formattables::model& lhs,
    masd::dogen::generation::csharp::formattables::model& rhs) {
    lhs.swap(rhs);
}

}

#endif
