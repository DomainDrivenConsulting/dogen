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
#ifndef DOGEN_EXTRACTION_TYPES_FEATURES_FILESYSTEM_HPP
#define DOGEN_EXTRACTION_TYPES_FEATURES_FILESYSTEM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include "dogen.variability/types/meta_model/feature.hpp"
#include "dogen.variability/types/meta_model/configuration.hpp"
#include "dogen.variability/types/meta_model/feature_model.hpp"
#include "dogen.variability/types/meta_model/feature_template.hpp"

namespace dogen::extraction::features {

class filesystem final {
public:
    struct feature_group {
        variability::meta_model::feature force_write;
        variability::meta_model::feature delete_extra_files;
        variability::meta_model::feature ignore_files_matching_regex;
        variability::meta_model::feature delete_empty_directories;
        variability::meta_model::feature enable_backend_directories;
    };

    static feature_group
    make_feature_group(const variability::meta_model::feature_model& fm);

public:
    struct static_configuration {
        bool force_write;
        bool delete_extra_files;
        std::list<std::string> ignore_files_matching_regex;
        bool delete_empty_directories;
        bool enable_backend_directories;
    };

    static static_configuration make_static_configuration(
        const feature_group& fg,
        const variability::meta_model::configuration& cfg);


public:
    static std::list<dogen::variability::meta_model::feature_template>
    make_templates();
};

}

#endif
