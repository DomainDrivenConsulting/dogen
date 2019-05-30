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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_VARIABILITY_FEATURE_BUNDLE_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_VARIABILITY_FEATURE_BUNDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include "dogen.assets/types/meta_model/name.hpp"
#include "dogen.assets/types/meta_model/element.hpp"
#include "dogen.assets/types/meta_model/variability/feature_template.hpp"

namespace dogen::assets::meta_model::variability {

/**
 * @brief A feature bundle represents an aggregation of feature templates in a model.
 *
 * The feature templates should be "semantically related", that is, belong to a related
 * topic. A feature bundle is used by code generation to generate infrastructural code
 * to ease the creation and subsequent processing of features. Generated code
 * comprises of two aspects: the registration of the feature for the dynamic part of the
 * processing and the generation of a static configuration class to represent the
 * feature once read out from the dynamic configuration.
 */
class feature_bundle final : public dogen::assets::meta_model::element {
public:
    feature_bundle(const feature_bundle&) = default;
    feature_bundle(feature_bundle&&) = default;

public:
    feature_bundle();

    virtual ~feature_bundle() noexcept { }

public:
    feature_bundle(
        const dogen::assets::meta_model::name& name,
        const std::string& documentation,
        const dogen::assets::meta_model::origin_types origin_type,
        const std::string& contained_by,
        const bool in_global_module,
        const std::list<dogen::assets::meta_model::static_stereotypes>& static_stereotypes,
        const std::list<std::string>& dynamic_stereotypes,
        const dogen::assets::meta_model::name& meta_name,
        const dogen::assets::meta_model::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
        const bool is_element_extension,
        const std::unordered_map<std::string, dogen::assets::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::assets::meta_model::local_archetype_location_properties>& archetype_location_properties,
        const boost::optional<dogen::assets::meta_model::decoration::element_properties>& decoration,
        const std::list<dogen::assets::meta_model::name>& transparent_associations,
        const std::list<dogen::assets::meta_model::name>& opaque_associations,
        const std::list<dogen::assets::meta_model::name>& associative_container_keys,
        const std::list<dogen::assets::meta_model::variability::feature_template>& feature_templates,
        const bool generate_static_configuration,
        const bool requires_manual_default_constructor);

public:
    using element::accept;

    virtual void accept(const element_visitor& v) const override;
    virtual void accept(element_visitor& v) const override;
    virtual void accept(const element_visitor& v) override;
    virtual void accept(element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief Elements that are involved in aggregation or composition relationships.
     */
    /**@{*/
    const std::list<dogen::assets::meta_model::name>& transparent_associations() const;
    std::list<dogen::assets::meta_model::name>& transparent_associations();
    void transparent_associations(const std::list<dogen::assets::meta_model::name>& v);
    void transparent_associations(const std::list<dogen::assets::meta_model::name>&& v);
    /**@}*/

    /**
     * @brief Elements that are involved in aggregation or composition relationships via
     * indirection.
     *
     * This is used to break cycles where required.
     */
    /**@{*/
    const std::list<dogen::assets::meta_model::name>& opaque_associations() const;
    std::list<dogen::assets::meta_model::name>& opaque_associations();
    void opaque_associations(const std::list<dogen::assets::meta_model::name>& v);
    void opaque_associations(const std::list<dogen::assets::meta_model::name>&& v);
    /**@}*/

    /**
     * @brief Elements that are keys in an associative container.
     */
    /**@{*/
    const std::list<dogen::assets::meta_model::name>& associative_container_keys() const;
    std::list<dogen::assets::meta_model::name>& associative_container_keys();
    void associative_container_keys(const std::list<dogen::assets::meta_model::name>& v);
    void associative_container_keys(const std::list<dogen::assets::meta_model::name>&& v);
    /**@}*/

    /**
     * @brief Set of feature templates associated with this feature bundle.
     */
    /**@{*/
    const std::list<dogen::assets::meta_model::variability::feature_template>& feature_templates() const;
    std::list<dogen::assets::meta_model::variability::feature_template>& feature_templates();
    void feature_templates(const std::list<dogen::assets::meta_model::variability::feature_template>& v);
    void feature_templates(const std::list<dogen::assets::meta_model::variability::feature_template>&& v);
    /**@}*/

    /**
     * @brief If true, the code generator will output a class to represent the static configuration.
     */
    /**@{*/
    bool generate_static_configuration() const;
    void generate_static_configuration(const bool v);
    /**@}*/

    /**
     * @brief If true, the code generated for this feature bundle needs a manually generated
     * default constructor.
     */
    /**@{*/
    bool requires_manual_default_constructor() const;
    void requires_manual_default_constructor(const bool v);
    /**@}*/

public:
    bool operator==(const feature_bundle& rhs) const;
    bool operator!=(const feature_bundle& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::assets::meta_model::element& other) const override;

public:
    void swap(feature_bundle& other) noexcept;
    feature_bundle& operator=(feature_bundle other);

private:
    std::list<dogen::assets::meta_model::name> transparent_associations_;
    std::list<dogen::assets::meta_model::name> opaque_associations_;
    std::list<dogen::assets::meta_model::name> associative_container_keys_;
    std::list<dogen::assets::meta_model::variability::feature_template> feature_templates_;
    bool generate_static_configuration_;
    bool requires_manual_default_constructor_;
};

}

namespace std {

template<>
inline void swap(
    dogen::assets::meta_model::variability::feature_bundle& lhs,
    dogen::assets::meta_model::variability::feature_bundle& rhs) {
    lhs.swap(rhs);
}

}

#endif
