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
#ifndef DOGEN_ASSETS_TYPES_ASSETS_HPP
#define DOGEN_ASSETS_TYPES_ASSETS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

/**
 * @brief Assets is the core Dogen meta-model representing software entities.
 *
 * @section assets_0 Overview
 *
 * Assets is a meta-model that strives to provide a technical-space agnostic
 * type representation, designed for code generation. Injection models
 * are obtained via frontends and transformed into "bare" asset models, at
 * which point they can enter its pipeline. Within it, they are processed
 * until they form a cohesive whole. They are then in a suitable state for
 * code generation.
 *
 * @section asset_1 Mission
 *
 * The objectives of the assets model are:
 *
 * @li to represent all high-level entities that exist across a number
 * of technical spaces used in software engineering. These entities
 * are not necessarily limited to programming entities, though, of course,
 * these form the core set of elements we're interested in. Additional
 * entities such as build sytems and high-level patterns such as GoF
 * and others are also captured.
 *
 * @li to provide the tooling required to combine multiple models
 * together into a bigger model - called the @e merged model.
 *
 * @li to ensure the consistency of the merged model via validation
 * rules (such as verifying that all types have a definitions,
 * etc.).
 */
namespace dogen::assets {
}

#endif
