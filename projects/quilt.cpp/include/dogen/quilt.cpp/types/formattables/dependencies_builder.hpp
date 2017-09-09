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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_DEPENDENCIES_BUILDER_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_DEPENDENCIES_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include "dogen/yarn/types/meta_model/object.hpp"
#include "dogen/yarn/types/meta_model/element_archetype.hpp"
#include "dogen/quilt.cpp/types/formattables/formattable.hpp"
#include "dogen/quilt.cpp/types/formattables/directive_group.hpp"
#include "dogen/quilt.cpp/types/formattables/directive_group_repository.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

/**
 * @brief Helps in building the inclusion dependencies for a given
 * formatter.
 */
class dependencies_builder {
public:
    dependencies_builder(
        const directive_group_repository& dgrp,
        const std::unordered_map<std::string, formattable>& formattables,
        const std::unordered_set<yarn::meta_model::element_archetype>&
        enabled_archetype_for_element);

private:
    /**
     * @brief Returns the inclusion directive group for a given name
     * and formatter name.
     *
     * @pre name must exist in path derivatives collection.
     */
    boost::optional<directive_group>
    get_directive_group(const yarn::meta_model::name& n,
        const std::string& archetype) const;

public:
    /**
     * @brief Returns true if the formatter is enabled.
     */
    bool is_enabled(const yarn::meta_model::name& n,
        const std::string& archetype) const;

public:
    /**
     * @brief Adds the supplied inclusion directive.
     */
    /**@{*/
    void add(const std::string& directive);
    void add(const std::list<std::string>& directives);

    /**@{*/

    /**
     * @brief Adds the inclusion directive for the supplied archetype
     * and name.
     */
    /**@{*/
    void add(const yarn::meta_model::name& n, const std::string& archetype);
    void add(const boost::optional<yarn::meta_model::name>& n,
        const std::string& archetype);
    /**@}*/

    /**
     * @brief Adds the inclusion directives for the supplied
     * archetype, for each of the supplied names.
     */
    void add(const std::list<yarn::meta_model::name>& names,
        const std::string& archetype);

public:
    /**
     * @brief Builds the inclusion dependencies. All additions must
     * have been performed already.
     */
    std::list<std::string> build();

private:
    const directive_group_repository& repository_;
    const std::unordered_map<std::string, formattable>& formattables_;
    // const std::unordered_set<yarn::meta_model::element_archetype>&
    // enabled_archetype_for_element_;
    std::list<std::string> dependencies_;
};

} } } }

#endif
