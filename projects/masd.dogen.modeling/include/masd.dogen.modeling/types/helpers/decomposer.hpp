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
#ifndef DOGEN_MODELING_TYPES_HELPERS_DECOMPOSER_HPP
#define DOGEN_MODELING_TYPES_HELPERS_DECOMPOSER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include "masd.dogen.modeling/types/meta_model/element.hpp"
#include "masd.dogen.modeling/types/meta_model/module.hpp"
#include "masd.dogen.modeling/types/meta_model/object.hpp"
#include "masd.dogen.modeling/types/meta_model/element.hpp"
#include "masd.dogen.modeling/types/meta_model/exception.hpp"
#include "masd.dogen.modeling/types/meta_model/builtin.hpp"
#include "masd.dogen.modeling/types/meta_model/visitor.hpp"
#include "masd.dogen.modeling/types/meta_model/primitive.hpp"
#include "masd.dogen.modeling/types/meta_model/enumeration.hpp"
#include "masd.dogen.modeling/types/meta_model/object_template.hpp"
#include "masd.dogen.modeling/types/meta_model/attribute.hpp"
#include "masd.dogen.modeling/types/meta_model/endomodel.hpp"
#include "masd.dogen.modeling/types/helpers/decomposition_result.hpp"

namespace masd::dogen::modeling::helpers {

/**
 * @brief Collect the names of all elements and attributes, for
 * subsequent validation.
 *
 * Note that we do not add the model name itself; this is because we
 * will validate the model's module, which is generated from the model
 * name.
 */
class decomposer final {
private:
    void add_name(const std::string& owner, const meta_model::name& n);
    void add_meta_name(const std::string& owner, const meta_model::name& n);
    void add_injected_name(const std::string& owner, const meta_model::name& n);
    void add_name_tree(const std::string& owner,
        const meta_model::name_tree& nt);
    void add_names(const std::string& owner,
        const std::list<meta_model::name>& names);
    void decompose_attributes(const std::string& owner,
        const std::list<meta_model::attribute>& attrs);
    void decompose_element(const meta_model::element& e);

public:
    /*
     * These methods are morally private, but are required to be
     * public due to the traversal.
     */
    void operator()(const meta_model::element& e);
    void operator()(const meta_model::module& m);
    void operator()(const meta_model::object_template& ot);
    void operator()(const meta_model::builtin& b);
    void operator()(const meta_model::enumeration& e);
    void operator()(const meta_model::primitive& p);
    void operator()(const meta_model::object& o);
    void operator()(const meta_model::exception& e);
    void operator()(const meta_model::visitor& v);

private:
    const decomposition_result& result() const;

public:
    static decomposition_result
    decompose(const meta_model::endomodel& em);

private:
    decomposition_result result_;
};

}

#endif
