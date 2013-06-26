/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_STEREOTYPES_TYPES_BASE_WITH_CONCEPT_HPP
#define DOGEN_STEREOTYPES_TYPES_BASE_WITH_CONCEPT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/stereotypes/serialization/base_with_concept_fwd_ser.hpp"

namespace dogen {
namespace stereotypes {

/**
 * @brief Base class that models a refined concept.
 */
class base_with_concept {
public:
    base_with_concept(const base_with_concept&) = default;
    base_with_concept(base_with_concept&&) = default;

public:
    base_with_concept();

    virtual ~base_with_concept() noexcept = 0;

public:
    base_with_concept(
        const int prop_0,
        const int prop_2);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const base_with_concept& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, base_with_concept& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    /**
     * @brief Base concept property
     */
    /**@{*/
    int prop_0() const;
    void prop_0(const int v);
    /**@}*/

    /**
     * @brief Second refinement property
     */
    /**@{*/
    int prop_2() const;
    void prop_2(const int v);
    /**@}*/

protected:
    bool compare(const base_with_concept& rhs) const;
public:
    virtual bool equals(const base_with_concept& other) const = 0;

protected:
    void swap(base_with_concept& other) noexcept;

private:
    int prop_0_;
    int prop_2_;
};

inline base_with_concept::~base_with_concept() noexcept { }

inline bool operator==(const base_with_concept& lhs, const base_with_concept& rhs) {
    return lhs.equals(rhs);
}

} }



#endif
