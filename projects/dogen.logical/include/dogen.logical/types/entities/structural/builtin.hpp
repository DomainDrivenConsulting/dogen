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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_STRUCTURAL_BUILTIN_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_STRUCTURAL_BUILTIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen.logical/types/entities/element.hpp"

namespace dogen::logical::entities::structural {

/**
 * @brief Represents a value type that is built-in at the hardware level.
 */
class builtin final : public dogen::logical::entities::element {
public:
    builtin(const builtin&) = default;
    builtin(builtin&&) = default;

public:
    builtin();

    virtual ~builtin() noexcept { }

public:
    builtin(
        const dogen::identification::entities::logical_name& name,
        const std::string& documentation,
        const dogen::identification::entities::codec_provenance& provenance,
        const dogen::identification::entities::logical_id& contained_by,
        const bool in_global_module,
        const dogen::logical::entities::stereotypes& stereotypes,
        const dogen::identification::entities::logical_meta_name& meta_name,
        const dogen::identification::entities::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const std::list<dogen::identification::entities::label>& labels,
        const dogen::logical::entities::generability_status generability_status,
        const std::unordered_map<dogen::identification::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
        const std::list<dogen::logical::entities::helper_properties>& helper_properties,
        const bool is_default_enumeration_type,
        const bool is_floating_point,
        const bool can_be_enumeration_underlier,
        const bool can_be_primitive_underlier);

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
     * @brief If true, this built-in is the default type to be used on enumerations.
     */
    /**@{*/
    bool is_default_enumeration_type() const;
    void is_default_enumeration_type(const bool v);
    /**@}*/

    /**
     * @brief If true, this built-in represents a floating point number.
     */
    /**@{*/
    bool is_floating_point() const;
    void is_floating_point(const bool v);
    /**@}*/

    /**
     * @brief If true, this element can be the underlying element of an enumeration.
     */
    /**@{*/
    bool can_be_enumeration_underlier() const;
    void can_be_enumeration_underlier(const bool v);
    /**@}*/

    /**
     * @brief If true, this built-in can be the underlying element of a primitive.
     */
    /**@{*/
    bool can_be_primitive_underlier() const;
    void can_be_primitive_underlier(const bool v);
    /**@}*/

public:
    bool operator==(const builtin& rhs) const;
    bool operator!=(const builtin& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::logical::entities::element& other) const override;

public:
    void swap(builtin& other) noexcept;
    builtin& operator=(builtin other);

private:
    bool is_default_enumeration_type_;
    bool is_floating_point_;
    bool can_be_enumeration_underlier_;
    bool can_be_primitive_underlier_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::structural::builtin& lhs,
    dogen::logical::entities::structural::builtin& rhs) {
    lhs.swap(rhs);
}

}

#endif
