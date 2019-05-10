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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_VARIABILITY_ELEMENT_REPOSITORY_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_VARIABILITY_ELEMENT_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include "masd.dogen.coding/types/meta_model/variability/feature_bundle_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/variability/profile_template_fwd.hpp"
#include "masd.dogen.coding/types/meta_model/variability/feature_template_initializer_fwd.hpp"

namespace masd::dogen::coding::meta_model::variability {

class element_repository final {
public:
    element_repository() = default;
    element_repository(const element_repository&) = default;
    element_repository(element_repository&&) = default;
    ~element_repository() = default;

public:
    element_repository(
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> >& profile_templates,
        const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_bundle> >& feature_bundles,
        const boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_initializer>& feature_template_initializer);

public:
    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> >& profile_templates() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> >& profile_templates();
    void profile_templates(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> >& v);
    void profile_templates(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> >&& v);

    const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_bundle> >& feature_bundles() const;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_bundle> >& feature_bundles();
    void feature_bundles(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_bundle> >& v);
    void feature_bundles(const std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_bundle> >&& v);

    const boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_initializer>& feature_template_initializer() const;
    boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_initializer>& feature_template_initializer();
    void feature_template_initializer(const boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_initializer>& v);
    void feature_template_initializer(const boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_initializer>&& v);

public:
    bool operator==(const element_repository& rhs) const;
    bool operator!=(const element_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(element_repository& other) noexcept;
    element_repository& operator=(element_repository other);

private:
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::profile_template> > profile_templates_;
    std::unordered_map<std::string, boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_bundle> > feature_bundles_;
    boost::shared_ptr<masd::dogen::coding::meta_model::variability::feature_template_initializer> feature_template_initializer_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::coding::meta_model::variability::element_repository& lhs,
    masd::dogen::coding::meta_model::variability::element_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
