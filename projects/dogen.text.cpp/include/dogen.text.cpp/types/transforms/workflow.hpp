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
#ifndef DOGEN_TEXT_CPP_TYPES_TRANSFORMS_WORKFLOW_HPP
#define DOGEN_TEXT_CPP_TYPES_TRANSFORMS_WORKFLOW_HPP

#include "dogen.text/types/entities/logical_physical_region.hpp"
#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include "dogen.tracing/types/tracer.hpp"
#include "dogen.physical/types/entities/model.hpp"
#include "dogen.physical/types/entities/region.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.identification/types/entities/logical_meta_physical_id.hpp"
#include "dogen.text/types/entities/model.hpp"
#include "dogen.text.cpp/types/transforms/registrar.hpp"

namespace dogen::text::cpp::transforms {

/**
 * @brief Generates all files for the supplied entity.
 */
class workflow final {
public:
    workflow(const physical::entities::model& pm,
        const identification::entities::technical_space_version tsv);

public:
    /**
     * @brief Returns the registrar. If it has not yet been
     * initialised, initialises it.
     */
    static cpp::transforms::registrar& registrar();

private:
    boost::shared_ptr<physical::entities::artefact>
    get_artefact(const physical::entities::region& region,
        const identification::entities::physical_meta_id& archetype) const;

private:
    void execute(boost::shared_ptr<tracing::tracer> tracer,
        const text::entities::model& m,
        text::entities::logical_physical_region& region) const;

public:
    void execute(boost::shared_ptr<tracing::tracer> tracer,
        text::entities::model& m) const;

private:
    static std::shared_ptr<cpp::transforms::registrar> registrar_;
    const physical::entities::model& physical_model_;
    const identification::entities::technical_space_version
    technical_space_version_;
};

}

#endif
