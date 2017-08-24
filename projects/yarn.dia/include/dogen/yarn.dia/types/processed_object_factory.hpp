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
#ifndef DOGEN_YARN_DIA_TYPES_PROCESSED_OBJECT_FACTORY_HPP
#define DOGEN_YARN_DIA_TYPES_PROCESSED_OBJECT_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "dogen/dia/types/attribute_fwd.hpp"
#include "dogen/dia/types/object_fwd.hpp"
#include "dogen/dia/types/attribute_fwd.hpp"
#include "dogen/dia/types/composite_fwd.hpp"
#include "dogen/dia/types/diagram_fwd.hpp"
#include "dogen/yarn.dia/types/dia_object_types.hpp"
#include "dogen/yarn.dia/types/processed_object_fwd.hpp"

namespace dogen {
namespace yarn {
namespace dia {

/**
 * @brief Processes dia objects into an intermediate format.
 */
class processed_object_factory {
private:
    /**
     * @brief Parses the dia attribute as a string, returning its value.
     */
    static std::string parse_string_attribute(const dogen::dia::attribute& a);

    /**
     * @brief Makes a processed comment from the input attribute.
     *
     * @pre Attribute must be of type string.
     */
    static processed_comment
    create_processed_comment(const dogen::dia::attribute& a);

    /**
     * @brief Given a string with a dia object type, returns the
     * appropriate enum.
     */
    static dia_object_types parse_object_type(const std::string& ot);

    /**
     * @brief Parse connection information from Dia object.
     */
    static void
    parse_connections(const dogen::dia::object& o, processed_object& po);

    /**
     * @brief Parse the attribute as a Dia text.
     */
    static void
    parse_as_dia_text(const dogen::dia::attribute a, processed_object& po);

    /**
     * @brief Throws if the yarn type has already been setup.
     */
    static void require_yarn_type_not_set(const yarn_element_types yet);

    /**
     * @brief Processes the raw Dia stereotypes.
     */
    static void
    parse_as_stereotypes(dogen::dia::attribute a, processed_object& po);

    /**
     * @brief Parses the contents of the Dia attribute assuming it
     * contains UML attributes.
     */
    static void parse_as_class_attributes(
        const dogen::dia::attribute a, processed_object& po);

    /**
     * @brief Parses the Dia attributes from the Dia object.
     */
    static void
    parse_attributes(const dogen::dia::object& o, processed_object& po);

    /**
     * @brief Defaults the yarn object type, if required.
     */
    static void setup_yarn_object_type(processed_object& po);

public:
    /**
     * @brief Generates a processed object.
     */
    static processed_object make(const dogen::dia::object& o);

    /**
     * @brief Generates a processed object representation of the
     * diagram.
     */
    static std::list<processed_object> make(const dogen::dia::diagram& d);
};

} } }

#endif
