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
#ifndef DOGEN_QUILT_CSHARP_TYPES_FABRIC_INJECTOR_HPP
#define DOGEN_QUILT_CSHARP_TYPES_FABRIC_INJECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <boost/shared_ptr.hpp>
#include "dogen/annotations/types/type_repository.hpp"
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/intermediate_model.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace fabric {

class injector {
public:
    virtual ~injector() noexcept;

private:
    void add_element(const boost::shared_ptr<yarn::meta_model::element>& e,
        yarn::meta_model::intermediate_model& im) const;

    void add_elements(
        const std::list<boost::shared_ptr<yarn::meta_model::element>>& elements,
        yarn::meta_model::intermediate_model& im) const;

private:
    void inject_visual_studio(const annotations::type_repository& atrp,
        yarn::meta_model::intermediate_model& im) const;
    void inject_assembly_info(yarn::meta_model::intermediate_model& im) const;
    void inject_assistant(yarn::meta_model::intermediate_model& im) const;

public:
    void inject(const annotations::type_repository& atrp,
        yarn::meta_model::intermediate_model& im) const;
};

} } } }

#endif
