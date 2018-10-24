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
#ifndef DOGEN_GENERATION_CSHARP_TYPES_FABRIC_ELEMENT_VISITOR_HPP
#define DOGEN_GENERATION_CSHARP_TYPES_FABRIC_ELEMENT_VISITOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen.modeling/types/meta_model/element_visitor.hpp"
#include "dogen.generation.csharp/types/fabric/assistant_fwd.hpp"
#include "dogen.generation.csharp/types/fabric/assembly_info_fwd.hpp"
#include "dogen.generation.csharp/types/fabric/visual_studio_project_fwd.hpp"
#include "dogen.generation.csharp/types/fabric/visual_studio_solution_fwd.hpp"

namespace dogen::generation::csharp::fabric {

/**
 * @brief Visitor for element
 */
class element_visitor : public dogen::modeling::meta_model::element_visitor {
public:
    virtual ~element_visitor() noexcept = 0;

public:
    using dogen::modeling::meta_model::element_visitor::visit;

    /**
     * @brief Accept visits for type dogen::generation::csharp::fabric::assembly_info
     */
    /**@{*/
    virtual void visit(const dogen::generation::csharp::fabric::assembly_info&) const { }
    virtual void visit(const dogen::generation::csharp::fabric::assembly_info&) { }
    virtual void visit(dogen::generation::csharp::fabric::assembly_info&) const { }
    virtual void visit(dogen::generation::csharp::fabric::assembly_info&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::generation::csharp::fabric::assistant
     */
    /**@{*/
    virtual void visit(const dogen::generation::csharp::fabric::assistant&) const { }
    virtual void visit(const dogen::generation::csharp::fabric::assistant&) { }
    virtual void visit(dogen::generation::csharp::fabric::assistant&) const { }
    virtual void visit(dogen::generation::csharp::fabric::assistant&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::generation::csharp::fabric::visual_studio_project
     */
    /**@{*/
    virtual void visit(const dogen::generation::csharp::fabric::visual_studio_project&) const { }
    virtual void visit(const dogen::generation::csharp::fabric::visual_studio_project&) { }
    virtual void visit(dogen::generation::csharp::fabric::visual_studio_project&) const { }
    virtual void visit(dogen::generation::csharp::fabric::visual_studio_project&) { }
    /**@}*/

    /**
     * @brief Accept visits for type dogen::generation::csharp::fabric::visual_studio_solution
     */
    /**@{*/
    virtual void visit(const dogen::generation::csharp::fabric::visual_studio_solution&) const { }
    virtual void visit(const dogen::generation::csharp::fabric::visual_studio_solution&) { }
    virtual void visit(dogen::generation::csharp::fabric::visual_studio_solution&) const { }
    virtual void visit(dogen::generation::csharp::fabric::visual_studio_solution&) { }
    /**@}*/
};

inline element_visitor::~element_visitor() noexcept { }

}

#endif
