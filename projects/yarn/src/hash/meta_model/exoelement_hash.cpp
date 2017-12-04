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
#include "dogen/yarn/hash/meta_model/exoelement_hash.hpp"
#include "dogen/yarn/hash/meta_model/exoattribute_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_pair_std_string_std_string(const std::pair<std::string, std::string>& v) {
    std::size_t seed(0);

    combine(seed, v.first);
    combine(seed, v.second);
    return seed;
}

inline std::size_t hash_std_list_std_pair_std_string_std_string(const std::list<std::pair<std::string, std::string> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_std_pair_std_string_std_string(i));
    }
    return seed;
}

inline std::size_t hash_std_list_std_string(const std::list<std::string>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

inline std::size_t hash_std_list_dogen_yarn_meta_model_exoattribute(const std::list<dogen::yarn::meta_model::exoattribute>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

}

namespace dogen {
namespace yarn {
namespace meta_model {

std::size_t exoelement_hasher::hash(const exoelement& v) {
    std::size_t seed(0);

    combine(seed, v.documentation());
    combine(seed, hash_std_list_std_pair_std_string_std_string(v.tagged_values()));
    combine(seed, v.name());
    combine(seed, hash_std_list_std_string(v.parents()));
    combine(seed, hash_std_list_dogen_yarn_meta_model_exoattribute(v.attributes()));
    combine(seed, v.can_be_primitive_underlier());
    combine(seed, v.in_global_module());
    combine(seed, v.can_be_enumeration_underlier());
    combine(seed, v.is_default_enumeration_type());
    combine(seed, v.is_associative_container());
    combine(seed, v.is_floating_point());
    combine(seed, hash_std_list_std_string(v.stereotypes()));
    combine(seed, v.fallback_element_type());

    return seed;
}

} } }
