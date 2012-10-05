/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda
 *
 * This file is distributed under the Kitanda Proprietary Software
 * Licence. See doc/LICENCE.TXT for details.
 *
 */
#ifndef DOGEN_SPLIT_PROJECT_HASH_VERSIONED_KEY_HASH_HPP
#define DOGEN_SPLIT_PROJECT_HASH_VERSIONED_KEY_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <functional>
#include "dogen/split_project/domain/versioned_key.hpp"
#include "dogen/utility/hash/combine.hpp"

namespace std {

template<>
class hash<dogen::split_project::versioned_key> {
public:
    size_t operator()(dogen::split_project::versioned_key value) const {
        using dogen::utility::hash::combine;
        std::size_t seed(0);

        combine(seed, value.id());
        combine(seed, value.version());

        return seed;
    }
};

}
#endif
