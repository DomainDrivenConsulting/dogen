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
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/string/splitter.hpp"
#include "dogen/external.dia/types/adaptation_error.hpp"
#include "dogen/external.dia/types/adapter.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("external.dia.adapter"));

const std::string name_delimiter("::");
const std::string yarn_object_element("yarn::object");
const std::string yarn_module_element("yarn::module");

const std::string empty_dia_name("Dia name is empty.");

}

namespace dogen {
namespace external {
namespace dia {

void adapter::validate_dia_name(const std::string& n) {
    if (n.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_name;
        BOOST_THROW_EXCEPTION(adaptation_error(empty_dia_name));
    }
}

std::string adapter::qualified_name(const std::string& contained_by,
    const std::string& simple_name) {

    if (contained_by.empty())
        return simple_name;

    return contained_by + name_delimiter + simple_name;
}

external::meta_model::attribute
adapter::adapt(const processed_attribute& a) {
    validate_dia_name(a.name());

    external::meta_model::attribute r;
    r.name(a.name());
    r.type(a.type());
    r.documentation(a.comment().documentation());
    r.tagged_values(a.comment().tagged_values());
    return r;
}

void adapter::process_stereotypes(const processed_object& po,
    external::meta_model::element& e) {
    BOOST_LOG_SEV(lg, debug) << "Original stereotypes string: '"
                             << po.stereotypes() << "'";

    /*
     * Provide the appropriate element types defaulting based on the
     * dia UML types.
     */
    if (po.dia_object_type() == dia_object_types::uml_class)
        e.fallback_element_type(yarn_object_element);
    else if (po.dia_object_type() == dia_object_types::uml_large_package)
        e.fallback_element_type(yarn_module_element);

    /*
     * Split and copy across the user-supplied stereotypes.
     */
    using utility::string::splitter;
    const auto st(splitter::split_csv(po.stereotypes()));
    e.stereotypes(st);

    BOOST_LOG_SEV(lg, debug) << "Split stereotypes: " << st;
}

external::meta_model::element adapter::
adapt(const processed_object& po, const std::string& contained_by,
    const std::list<std::string>& parents) {
    validate_dia_name(po.name());

    external::meta_model::element r;
    r.name(qualified_name(contained_by, po.name()));
    r.parents(parents);
    r.documentation(po.comment().documentation());
    r.tagged_values(po.comment().tagged_values());
    process_stereotypes(po, r);

    for (const auto& attr : po.attributes())
        r.attributes().push_back(adapt(attr));

    return r;
}

} } }
