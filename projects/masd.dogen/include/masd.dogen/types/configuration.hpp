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
#include <boost/optional.hpp>
#include <boost/filesystem/path.hpp>
#include "masd.dogen/types/diffing_configuration.hpp"
#include "masd.dogen/types/tracing_configuration.hpp"
#include "masd.dogen/types/model_processing_configuration.hpp"
#include "masd.dogen/types/operational_reporting_configuration.hpp"

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
        const boost::optional<masd::dogen::model_processing_configuration>& model_processing,
        const boost::optional<masd::dogen::tracing_configuration>& tracing,
        const boost::optional<masd::dogen::diffing_configuration>& diffing,
        const boost::optional<masd::dogen::operational_reporting_configuration>& operational_reporting,
        const boost::filesystem::path& byproduct_directory);

public:
    const boost::optional<masd::dogen::model_processing_configuration>& model_processing() const;
    boost::optional<masd::dogen::model_processing_configuration>& model_processing();
    configuration& model_processing(const boost::optional<masd::dogen::model_processing_configuration>& v);
    configuration& model_processing(const boost::optional<masd::dogen::model_processing_configuration>&& v);

    /**
     * @brief Configuration for tracing.
     */
    /**@{*/
    const boost::optional<masd::dogen::tracing_configuration>& tracing() const;
    boost::optional<masd::dogen::tracing_configuration>& tracing();
    configuration& tracing(const boost::optional<masd::dogen::tracing_configuration>& v);
    configuration& tracing(const boost::optional<masd::dogen::tracing_configuration>&& v);
    /**@}*/

    const boost::optional<masd::dogen::diffing_configuration>& diffing() const;
    boost::optional<masd::dogen::diffing_configuration>& diffing();
    configuration& diffing(const boost::optional<masd::dogen::diffing_configuration>& v);
    configuration& diffing(const boost::optional<masd::dogen::diffing_configuration>&& v);

    const boost::optional<masd::dogen::operational_reporting_configuration>& operational_reporting() const;
    boost::optional<masd::dogen::operational_reporting_configuration>& operational_reporting();
    configuration& operational_reporting(const boost::optional<masd::dogen::operational_reporting_configuration>& v);
    configuration& operational_reporting(const boost::optional<masd::dogen::operational_reporting_configuration>&& v);

    /**
     * @brief Directory in which to place all files not directly related to generated code.
     */
    /**@{*/
    const boost::filesystem::path& byproduct_directory() const;
    boost::filesystem::path& byproduct_directory();
    configuration& byproduct_directory(const boost::filesystem::path& v);
    configuration& byproduct_directory(const boost::filesystem::path&& v);
    /**@}*/

public:
    bool operator==(const configuration& rhs) const;
    bool operator!=(const configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(configuration& other) noexcept;
    configuration& operator=(configuration other);

private:
    boost::optional<masd::dogen::model_processing_configuration> model_processing_;
    boost::optional<masd::dogen::tracing_configuration> tracing_;
    boost::optional<masd::dogen::diffing_configuration> diffing_;
    boost::optional<masd::dogen::operational_reporting_configuration> operational_reporting_;
    boost::filesystem::path byproduct_directory_;
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
