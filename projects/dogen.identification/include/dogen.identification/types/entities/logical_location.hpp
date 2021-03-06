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
#ifndef DOGEN_IDENTIFICATION_TYPES_ENTITIES_LOGICAL_LOCATION_HPP
#define DOGEN_IDENTIFICATION_TYPES_ENTITIES_LOGICAL_LOCATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>

namespace dogen::identification::entities {

/**
 * @brief Identifies a hierarchy of containment within the logical space.
 */
class logical_location final {
public:
    logical_location() = default;
    logical_location(const logical_location&) = default;
    logical_location(logical_location&&) = default;
    ~logical_location() = default;

public:
    logical_location(
        const std::list<std::string>& external_modules,
        const std::list<std::string>& model_modules,
        const std::list<std::string>& internal_modules,
        const std::string& element);

public:
    /**
     * @brief All modules external to the model itself.
     *
     * It is sometimes useful to create a model within a set of existing
     * modules. In this case, the model does not own the existing modules and
     * they are considered "external" to the model. This is useful, for
     * example, when declaring a model within a larger project such as @e
     * dogen::logical. In this case, @e dogen is the external module.
     */
    /**@{*/
    const std::list<std::string>& external_modules() const;
    std::list<std::string>& external_modules();
    void external_modules(const std::list<std::string>& v);
    void external_modules(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Modules related to just the model itself.
     *
     * It is only different from the model name if the model name is composite;
     * that is, if the model name has multiple fields separated by dots, e.g. @ a.b.
     */
    /**@{*/
    const std::list<std::string>& model_modules() const;
    std::list<std::string>& model_modules();
    void model_modules(const std::list<std::string>& v);
    void model_modules(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Sub-modules within a model.
     */
    /**@{*/
    const std::list<std::string>& internal_modules() const;
    std::list<std::string>& internal_modules();
    void internal_modules(const std::list<std::string>& v);
    void internal_modules(const std::list<std::string>&& v);
    /**@}*/

    /**
     * @brief Name of the owning element, if any.
     *
     * For coding elements which are located within other logical elements
     * that are not modules, such as attributes, inner classes, etc.
     */
    /**@{*/
    const std::string& element() const;
    std::string& element();
    void element(const std::string& v);
    void element(const std::string&& v);
    /**@}*/

public:
    bool operator==(const logical_location& rhs) const;
    bool operator!=(const logical_location& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(logical_location& other) noexcept;
    logical_location& operator=(logical_location other);

private:
    std::list<std::string> external_modules_;
    std::list<std::string> model_modules_;
    std::list<std::string> internal_modules_;
    std::string element_;
};

}

namespace std {

template<>
inline void swap(
    dogen::identification::entities::logical_location& lhs,
    dogen::identification::entities::logical_location& rhs) {
    lhs.swap(rhs);
}

}

#endif
