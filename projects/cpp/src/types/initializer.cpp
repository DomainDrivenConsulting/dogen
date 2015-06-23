/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/backend/types/workflow.hpp"
#include "dogen/cpp/types/formatters/workflow.hpp"
#include "dogen/cpp/types/settings/bundle_repository_factory.hpp"
#include "dogen/cpp/types/settings/initializer.hpp"
#include "dogen/cpp/types/formatters/initializer.hpp"
#include "dogen/cpp/types/workflow.hpp"
#include "dogen/cpp/types/initializer.hpp"

namespace dogen {
namespace cpp {

void initializer::initialize() {
    formatters::initializer::initialize(formatters::workflow::registrar());
    settings::initializer::initialize(
        settings::bundle_repository_factory::registrar());
    backend::workflow::registrar().register_backend(
        std::make_shared<workflow>());
}

} }
