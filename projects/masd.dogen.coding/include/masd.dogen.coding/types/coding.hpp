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
#ifndef MASD_DOGEN_CODING_TYPES_CODING_HPP
#define MASD_DOGEN_CODING_TYPES_CODING_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

/**
 * @brief Coding is the core Dogen meta-model representing software entities.
 *
 * @section coding_0 Overview
 *
 * Coding is a meta-model that provides a programming-language-neutral
 * type representation, designed for code generation. Intermediate models
 * are obtained via frontends and post-processed until they form a
 * cohesive whole. They are then suitable to be sent down the
 * pipeline for further processing.
 *
 * @section coding_0 Mission
 *
 * Coding's objectives are:
 *
 * @li to represent all high-level entities that exist across a number
 * of technical spaces used in software engineering. These entities
 * are not necessarily limited to programming language entities, though
 * of course, these form the core set of elements we're interested in.
 * Additional entities such as build sytems and high-level patterns
 * such as GoF and others are also captured.
 *
 * @li to provide the tooling required to combine multiple coding
 * models together into a bigger model - called the @e merged model.
 *
 * @li to ensure the consistency of the merged model via validation
 * rules (such as verifying that all types have a definitions,
 * etc.).
 */
namespace masd::dogen::coding {
}

#endif
