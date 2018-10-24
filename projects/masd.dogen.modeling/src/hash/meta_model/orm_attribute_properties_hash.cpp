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
#include "masd.dogen.modeling/hash/meta_model/orm_database_systems_hash.hpp"
#include "masd.dogen.modeling/hash/meta_model/orm_attribute_properties_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_boost_optional_bool(const boost::optional<bool>& v) {
    std::size_t seed(0);

    if (!v)
        return seed;

    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_unordered_map_masd_dogen_modeling_meta_model_orm_database_systems_std_string(const std::unordered_map<masd::dogen::modeling::meta_model::orm_database_systems, std::string>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i.first);
        combine(seed, i.second);
    }
    return seed;
}

}

namespace masd::dogen::modeling::meta_model {

std::size_t orm_attribute_properties_hasher::hash(const orm_attribute_properties& v) {
    std::size_t seed(0);

    combine(seed, v.column_name());
    combine(seed, v.is_primary_key());
    combine(seed, hash_boost_optional_bool(v.is_nullable()));
    combine(seed, hash_std_unordered_map_masd_dogen_modeling_meta_model_orm_database_systems_std_string(v.type_overrides()));
    combine(seed, v.is_composite());

    return seed;
}

}
