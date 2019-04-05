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
#ifndef MASD_DOGEN_TEMPLATING_TYPES_STITCH_TEXT_TEMPLATE_HPP
#define MASD_DOGEN_TEMPLATING_TYPES_STITCH_TEXT_TEMPLATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <boost/filesystem/path.hpp>
#include "masd.dogen.templating/types/stitch/properties.hpp"
#include "masd.dogen.templating/types/stitch/text_template_body.hpp"

namespace masd::dogen::templating::stitch {

/**
 * @brief Domain representation of a stitch template.
 */
class text_template final {
public:
    text_template() = default;
    text_template(const text_template&) = default;
    ~text_template() = default;

public:
    text_template(text_template&& rhs);

public:
    text_template(
        const std::unordered_set<std::string>& expected_keys,
        const std::unordered_map<std::string, std::string>& supplied_kvps,
        const boost::filesystem::path& input_path,
        const boost::filesystem::path& output_path,
        const masd::dogen::templating::stitch::properties& properties,
        const masd::dogen::templating::stitch::text_template_body& body);

public:
    /**
     * @brief Set of keys that are expected to be supplied.
     */
    /**@{*/
    const std::unordered_set<std::string>& expected_keys() const;
    std::unordered_set<std::string>& expected_keys();
    void expected_keys(const std::unordered_set<std::string>& v);
    void expected_keys(const std::unordered_set<std::string>&& v);
    /**@}*/

    /**
     * @brief Key value pairs that were supplied for instantiation.
     */
    /**@{*/
    const std::unordered_map<std::string, std::string>& supplied_kvps() const;
    std::unordered_map<std::string, std::string>& supplied_kvps();
    void supplied_kvps(const std::unordered_map<std::string, std::string>& v);
    void supplied_kvps(const std::unordered_map<std::string, std::string>&& v);
    /**@}*/

    /**
     * @brief Path where the template was read out from, if any.
     */
    /**@{*/
    const boost::filesystem::path& input_path() const;
    boost::filesystem::path& input_path();
    void input_path(const boost::filesystem::path& v);
    void input_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Path where the template should be outputted to, if any.
     */
    /**@{*/
    const boost::filesystem::path& output_path() const;
    boost::filesystem::path& output_path();
    void output_path(const boost::filesystem::path& v);
    void output_path(const boost::filesystem::path&& v);
    /**@}*/

    /**
     * @brief Properties of the template.
     */
    /**@{*/
    const masd::dogen::templating::stitch::properties& properties() const;
    masd::dogen::templating::stitch::properties& properties();
    void properties(const masd::dogen::templating::stitch::properties& v);
    void properties(const masd::dogen::templating::stitch::properties&& v);
    /**@}*/

    /**
     * @brief Body of the text template.
     */
    /**@{*/
    const masd::dogen::templating::stitch::text_template_body& body() const;
    masd::dogen::templating::stitch::text_template_body& body();
    void body(const masd::dogen::templating::stitch::text_template_body& v);
    void body(const masd::dogen::templating::stitch::text_template_body&& v);
    /**@}*/

public:
    bool operator==(const text_template& rhs) const;
    bool operator!=(const text_template& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(text_template& other) noexcept;
    text_template& operator=(text_template other);

private:
    std::unordered_set<std::string> expected_keys_;
    std::unordered_map<std::string, std::string> supplied_kvps_;
    boost::filesystem::path input_path_;
    boost::filesystem::path output_path_;
    masd::dogen::templating::stitch::properties properties_;
    masd::dogen::templating::stitch::text_template_body body_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::templating::stitch::text_template& lhs,
    masd::dogen::templating::stitch::text_template& rhs) {
    lhs.swap(rhs);
}

}

#endif
