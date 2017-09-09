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
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/list.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include "dogen/annotations/serialization/archetype_location_ser.hpp"
#include "dogen/annotations/serialization/archetype_locations_group_ser.hpp"

namespace boost {
namespace serialization {

template<typename Archive>
void save(Archive& ar,
    const dogen::annotations::archetype_locations_group& v,
    const unsigned int /*version*/) {
    ar << make_nvp("archetype_locations", v.archetype_locations_);
    ar << make_nvp("canonical_archetype_locations", v.canonical_archetype_locations_);
}

template<typename Archive>
void load(Archive& ar,
    dogen::annotations::archetype_locations_group& v,
    const unsigned int /*version*/) {
    ar >> make_nvp("archetype_locations", v.archetype_locations_);
    ar >> make_nvp("canonical_archetype_locations", v.canonical_archetype_locations_);
}

} }

namespace boost {
namespace serialization {

template void save(archive::polymorphic_oarchive& ar, const dogen::annotations::archetype_locations_group& v, unsigned int version);
template void load(archive::polymorphic_iarchive& ar, dogen::annotations::archetype_locations_group& v, unsigned int version);

template void save(archive::text_oarchive& ar, const dogen::annotations::archetype_locations_group& v, unsigned int version);
template void load(archive::text_iarchive& ar, dogen::annotations::archetype_locations_group& v, unsigned int version);

template void save(archive::binary_oarchive& ar, const dogen::annotations::archetype_locations_group& v, unsigned int version);
template void load(archive::binary_iarchive& ar, dogen::annotations::archetype_locations_group& v, unsigned int version);

template void save(archive::xml_oarchive& ar, const dogen::annotations::archetype_locations_group& v, unsigned int version);
template void load(archive::xml_iarchive& ar, dogen::annotations::archetype_locations_group& v, unsigned int version);

} }
