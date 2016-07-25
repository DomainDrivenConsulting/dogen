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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/formatters/types/hydration_workflow.hpp"
#include "dogen/quilt.cpp/types/settings/element_settings_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.settings.element_settings_factory"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace settings {

element_settings_factory::element_settings_factory(
    const dynamic::repository& rp,
    const opaque_settings_builder& osb) :
    dynamic_repository_(rp), opaque_settings_builder_(osb) { }

std::unordered_map<
    std::string,
    boost::shared_ptr<opaque_settings>
>
element_settings_factory::
create_opaque_settings(const dynamic::object& o) const {
    return opaque_settings_builder_.build(o);
}

element_settings
element_settings_factory::make(const dynamic::object& o) const {
    element_settings r;
    r.opaque_settings(create_opaque_settings(o));
    return r;
}

} } } }
