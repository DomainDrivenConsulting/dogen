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
#ifndef MASD_DOGEN_GENERATION_TYPES_META_MODEL_FACET_PROPERTIES_HPP
#define MASD_DOGEN_GENERATION_TYPES_META_MODEL_FACET_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace masd::dogen::generation::meta_model {

class facet_properties final {
public:
    facet_properties(const facet_properties&) = default;
    facet_properties(facet_properties&&) = default;
    ~facet_properties() = default;

public:
    facet_properties();

public:
    facet_properties(
        const bool enabled,
        const bool overwrite,
        const std::string& directory,
        const std::string& postfix);

public:
    /**
     * @brief If true, this facet is enabled.
     */
    /**@{*/
    bool enabled() const;
    void enabled(const bool v);
    /**@}*/

    bool overwrite() const;
    void overwrite(const bool v);

    /**
     * @brief Directory in which to place artefacts that belong to this facet.
     */
    /**@{*/
    const std::string& directory() const;
    std::string& directory();
    void directory(const std::string& v);
    void directory(const std::string&& v);
    /**@}*/

    /**
     * @brief Postfix to use in file names of artefacts that belong to this facet.
     */
    /**@{*/
    const std::string& postfix() const;
    std::string& postfix();
    void postfix(const std::string& v);
    void postfix(const std::string&& v);
    /**@}*/

public:
    bool operator==(const facet_properties& rhs) const;
    bool operator!=(const facet_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(facet_properties& other) noexcept;
    facet_properties& operator=(facet_properties other);

private:
    bool enabled_;
    bool overwrite_;
    std::string directory_;
    std::string postfix_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::generation::meta_model::facet_properties& lhs,
    masd::dogen::generation::meta_model::facet_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
