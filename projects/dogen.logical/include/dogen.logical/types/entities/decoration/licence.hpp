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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_DECORATION_LICENCE_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_DECORATION_LICENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen.logical/types/entities/element.hpp"

namespace dogen::logical::entities::decoration {

/**
 * @brief Represents legal licence for software projects.
 */
class licence final : public dogen::logical::entities::element {
public:
    licence() = default;
    licence(const licence&) = default;
    licence(licence&&) = default;

    virtual ~licence() noexcept { }

public:
    licence(
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
        const std::string& short_form,
        const std::string& long_form);

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
     * @brief Short version of the licence, for inclusion in project files.
     */
    /**@{*/
    const std::string& short_form() const;
    std::string& short_form();
    void short_form(const std::string& v);
    void short_form(const std::string&& v);
    /**@}*/

    /**
     * @brief Long form of the licence text, suitable for generation of LICENCE files.
     */
    /**@{*/
    const std::string& long_form() const;
    std::string& long_form();
    void long_form(const std::string& v);
    void long_form(const std::string&& v);
    /**@}*/

public:
    bool operator==(const licence& rhs) const;
    bool operator!=(const licence& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::logical::entities::element& other) const override;

public:
    void swap(licence& other) noexcept;
    licence& operator=(licence other);

private:
    std::string short_form_;
    std::string long_form_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::decoration::licence& lhs,
    dogen::logical::entities::decoration::licence& rhs) {
    lhs.swap(rhs);
}

}

#endif
