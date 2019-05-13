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
#ifndef DOGEN_CODING_TYPES_META_MODEL_VARIABILITY_FEATURE_TEMPLATE_INITIALIZER_HPP
#define DOGEN_CODING_TYPES_META_MODEL_VARIABILITY_FEATURE_TEMPLATE_INITIALIZER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include "dogen.coding/types/meta_model/name.hpp"
#include "dogen.coding/types/meta_model/element.hpp"

namespace dogen::coding::meta_model::variability {

class feature_template_initializer final : public dogen::coding::meta_model::element {
public:
    feature_template_initializer() = default;
    feature_template_initializer(const feature_template_initializer&) = default;
    feature_template_initializer(feature_template_initializer&&) = default;

    virtual ~feature_template_initializer() noexcept { }

public:
    feature_template_initializer(
        const dogen::coding::meta_model::name& name,
        const std::string& documentation,
        const dogen::coding::meta_model::origin_types origin_type,
        const std::string& contained_by,
        const bool in_global_module,
        const std::list<dogen::coding::meta_model::static_stereotypes>& static_stereotypes,
        const std::list<std::string>& dynamic_stereotypes,
        const dogen::coding::meta_model::name& meta_name,
        const dogen::coding::meta_model::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
        const bool is_element_extension,
        const std::unordered_map<std::string, dogen::coding::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::coding::meta_model::local_archetype_location_properties>& archetype_location_properties,
        const boost::optional<dogen::coding::meta_model::decoration::element_properties>& decoration,
        const std::list<dogen::coding::meta_model::name>& bundles);

public:
    using element::accept;

    virtual void accept(const element_visitor& v) const override;
    virtual void accept(element_visitor& v) const override;
    virtual void accept(const element_visitor& v) override;
    virtual void accept(element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    const std::list<dogen::coding::meta_model::name>& bundles() const;
    std::list<dogen::coding::meta_model::name>& bundles();
    void bundles(const std::list<dogen::coding::meta_model::name>& v);
    void bundles(const std::list<dogen::coding::meta_model::name>&& v);

public:
    bool operator==(const feature_template_initializer& rhs) const;
    bool operator!=(const feature_template_initializer& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::coding::meta_model::element& other) const override;

public:
    void swap(feature_template_initializer& other) noexcept;
    feature_template_initializer& operator=(feature_template_initializer other);

private:
    std::list<dogen::coding::meta_model::name> bundles_;
};

}

namespace std {

template<>
inline void swap(
    dogen::coding::meta_model::variability::feature_template_initializer& lhs,
    dogen::coding::meta_model::variability::feature_template_initializer& rhs) {
    lhs.swap(rhs);
}

}

#endif
