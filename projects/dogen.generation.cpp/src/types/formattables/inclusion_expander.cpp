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
#include <typeindex>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.generation.cpp/types/formattables/expansion_error.hpp"
#include "dogen.generation.cpp/types/formatters/artefact_formatter_interface.hpp"
#include "dogen.generation.cpp/types/formattables/directive_group_repository_factory.hpp"
#include "dogen.generation.cpp/types/formattables/inclusion_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "generation.cpp.formattables.inclusion_expander"));

const char angle_bracket('<');
const std::string double_quote("\"");
const std::string boost_name("boost");
const std::string boost_serialization_gregorian("greg_serialize.hpp");

const std::string duplicate_element_name("Duplicate delement name: ");
const std::string missing_archetype("Archetype not found: ");
const std::string empty_include_directive("Include directive is empty.");
const std::string formatter_not_found_for_type(
    "Formatter not found for type: ");
const std::string empty_archetype("Formatter name is empty.");

bool include_directive_comparer(
    const std::string& lhs, const std::string& rhs) {

    if (lhs.empty() || rhs.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_include_directive;
        using dogen::generation::cpp::formattables::expansion_error;
        BOOST_THROW_EXCEPTION(expansion_error(empty_include_directive));
    }

    const bool lhs_has_angle_brackets(lhs[0] == angle_bracket);
    const bool rhs_has_angle_brackets(rhs[0] == angle_bracket);

    if (lhs_has_angle_brackets && !rhs_has_angle_brackets)
        return true;

    if (!lhs_has_angle_brackets && rhs_has_angle_brackets)
        return false;

    if (lhs_has_angle_brackets && rhs_has_angle_brackets) {
        const auto npos(std::string::npos);
        const bool lhs_is_boost(lhs.find_first_of(boost_name) != npos);
        const bool rhs_is_boost(rhs.find_first_of(boost_name) != npos);
        if (!lhs_is_boost && rhs_is_boost)
            return false;

        if (lhs_is_boost && !rhs_is_boost)
            return true;

        // FIXME: hacks for headers that must be last
        const bool lhs_is_gregorian(
            lhs.find_first_of(boost_serialization_gregorian) != npos);
        const bool rhs_is_gregorian(
            rhs.find_first_of(boost_serialization_gregorian) != npos);
        if (lhs_is_gregorian && !rhs_is_gregorian)
            return true;

        if (!lhs_is_gregorian && rhs_is_gregorian)
            return false;
    }

    if (lhs.size() != rhs.size())
        return lhs.size() < rhs.size();

    return lhs < rhs;
}

}

namespace dogen::generation::cpp::formattables {

directive_group_repository inclusion_expander::
create_directive_groups(
    const variability::meta_model::feature_model& feature_model,
    const formatters::repository& frp, const locator& l,
    const std::unordered_map<std::string, formattable>& formattables) const {

    directive_group_repository_factory f;
    return f.make(feature_model, frp, l, formattables);
}

inclusion_expander::element_inclusion_dependencies_type
inclusion_expander::compute_inclusion_dependencies(
    const formatters::repository& frp,
    const dependencies_builder_factory& df,
    const assets::meta_model::element& e) const {

    const auto id(e.name().qualified().dot());
    BOOST_LOG_SEV(lg, debug) << "Creating inclusion dependencies for: " << id;

    /*
     * First we must obtain all formatters for the type of element we
     * are building includes for. They may or may not exist in the
     * formatters' collection - for example, we do not have any
     * formatters for object templates at present. If so, we're done.
     *
     * Note also that we must query the formatters by meta-type
     * rather than use the archetype configuration container
     * directly. This is due to element segmentation, as we may have
     * more than one element associated with an id. To generate the
     * inclusion dependencies we must make sure we pick the pair of
     * element and the formatters that support it.
     */
    element_inclusion_dependencies_type r;
    const auto mn(e.meta_name().qualified().dot());
    const auto i(frp.stock_artefact_formatters_by_meta_name().find(mn));
    if (i == frp.stock_artefact_formatters_by_meta_name().end()) {
        BOOST_LOG_SEV(lg, debug) << "No formatters for type: " << mn;
        return r;
    }

    for (const auto fmt : i->second) {
        const auto arch(fmt->archetype_location().archetype());
        BOOST_LOG_SEV(lg, debug) << "Providing for: " << arch
                                 << " using formatter: " << fmt->id();

        /*
         * Obtain the formatter's list of inclusion dependencies. If
         * none, we're done.
         */
        auto deps(fmt->inclusion_dependencies(df, e));
        if (deps.empty())
            continue;

        /*
         * Ensure the dependencies are sorted according to a well
         * defined order and all duplicates are removed. Duplicates
         * arise because an element may refer to another element more
         * than once - e.g. std::list<T> as well as std::vector<T>.
         */
        deps.sort(include_directive_comparer);
        deps.unique();

        /*
         * Now slot in the results, ensuring our formatter name is
         * unique. We have guaranteed in the registrar that the
         * formatter name is unique, so no need to perform any
         * insertion checks here.
         */
        r[arch] = deps;
    }

    BOOST_LOG_SEV(lg, debug) << "Finished creating inclusion dependencies for: "
                             << id << ". Result: " << r;

    return r;
}

void inclusion_expander::populate_inclusion_dependencies(
    const formatters::repository& frp,
    const dependencies_builder_factory& df,
    std::unordered_map<std::string, formattable>& formattables) const {

    BOOST_LOG_SEV(lg, debug) << "Creating inclusion dependencies "
                             << "for all formattables. ";

    for (auto& pair : formattables) {
        const auto id(pair.first);
        auto& formattable(pair.second);

        /*
         * We need to compute the inclusion dependencies for each
         * segment of this element. By definition, the segments all
         * share the same element id so we can obtain a reference for
         * our container up front and populate it for each segment.
         */
        auto& eprops(formattable.element_properties());
        auto& art_props(eprops.artefact_properties());
        for (const auto& ptr : formattable.all_segments()) {
            const auto& e(*ptr);

            /*
             * We do not need to compute inclusion dependencies for
             * elements that are not part of the target
             * model. However, we do need them around for inclusion
             * directives, so we can't rely on reduction.
             */
            if (e.origin_type() != assets::meta_model::origin_types::target)
                continue;

            /*
             * Compute the dependencies for this segment of the
             * element. If it does not have any dependencies, we
             * haven't got any work to do.
             */
            const auto deps(compute_inclusion_dependencies(frp, df, e));
            if (deps.empty())
                continue;

            /*
             * Copy across all of the dependencies for the element.
             * Note that this caters for multi-segment elements,
             * merging them all into a single set of dependencies.
             */
            for (const auto& pair : deps) {
                /*
                 * First we need to obtain the configuration for this
                 * formatter. It must have been initialised by the
                 * transformer.
                 */
                const auto arch(pair.first);
                const auto i(art_props.find(arch));
                if (i == art_props.end()) {
                    BOOST_LOG_SEV(lg, error) << missing_archetype << arch;
                    BOOST_THROW_EXCEPTION(
                        expansion_error(missing_archetype + arch));
                }
                i->second.inclusion_dependencies(pair.second);
            }
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Finished creating inclusion dependencies "
                             << "for all formattables. ";
}

void inclusion_expander::expand(
    const variability::meta_model::feature_model& feature_model,
    const std::unordered_set<generation::meta_model::element_archetype>&
    enabled_archetype_for_element, const formatters::repository& frp,
    const locator& l, model& fm) const {

    auto& fbls(fm.formattables());
    const auto dgrp(create_directive_groups(feature_model, frp, l, fbls));
    dependencies_builder_factory df(dgrp, enabled_archetype_for_element);
    populate_inclusion_dependencies(frp, df, fbls);
}

}
