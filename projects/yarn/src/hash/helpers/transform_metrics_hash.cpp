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
#include "dogen/yarn/hash/helpers/transform_metrics_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_boost_posix_time_ptime(const boost::posix_time::ptime& v) {
    std::size_t seed(0);
    const boost::posix_time::ptime epoch(boost::gregorian::date(1970, 1, 1));
    boost::posix_time::time_duration d(v - epoch);
    seed = static_cast<std::size_t>(d.total_seconds());
    return seed;
}

inline std::size_t hash_boost_shared_ptr_dogen_yarn_helpers_transform_metrics(const boost::shared_ptr<dogen::yarn::helpers::transform_metrics>& v) {
    std::size_t seed(0);
    combine(seed, *v);
    return seed;
}

inline std::size_t hash_std_list_boost_shared_ptr_dogen_yarn_helpers_transform_metrics(const std::list<boost::shared_ptr<dogen::yarn::helpers::transform_metrics> >& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, hash_boost_shared_ptr_dogen_yarn_helpers_transform_metrics(i));
    }
    return seed;
}

}

namespace dogen {
namespace yarn {
namespace helpers {

std::size_t transform_metrics_hasher::hash(const transform_metrics& v) {
    std::size_t seed(0);

    combine(seed, v.id());
    combine(seed, v.guid());
    combine(seed, hash_boost_posix_time_ptime(v.start()));
    combine(seed, hash_boost_posix_time_ptime(v.finish()));
    combine(seed, hash_std_list_boost_shared_ptr_dogen_yarn_helpers_transform_metrics(v.children()));

    return seed;
}

} } }
