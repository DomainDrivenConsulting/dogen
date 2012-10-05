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
#include <sstream>
#include <iostream>
#include "dogen/generator/modeling/validation_error.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/sml/io/qualified_name_io.hpp"
#include "dogen/sml/io/primitive_io.hpp"
#include "dogen/sml/io/property_io.hpp"
#include "dogen/sml/io/pod_io.hpp"
#include "dogen/sml/io/model_io.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/generator/modeling/sml_builder.hpp"

namespace  {

static dogen::utility::log::logger
lg(dogen::utility::log::logger_factory("sml_builder"));

const std::string orphan_pod("Pod's parent could not be located: ");
const std::string undefined_type("Pod has property with undefined type");
const std::string missing_target("No target model found");

}

namespace dogen {
namespace generator {
namespace modeling {

sml_builder::sml_builder(bool verbose, std::string schema_name)
    : verbose_(verbose), has_target_(false), schema_name_(schema_name) { }

void sml_builder::resolve_parent(sml::pod pod) {
    const auto pods(merged_model_.pods());
    auto parent(pod.parent_name());

    while (parent) {
        sml::qualified_name pqn(*parent);
        const auto i(pods.find(pqn));
        if (i == pods.end()) {
            std::ostringstream stream;
            stream << orphan_pod << ". pod: "
                   << pod.name().type_name() << ". parent: "
                   << pqn.type_name();
            throw validation_error(stream.str());
        }

        parent = i->second.parent_name();
    }
}

std::vector<sml::property>
sml_builder::resolve_properties(sml::pod pod) {
    const auto pods(merged_model_.pods());
    const auto primitives(merged_model_.primitives());

    auto r(pod.properties());
    for (unsigned int i(0); i < r.size(); ++i) {
        sml::property property(r[i]);
        sml::qualified_name pqn(property.type_name());

        pqn.meta_type(sml::meta_types::pod);
        const auto j(pods.find(pqn));
        if (j != pods.end()) {
            property.type_name(pqn);
            r[i] = property;
            continue;
        }

        pqn.meta_type(sml::meta_types::primitive);
        const auto k(primitives.find(pqn));
        if (k != primitives.end()) {
            property.type_name(pqn);
            r[i] = property;
            continue;
        }

        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg, error) << "failed to find property type:" << pqn
                                 << "pods: " << pods
                                 << "primitives: " << primitives;

        std::ostringstream stream;
        stream << undefined_type << ". pod: "
               << pod.name().type_name() << ". property type: "
               << pqn.type_name();
        throw validation_error(stream.str());
    }
    return r;
}

void sml_builder::resolve() {
    const auto primitives(merged_model_.primitives());
    auto pods(merged_model_.pods());

    for (auto i(pods.begin()); i != pods.end(); ++i) {
        const sml::qualified_name qualified_name(i->first);
        sml::pod& pod(i->second);
        if (!pod.generate())
            continue;

        resolve_parent(pod);
        pod.properties(resolve_properties(pod));
    }
    merged_model_.pods(pods);
}

void sml_builder::merge() {
    if (!has_target_)
        throw validation_error(missing_target);

    merged_model_.name(name_);

    auto pods(merged_model_.pods());
    auto primitives(merged_model_.primitives());
    for (const auto m : models_) {
        using namespace dogen::utility::log;
        BOOST_LOG_SEV(lg, info) << "merging model: " << m.name()
                                << " pods: " << m.pods().size()
                                << " primitives: " << m.primitives().size();

        for (const auto p : m.pods()) {
            if (p.first.model_name() != m.name()) {
                std::ostringstream stream;
                stream << "Pod does not belong to this model. Model name: '"
                       << m.name() << "'. Pod qualified name: "
                       << p.first;
                BOOST_LOG_SEV(lg, error) << stream.str();
                throw validation_error(stream.str());
            }

            if (p.first.meta_type() != sml::meta_types::pod) {
                std::ostringstream stream;
                stream << "Pod has incorrect meta_type: '" << p.first;
                BOOST_LOG_SEV(lg, error) << stream.str();
                throw validation_error(stream.str());
            }

            if (p.first != p.second.name()) {
                std::ostringstream stream;
                stream << "Inconsistency between key and value qualified names: "
                       << " key: " << p.first << " value: " << p.second.name();
                BOOST_LOG_SEV(lg, error) << stream.str();
                throw validation_error(stream.str());
            }

            pods.insert(p);
        }

        for (const auto p : m.primitives()) {
            primitives.insert(p);
        }
    }
    merged_model_.pods(pods);
    merged_model_.primitives(primitives);
    merged_model_.external_package_path(external_package_path_);
    merged_model_.schema_name(schema_name_);
}

void sml_builder::add_target(sml::model model) {
    using namespace dogen::utility::log;
    if (has_target_) {
        std::ostringstream stream;
        stream << "Only one target expected. Last target model name: '"
               << name_ << "'. New target model name: "
               << model.name();
        BOOST_LOG_SEV(lg, error) << stream.str();
        throw validation_error(stream.str());
    }

    name_ = model.name();
    has_target_ = true;
    external_package_path_ = model.external_package_path();

    add(model);
    BOOST_LOG_SEV(lg, debug) << "added target model: " << model.name();
}

void sml_builder::add(sml::model model) {
    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg, debug) << "adding model: " << model.name();
    models_.push_back(model);
}

sml::model sml_builder::build() {
    merge();
    resolve();
    using namespace dogen::utility::log;
    BOOST_LOG_SEV(lg, debug) << "merged model: " << merged_model_;
    return merged_model_;
}

} } }
