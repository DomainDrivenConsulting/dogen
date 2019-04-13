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
#ifndef MASD_DOGEN_GENERATION_CPP_TYPES_FORMATTERS_ARTEFACT_FORMATTER_INTERFACE_HPP
#define MASD_DOGEN_GENERATION_CPP_TYPES_FORMATTERS_ARTEFACT_FORMATTER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <boost/filesystem/path.hpp>
#include "masd.dogen.archetypes/types/location.hpp"
#include "masd.dogen.coding/types/meta_model/name.hpp"
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.extraction/types/meta_model/artefact.hpp"
#include "masd.dogen.generation.cpp/types/formattables/locator.hpp"
#include "masd.dogen.generation.cpp/types/formattables/dependencies_builder_factory.hpp"
#include "masd.dogen.generation.cpp/types/formatters/inclusion_support_types.hpp"
#include "masd.dogen.generation.cpp/types/formatters/context.hpp"

namespace masd::dogen::generation::cpp::formatters {

class artefact_formatter_interface {
public:
    artefact_formatter_interface() = default;
    artefact_formatter_interface(artefact_formatter_interface&&) = default;
    artefact_formatter_interface(const artefact_formatter_interface&) = delete;
    virtual ~artefact_formatter_interface() noexcept = 0;

public:
    /**
     * @brief Unique identifier for the formatter in formatter space.
     */
    virtual std::string id() const = 0;

    /**
     * @brief Ownership hierarchy for this formatter
     */
    virtual archetypes::location archetype_location() const = 0;

    /**
     * @brief Returns name of the meta-model element that this
     * formatter supports.
     */
    virtual const coding::meta_model::name& meta_name() const = 0;

    /**
     * @brief Family to which this formatter belongs.
     */
    virtual std::string family() const = 0;

public:
    /**
     * @brief Returns the level of support of inclusions by this
     * formatter.
     */
    virtual inclusion_support_types inclusion_support_type() const = 0;

    /**
     * @brief Provide the inclusion path.
     *
     * @pre supports_inclusion must be true.
     */
    virtual boost::filesystem::path inclusion_path(
        const formattables::locator& l,
        const coding::meta_model::name& n) const = 0;

    /**
     * @brief Provides the full path.
     */
    virtual boost::filesystem::path full_path(const formattables::locator& l,
        const coding::meta_model::name& n) const = 0;

    /**
     * @brief Creates the inclusion dependencies for this formatter
     * against the supplied element.
     */
    virtual std::list<std::string> inclusion_dependencies(
        const formattables::dependencies_builder_factory& f,
        const coding::meta_model::element& e) const = 0;

public:
    /**
     * @brief Generate a file representation for the element.
     */
    virtual extraction::meta_model::artefact
    format(const context& ctx, const coding::meta_model::element& e) const = 0;
};

}

#endif
