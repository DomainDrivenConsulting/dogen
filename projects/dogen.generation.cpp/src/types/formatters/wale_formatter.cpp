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
#include <boost/throw_exception.hpp>
#include "dogen.utility/log/logger.hpp"
#include "dogen.formatting/types/utility_formatter.hpp"
#include "dogen.templating/types/wale/workflow.hpp"
#include "dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/formatters/wale_formatter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("generation.cpp.formatters.wale_formatter"));

const std::string missing_input("Missing formatting input");

}

namespace dogen {
namespace generation {
namespace cpp {
namespace formatters {

bool wale_formatter::is_header(const inclusion_support_types ist) const {
    return
        ist == inclusion_support_types::regular_support ||
        ist == inclusion_support_types::canonical_support;
}

modeling::meta_model::artefact wale_formatter::
format(const artefact_formatter_interface& stock_formatter, const context& ctx,
    const modeling::meta_model::element& e) const {
    const auto al(stock_formatter.archetype_location());
    const auto needs_guard(is_header(stock_formatter.inclusion_support_type()));
    assistant a(ctx, e, al, needs_guard);

    const auto kvps = std::unordered_map<std::string, std::string> {
        { "class.simple_name", e.name().simple() }
    };

    dogen::formatting::utility_formatter uf(a.stream());
    {
        const auto& n(e.name());
        const auto qn(a.get_qualified_name(n));
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(a.make_namespaces(n));
            auto snf(a.make_scoped_namespace_formatter(ns));

            const auto fi(a.new_artefact_properties().formatting_input());
            if (fi.empty()) {
                BOOST_LOG_SEV(lg, error) << missing_input;
                BOOST_THROW_EXCEPTION(formatting_error(missing_input));
            }

            uf.insert_end_line();
            templating::wale::workflow w;
            a.stream() << w.execute(fi, kvps);
            uf.insert_end_line();
        }
        uf.insert_end_line();
    }
    return a.make_artefact();
}

} } } }
