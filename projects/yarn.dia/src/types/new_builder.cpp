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
#include "dogen/yarn.dia/types/building_error.hpp"
#include "dogen/yarn.dia/types/new_adapter.hpp"
#include "dogen/yarn.dia/types/new_builder.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("yarn.dia.builder"));

const std::string empty_contained_by;
const std::list<std::string> empty_parents;
const std::string duplicate_id("Duplicate id: ");
const std::string package_not_mapped(
    "Dia package ID is not mapped to yarn module: ");

}

namespace dogen {
namespace yarn {
namespace dia {

new_builder::
new_builder(const std::unordered_map<std::string, std::list<std::string>>&
    parent_id_to_child_ids) : parent_id_to_child_ids_(parent_id_to_child_ids) {}

void
new_builder::update_parentage(const std::string& id, const std::string& n) {
    const auto i(parent_id_to_child_ids_.find(id));
    if (i == parent_id_to_child_ids_.end()) {
        /*
         * If we're not a parent, there is nothing to be done with
         * regards to parentage.
         */
        return;
    }

    /*
     * For every child of ours, map them against our name. Since we
     * are processing objects in dependency order, we know that all
     * parents have been processed before their children, and thus
     * this container is fully populated by the time the child reads
     * it.
     */
    for (const auto c : i->second)
        child_id_to_parent_names_[c].push_back(n);
}

const std::list<std::string>&
new_builder::parents_for_object(const std::string& id) const {
    const auto i(child_id_to_parent_names_.find(id));
    if (i != child_id_to_parent_names_.end())
        return i->second;

    return empty_parents;
}

std::string new_builder::contained_by(const std::string& id) const {
    auto& c(id_to_uml_large_package_properties_);
    const auto i(c.find(id));
    if (i != c.end())
        return i->second.name;

    return empty_contained_by;
}

void new_builder::handle_uml_large_package(const processed_object& po) {
    uml_large_package_properties p;
    p.name = po.name();

    /*
     * We have just finished inserting the exoelement so we can be
     * confident that the last element is the one we're interested
     * in. This is not ideal but will do for now.
     */
    p.exoelement = --(model_.elements().end());

    const auto& id(po.id());
    const auto pair(std::make_pair(id, p));

    auto& c(id_to_uml_large_package_properties_);
    const auto inserted(c.insert(pair).second);
    if (!inserted) {
        BOOST_LOG_SEV(lg, error) << duplicate_id << id;
        BOOST_THROW_EXCEPTION(building_error(duplicate_id + id));
    }
}

void new_builder::handle_uml_note(const processed_object& po) {
    const auto& c(po.comment());
    BOOST_LOG_SEV(lg, debug) << "Object is a note: " << po.id()
                             << ". Note text: '" << c.original_content() << "'";

    if (c.original_content().empty() || !c.applicable_to_parent_object())
        return;

    if (po.child_node_id().empty()) {
        /*
         * Since this note does not have a child, it is a top-level
         * note. Thus is may be used to convey both tagged values and
         * documentation for the model.
         */
        model_.documentation(c.documentation());
        model_.tagged_values(c.key_value_pairs());
        return;
    }

    /*
     * If the note is contained inside of a package, we need to ensure
     * we update the exoelement for the for that UML package with its
     * tagged values and documentation. The module must already exist.
     */
    const auto package_id(po.child_node_id());
    const auto i(id_to_uml_large_package_properties_.find(package_id));
    if (i == id_to_uml_large_package_properties_.end()) {
        BOOST_LOG_SEV(lg, error) << package_not_mapped << package_id;
        BOOST_THROW_EXCEPTION(building_error(package_not_mapped + package_id));
    }

    auto& e(*i->second.exoelement);
    e.documentation(c.documentation());
    e.tagged_values(c.key_value_pairs());
}

void new_builder::add(const processed_object& po) {
    /*
     * First, we handle UML notes. Since Dia does not support adding
     * comments directly to UML packages, we "extended" it via the use
     * of UML notes. This means that when we find a note, we need to
     * check if its contents must be added to its containing package.
     */
    const auto dot(po.dia_object_type());
    if (dot == dia_object_types::uml_note) {
        handle_uml_note(po);
        return;
    }

    /*
     * For all other cases other than UML notes, we know we need to
     * generate a exoelement. For these, the first thing we need to do
     * is to figure out the containment of the current process object.
     */
    const auto& id(po.id());
    const auto cby(contained_by(id));

    /*
     * Then we get the parents for the processed object.
     */
    const auto& p(parents_for_object(id));

    /*
     * Now we can adapt the processed object and add it to the exomodel.
     */
    const auto e(new_adapter::adapt(po, cby, p));
    model_.elements().push_back(e);

    /*
     * Now we need to deal with the post-processing. For UML packages,
     * we need to remember them for later. As explained above, we need
     * to update them with the contents of UML notes.
     */
    if (dot == dia_object_types::uml_large_package) {
        handle_uml_large_package(po);
        return;
    }

    /*
     * For processed objects which can be parents, we need to update
     * their parenting details. Note that this refers to the children
     * of the current object, not its parents (which were handled
     * above).
     */
    update_parentage(id, po.name());
}

meta_model::exomodel new_builder::build() {
    return model_;
}

} } }
