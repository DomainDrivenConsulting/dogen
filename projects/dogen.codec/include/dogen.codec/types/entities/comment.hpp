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
#ifndef DOGEN_CODEC_TYPES_ENTITIES_COMMENT_HPP
#define DOGEN_CODEC_TYPES_ENTITIES_COMMENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen.identification/types/entities/tagged_value.hpp"

namespace dogen::codec::entities {

/**
 * @brief Represents a comment block as read out from the codec representation.
 */
class comment final {
public:
    comment(const comment&) = default;
    comment(comment&&) = default;
    ~comment() = default;

public:
    comment();

public:
    comment(
        const std::list<dogen::identification::entities::tagged_value>& tagged_values,
        const bool applies_to_container,
        const std::string& original_content,
        const std::string& documentation);

public:
    const std::list<dogen::identification::entities::tagged_value>& tagged_values() const;
    std::list<dogen::identification::entities::tagged_value>& tagged_values();
    void tagged_values(const std::list<dogen::identification::entities::tagged_value>& v);
    void tagged_values(const std::list<dogen::identification::entities::tagged_value>&& v);

    /**
     * @brief Content of the field as it belonged to the containing object.
     */
    /**@{*/
    bool applies_to_container() const;
    void applies_to_container(const bool v);
    /**@}*/

    /**
     * @brief Content, as read from the codec representation.
     */
    /**@{*/
    const std::string& original_content() const;
    std::string& original_content();
    void original_content(const std::string& v);
    void original_content(const std::string&& v);
    /**@}*/

    /**
     * @brief Code comments.
     *
     * These are expected to follow the grammar of the comment processing
     * tools of the technical space in question, e.g. Doxygen for C++,
     * JavaDoc for Java, etc.
     */
    /**@{*/
    const std::string& documentation() const;
    std::string& documentation();
    void documentation(const std::string& v);
    void documentation(const std::string&& v);
    /**@}*/

public:
    bool operator==(const comment& rhs) const;
    bool operator!=(const comment& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(comment& other) noexcept;
    comment& operator=(comment other);

private:
    std::list<dogen::identification::entities::tagged_value> tagged_values_;
    bool applies_to_container_;
    std::string original_content_;
    std::string documentation_;
};

}

namespace std {

template<>
inline void swap(
    dogen::codec::entities::comment& lhs,
    dogen::codec::entities::comment& rhs) {
    lhs.swap(rhs);
}

}

#endif
