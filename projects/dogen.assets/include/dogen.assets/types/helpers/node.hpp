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
#ifndef DOGEN_ASSETS_TYPES_HELPERS_NODE_HPP
#define DOGEN_ASSETS_TYPES_HELPERS_NODE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen.assets/types/meta_model/name.hpp"
#include "dogen.assets/types/helpers/node_fwd.hpp"

namespace dogen::assets::helpers {

/**
 * @brief Node in a tree of names.
 *
 * Temporary data structure used to build trees of names.
 */
class node final {
public:
    node() = default;
    node(const node&) = default;
    node(node&&) = default;
    ~node() = default;

public:
    node(
        const boost::shared_ptr<dogen::assets::helpers::node>& parent,
        const dogen::assets::meta_model::name& data,
        const std::list<boost::shared_ptr<dogen::assets::helpers::node> >& children);

public:
    /**
     * @brief Parent in a tree.
     */
    /**@{*/
    const boost::shared_ptr<dogen::assets::helpers::node>& parent() const;
    boost::shared_ptr<dogen::assets::helpers::node>& parent();
    void parent(const boost::shared_ptr<dogen::assets::helpers::node>& v);
    void parent(const boost::shared_ptr<dogen::assets::helpers::node>&& v);
    /**@}*/

    /**
     * @brief Current node.
     */
    /**@{*/
    const dogen::assets::meta_model::name& data() const;
    dogen::assets::meta_model::name& data();
    void data(const dogen::assets::meta_model::name& v);
    void data(const dogen::assets::meta_model::name&& v);
    /**@}*/

    /**
     * @brief Child nodes in a tree.
     */
    /**@{*/
    const std::list<boost::shared_ptr<dogen::assets::helpers::node> >& children() const;
    std::list<boost::shared_ptr<dogen::assets::helpers::node> >& children();
    void children(const std::list<boost::shared_ptr<dogen::assets::helpers::node> >& v);
    void children(const std::list<boost::shared_ptr<dogen::assets::helpers::node> >&& v);
    /**@}*/

public:
    bool operator==(const node& rhs) const;
    bool operator!=(const node& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(node& other) noexcept;
    node& operator=(node other);

private:
    boost::shared_ptr<dogen::assets::helpers::node> parent_;
    dogen::assets::meta_model::name data_;
    std::list<boost::shared_ptr<dogen::assets::helpers::node> > children_;
};

}

namespace std {

template<>
inline void swap(
    dogen::assets::helpers::node& lhs,
    dogen::assets::helpers::node& rhs) {
    lhs.swap(rhs);
}

}

#endif
