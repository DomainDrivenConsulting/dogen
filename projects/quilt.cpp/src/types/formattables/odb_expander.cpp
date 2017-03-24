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
#include <sstream>
#include <boost/algorithm/string.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/annotations/io/type_io.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/types/primitive.hpp"
#include "dogen/quilt.cpp/types/fabric/common_odb_options.hpp"
#include "dogen/quilt.cpp/types/fabric/object_odb_options.hpp"
#include "dogen/quilt.cpp/types/fabric/element_visitor.hpp"
#include "dogen/quilt.cpp/types/fabric/odb_options_factory.hpp"
#include "dogen/quilt.cpp/io/formattables/odb_properties_io.hpp"
#include "dogen/quilt.cpp/types/formattables/header_guard_factory.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formattables/odb_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formattables.odb_expander"));

const std::string empty_column_attribute("column(\"\")");
const std::string id_pragma("id");
const std::string no_id_pragma("no_id");

const std::string null_pragma("null");
const std::string not_null_pragma("not_null");
const std::string value_pragma("value");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class updator : public fabric::element_visitor {
public:
    updator(const locator& l, const odb_expander::type_group& tg);

private:
    std::list<std::string> make_odb_pragmas(const odb_expander::type_group& tg,
        const annotations::annotation& a) const;

public:
    using fabric::element_visitor::visit;
    void visit(fabric::object_odb_options& ooo);
    void visit(yarn::object& o);
    void visit(yarn::primitive& p);

public:
    const boost::optional<odb_properties>& result() const;

private:
    const locator locator_;
    const odb_expander::type_group& type_group_;
    boost::optional<odb_properties> result_;
};

updator::updator(const locator& l,
    const odb_expander::type_group& tg) : locator_(l), type_group_(tg) {}

std::list<std::string>
updator::make_odb_pragmas(const odb_expander::type_group& tg,
    const annotations::annotation& a) const {

    const annotations::entry_selector s(a);
    if (!s.has_entry(tg.odb_pragma))
        return std::list<std::string>();

    return s.get_text_collection_content(tg.odb_pragma);
}

void updator::visit(fabric::object_odb_options& ooo) {
    const auto odb_arch(formatters::odb::traits::class_header_archetype());
    const auto odb_rp(locator_.make_inclusion_path_for_cpp_header(ooo.name(),
            odb_arch));

    std::ostringstream os;
    os << "'#include \"" << odb_rp.generic_string() << "\"'";
    ooo.epilogue(os.str());
    os.str("");

    const auto types_arch(formatters::types::traits::class_header_archetype());
    const auto types_rp(locator_.make_inclusion_path_for_cpp_header(ooo.name(),
            types_arch).parent_path());

    os << "'%(.*).hpp%" << types_rp.generic_string() << "/$1.hpp%'";
    ooo.include_regexes().push_back(os.str());

    os.str("");
    os << "'%(^[a-zA-Z0-9_]+)-odb(.*)%"
       << odb_rp.parent_path().generic_string() << "/$1-odb$2'";
    ooo.include_regexes().push_back(os.str());

    os.str("");
    os << "'%" << types_rp.generic_string() << "/(.*)-odb(.*)%"
       << odb_rp.parent_path().generic_string() << "/$1-odb$2%'";
    ooo.include_regexes().push_back(os.str());

    const auto odb_fctn(formatters::odb::traits::facet());
    const auto odb_dp(locator_.make_relative_include_path_for_facet(odb_fctn,
            true/*for_include_statement*/));
    ooo.header_guard_prefix(header_guard_factory::make(odb_dp));
}

void updator::visit(yarn::object& o) {
    odb_properties op;

    const annotations::entry_selector s(o.annotation());
    auto top_level_pragmas(make_odb_pragmas(type_group_, o.annotation()));
    if (o.orm_properties()) {
        /*
         * If the user has supplied an ORM properties and this
         * object does not have a primary key, we need to inject ODB's
         * pragma for it.
         */
        const auto& cfg(*o.orm_properties());
        op.is_value(cfg.is_value());

        if (cfg.generate_mapping() && !op.is_value() && !cfg.has_primary_key())
            top_level_pragmas.push_back(no_id_pragma);

        const auto& sn(cfg.schema_name());
        if (!sn.empty() && (op.is_value() || cfg.generate_mapping())) {
            std::ostringstream s;
            s << "schema(\"";

            if (!cfg.letter_case())
                s << cfg.schema_name();
            else if (*cfg.letter_case() == yarn::letter_cases::upper_case)
                s << boost::to_upper_copy(cfg.schema_name());
            else if (*cfg.letter_case() == yarn::letter_cases::lower_case)
                s << boost::to_lower_copy(cfg.schema_name());

            s <<"\")";
            top_level_pragmas.push_back(s.str());
        }
    }

    op.top_level_odb_pragmas(top_level_pragmas);

    for (const auto& attr : o.local_attributes()) {
        const auto id(attr.name().id());
        auto attr_pragmas(make_odb_pragmas(type_group_, attr.annotation()));

        if (attr.orm_properties()) {
            const auto& cfg(*attr.orm_properties());
            if (cfg.is_primary_key())
                attr_pragmas.push_back(id_pragma);

            /*
             * For composite keys, we do not want to use the column
             * name as a prefix.
             */
            if (cfg.is_composite())
                attr_pragmas.push_back(empty_column_attribute);

            if (cfg.is_nullable()) {
                if (*cfg.is_nullable())
                    attr_pragmas.push_back(null_pragma);
                else
                    attr_pragmas.push_back(not_null_pragma);
            }

            if (!cfg.type_overrides().empty()) {
                std::ostringstream s;
                bool is_first(true);
                for (const auto pair : cfg.type_overrides()) {
                    if (!is_first)
                        s << " ";

                    const auto ds(pair.first);
                    const auto type(pair.second);
                    s << fabric::odb_options_factory::to_odb_database(ds)
                      << ":type(\"" << type << "\")";

                    is_first = false;
                }
                attr_pragmas.push_back(s.str());
            }
        }

        if (attr_pragmas.empty())
            continue;

        op.attribute_level_odb_pragmas()[id] = attr_pragmas;
    }

    const bool has_top_level_pragmas(!op.top_level_odb_pragmas().empty());
    const bool has_attribute_pragmas(!op.attribute_level_odb_pragmas().empty());
    const bool has_pragmas(has_top_level_pragmas || has_attribute_pragmas);

    if (has_pragmas)
        result_ = op;
}

void updator::visit(yarn::primitive& p) {
    odb_properties op;
    op.is_value(true);
    op.top_level_odb_pragmas(make_odb_pragmas(type_group_, p.annotation()));

    if (p.orm_properties()) {
        const auto& cfg(*p.orm_properties());

        const auto& sn(cfg.schema_name());
        if (!sn.empty() && cfg.generate_mapping()) {
            std::ostringstream s;
            s << "schema(\"";

            if (!cfg.letter_case())
                s << cfg.schema_name();
            else if (*cfg.letter_case() == yarn::letter_cases::upper_case)
                s << boost::to_upper_copy(cfg.schema_name());
            else if (*cfg.letter_case() == yarn::letter_cases::lower_case)
                s << boost::to_lower_copy(cfg.schema_name());

            s <<"\")";
            op.top_level_odb_pragmas().push_back(s.str());
        }
    }

    const bool has_top_level_pragmas(!op.top_level_odb_pragmas().empty());
    if (!has_top_level_pragmas)
        return;

    /*
     * For primitives, we need to inject manually the attribute level
     * pragmas, if there was a top-level pragma. This is because users
     * cannot see the internal attribute.
     *
     * We add this pragma so as to name the primitive's internal value
     * attribute correctly. Primitives do not have column names; they
     * are set by the type that owns them. This avoids names such as
     * "primitive_id_primitive_id", which become "primitive_id"
     * instead.
     */
    const auto& attr(p.value_attribute());
    const auto pragmas(std::list<std::string> { empty_column_attribute });

    const auto id(attr.name().id());
    op.attribute_level_odb_pragmas()[id] = pragmas;
    result_ = op;
}

const boost::optional<odb_properties>&
updator::result() const {
    return result_;
}

std::ostream& operator<<(std::ostream& s,
    const odb_expander::type_group& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::formattables::"
      << "odb_expander::type_group\"" << ", "
      << "\"odb_pragma\": " << v.odb_pragma
      << " }";

    return s;
}

odb_expander::type_group odb_expander::
make_type_group(const annotations::type_repository& atrp) const {
    BOOST_LOG_SEV(lg, debug) << "Creating type groups.";

    type_group r;
    const annotations::type_repository_selector s(atrp);
    const auto& op(formatters::odb::traits::odb_pragma());
    r.odb_pragma = s.select_type_by_name(op);

    BOOST_LOG_SEV(lg, debug) << "Created type groups. Result: " << r;
    return r;
}

void odb_expander::expand(const annotations::type_repository& atrp,
    const locator& l, model& fm) const {
    BOOST_LOG_SEV(lg, debug) << "Started expanding odb properties.";

    const auto tg(make_type_group(atrp));
    for (auto& pair : fm.formattables()) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        /*
         * We only need to generate the aspect properties for
         * elements of the target model. However, we can't perform
         * this after reduction because the aspect propertiess must
         * be build prior to reduction or else we will not get aspects
         * for referenced models.
         */
        auto segment(formattable.master_segment());
        if (segment->origin_type() != yarn::origin_types::target)
            continue;

        for (const auto& ptr : formattable.all_segments()) {
            auto& e(*ptr);
            updator g(l, tg);
            e.accept(g);

            if (!g.result())
                continue;

            auto& eprops(formattable.element_properties());
            eprops.odb_properties(*g.result());
        }
    }

    BOOST_LOG_SEV(lg, debug) << "Finished expanding odb properties. ";
}

} } } }
