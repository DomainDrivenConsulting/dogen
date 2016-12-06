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
#ifndef DOGEN_QUILT_CSHARP_TYPES_FORMATTERS_ARTEFACT_FORMATTER_INTERFACE_HPP
#define DOGEN_QUILT_CSHARP_TYPES_FORMATTERS_ARTEFACT_FORMATTER_INTERFACE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <typeindex>
#include <boost/filesystem/path.hpp>
#include "dogen/annotations/types/archetype_location.hpp"
#include "dogen/formatters/types/artefact.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/quilt.csharp/types/formatters/locator.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {

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
    virtual std::string formatter_name() const = 0;

    /**
     * @brief Ownership hierarchy for this formatter
     */
    virtual annotations::archetype_location archetype_location() const = 0;

    /**
     * @brief Returns the type index of the element supported by this
     * formatter.
     */
    virtual std::type_index element_type_index() const = 0;

public:
    /**
     * @brief Provides the full path.
     */
    virtual boost::filesystem::path
    full_path(const locator& l, const yarn::name& n) const = 0;

    /**
     * @brief Creates the inclusion dependencies for this formatter
     * against the supplied element.
     */
    virtual std::list<std::string>
    inclusion_dependencies(const yarn::element& e) const = 0;

public:
    /**
     * @brief Generate a file representation for the element.
     */
    virtual dogen::formatters::artefact
    format(const yarn::element& e) const = 0;
};

} } } }

#endif
