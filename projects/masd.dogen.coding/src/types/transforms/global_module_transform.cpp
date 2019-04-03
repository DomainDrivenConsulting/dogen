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
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/io/meta_model/model_io.hpp"
#include "masd.dogen.coding/types/meta_model/object.hpp"
#include "masd.dogen.coding/types/meta_model/builtin.hpp"
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.coding/types/meta_model/visitor.hpp"
#include "masd.dogen.coding/types/meta_model/exception.hpp"
#include "masd.dogen.coding/types/meta_model/primitive.hpp"
#include "masd.dogen.coding/types/meta_model/enumeration.hpp"
#include "masd.dogen.coding/types/meta_model/object_template.hpp"
#include "masd.dogen.coding/types/helpers/name_builder.hpp"
#include "masd.dogen.coding/types/transforms/transformation_error.hpp"
#include "masd.dogen.coding/types/transforms/global_module_transform.hpp"

namespace {

const std::string transform_id("coding.transforms.global_module_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string global_module_doc("Module that represents the global scope.");
const std::string model_already_has_global_module(
    "Found a global module in model: ");

}

namespace masd::dogen::coding::transforms {

template<typename AssociativeContainerOfContainable>
inline void add_containing_module_to_non_contained_entities(
    const meta_model::name& container_name,
    AssociativeContainerOfContainable& c) {
    for (auto& pair : c) {
        auto& s(*pair.second);
        if (s.contained_by().empty())
            s.contained_by(container_name.qualified().dot());
    }
}

boost::shared_ptr<meta_model::module> global_module_transform::
create_global_module(const meta_model::origin_types ot) {
    const std::string gm("global_module");
    const meta_model::fully_qualified_representation fqr(gm, gm, gm);
    auto r(boost::make_shared<meta_model::module>());
    r->name().qualified(fqr);
    r->origin_type(ot);
    r->documentation(global_module_doc);
    r->is_global_module(true);
    r->intrinsic_technical_space(meta_model::technical_space::agnostic);
    return r;
}

meta_model::name global_module_transform::
inject_global_module(meta_model::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Injecting global module for: "
                             << m.name().qualified().dot();

    const auto gm(create_global_module(m.origin_type()));
    const auto r(gm->name());
    const auto i(m.modules().find(r.qualified().dot()));
    if (i != m.modules().end()) {
        const auto id(m.name().qualified().dot());
        BOOST_LOG_SEV(lg, error) << model_already_has_global_module << id;
        BOOST_THROW_EXCEPTION(
            transformation_error(model_already_has_global_module + id));
    }
    m.modules().insert(std::make_pair(r.qualified().dot(), gm));

    BOOST_LOG_SEV(lg, debug) << "Done injecting global module";
    return r;
}

void global_module_transform::
update_element_containment(const meta_model::name& global_module_name,
    meta_model::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Updating element containment.";

    const auto& gmn(global_module_name);
    add_containing_module_to_non_contained_entities(gmn, m.modules());
    add_containing_module_to_non_contained_entities(gmn, m.object_templates());
    add_containing_module_to_non_contained_entities(gmn, m.builtins());
    add_containing_module_to_non_contained_entities(gmn, m.enumerations());
    add_containing_module_to_non_contained_entities(gmn, m.objects());
    add_containing_module_to_non_contained_entities(gmn, m.exceptions());
    add_containing_module_to_non_contained_entities(gmn, m.visitors());
    add_containing_module_to_non_contained_entities(gmn, m.primitives());

    BOOST_LOG_SEV(lg, debug) << "Finished updating element containment.";
}

void global_module_transform::
apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "containment transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto gmn(inject_global_module(m));
    update_element_containment(gmn, m);

    stp.end_transform(m);
}

}
