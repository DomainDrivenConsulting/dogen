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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_PHYSICAL_ELEMENT_REPOSITORY_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_PHYSICAL_ELEMENT_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.logical/types/entities/physical/part_fwd.hpp"
#include "dogen.logical/types/entities/physical/facet_fwd.hpp"
#include "dogen.logical/types/entities/physical/helper_fwd.hpp"
#include "dogen.logical/types/entities/physical/backend_fwd.hpp"
#include "dogen.identification/hash/entities/logical_id_hash.hpp"
#include "dogen.logical/types/entities/physical/archetype_fwd.hpp"
#include "dogen.logical/types/entities/physical/archetype_kind_fwd.hpp"

namespace dogen::logical::entities::physical {

class element_repository final {
public:
    element_repository() = default;
    element_repository(const element_repository&) = default;
    element_repository(element_repository&&) = default;
    ~element_repository() = default;

public:
    element_repository(
        const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::backend> >& backends,
        const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::facet> >& facets,
        const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::archetype> >& archetypes,
        const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::part> >& parts,
        const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::archetype_kind> >& archetype_kinds,
        const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::helper> >& helpers);

public:
    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::backend> >& backends() const;
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::backend> >& backends();
    void backends(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::backend> >& v);
    void backends(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::backend> >&& v);

    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::facet> >& facets() const;
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::facet> >& facets();
    void facets(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::facet> >& v);
    void facets(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::facet> >&& v);

    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::archetype> >& archetypes() const;
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::archetype> >& archetypes();
    void archetypes(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::archetype> >& v);
    void archetypes(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::archetype> >&& v);

    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::part> >& parts() const;
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::part> >& parts();
    void parts(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::part> >& v);
    void parts(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::part> >&& v);

    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::archetype_kind> >& archetype_kinds() const;
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::archetype_kind> >& archetype_kinds();
    void archetype_kinds(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::archetype_kind> >& v);
    void archetype_kinds(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::archetype_kind> >&& v);

    const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::helper> >& helpers() const;
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::helper> >& helpers();
    void helpers(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::helper> >& v);
    void helpers(const std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::helper> >&& v);

public:
    bool operator==(const element_repository& rhs) const;
    bool operator!=(const element_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(element_repository& other) noexcept;
    element_repository& operator=(element_repository other);

private:
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::backend> > backends_;
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::facet> > facets_;
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::archetype> > archetypes_;
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::part> > parts_;
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::archetype_kind> > archetype_kinds_;
    std::unordered_map<dogen::identification::entities::logical_id, boost::shared_ptr<dogen::logical::entities::physical::helper> > helpers_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::physical::element_repository& lhs,
    dogen::logical::entities::physical::element_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
