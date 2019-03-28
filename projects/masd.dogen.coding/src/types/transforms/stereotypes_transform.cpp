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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.utility/types/io/vector_io.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/io/meta_model/name_io.hpp"
#include "masd.dogen.coding/io/meta_model/static_stereotypes_io.hpp"
#include "masd.dogen.coding/types/helpers/resolver.hpp"
#include "masd.dogen.coding/types/helpers/name_builder.hpp"
#include "masd.dogen.coding/types/transforms/transformation_error.hpp"
#include "masd.dogen.coding/io/meta_model/model_io.hpp"
#include "masd.dogen.coding/types/meta_model/orm_object_properties.hpp"
#include "masd.dogen.coding/types/meta_model/orm_primitive_properties.hpp"
#include "masd.dogen.coding/types/transforms/stereotypes_transform.hpp"

namespace {

const std::string transform_id("coding.transforms.stereotypes_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string stereotype_pretty_printable("dogen::pretty_printable");
const std::string stereotype_serializable("dogen::serializable");
const std::string stereotype_hashable("dogen::hashable");
const std::string stereotype_entry_point("masd::entry_point");
const std::string stereotype_header_only("masd::cpp::header_only");
const std::string stereotype_interface("masd::interface");
const std::string stereotype_handcrafted("masd::handcrafted");
const std::string stereotype_cpp_helper_formatter("masd::cpp_helper_formatter");
const std::string stereotype_cpp_artefact_formatter(
    "masd::cpp_artefact_formatter");
const std::string stereotype_csharp_helper_formatter(
    "masd::csharp_helper_formatter");
const std::string stereotype_csharp_artefact_formatter(
    "masd::csharp_artefact_formatter");

const std::string visitor_name("visitor");
const std::string visitor_argument_name("v");
const std::string visitor_doc("Visitor for ");
const std::string visit_operation_doc("Accept visits for type ");

const std::string duplicate_name(
    "Attempt to add object with a name that already exists in model: ");
const std::string zero_leaves("Type marked as visitable but has no leaves: ");
const std::string leaf_not_found("Could not find leaf object: ");
const std::string leaves_not_found("Could not find leaves for: ");
const std::string no_visitees("Visitor is not visiting any types: ");
const std::string visitable_child("Children cannot be marked as visitable: ");
const std::string invalid_stereotypes("Stereotypes are not valid: ");

}

namespace masd::dogen::coding::transforms {

bool stereotypes_transform::
is_stereotype_handled_externally(const std::string& s) {
    return
        s == stereotype_pretty_printable ||
        s == stereotype_serializable ||
        s == stereotype_hashable ||
        s == stereotype_handcrafted ||
        s == stereotype_entry_point ||
        s == stereotype_header_only ||
        s == stereotype_interface ||
        s == stereotype_cpp_helper_formatter ||
        s == stereotype_cpp_artefact_formatter ||
        s == stereotype_csharp_helper_formatter ||
        s == stereotype_csharp_artefact_formatter;
}

bool stereotypes_transform::
is_element_type(const meta_model::static_stereotypes ss) {
    using meta_model::static_stereotypes;
    return
        ss == static_stereotypes::object ||
        ss == static_stereotypes::object_template ||
        ss == static_stereotypes::exception ||
        ss == static_stereotypes::primitive ||
        ss == static_stereotypes::enumeration ||
        ss == static_stereotypes::module ||
        ss == static_stereotypes::builtin;
}

void stereotypes_transform::
transform_static_stereotypes(meta_model::object& o, meta_model::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Static  stereotypes: "
                             << o.static_stereotypes();

    /*
     * First we process all of the well-known stereotypes, collecting
     * any invalid ones as we go along.
     */
    using meta_model::static_stereotypes;
    std::list<static_stereotypes> unknown_stereotypes;
    for (const auto ss : o.static_stereotypes()) {
        if (is_element_type(ss)) {
            /*
             * We can safely ignore any element type information as
             * that has already been used to instantiate the
             * appropriate meta-model elements.
             */
            continue;
        } else if (ss == static_stereotypes::visitable)
            expand_visitable(o, m);
        else if (ss == static_stereotypes::fluent)
            o.is_fluent(true);
        else if (ss == static_stereotypes::immutable)
            o.is_immutable(true);
        else if (ss == static_stereotypes::orm_object) {
            meta_model::orm_object_properties cfg;
            cfg.generate_mapping(true);
            o.orm_properties(cfg);
        } else if (ss == static_stereotypes::orm_value) {
            meta_model::orm_object_properties cfg;
            cfg.generate_mapping(true);
            cfg.is_value(true);
            o.orm_properties(cfg);
        } else
            unknown_stereotypes.push_back(ss);
    }

    /*
     * Any attempt to use a well-known stereotype against this model
     * element which we do not recognise must be invalid (since we
     * process all of the well-known stereotypes at this point).
     */
    if (!unknown_stereotypes.empty()) {
        const auto s(boost::lexical_cast<std::string>(unknown_stereotypes));
        BOOST_LOG_SEV(lg, error) << invalid_stereotypes << s;
        BOOST_THROW_EXCEPTION(transformation_error(invalid_stereotypes + s));
    }
}

void stereotypes_transform::transform_dynamic_stereotypes(meta_model::object& o,
    const meta_model::model& em) {
    BOOST_LOG_SEV(lg, debug) << "Dynamic stereotypes: "
                             << o.dynamic_stereotypes();

    std::list<std::string> unknown_stereotypes;
    for (const auto us : o.dynamic_stereotypes()) {
        /*
         * Exclude all stereotypes that are handled externally -
         * i.e. profiles.
         *
         * FIXME: This is a massive hack; we should really ask
         * annotations for all valid profile names and exclude those
         * instead of hard-coding them here.
         */
        if (is_stereotype_handled_externally(us))
            continue;

        /*
         * Attempt to process the stereotype as an object template. If
         * it isn't then is definitely not one of ours.
         */
        const bool is_object_template(try_as_object_template(us, o, em));
        if (!is_object_template)
            unknown_stereotypes.push_back(us);
    }

    /*
     * If there are any stereotypes we do not know about, throw an
     * error. This way the user can figure out if its trying to use a
     * object template but it has not been found or if its trying to
     * use an unsupported feature.
     */
    if (!unknown_stereotypes.empty()) {
        const auto s(boost::lexical_cast<std::string>(unknown_stereotypes));
        BOOST_LOG_SEV(lg, error) << invalid_stereotypes << s;
        BOOST_THROW_EXCEPTION(transformation_error(invalid_stereotypes + s));
    }
}

std::unordered_map<meta_model::location,
                   std::list<meta_model::name>> stereotypes_transform::
bucket_leaves_by_location(const std::list<meta_model::name>& leaves) {
    std::unordered_map<meta_model::location, std::list<meta_model::name>>  r;
    for (const auto& l : leaves)
        r[l.location()].push_back(l);

    return r;
}

boost::shared_ptr<meta_model::visitor>
stereotypes_transform::create_visitor(const meta_model::object& o,
    const meta_model::location& l, const meta_model::origin_types ot,
    const std::list<meta_model::name>& leaves) {
    helpers::name_builder b;
    b.simple_name(o.name().simple() + "_" + visitor_name);
    b.location(l);

    const auto n(b.build());
    BOOST_LOG_SEV(lg, debug) << "Creating visitor: " << n.qualified().dot();

    auto r(boost::make_shared<meta_model::visitor>());
    r->name(n);
    r->origin_type(ot);
    r->documentation(visitor_doc + o.name().simple());

    if (leaves.empty()) {
        const auto id(n.qualified().dot());
        BOOST_LOG_SEV(lg, error) << no_visitees << id;
        BOOST_THROW_EXCEPTION(transformation_error(no_visitees + id));
    }

    for (const auto& l : leaves)
        r->visits().push_back(l);

    BOOST_LOG_SEV(lg, debug) << "Created visitor: " << n.qualified().dot();
    return r;
}

void stereotypes_transform::
update_visited_leaves(const std::list<meta_model::name>& leaves,
    const visitor_details& vd, meta_model::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Updating leaves for: "
                             << vd.base.qualified().dot();

    for (const auto& l : leaves) {
        auto i(m.objects().find(l.qualified().dot()));
        if (i == m.objects().end()) {
            BOOST_LOG_SEV(lg, error) << leaf_not_found << l.qualified().dot();
            BOOST_THROW_EXCEPTION(
                transformation_error(leaf_not_found + l.qualified().dot()));
        }

        auto& o(*i->second);
        o.is_visitation_leaf(true);
        o.base_visitor(vd.base);
        o.derived_visitor(vd.derived);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished updating leaves.";
}

void stereotypes_transform::
add_visitor_to_model(const boost::shared_ptr<meta_model::visitor> v,
    meta_model::model& em) {
    const auto id(v->name().qualified().dot());
    BOOST_LOG_SEV(lg, debug) << "Adding visitor: " << id;

    const auto pair(std::make_pair(id, v));
    const auto i(em.visitors().insert(pair));
    if (!i.second) {
        BOOST_LOG_SEV(lg, error) << duplicate_name << id;
        BOOST_THROW_EXCEPTION(transformation_error(duplicate_name + id));
    }
    BOOST_LOG_SEV(lg, debug) << "Added visitor: " << id;
}

void stereotypes_transform::
expand_visitable(meta_model::object& o, meta_model::model& em) {
    BOOST_LOG_SEV(lg, debug) << "Expanding visitable for: "
                             << o.name().qualified().dot();

    /*
     * The visitable stereotype can only be applied to the root of
     * an inheritance tree - it's an error otherwise.
     */
    const auto id(o.name().qualified().dot());
    if (o.is_child()) {
        BOOST_LOG_SEV(lg, error) << visitable_child << id;
        BOOST_THROW_EXCEPTION(transformation_error(visitable_child + id));
    }

    BOOST_LOG_SEV(lg, debug) << "Found visitation root: " << o.name().qualified().dot();

    /*
     * Visitable types must have at least one leaf. We probably
     * should relax this in light of cross model visitation
     * support, but we'll leave it for now until there is a use
     * case. This means its not possible to mark a type as
     * visitable in one model and have all of its leaves on
     * different models.
     */
    if (o.leaves().empty()) {
        BOOST_LOG_SEV(lg, error) << zero_leaves << id;
        BOOST_THROW_EXCEPTION(transformation_error(zero_leaves + id));
    }

    /*
     * We need to organise the leaves by location. In truth, we
     * are trying to organise the leaves by model really, as there
     * is an assumption that we do not have multiple leaves in
     * different modules for the same model. But it should still
     * work if we do, we just end up generating multiple visitors
     * - one per module.
     *
     * Additional (crazy) limitation: we must have leaves on the
     * same location as the root parent.
     */
    auto bucketed_leaves(bucket_leaves_by_location(o.leaves()));
    auto j(bucketed_leaves.find(o.name().location()));
    if (j == bucketed_leaves.end()) {
        const auto id(o.name().qualified().dot());
        BOOST_LOG_SEV(lg, error) << leaves_not_found << id;
        BOOST_THROW_EXCEPTION(transformation_error(leaves_not_found + id));
    }

    BOOST_LOG_SEV(lg, debug) << "Found bucketed leaves. Total: "
                             << j->second.size();

    /*
     * Now we need to create the base visitor. This always maps
     * to the root parent of the inheritance tree.
     */
    const auto& bvl(j->second);
    const auto& loc(o.name().location());

    /*
     * Preserve the origin type from the root object and generate the
     * visitor base.
     */
    const auto bv(create_visitor(o, loc, o.origin_type(), bvl));
    const auto bvn(bv->name());
    o.is_visitation_root(true);
    o.base_visitor(bvn);
    update_visited_leaves(bvl, visitor_details(bvn), em);
    add_visitor_to_model(bv, em);

    /*
     * If there is only one bucket of leaves then that refers to
     * the parent visitor, which we've already processed so there
     * is nothing else to do.
     */
    if (bucketed_leaves.size() == 1)
        return;

    /*
     * There are other buckets, so first we need to remove the
     * bucket we've already processed.
     */
    bucketed_leaves.erase(j->first);

    /*
     * Now we need to create the descendant visitors, one per
     * bucket.
     */
    for (const auto& pair : bucketed_leaves) {
        /*
         * We are now, possibly, in models other than the model of the
         * root parent. So, if we are generating a visitor for the
         * target model, we must ensure we set the origin type
         * correctly or else it will not come out. Note though that we
         * are setting the origin type to the visitable object, unless
         * the leaf belongs to the target model; whilst not strictly
         * correct, this approximation works in practice because we
         * can only be either a reference model or the target model as
         * proxy models do not contribute visitable types.
         */
        const auto& dv_location(pair.first);
        const auto emmm(em.name().location().model_modules());
        const bool in_target_model(emmm == dv_location.model_modules());
        const auto ot(in_target_model ?
            meta_model::origin_types::target : o.origin_type());

        /*
         * Generate the derived visitor and update its leaves.
         */
        const auto& bl(pair.second);
        auto dv(create_visitor(o, dv_location, ot, bl));
        const auto dvn(dv->name());
        dv->parent(bvn);
        update_visited_leaves(bl, visitor_details(bvn, dvn), em);
        add_visitor_to_model(dv, em);
    }

    BOOST_LOG_SEV(lg, debug) << "Done injecting visitor.";
}

bool stereotypes_transform::try_as_object_template(const std::string& s,
    meta_model::object& o, const meta_model::model& m) {

    using helpers::resolver;
    const auto oot(resolver::try_resolve_object_template_name(o.name(), s, m));
    if (!oot)
        return false;

    o.object_templates().push_back(*oot);
    return true;
}

void stereotypes_transform::apply(meta_model::object& o, meta_model::model& m) {
    BOOST_LOG_SEV(lg, debug) << "Expanding stereotypes for: " << o.name().qualified().dot();

    /*
     * If there are no stereotypes of either type, then there is no
     * point in proceeding.
     */
    if (o.static_stereotypes().empty() && o.dynamic_stereotypes().empty()) {
        BOOST_LOG_SEV(lg, debug) << "No stereotypes found.";
        return;
    }

    transform_static_stereotypes(o, m);
    transform_dynamic_stereotypes(o, m);
}

void stereotypes_transform::apply(meta_model::primitive& p) {
    const auto id(p.name().qualified().dot());
    BOOST_LOG_SEV(lg, debug) << "Expanding stereotypes for: " << id;

    /*
     * Primitives do not support any unknown stereotypes.
     */
    if (!p.dynamic_stereotypes().empty()) {
        const auto s(boost::lexical_cast<std::string>(p.dynamic_stereotypes()));
        BOOST_LOG_SEV(lg, error) << invalid_stereotypes << s;
        BOOST_THROW_EXCEPTION(transformation_error(invalid_stereotypes + s));
    }

    /*
     * If there are no well-known stereotypes, then there is no point
     * in proceeding.
     */
    if (p.static_stereotypes().empty()) {
        BOOST_LOG_SEV(lg, debug) << "No stereotypes found.";
        return;
    }

    /*
     * Process all of the well-known stereotypes, collecting any
     * invalid ones as we go along.
     */
    using meta_model::static_stereotypes;
    std::list<static_stereotypes> unknown_static_stereotypes;
    for (const auto st : p.static_stereotypes()) {
        if (is_element_type(st)) {
            /*
             * We can safely ignore any element type information as
             * that has already been used to instantiate the
             * appropriate meta-model elements.
             */
            continue;
        } else if (st == static_stereotypes::immutable)
            p.is_immutable(true);
        else if (st == static_stereotypes::orm_value) {
            meta_model::orm_primitive_properties cfg;
            cfg.generate_mapping(true);
            p.orm_properties(cfg);
        } else
            unknown_static_stereotypes.push_back(st);
    }

    /*
     * Any attempt to use a well-known stereotype against this model
     * element which we do not recognise must be invalid (since we
     * process all of the well-known stereotypes at this point).
     */
    if (!unknown_static_stereotypes.empty()) {
        const auto s(boost::lexical_cast<std::string>(
                unknown_static_stereotypes));
        BOOST_LOG_SEV(lg, error) << invalid_stereotypes << s;
        BOOST_THROW_EXCEPTION(transformation_error(invalid_stereotypes + s));
    }
}

void stereotypes_transform::apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "stereotypes transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    for (auto& pair : m.objects())
        apply(*pair.second, m);

    for (auto& pair : m.primitives())
        apply(*pair.second);

    stp.end_transform(m);
}

}
