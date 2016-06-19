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
#ifndef DOGEN_YARN_TYPES_NAME_HPP
#define DOGEN_YARN_TYPES_NAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <map>
#include "dogen/yarn/types/language.hpp"
#include "dogen/yarn/types/location.hpp"
#include "dogen/yarn/hash/language_hash.hpp"
#include "dogen/yarn/serialization/name_fwd_ser.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Name of an element in modeling space.
 *
 * A name represents a point in modeling space, and this point can only be
 * used by one modeling element. Names can be uniquely identified by their
 * qualified ID.
 *
 * Name has the following properties: a) two different points in element space
 * cannot have the same name and b) the same point in element space can only
 * have one and only one name.
 *
 * Names are required in addition to just using the qualfied ID representation
 * because we use them to infer all sorts of properties for an element (namespaces,
 * naming files, etc).
 */
class name final {
public:
    name() = default;
    name(const name&) = default;
    name(name&&) = default;
    ~name() = default;

public:
    name(
        const std::string& id,
        const std::string& simple,
        const std::map<dogen::yarn::language, std::string>& qualified,
        const dogen::yarn::location& location,
        const std::string& identifiable);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const name& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, name& v, unsigned int version);

public:
    /**
     * @brief Unique identifier representation for this name, using a well-defined notation.
     *
     * Note that the qualified ID itself should not be part of the address, but it is
     * placed here as an optimisation. The ID is a bijective function on the address,
     * but designed not to have the ability to split out its constituent parts. The ID
     * is generated by combining all the constituents of the address, including the
     * location (but not the ID itself, of course).
     */
    /**@{*/
    const std::string& id() const;
    std::string& id();
    void id(const std::string& v);
    void id(const std::string&& v);
    /**@}*/

    /**
     * @brief Simple (non-qualified) name of the modeling element at this address.
     *
     * The simple name must be unique for a given location.
     */
    /**@{*/
    const std::string& simple() const;
    std::string& simple();
    void simple(const std::string& v);
    void simple(const std::string&& v);
    /**@}*/

    /**
     * @brief Qualified name in a language specific representation.
     */
    /**@{*/
    const std::map<dogen::yarn::language, std::string>& qualified() const;
    std::map<dogen::yarn::language, std::string>& qualified();
    void qualified(const std::map<dogen::yarn::language, std::string>& v);
    void qualified(const std::map<dogen::yarn::language, std::string>&& v);
    /**@}*/

    /**
     * @brief Where the name is located in element space.
     */
    /**@{*/
    const dogen::yarn::location& location() const;
    dogen::yarn::location& location();
    void location(const dogen::yarn::location& v);
    void location(const dogen::yarn::location&& v);
    /**@}*/

    /**
     * @brief Representation of the name that can usable as an identifier on all of the supported
     * languages, using the entire name structure.
     */
    /**@{*/
    const std::string& identifiable() const;
    std::string& identifiable();
    void identifiable(const std::string& v);
    void identifiable(const std::string&& v);
    /**@}*/

public:
    bool operator==(const name& rhs) const;
    bool operator!=(const name& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(name& other) noexcept;
    name& operator=(name other);

private:
    std::string id_;
    std::string simple_;
    std::map<dogen::yarn::language, std::string> qualified_;
    dogen::yarn::location location_;
    std::string identifiable_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::name& lhs,
    dogen::yarn::name& rhs) {
    lhs.swap(rhs);
}

}

#endif
