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
#ifndef DOGEN_TEXT_CPP_TYPES_FORMATTABLES_MODEL_HPP
#define DOGEN_TEXT_CPP_TYPES_FORMATTABLES_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.text.cpp/types/formattables/formattable.hpp"
#include "dogen.identification/types/entities/logical_id.hpp"
#include "dogen.text.cpp/types/formattables/cpp_standards.hpp"
#include "dogen.identification/types/entities/logical_name.hpp"
#include "dogen.identification/hash/entities/logical_id_hash.hpp"
#include "dogen.text.cpp/types/formattables/streaming_properties.hpp"

namespace dogen::text::cpp::formattables {

class model final {
public:
    model(const model&) = default;
    model(model&&) = default;
    ~model() = default;

public:
    model();

public:
    model(
        const dogen::identification::entities::logical_name& name,
        const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::streaming_properties>& streaming_properties,
        const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::formattable>& formattables,
        const dogen::text::cpp::formattables::cpp_standards cpp_standard,
        const std::string& odb_sql_name_case);

public:
    const dogen::identification::entities::logical_name& name() const;
    dogen::identification::entities::logical_name& name();
    void name(const dogen::identification::entities::logical_name& v);
    void name(const dogen::identification::entities::logical_name&& v);

    const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::streaming_properties>& streaming_properties() const;
    std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::streaming_properties>& streaming_properties();
    void streaming_properties(const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::streaming_properties>& v);
    void streaming_properties(const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::streaming_properties>&& v);

    const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::formattable>& formattables() const;
    std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::formattable>& formattables();
    void formattables(const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::formattable>& v);
    void formattables(const std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::formattable>&& v);

    dogen::text::cpp::formattables::cpp_standards cpp_standard() const;
    void cpp_standard(const dogen::text::cpp::formattables::cpp_standards v);

    const std::string& odb_sql_name_case() const;
    std::string& odb_sql_name_case();
    void odb_sql_name_case(const std::string& v);
    void odb_sql_name_case(const std::string&& v);

public:
    bool operator==(const model& rhs) const;
    bool operator!=(const model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(model& other) noexcept;
    model& operator=(model other);

private:
    dogen::identification::entities::logical_name name_;
    std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::streaming_properties> streaming_properties_;
    std::unordered_map<dogen::identification::entities::logical_id, dogen::text::cpp::formattables::formattable> formattables_;
    dogen::text::cpp::formattables::cpp_standards cpp_standard_;
    std::string odb_sql_name_case_;
};

}

namespace std {

template<>
inline void swap(
    dogen::text::cpp::formattables::model& lhs,
    dogen::text::cpp::formattables::model& rhs) {
    lhs.swap(rhs);
}

}

#endif
