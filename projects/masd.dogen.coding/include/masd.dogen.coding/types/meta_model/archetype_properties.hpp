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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_ARCHETYPE_PROPERTIES_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_ARCHETYPE_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/optional.hpp>

namespace masd::dogen::coding::meta_model {

/**
 * @brief Archetype level properties, applicable to all instances of this archetype.
 */
class archetype_properties final {
public:
    archetype_properties(const archetype_properties&) = default;
    ~archetype_properties() = default;

public:
    archetype_properties();

public:
    archetype_properties(archetype_properties&& rhs);

public:
    archetype_properties(
        const bool enabled,
        const boost::optional<bool>& overwrite,
        const std::string& postfix);

public:
    /**
     * @brief If false, will disable all instances of this archetype.
     */
    /**@{*/
    bool enabled() const;
    void enabled(const bool v);
    /**@}*/

    const boost::optional<bool>& overwrite() const;
    boost::optional<bool>& overwrite();
    void overwrite(const boost::optional<bool>& v);
    void overwrite(const boost::optional<bool>&& v);

    /**
     * @brief Postfix to use for artefacts of this archetype.
     */
    /**@{*/
    const std::string& postfix() const;
    std::string& postfix();
    void postfix(const std::string& v);
    void postfix(const std::string&& v);
    /**@}*/

public:
    bool operator==(const archetype_properties& rhs) const;
    bool operator!=(const archetype_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(archetype_properties& other) noexcept;
    archetype_properties& operator=(archetype_properties other);

private:
    bool enabled_;
    boost::optional<bool> overwrite_;
    std::string postfix_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::coding::meta_model::archetype_properties& lhs,
    masd::dogen::coding::meta_model::archetype_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
