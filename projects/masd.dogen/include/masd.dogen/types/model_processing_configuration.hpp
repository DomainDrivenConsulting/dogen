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
#ifndef MASD_DOGEN_TYPES_MODEL_PROCESSING_CONFIGURATION_HPP
#define MASD_DOGEN_TYPES_MODEL_PROCESSING_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "masd.dogen/serialization/model_processing_configuration_fwd_ser.hpp"

namespace masd::dogen {

/**
 * @brief Configuration related to the behaviour of Dogen whilst processing models.
 */
class model_processing_configuration final {
public:
    model_processing_configuration(const model_processing_configuration&) = default;
    model_processing_configuration(model_processing_configuration&&) = default;
    ~model_processing_configuration() = default;

public:
    model_processing_configuration();

public:
    model_processing_configuration(
        const bool compatibility_mode_enabled,
        const bool dry_run_mode_enabled);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const masd::dogen::model_processing_configuration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, masd::dogen::model_processing_configuration& v, unsigned int version);

public:
    /**
     * @brief Try to process models even if there are errors.
     *
     * Only a certain class of errors are allowed, believed to be caused by backwards or
     * forwards compatibility problems: missing types or types that do not exist.
     */
    /**@{*/
    bool compatibility_mode_enabled() const;
    void compatibility_mode_enabled(const bool v);
    /**@}*/

    /**
     * @brief If true, all transforms wil be executed but no code will be emitted.
     */
    /**@{*/
    bool dry_run_mode_enabled() const;
    void dry_run_mode_enabled(const bool v);
    /**@}*/

public:
    bool operator==(const model_processing_configuration& rhs) const;
    bool operator!=(const model_processing_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model_processing_configuration& other) noexcept;
    model_processing_configuration& operator=(model_processing_configuration other);

private:
    bool compatibility_mode_enabled_;
    bool dry_run_mode_enabled_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::model_processing_configuration& lhs,
    masd::dogen::model_processing_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif
