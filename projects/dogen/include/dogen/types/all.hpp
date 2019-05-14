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
#ifndef DOGEN_TYPES_ALL_HPP
#define DOGEN_TYPES_ALL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/types/dogen.hpp"
#include "dogen/types/converter.hpp"
#include "dogen/types/generator.hpp"
#include "dogen/types/configuration.hpp"
#include "dogen/types/tracing_level.hpp"
#include "dogen/types/tracing_format.hpp"
#include "dogen/types/reporting_style.hpp"
#include "dogen/types/diffing_destination.hpp"
#include "dogen/types/conversion_exception.hpp"
#include "dogen/types/generation_exception.hpp"
#include "dogen/types/configuration_builder.hpp"
#include "dogen/types/diffing_configuration.hpp"
#include "dogen/types/tracing_configuration.hpp"
#include "dogen/types/configuration_validator.hpp"
#include "dogen/types/reporting_configuration.hpp"
#include "dogen/types/mock_configuration_factory.hpp"
#include "dogen/types/model_processing_configuration.hpp"
#include "dogen/types/invalid_configuration_exception.hpp"

#endif