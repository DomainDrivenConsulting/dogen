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
#ifndef DOGEN_GENERATION_CPP_TYPES_FABRIC_ENTRY_POINT_HPP
#define DOGEN_GENERATION_CPP_TYPES_FABRIC_ENTRY_POINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen.coding/types/meta_model/element.hpp"

namespace dogen::generation::cpp::fabric {

class entry_point final : public dogen::coding::meta_model::element {
public:
    entry_point() = default;
    entry_point(const entry_point&) = default;
    entry_point(entry_point&&) = default;

    virtual ~entry_point() noexcept { }

public:
    entry_point(
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
        const boost::optional<dogen::coding::meta_model::decoration::element_properties>& decoration);

public:
    using dogen::coding::meta_model::element::accept;

    virtual void accept(const dogen::coding::meta_model::element_visitor& v) const override;
    virtual void accept(dogen::coding::meta_model::element_visitor& v) const override;
    virtual void accept(const dogen::coding::meta_model::element_visitor& v) override;
    virtual void accept(dogen::coding::meta_model::element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    bool operator==(const entry_point& rhs) const;
    bool operator!=(const entry_point& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::coding::meta_model::element& other) const override;

public:
    void swap(entry_point& other) noexcept;
    entry_point& operator=(entry_point other);

};

}

namespace std {

template<>
inline void swap(
    dogen::generation::cpp::fabric::entry_point& lhs,
    dogen::generation::cpp::fabric::entry_point& rhs) {
    lhs.swap(rhs);
}

}

#endif
