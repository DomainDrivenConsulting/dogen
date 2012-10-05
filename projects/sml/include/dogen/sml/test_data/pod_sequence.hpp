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
#ifndef DOGEN_SML_TEST_DATA_POD_SEQUENCE_HPP
#define DOGEN_SML_TEST_DATA_POD_SEQUENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/utility/test_data/generator.hpp"
#include "dogen/utility/test_data/sequence.hpp"
#include "dogen/sml/domain/pod.hpp"
#include "dogen/sml/test_data/property_sequence.hpp"
#include "dogen/sml/test_data/qualified_name_sequence.hpp"

namespace dogen {
namespace sml {
namespace test_data {

namespace detail {

/**
 * @brief Generates an open ended sequence of versions.
 *
 * @see sequence.
 */
class pod_generator {
public:
    typedef dogen::sml::pod value_type;

public:
    value_type next_term(const unsigned int position) {
        dogen::sml::pod result;
        dogen::sml::test_data::property_sequence pseq;
        dogen::sml::test_data::qualified_name_sequence qseq;
        std::vector<dogen::sml::property> properties;

        if (position == 0) {
            properties.push_back(pseq());
        } else if (position == 1) {
            result.generate(true);
            pseq();
            properties.push_back(pseq());
        } else {
            pseq();
            pseq();
            properties.push_back(pseq());
        }

        result.generate(position % 2);
        result.properties(properties);
        return result;
    }

    unsigned int length() const { return(3); }
};

}

typedef utility::test_data::sequence<detail::pod_generator> pod_sequence;

} } }


#endif
