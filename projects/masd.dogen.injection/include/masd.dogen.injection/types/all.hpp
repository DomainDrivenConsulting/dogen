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
#ifndef MASD_DOGEN_INJECTION_TYPES_ALL_HPP
#define MASD_DOGEN_INJECTION_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "masd.dogen.injection/types/traits.hpp"
#include "masd.dogen.injection/types/injection.hpp"
#include "masd.dogen.injection/types/meta_model/model.hpp"
#include "masd.dogen.injection/types/meta_model/element.hpp"
#include "masd.dogen.injection/types/transforms/context.hpp"
#include "masd.dogen.injection/types/meta_model/attribute.hpp"
#include "masd.dogen.injection/types/meta_model/model_set.hpp"
#include "masd.dogen.injection/types/transforms/registrar.hpp"
#include "masd.dogen.injection/types/transforms/registrar_error.hpp"
#include "masd.dogen.injection/types/helpers/references_resolver.hpp"
#include "masd.dogen.injection/types/transforms/model_to_model_chain.hpp"
#include "masd.dogen.injection/types/transforms/references_transform.hpp"
#include "masd.dogen.injection/types/transforms/transformation_error.hpp"
#include "masd.dogen.injection/types/transforms/annotations_transform.hpp"
#include "masd.dogen.injection/types/transforms/model_production_chain.hpp"
#include "masd.dogen.injection/types/transforms/input_language_transform.hpp"
#include "masd.dogen.injection/types/transforms/model_set_production_chain.hpp"
#include "masd.dogen.injection/types/helpers/reference_resolution_exception.hpp"
#include "masd.dogen.injection/types/transforms/decoding_transform_interface.hpp"
#include "masd.dogen.injection/types/transforms/encoding_transform_interface.hpp"

#endif
