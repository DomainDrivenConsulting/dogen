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
#ifndef MASD_DOGEN_GENERATION_CPP_TYPES_FABRIC_OBJECT_ODB_OPTIONS_HPP
#define MASD_DOGEN_GENERATION_CPP_TYPES_FABRIC_OBJECT_ODB_OPTIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include "masd.dogen.coding/types/meta_model/element.hpp"

namespace masd::dogen::generation::cpp::fabric {

class object_odb_options final : public masd::dogen::coding::meta_model::element {
public:
    object_odb_options() = default;
    object_odb_options(const object_odb_options&) = default;
    object_odb_options(object_odb_options&&) = default;

    virtual ~object_odb_options() noexcept { }

public:
    object_odb_options(
        const masd::dogen::coding::meta_model::name& name,
        const std::string& documentation,
        const masd::dogen::annotations::annotation& annotation,
        const masd::dogen::coding::meta_model::origin_types origin_type,
        const boost::optional<masd::dogen::coding::meta_model::name>& contained_by,
        const bool in_global_module,
        const std::list<masd::dogen::coding::meta_model::static_stereotypes>& static_stereotypes,
        const std::list<std::string>& dynamic_stereotypes,
        const masd::dogen::coding::meta_model::name& meta_name,
        const masd::dogen::coding::meta_model::technical_space intrinsic_technical_space,
        const bool is_element_extension,
        const masd::dogen::extraction::decoration_properties& decoration_properties,
        const std::unordered_map<std::string, masd::dogen::coding::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, masd::dogen::coding::meta_model::local_archetype_location_properties>& archetype_location_properties,
        const boost::optional<masd::dogen::coding::meta_model::decoration>& decoration,
        const std::string& epilogue,
        const std::list<std::string>& include_regexes,
        const std::string& header_guard_prefix);

public:
    using masd::dogen::coding::meta_model::element::accept;

    virtual void accept(const masd::dogen::coding::meta_model::element_visitor& v) const override;
    virtual void accept(masd::dogen::coding::meta_model::element_visitor& v) const override;
    virtual void accept(const masd::dogen::coding::meta_model::element_visitor& v) override;
    virtual void accept(masd::dogen::coding::meta_model::element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    const std::string& epilogue() const;
    std::string& epilogue();
    void epilogue(const std::string& v);
    void epilogue(const std::string&& v);

    const std::list<std::string>& include_regexes() const;
    std::list<std::string>& include_regexes();
    void include_regexes(const std::list<std::string>& v);
    void include_regexes(const std::list<std::string>&& v);

    const std::string& header_guard_prefix() const;
    std::string& header_guard_prefix();
    void header_guard_prefix(const std::string& v);
    void header_guard_prefix(const std::string&& v);

public:
    bool operator==(const object_odb_options& rhs) const;
    bool operator!=(const object_odb_options& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const masd::dogen::coding::meta_model::element& other) const override;

public:
    void swap(object_odb_options& other) noexcept;
    object_odb_options& operator=(object_odb_options other);

private:
    std::string epilogue_;
    std::list<std::string> include_regexes_;
    std::string header_guard_prefix_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::generation::cpp::fabric::object_odb_options& lhs,
    masd::dogen::generation::cpp::fabric::object_odb_options& rhs) {
    lhs.swap(rhs);
}

}

#endif
