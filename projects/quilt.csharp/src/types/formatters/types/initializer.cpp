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
#include "dogen/quilt.csharp/types/formatters/registrar.hpp"
#include "dogen/quilt.csharp/types/formatters/types/class_formatter.hpp"
#include "dogen/quilt.csharp/types/formatters/types/enum_formatter.hpp"
#include "dogen/quilt.csharp/types/formatters/types/exception_formatter.hpp"
#include "dogen/quilt.csharp/types/formatters/types/builtin_formatter.hpp"
#include "dogen/quilt.csharp/types/formatters/types/floating_point_number_helper.hpp"
#include "dogen/quilt.csharp/types/formatters/types/initializer.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {
namespace types {

void initializer::initialize(registrar& rg) {
    register_formatter<class_formatter>(rg);
    register_formatter<enum_formatter>(rg);
    register_formatter<exception_formatter>(rg);
    register_formatter<builtin_formatter>(rg);
    register_formatter_helper<floating_point_number_helper>(rg);
}

} } } } }
