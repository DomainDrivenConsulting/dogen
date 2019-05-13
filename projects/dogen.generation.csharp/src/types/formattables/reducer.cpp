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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.coding/types/meta_model/element.hpp"
#include "dogen.generation.csharp/types/formattables/reducer.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("generation.cpp.formatters.reducer"));

}

namespace dogen::generation::csharp::formattables {

void reducer::reduce(model& fm) const {
    BOOST_LOG_SEV(lg, debug) << "Starting reduction.";
    BOOST_LOG_SEV(lg, debug) << "Original size: " << fm.formattables().size();

    std::unordered_map<std::string, formattable> reduced;
    for (const auto& pair : fm.formattables()) {
        const auto& formattable(pair.second);
        const auto& e(*formattable.element());
        if (e.origin_type() != coding::meta_model::origin_types::target)
            continue;

        reduced.insert(pair);
    }

    fm.formattables().swap(reduced);
    BOOST_LOG_SEV(lg, debug) << "Reduced size: " << fm.formattables().size();
}

}
