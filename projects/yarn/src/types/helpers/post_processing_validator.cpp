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
#include <array>
#include <algorithm>
#include <unordered_set>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/utility/string/splitter.hpp"
#include "dogen/yarn/io/meta_model/name_io.hpp"
#include "dogen/yarn/types/helpers/decomposer.hpp"
#include "dogen/yarn/types/helpers/validation_error.hpp"
#include "dogen/yarn/types/helpers/post_processing_validator.hpp"

typedef boost::error_info<struct owner, std::string>
errmsg_validation_owner;

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.helpers.post_processing_validator"));

const std::string space(" ");
const std::regex strict_name_regex("^[a-zA-Z_][a-zA-Z0-9_]*$");
const std::regex loose_name_regex("^[a-zA-Z_][\\-\\.a-zA-Z0-9_]*$");

/*
 * FIXME: we've removed the following keywords for now because yarn
 * uses these terms: "module", "concept".
 */
std::array<std::string, 81> cpp_reserved = { {
        "alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel",
        "atomic_commit", "atomic_noexcept", "auto", "bitand", "bitor",
        "break", "case", "catch", "class", "compl", "const",
        "const_cast", "constexpr", "continue", "decltype", "default", "delete",
        "do", "dynamic_cast", "else", "enum", "explicit", "export", "extern",
        "false", "for", "friend", "goto", "if", "import", "inline",
        "mutable", "namespace", "new", "noexcept", "not",
        "not_eq", "nullptr", "operator", "or", "or_eq", "private", "protected",
        "public", "register", "reinterpret_cast", "requires", "return",
        "sizeof", "static", "static_assert", "static_cast", "struct", "switch",
        "synchronized", "template", "this", "thread_local", "throw", "true",
        "try", "typedef", "typeid", "typename", "union", "using", "virtual",
        "void", "volatile", "wchar_t", "while", "xor", "xor_eq", "xor_eqalignas"
    } };

std::array<std::string, 11> cpp_builtins = { {
    "char16_t", "char32_t", "unsigned", "bool", "char", "double", "float",
    "int", "long", "short", "signed"
    }
};

/*
 * FIXME: we've removed the following keywords for now because test
 * models use these terms: "base".
 */
std::array<std::string, 64> csharp_reserved = { {
        "abstract", "as", "break",
        "case", "catch", "checked", "class",
        "const", "continue", "default", "delegate",
        "do", "else", "enum", "event",
        "explicit", "extern",   "false", "finally",
        "fixed", "for", "foreach", "goto",
        "if", "implicit", "in", "interface",
        "internal",  "is", "lock", "namespace",
        "new", "null", "operator", "out",
        "override", "params", "private", "protected",
        "public", "readonly", "ref", "return",
        "sealed", "sizeof", "stackalloc", "static",
        "struct", "switch", "this", "throw",
        "true", "try", "typeof", "unchecked",
        "unsafe", "using", "var", "virtual",
        "void", "volatile", "while"
    } };

/*
 * FIXME: we've removed the following builtins for now, because they
 * are being used by the following models:
 *
 * - "decimal": yarn.upsilon
 * - "object": yarn
 * - "string": std
 */
std::array<std::string, 12> csharp_builtins = { {
        "byte", "bool", "char", "double", "float", "int", "long",
        "sbyte", "short",  "uint", "ulong", "ushort"
    }
};

const std::string duplicate_element("Element has an ID already defined: ");
const std::string invalid_string(
    "String is not valid according to the identifier regular expression: ");
const std::string reserved_keyword(
    "String matches a resvered keyword on one of the supported languages: ");
const std::string builtin_name("String matches the name of a built in type: ");
const std::string abstract_instance(
    "Attempt to instantiate an abstract type: ");
const std::string invalid_empty_id("Name must have a non-empty id.");

}

namespace dogen {
namespace yarn {
namespace helpers {

template<typename Container>
inline void check_not_in_container(const Container& c, const std::string& str,
    const std::string& error_msg) {
    const auto i(std::find(c.begin(), c.end(), str));
    if (i != c.end()) {
        BOOST_LOG_SEV(lg, error) << error_msg << str;
        BOOST_THROW_EXCEPTION(validation_error(error_msg + str));
    }
}

bool post_processing_validator::
allow_spaces_in_built_in_types(const meta_model::languages l) {
    return l == meta_model::languages::cpp;
}

void post_processing_validator::validate_string(const std::string& s,
    const std::regex& regex, bool check_not_builtin) {
    BOOST_LOG_SEV(lg, trace) << "Sanity checking string: " << s;

    /*
     * String must match the regular expression for a valid
     * identifier across all supported languages.
     */
    if (!std::regex_match(s, regex)) {
        BOOST_LOG_SEV(lg, error) << invalid_string << "'" << s << "'";
        BOOST_THROW_EXCEPTION(validation_error(invalid_string + s));
    }

    /*
     * String must not be in our list of reserved keywords for C++.
     */
    check_not_in_container(cpp_reserved, s, reserved_keyword);

    /*
     * String must not be in our list of reserved keywords for C#.
     */
    check_not_in_container(csharp_reserved, s, reserved_keyword);

    if (check_not_builtin) {
        /*
         * String must not be in our list of builtins for C++.
         */
        check_not_in_container(cpp_builtins, s, builtin_name);

        /*
         * String must not be in our list of builtins for C#.
         */
        check_not_in_container(csharp_builtins, s, builtin_name);
    }

    BOOST_LOG_SEV(lg, trace) << "String passed all sanity checks.";
}

void post_processing_validator::validate_strings(
    const std::list<std::string>& strings, const std::regex& regex) {
    for (const auto& s : strings)
        validate_string(s, regex);
}

void post_processing_validator::validate_name(const meta_model::name& n,
    const std::regex& regex, const bool allow_spaces_in_built_in_types) {
    /*
     * All names must have a non-empty id.
     */
    if (n.id().empty()) {
        BOOST_LOG_SEV(lg, error) << invalid_empty_id;
        BOOST_THROW_EXCEPTION(validation_error(invalid_empty_id));
    }

    /*
     * Built-in types are defined at the global namespace level; if we
     * are at the global namespace level, then built-ins are valid
     * element names. In this case, we should not check the name
     * against the built-in list.
     */
    const auto& l(n.location());
    const bool at_global_namespace(l.external_modules().empty() &&
        l.model_modules().empty() &&
        l.internal_modules().empty());
    const bool check_not_builtin(!at_global_namespace);

    /*
     * Sanity check all of the components of the name. Bit of a hack
     * here: if we are at global namespace and our model is in a
     * language where built-ins can have spaces, we split the name on
     * space and validate each component separately.
     */
    BOOST_LOG_SEV(lg, debug) << "at_global_namespace: "
                             << at_global_namespace
                             << " allow_spaces_in_built_in_types: "
                             << allow_spaces_in_built_in_types;

    if (at_global_namespace && allow_spaces_in_built_in_types) {
        using utility::string::splitter;
        const auto splitted(splitter::split_delimited(n.simple(), space));
        BOOST_LOG_SEV(lg, debug) << "Splitted simple name: " << splitted;
        for (const auto& s : splitted)
            validate_string(s, regex, check_not_builtin);
    } else
        validate_string(n.simple(), regex, check_not_builtin);

    validate_strings(l.external_modules(), regex);
    validate_strings(l.model_modules(), regex);
    validate_strings(l.internal_modules(), regex);

    if (!l.element().empty())
        validate_string(l.element(), regex);
}

void post_processing_validator::
validate_names(const std::list<std::pair<std::string, meta_model::name>>& names,
    const meta_model::languages l) {
    BOOST_LOG_SEV(lg, debug) << "Sanity checking names.";
    std::unordered_set<std::string> ids_done;

    const bool allow_spaces(allow_spaces_in_built_in_types(l));
    for (const auto& pair : names) {
        const auto& owner(pair.first);
        const auto& n(pair.second);
        const auto& id(n.id());
        BOOST_LOG_SEV(lg, debug) << "Validating: '" << id << "'";

        try {
            /*
             * Element identifier must be unique across all model
             * elements.
             */
            const auto inserted(ids_done.insert(id).second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, error) << duplicate_element << id;
                BOOST_THROW_EXCEPTION(validation_error(duplicate_element + id));
            }

            /*
             * Element name must pass all sanity checks.
             */
            validate_name(n, strict_name_regex, allow_spaces);

            BOOST_LOG_SEV(lg, debug) << "Name is valid.";
        } catch (boost::exception& e) {
            e << errmsg_validation_owner(owner);
            throw;
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Finished validating names.";
}

void post_processing_validator::
validate_injected_names(
    const std::list<std::pair<std::string, meta_model::name>>& names) {
    BOOST_LOG_SEV(lg, debug) << "Sanity checking injected names.";

    /*
     * Injected names have a number of peculiarities that make
     * validation harder:
     *
     * - we need a looser regular expression validation because the
     *   injected types represent in many cases file names -
     *   e.g. CMakeLists, Visual Studio solutions and project files,
     *   etc. These may require things such as dashes and dots. All
     *   other model types which map to programming language
     *   constructs do not allow these characters. So to make our life
     *   easier we use strict validation for most model types and the
     *   loose validation for the injected types. This is, of course,
     *   not strictly correct, because in theory one can inject fabric
     *   types which do not correspond to a file - e.g. serialisation
     *   registrar in c++). However, this is a good enough
     *   approximation for now.
     *
     * - injected types can have duplicate names. This is due to
     *   element extensions such as forward declarations and ODB
     *   options. These take on the name of the element they are
     *   extending; now, normally, this is not a problem because the
     *   extended element will be processed as part of the names
     *   collection and the extension as part of the injected
     *   elements. However, when we are using ORM support, we end up
     *   with more than one extension for each element (both forward
     *   declaration and the ODB option). This means that duplicates
     *   will occur even within the injected names collection. So we
     *   just ignore duplicates altogether to make our life easier.
     */
    for (const auto& pair : names) {
        const auto& owner(pair.first);
        const auto& n(pair.second);
        const auto& id(n.id());
        BOOST_LOG_SEV(lg, debug) << "Validating: '" << id << "'";

        try {
            /*
             * Element name must pass all sanity checks. Note that in
             */
            validate_name(n, loose_name_regex, false/*allow_spaces*/);

            BOOST_LOG_SEV(lg, debug) << "Name is valid.";
        } catch (boost::exception& e) {
            e << errmsg_validation_owner(owner);
            throw;
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Finished validating all names.";
}

void post_processing_validator::validate_meta_names(
    const std::list<std::pair<std::string, meta_model::name>>& meta_names) {
    BOOST_LOG_SEV(lg, debug) << "Sanity checking all meta-names.";

    /*
     * Note that we can't just simply call validate_names here because
     * meta-names are known to have duplicates - i.e. we use the same
     * meta-model element many times).
     */
    for (const auto& pair : meta_names) {
        const auto& owner(pair.first);
        const auto& n(pair.second);
        const auto& id(n.id());
        BOOST_LOG_SEV(lg, debug) << "Validating: '" << id << "'";

        try {
            /*
             * Element name must pass all sanity checks.
             */
            validate_name(n, strict_name_regex, false/*allow_spaces*/);

            BOOST_LOG_SEV(lg, debug) << "Name is valid.";
        } catch (boost::exception& e) {
            e << errmsg_validation_owner(owner);
            throw;
        }
    }
    BOOST_LOG_SEV(lg, debug) << "Finished validating all meta-names.";
}

void post_processing_validator::
validate_name_tree(const std::unordered_set<std::string>& abstract_elements,
    const meta_model::languages l, const meta_model::name_tree& nt,
    const bool inherit_opaqueness_from_parent) {

    const auto& ae(abstract_elements);
    const auto id(nt.current().id());
    const bool is_abstract(ae.find(id) != ae.end());
    if (is_abstract && !inherit_opaqueness_from_parent) {
        BOOST_LOG_SEV(lg, error) << abstract_instance << id;
        BOOST_THROW_EXCEPTION(validation_error(abstract_instance + id));
    }

    for (const auto& c : nt.children())
        validate_name_tree(ae, l, c, nt.are_children_opaque());
}

void post_processing_validator::validate_name_trees(
    const std::unordered_set<std::string>& abstract_elements,
    const meta_model::languages l,
    const std::list<std::pair<std::string, meta_model::name_tree>>& nts) {

    /*
     * The only validation we perform on name trees at present is done
     * just for c++, so we can ignore all other languages. Note that
     * we already resolve all of the names in the name tree so we know
     * they are valid. These are just additional checks we perform on
     * these names.
     */
    if (l != meta_model::languages::cpp)
        return;

    for (const auto& pair : nts) {
        const auto& owner(pair.first);
        const auto& nt(pair.second);
        BOOST_LOG_SEV(lg, trace) << "Validating: '" << nt.identifiable() << "'";

        try {
            validate_name_tree(abstract_elements, l, nt);
        } catch (boost::exception& e) {
            e << errmsg_validation_owner(owner);
            throw;
        }
    }
}

void post_processing_validator::
validate(const indices& idx, const meta_model::endomodel& im) {
    BOOST_LOG_SEV(lg, debug) << "Started validation. Model: " << im.name().id();

    const auto l(im.input_language());
    const auto dr(decomposer::decompose(im));
    validate_names(dr.names(), l);
    validate_injected_names(dr.injected_names());
    validate_meta_names(dr.meta_names());
    validate_name_trees(idx.abstract_elements(), l, dr.name_trees());

    BOOST_LOG_SEV(lg, debug) << "Finished validation.";
}

} } }
