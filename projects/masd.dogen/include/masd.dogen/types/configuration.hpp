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
#ifndef MASD_DOGEN_TYPES_CONFIGURATION_HPP
#define MASD_DOGEN_TYPES_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/variant.hpp>
#include "masd.dogen/types/diffing_configuration.hpp"
#include "masd.dogen/types/logging_configuration.hpp"
#include "masd.dogen/types/tracing_configuration.hpp"
#include "masd.dogen/types/weaving_configuration.hpp"
#include "masd.dogen/types/conversion_configuration.hpp"
#include "masd.dogen/types/generation_configuration.hpp"

namespace masd::dogen {

class configuration final {
public:
    configuration() = default;
    configuration(const configuration&) = default;
    ~configuration() = default;

public:
    configuration(configuration&& rhs);

public:
    configuration(
        const boost::variant<masd::dogen::generation_configuration, masd::dogen::weaving_configuration, masd::dogen::conversion_configuration>& activity,
        const masd::dogen::tracing_configuration& tracing,
        const masd::dogen::logging_configuration& logging,
        const masd::dogen::diffing_configuration& diffing);

public:
    const boost::variant<masd::dogen::generation_configuration, masd::dogen::weaving_configuration, masd::dogen::conversion_configuration>& activity() const;
    boost::variant<masd::dogen::generation_configuration, masd::dogen::weaving_configuration, masd::dogen::conversion_configuration>& activity();
    configuration& activity(const boost::variant<masd::dogen::generation_configuration, masd::dogen::weaving_configuration, masd::dogen::conversion_configuration>& v);
    configuration& activity(const boost::variant<masd::dogen::generation_configuration, masd::dogen::weaving_configuration, masd::dogen::conversion_configuration>&& v);

    /**
     * @brief Configuration for tracing.
     */
    /**@{*/
    const masd::dogen::tracing_configuration& tracing() const;
    masd::dogen::tracing_configuration& tracing();
    configuration& tracing(const masd::dogen::tracing_configuration& v);
    configuration& tracing(const masd::dogen::tracing_configuration&& v);
    /**@}*/

    /**
     * @brief Configuration for logging.
     */
    /**@{*/
    const masd::dogen::logging_configuration& logging() const;
    masd::dogen::logging_configuration& logging();
    configuration& logging(const masd::dogen::logging_configuration& v);
    configuration& logging(const masd::dogen::logging_configuration&& v);
    /**@}*/

    const masd::dogen::diffing_configuration& diffing() const;
    masd::dogen::diffing_configuration& diffing();
    configuration& diffing(const masd::dogen::diffing_configuration& v);
    configuration& diffing(const masd::dogen::diffing_configuration&& v);

public:
    bool operator==(const configuration& rhs) const;
    bool operator!=(const configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(configuration& other) noexcept;
    configuration& operator=(configuration other);

private:
    boost::variant<masd::dogen::generation_configuration, masd::dogen::weaving_configuration, masd::dogen::conversion_configuration> activity_;
    masd::dogen::tracing_configuration tracing_;
    masd::dogen::logging_configuration logging_;
    masd::dogen::diffing_configuration diffing_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::configuration& lhs,
    masd::dogen::configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
