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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_PHYSICAL_CONSTANT_RELATION_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_PHYSICAL_CONSTANT_RELATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen.identification/types/entities/label.hpp"

namespace dogen::logical::entities::physical {

class constant_relation final {
public:
    constant_relation() = default;
    constant_relation(const constant_relation&) = default;
    constant_relation(constant_relation&&) = default;
    ~constant_relation() = default;

public:
    constant_relation(
        const std::string& original_urn,
        const std::list<dogen::identification::entities::label>& labels,
        const std::string& logical_model_element_id);

public:
    /**
     * @brief URN pointing to an archetype or a label, as it was originally created by the user.
     *
     *  It must have the form "archetype:" if pointing to an archetype, or  "label:" if
     * pointing to a label, and then is followed by "KEY:VALUE". The label must resolve
     * to a unique archetype.
     */
    /**@{*/
    const std::string& original_urn() const;
    std::string& original_urn();
    void original_urn(const std::string& v);
    void original_urn(const std::string&& v);
    /**@}*/

    /**
     * @brief All labels associated with this element.
     */
    /**@{*/
    const std::list<dogen::identification::entities::label>& labels() const;
    std::list<dogen::identification::entities::label>& labels();
    void labels(const std::list<dogen::identification::entities::label>& v);
    void labels(const std::list<dogen::identification::entities::label>&& v);
    /**@}*/

    const std::string& logical_model_element_id() const;
    std::string& logical_model_element_id();
    void logical_model_element_id(const std::string& v);
    void logical_model_element_id(const std::string&& v);

public:
    bool operator==(const constant_relation& rhs) const;
    bool operator!=(const constant_relation& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(constant_relation& other) noexcept;
    constant_relation& operator=(constant_relation other);

private:
    std::string original_urn_;
    std::list<dogen::identification::entities::label> labels_;
    std::string logical_model_element_id_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::physical::constant_relation& lhs,
    dogen::logical::entities::physical::constant_relation& rhs) {
    lhs.swap(rhs);
}

}

#endif
