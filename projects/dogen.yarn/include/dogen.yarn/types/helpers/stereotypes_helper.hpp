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
#ifndef DOGEN_YARN_TYPES_HELPERS_STEREOTYPES_HELPER_HPP
#define DOGEN_YARN_TYPES_HELPERS_STEREOTYPES_HELPER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include "dogen.yarn/types/meta_model/static_stereotypes.hpp"
#include "dogen.yarn/types/helpers/stereotypes_conversion_result.hpp"

namespace dogen {
namespace yarn {
namespace helpers {

/**
 * @brief Converts well-known stereotypes from and to strings.
 */
class stereotypes_helper final {
public:
    /**
     * @brief Converts a string with a single well-known stereotype
     * into its enum.
     *
     * @note The string must not have any leading or trailing spaces
     * or other artefacts and must match exactly the definition of a
     * well-known yarn stereotype, e.g. 'yarn::object', etc.
     */
    meta_model::static_stereotypes from_string(const std::string& s) const;

public:
    /**
     * @brief Given a CSV-separated string, returns the set of
     * well-known stereotypes as well as those it does not know of.
     */
    stereotypes_conversion_result from_csv_string(const std::string& s) const;

    /**
     * @brief Given a list of stereotypes as strings, returns the set
     * of well-known stereotypes as well as those it does not know of.
     */
    stereotypes_conversion_result
    from_string(const std::list<std::string>& stereotypes) const;

    /**
     * @brief Converts a well-known stereotype to its string representation.
     */
    std::string to_string(const meta_model::static_stereotypes ss) const;

public:
    /**
     * @brief Returns true if the well-known stereotype denotes a yarn
     * element type, false otherwise.
     */
    bool is_element_type(const meta_model::static_stereotypes ss) const;

    /**
     * @brief Given a list of well-known stereotypes, extracts those
     * which are element types.
     */
    std::list<meta_model::static_stereotypes> extract_element_types(
        const std::list<meta_model::static_stereotypes>& ss) const;

    /**
     * @brief Given a list of well-known stereotypes, extracts those
     * which are not element types.
     */
    std::list<meta_model::static_stereotypes>
    extract_non_element_types(
        const std::list<meta_model::static_stereotypes>& ss) const;
};

} } }

#endif
