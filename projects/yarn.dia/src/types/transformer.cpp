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
#include <set>
#include <boost/make_shared.hpp>
#include <boost/variant/get.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/dia/types/composite.hpp"
#include "dogen/dia/types/attribute.hpp"
#include "dogen/yarn.dia/types/traits.hpp"
#include "dogen/yarn.dia/types/transformation_error.hpp"
#include "dogen/yarn.dia/io/object_types_io.hpp"
#include "dogen/yarn.dia/types/processed_object.hpp"
#include "dogen/yarn.dia/io/processed_object_io.hpp"
#include "dogen/yarn.dia/io/context_io.hpp"
#include "dogen/yarn.dia/types/validator.hpp"
#include "dogen/yarn.dia/types/transformer.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.dia.transformer"));

const std::string empty;
const std::string unsigned_int("unsigned int");
const std::string empty_dia_object_name("Dia object name is empty");
const std::string empty_package_id("Supplied package id is empty");
const std::string parent_not_found("Object has a parent but its not defined: ");
const std::string empty_parent_container(
    "Object has an entry in child to parent container but its empty: ");
const std::string missing_module_for_name("Missing module for name: ");
const std::string missing_name_for_id("Missing name for dia object ID: ");
const std::string type_attribute_expected(
    "Could not find type attribute. ID: ");
const std::string invalid_type_string(
    "String provided with type did not parse into Yarn names: ");
const std::string object_has_invalid_type("Invalid dia type: ");
const std::string invalid_stereotype_in_graph("Invalid stereotype: ");
const std::string immutabilty_with_inheritance(
    "Immutability not supported with inheritance: ");
const std::string multiple_inheritance(
    "Child has more than one parent, but multiple inheritance not supported:");

}

namespace dogen {
namespace yarn {
namespace dia {

transformer::transformer(const dynamic::workflow& w, context& c)
    : context_(c), dynamic_workflow_(w) {

    BOOST_LOG_SEV(lg, debug) << "Initial context: " << context_;
}

void transformer::require_is_transformable(const processed_object& po) const {
    if (!is_transformable(po)) {
        const auto type(boost::lexical_cast<std::string>(po.object_type()));
        BOOST_LOG_SEV(lg, error) << object_has_invalid_type << type;
        BOOST_THROW_EXCEPTION(
            transformation_error(object_has_invalid_type + type));
    }
}

yarn::generation_types transformer::generation_type(const profile& p) const {
    using yarn::generation_types;
    if (!context_.model().is_target())
        return generation_types::no_generation;

    if (p.is_non_generatable() || p.is_service())
        return generation_types::partial_generation;

    return generation_types::full_generation;
}

yarn::name transformer::to_name(const std::string& n) const {
    if (n.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(transformation_error(empty_dia_object_name));
    }

    yarn::name_factory f;
    return f.build_element_in_model(context_.model().name(), n);
}

yarn::name transformer::to_name(const std::string& n,
    const yarn::name& module_n) const {

    if (n.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(transformation_error(empty_dia_object_name));
    }

    yarn::name_factory f;
    return f.build_element_in_module(module_n, n);
}

yarn::module& transformer::module_for_name(const yarn::name& n) {
    auto i(context_.model().modules().find(n.qualified()));
    if (i == context_.model().modules().end()) {
        const auto sn(n.simple());
        BOOST_LOG_SEV(lg, error) << missing_module_for_name << sn;
        BOOST_THROW_EXCEPTION(
            transformation_error(missing_module_for_name + sn));
    }
    return i->second;
}

yarn::module& transformer::module_for_id(const std::string& id) {
    if (id.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_package_id;
        BOOST_THROW_EXCEPTION(transformation_error(empty_package_id));
    }

    const auto i(context_.id_to_name().find(id));
    if (i == context_.id_to_name().end()) {
        BOOST_LOG_SEV(lg, error) << missing_name_for_id << id;
        BOOST_THROW_EXCEPTION(transformation_error(missing_name_for_id + id));
    }

    return module_for_name(i->second);
}

yarn::property transformer::to_property(const yarn::name& owning_element,
    const processed_property& p) const {
    if (p.name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(transformation_error(empty_dia_object_name));
    }

    yarn::name_factory f;
    const auto n(f.build_property_name(owning_element, p.name()));

    yarn::property r;
    r.name(n);
    r.unparsed_type(p.type());
    r.documentation(p.comment().documentation());

    const auto& kvps(p.comment().key_value_pairs());
    const auto scope(dynamic::scope_types::property);
    r.extensions(dynamic_workflow_.execute(scope, kvps));

    return r;
}

yarn::enumerator transformer::to_enumerator(const processed_property& p,
    const unsigned int position) const {
    yarn::enumerator r;
    r.name(p.name());
    r.value(boost::lexical_cast<std::string>(position));
    r.documentation(p.comment().documentation());

    if (r.name().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_dia_object_name;
        BOOST_THROW_EXCEPTION(transformation_error(empty_dia_object_name));
    }
    return r;
}

void transformer::
update_object(yarn::object& o, const processed_object& po, const profile& p) {
    update_element(o, po, p);

    o.is_fluent(p.is_fluent());
    o.is_visitable(p.is_visitable());

    for (const auto us : p.unknown_stereotypes()) {
        const auto n(to_name(us));
        o.modeled_concepts().push_back(n);
    }

    for (const auto& p : po.properties())
        o.local_properties().push_back(to_property(o.name(), p));

    const auto i(context_.child_id_to_parent_ids().find(po.id()));
    if (i != context_.child_id_to_parent_ids().end()) {
        if (i->second.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_parent_container << po.id();
            BOOST_THROW_EXCEPTION(
                transformation_error(empty_parent_container + po.id()));
        }

        if (i->second.size() > 1) {
            BOOST_LOG_SEV(lg, error) << multiple_inheritance << po.id();
            BOOST_THROW_EXCEPTION(
                transformation_error(multiple_inheritance + po.id()));
        }

        const auto parent_name(i->second.front());
        const auto j(context_.id_to_name().find(parent_name));
        if (j == context_.id_to_name().end()) {
            BOOST_LOG_SEV(lg, error) << "Object has a parent but "
                                     << " there is no Name mapping defined."
                                     << " Child ID: '" << po.id()
                                     << "' Parent ID: '" << parent_name << "'";

            BOOST_THROW_EXCEPTION(
                transformation_error(parent_not_found + po.id()));
        }

        BOOST_LOG_SEV(lg, debug) << "Setting parent for: "
                                 << o.name().qualified() << " as "
                                 << j->second.qualified();
        o.is_child(true);
        o.parents().push_back(j->second);
    } else {
        BOOST_LOG_SEV(lg, debug) << "Object has no parent: "
                                 << o.name().qualified();
    }

    const auto j(context_.parent_ids().find(po.id()));
    o.is_parent(j != context_.parent_ids().end());
    o.is_final(!o.is_parent());
    context_.id_to_name().insert(std::make_pair(po.id(), o.name()));

    o.is_immutable(p.is_immutable());
    if ((o.is_parent() || o.is_child()) && p.is_immutable())  {
        BOOST_LOG_SEV(lg, error) << immutabilty_with_inheritance
                                 << o.name().simple();

        BOOST_THROW_EXCEPTION(
            transformation_error(immutabilty_with_inheritance +
                o.name().simple()));
    }
}

void transformer::to_exception(const processed_object& o, const profile& p) {
    BOOST_LOG_SEV(lg, debug) << "Object is an exception: " << o.id();

    yarn::exception e;
    update_element(e, o, p);

    auto& exceptions(context_.model().exceptions());
    exceptions.insert(std::make_pair(e.name().qualified(), e));
}

void transformer::to_service(const processed_object& o, const profile& p) {
    BOOST_LOG_SEV(lg, debug) << "Object is a service: " << o.id();

    yarn::object s;
    s.object_type(yarn::object_types::user_defined_service);
    update_object(s, o, p);
    auto& objects(context_.model().objects());
    objects.insert(std::make_pair(s.name().qualified(), s));
}

void transformer::to_value_object(const processed_object& o, const profile& p) {
    BOOST_LOG_SEV(lg, debug) << "Object is a value object: " << o.id();

    yarn::object vo;
    update_object(vo, o, p);
    vo.object_type(yarn::object_types::user_defined_value_object);
    auto& objects(context_.model().objects());
    objects.insert(std::make_pair(vo.name().qualified(), vo));
}

void transformer::to_enumeration(const processed_object& o, const profile& p) {
    BOOST_LOG_SEV(lg, debug) << "Object is an enumeration: " << o.id();
    yarn::enumeration e;
    update_element(e, o, p);

    // FIXME: we should do this further down the stack.
    dogen::yarn::name n;
    n.simple(unsigned_int);
    e.underlying_type(n);

    dogen::yarn::enumerator invalid;
    invalid.name("invalid");
    invalid.documentation("Represents an uninitialised enum");
    invalid.value("0");
    e.enumerators().push_back(invalid);

    std::set<std::string> enumerator_names;
    enumerator_names.insert(invalid.name());

    unsigned int pos(1);
    for (const auto& p : o.properties()) {
        auto enumerator(to_enumerator(p, pos++));

        const auto i(enumerator_names.find(enumerator.name()));
        if (i != enumerator_names.end()) {
            BOOST_LOG_SEV(lg, error) << "Duplicate enumerator name: "
                                     << enumerator.name();
            BOOST_THROW_EXCEPTION(transformation_error(
                    "Duplicate enumerator name: " + enumerator.name()));
        }
        e.enumerators().push_back(enumerator);
        enumerator_names.insert(enumerator.name());
    }
    auto& enumerations(context_.model().enumerations());
    enumerations.insert(std::make_pair(e.name().qualified(), e));
}

void transformer::to_module(const processed_object& o, const profile& p) {
    BOOST_LOG_SEV(lg, debug) << "Object is a module: " << o.id();

    yarn::module m;
    update_element(m, o, p);
    auto& modules(context_.model().modules());
    modules.insert(std::make_pair(m.name().qualified(), m));
}

void transformer::from_note(const processed_object& o) {
    BOOST_LOG_SEV(lg, debug) << "Object is a note: " << o.id()
                             << ". Note text: '"
                             << o.comment().original_content() << "'";

    if (o.comment().original_content().empty() ||
        !o.comment().applicable_to_parent_object())
        return;

    const auto& documentation(o.comment().documentation());
    const auto& kvps(o.comment().key_value_pairs());
    const auto& model(context_.model());
    using dynamic::scope_types;
    if (o.child_node_id().empty()) {
        auto& module(module_for_name(model.name()));
        module.documentation(documentation);

        const auto scope(scope_types::root_module);
        module.extensions(dynamic_workflow_.execute(scope, kvps));
        return;
    }

    yarn::module& module(module_for_id(o.child_node_id()));
    module.documentation(documentation);

    const auto scope(scope_types::any_module);
    module.extensions(dynamic_workflow_.execute(scope, kvps));
}

void transformer::to_concept(const processed_object& o, const profile& p) {
    yarn::concept c;
    update_element(c, o, p);

    for (const auto& prop : o.properties())
        c.local_properties().push_back(to_property(c.name(), prop));

    const auto i(context_.child_id_to_parent_ids().find(o.id()));
    c.is_child(i != context_.child_id_to_parent_ids().end());
    if (c.is_child()) {
        if (i->second.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_parent_container << o.id();
            BOOST_THROW_EXCEPTION(
                transformation_error(empty_parent_container + o.id()));
        }

        for (const auto& concept_id : i->second) {
            const auto j(context_.id_to_name().find(concept_id));
            if (j == context_.id_to_name().end()) {
                BOOST_LOG_SEV(lg, error) << "Object has a parent but "
                                         << " there is no Name mapping."
                                         << " Child ID: '" << o.id()
                                         << "' Parent ID: '" << concept_id
                                         << "'";

                BOOST_THROW_EXCEPTION(
                    transformation_error(parent_not_found + o.id()));
            }
            c.refines().push_back(j->second);
        }
    }

    const auto j(context_.parent_ids().find(o.id()));
    c.is_parent(j != context_.parent_ids().end());
    auto& concepts(context_.model().concepts());
    concepts.insert(std::make_pair(c.name().qualified(), c));
}

bool transformer::is_transformable(const processed_object& o) const {
    const auto ot(o.object_type());
    return
        ot == object_types::uml_large_package ||
        ot == object_types::uml_generalization ||
        ot == object_types::uml_class ||
        ot == object_types::uml_note;
}

void transformer::dispatch(const processed_object& o, const profile& p) {
    if (p.is_uml_large_package())
        to_module(o, p);
    else if (p.is_uml_note())
        from_note(o);
    else if (p.is_enumeration())
        to_enumeration(o, p);
    else if (p.is_concept())
        to_concept(o, p);
    else if (p.is_exception())
        to_exception(o, p);
    else if (p.is_service())
        to_service(o, p);
    else
        to_value_object(o, p);
}

void transformer::transform(const processed_object& o, const profile& p) {
    BOOST_LOG_SEV(lg, debug) << "Starting to transform: " << o.id();
    BOOST_LOG_SEV(lg, debug) << "Object contents: " << o;

    require_is_transformable(o);
    dispatch(o, p);

    BOOST_LOG_SEV(lg, debug) << "Transformed: " << o.id();
}

} } }
