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
#ifndef DOGEN_YARN_JSON_TYPES_HYDRATOR_HPP
#define DOGEN_YARN_JSON_TYPES_HYDRATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/ptree.hpp>
#include "dogen.external/types/meta_model/model.hpp"
#include "dogen.external/types/meta_model/element.hpp"
#include "dogen.external/types/meta_model/attribute.hpp"

namespace dogen {
namespace external {
namespace json {

class hydrator final {
private:
    /**
     * @brief Reads the key value pairs from the property tree.
     */
    std::list<std::pair<std::string, std::string>>
    read_kvps(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads the stereotypes, if any exists.
     */
    std::list<std::string>
    read_stereotypes(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads the parents, if any exists.
     */
    std::list<std::string>
    read_parents(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads the documentation, if any exists.
     */
    std::string read_documentation(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads the tagged values, if any exists.
     */
    std::list<std::pair<std::string, std::string>>
    read_tagged_values(const boost::property_tree::ptree& pt) const;

private:
    /**
     * @brief Reads the attributes, if any.
     */
    external::meta_model::attribute
    read_attribute(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads an element according to its meta-type by
     * dispatching to the correct read functions.
     */
    external::meta_model::element
    read_element(const boost::property_tree::ptree& pt) const;

    /**
     * @brief Reads the entire stream as a property tree.
     */
    external::meta_model::model read_stream(std::istream& s) const;

public:
    /**
     * @brief Hydrates the model from the JSON stream.
     */
    external::meta_model::model hydrate(std::istream& s) const;

    /**
     * @brief Opens up the file at path and then hydrates the model
     * from the JSON stream.
     */
    external::meta_model::model hydrate(const boost::filesystem::path& p) const;
};

} } }

#endif
