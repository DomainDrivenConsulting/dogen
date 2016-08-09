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
#ifndef DOGEN_YARN_TYPES_INTERMEDIATE_MODEL_HPP
#define DOGEN_YARN_TYPES_INTERMEDIATE_MODEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/module.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/concept.hpp"
#include "dogen/yarn/types/visitor.hpp"
#include "dogen/yarn/hash/name_hash.hpp"
#include "dogen/yarn/types/exception.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include "dogen/yarn/types/origin_types.hpp"
#include "dogen/yarn/types/generation_types.hpp"
#include "dogen/yarn/serialization/intermediate_model_fwd_ser.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Intermediate representation of a yarn model.
 */
class intermediate_model final {
public:
    intermediate_model(const intermediate_model&) = default;
    intermediate_model(intermediate_model&&) = default;
    ~intermediate_model() = default;

public:
    intermediate_model();

public:
    intermediate_model(
        const dogen::yarn::name& name,
        const dogen::yarn::origin_types origin_type,
        const std::string& original_model_name,
        const dogen::yarn::generation_types generation_type,
        const std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>& references,
        const std::unordered_set<dogen::yarn::name>& leaves,
        const std::unordered_map<std::string, dogen::yarn::module>& modules,
        const std::unordered_map<std::string, dogen::yarn::concept>& concepts,
        const std::unordered_map<std::string, dogen::yarn::primitive>& primitives,
        const std::unordered_map<std::string, dogen::yarn::enumeration>& enumerations,
        const std::unordered_map<std::string, dogen::yarn::object>& objects,
        const std::unordered_map<std::string, dogen::yarn::exception>& exceptions,
        const std::unordered_map<std::string, dogen::yarn::visitor>& visitors,
        const bool is_target,
        const bool has_generatable_types);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::intermediate_model& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::intermediate_model& v, unsigned int version);

public:
    /**
     * @brief Fully qualified name.
     */
    /**@{*/
    const dogen::yarn::name& name() const;
    dogen::yarn::name& name();
    void name(const dogen::yarn::name& v);
    void name(const dogen::yarn::name&& v);
    /**@}*/

    /**
     * @brief How was this model element originated.
     */
    /**@{*/
    dogen::yarn::origin_types origin_type() const;
    void origin_type(const dogen::yarn::origin_types v);
    /**@}*/

    /**
     * @brief Name of the model where the element came from.
     */
    /**@{*/
    const std::string& original_model_name() const;
    std::string& original_model_name();
    void original_model_name(const std::string& v);
    void original_model_name(const std::string&& v);
    /**@}*/

    /**
     * @brief What to do with this type in terms of code generation.
     */
    /**@{*/
    dogen::yarn::generation_types generation_type() const;
    void generation_type(const dogen::yarn::generation_types v);
    /**@}*/

    /**
     * @brief All other intermediate models that this intermediate model depends on, mapped to their origin.
     */
    /**@{*/
    const std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>& references() const;
    std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>& references();
    void references(const std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>& v);
    void references(const std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types>&& v);
    /**@}*/

    /**
     * @brief All leaf types in this intermediate model.
     *
     * Leaves are types concrete types which have a parent.
     */
    /**@{*/
    const std::unordered_set<dogen::yarn::name>& leaves() const;
    std::unordered_set<dogen::yarn::name>& leaves();
    void leaves(const std::unordered_set<dogen::yarn::name>& v);
    void leaves(const std::unordered_set<dogen::yarn::name>&& v);
    /**@}*/

    /**
     * @brief Modules contained in the intermediate model.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::yarn::module>& modules() const;
    std::unordered_map<std::string, dogen::yarn::module>& modules();
    void modules(const std::unordered_map<std::string, dogen::yarn::module>& v);
    void modules(const std::unordered_map<std::string, dogen::yarn::module>&& v);
    /**@}*/

    /**
     * @brief All the concepts available in this intermediate model.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::yarn::concept>& concepts() const;
    std::unordered_map<std::string, dogen::yarn::concept>& concepts();
    void concepts(const std::unordered_map<std::string, dogen::yarn::concept>& v);
    void concepts(const std::unordered_map<std::string, dogen::yarn::concept>&& v);
    /**@}*/

    /**
     * @brief All primitives contained in this intermediate model.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::yarn::primitive>& primitives() const;
    std::unordered_map<std::string, dogen::yarn::primitive>& primitives();
    void primitives(const std::unordered_map<std::string, dogen::yarn::primitive>& v);
    void primitives(const std::unordered_map<std::string, dogen::yarn::primitive>&& v);
    /**@}*/

    /**
     * @brief All enumerations contained in this intermediate model.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::yarn::enumeration>& enumerations() const;
    std::unordered_map<std::string, dogen::yarn::enumeration>& enumerations();
    void enumerations(const std::unordered_map<std::string, dogen::yarn::enumeration>& v);
    void enumerations(const std::unordered_map<std::string, dogen::yarn::enumeration>&& v);
    /**@}*/

    /**
     * @brief All objects contained in this intermediate model.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::yarn::object>& objects() const;
    std::unordered_map<std::string, dogen::yarn::object>& objects();
    void objects(const std::unordered_map<std::string, dogen::yarn::object>& v);
    void objects(const std::unordered_map<std::string, dogen::yarn::object>&& v);
    /**@}*/

    /**
     * @brief All exceptions in this model.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::yarn::exception>& exceptions() const;
    std::unordered_map<std::string, dogen::yarn::exception>& exceptions();
    void exceptions(const std::unordered_map<std::string, dogen::yarn::exception>& v);
    void exceptions(const std::unordered_map<std::string, dogen::yarn::exception>&& v);
    /**@}*/

    /**
     * @brief All visitors in this model.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::yarn::visitor>& visitors() const;
    std::unordered_map<std::string, dogen::yarn::visitor>& visitors();
    void visitors(const std::unordered_map<std::string, dogen::yarn::visitor>& v);
    void visitors(const std::unordered_map<std::string, dogen::yarn::visitor>&& v);
    /**@}*/

    /**
     * @brief If true, this intermediate model is the target model.
     */
    /**@{*/
    bool is_target() const;
    void is_target(const bool v);
    /**@}*/

    /**
     * @brief If true the intermediate model has at least one generable type, false otherwise.
     */
    /**@{*/
    bool has_generatable_types() const;
    void has_generatable_types(const bool v);
    /**@}*/

public:
    bool operator==(const intermediate_model& rhs) const;
    bool operator!=(const intermediate_model& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(intermediate_model& other) noexcept;
    intermediate_model& operator=(intermediate_model other);

private:
    dogen::yarn::name name_;
    dogen::yarn::origin_types origin_type_;
    std::string original_model_name_;
    dogen::yarn::generation_types generation_type_;
    std::unordered_map<dogen::yarn::name, dogen::yarn::origin_types> references_;
    std::unordered_set<dogen::yarn::name> leaves_;
    std::unordered_map<std::string, dogen::yarn::module> modules_;
    std::unordered_map<std::string, dogen::yarn::concept> concepts_;
    std::unordered_map<std::string, dogen::yarn::primitive> primitives_;
    std::unordered_map<std::string, dogen::yarn::enumeration> enumerations_;
    std::unordered_map<std::string, dogen::yarn::object> objects_;
    std::unordered_map<std::string, dogen::yarn::exception> exceptions_;
    std::unordered_map<std::string, dogen::yarn::visitor> visitors_;
    bool is_target_;
    bool has_generatable_types_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::intermediate_model& lhs,
    dogen::yarn::intermediate_model& rhs) {
    lhs.swap(rhs);
}

}

#endif
