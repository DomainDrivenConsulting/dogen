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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.extraction/types/utility_formatter.hpp"
#include "masd.dogen.extraction/types/indent_filter.hpp"
#include "masd.dogen.extraction/types/cpp/scoped_boilerplate_formatter.hpp"
#include "masd.dogen.extraction/types/cpp/scoped_namespace_formatter.hpp"
#include "masd.dogen.templating/io/stitch/block_types_io.hpp"
#include "masd.dogen.templating/types/stitch/formatting_error.hpp"
#include "masd.dogen.templating/types/stitch/formatter.hpp"

namespace {

using namespace masd::dogen::utility::log;
static logger lg(logger_factory("templating.stitch.formatter"));

const std::string empty_header_guard;
/*
 * FIXME: humongous hackery just to get annotations to let us
 * through. It reality, we should just have a family and no facet or
 * backend.
 */
const std::string family_name("stitch");
const std::string backend_name("stitch");
const std::string facet_name("types");
const std::string archetype_name("stitch.formatter");

const std::string inserter("<<");
const std::string endl("std::endl;");

const std::string empty_stream_name("Stream name cannot be empty.");
const std::string empty_line("Line has no content.");
const std::string unsupported_block_type("Block type is unsupported: ");

// FIXME: hacks for now
// #define USE_NEW_DECORATION
const std::string include("#include ");
const std::string decoration_preamble_key(
    "masd.generation.decoration.preamble");
const std::string decoration_postamble_key(
    "masd.generation.decoration.postamble");

}

namespace masd::dogen::templating::stitch {

void formatter::format_text_block_line(const std::string& stream_name,
    const std::string& l, std::ostream& s) const {
    const auto spaces(extraction::spacing_types::left_and_right_space);
    s << stream_name;

    const extraction::utility_formatter u(s);
    u.insert(inserter, spaces);
    if (!l.empty()) {
        u.insert_quoted(l, true/*escape_content*/);
        u.insert(inserter, spaces);
    }
    u.insert(endl);
    s << std::endl;
}

void formatter::
format_expression_block_line(const std::string& stream_name,
    const std::string& l, std::ostream& s) const {
    s << stream_name;

    const extraction::utility_formatter u(s);
    const auto spaces(extraction::spacing_types::left_and_right_space);
    u.insert(inserter, spaces);

    s << l;

    u.insert(inserter, spaces);
    u.insert(endl);
    s << std::endl;
}

void formatter::format_variable_block_line(const std::string& l,
    const helpers::kvp_resolver& rs, std::ostream& s) const {
    const auto v(rs.resolve(l));
    s << v;
}

void formatter::
format_standard_control_block_line(
    const std::string& l, std::ostream& s) const {
    s << l << std::endl;
}

void formatter::format_mixed_content_line(const std::string& stream_name,
    const line& l, std::ostream& s) const {
    const auto spaces(extraction::spacing_types::left_and_right_space);
    const extraction::utility_formatter u(s);
    bool is_first(true);
    for (const auto& b : l.blocks()) {
        if (is_first) {
            s << stream_name;
            is_first = false;
        }

        u.insert(inserter, spaces);
        if (b.type() == block_types::text_block)
            u.insert_quoted(b.content(), true/*escape_content*/);
        else
            s << b.content();
    }
    u.insert(inserter, spaces);
    u.insert(endl);
    s << std::endl;
}

void formatter::format_line_with_single_block(const std::string& stream_name,
    const line& l, const helpers::kvp_resolver& rs, std::ostream& s) const {
    const auto& b(l.blocks().front());
    const auto& c(b.content());
    switch(b.type()) {
    case block_types::text_block:
        format_text_block_line(stream_name, c, s);
        break;
    case block_types::expression_block:
        format_expression_block_line(stream_name, c, s);
        break;
    case block_types::variable_block:
        format_variable_block_line(c, rs, s);
        break;
    case block_types::standard_control_block:
        format_standard_control_block_line(c, s);
        break;
    default:
        BOOST_LOG_SEV(lg, error) << unsupported_block_type << b.type();
        const auto s(boost::lexical_cast<std::string>(b.type()));
        BOOST_THROW_EXCEPTION(
            formatting_error(unsupported_block_type + s));
    }
}

annotations::archetype_location formatter::archetype_location() const {
    using annotations::archetype_location;
    static archetype_location
        r(family_name, backend_name, facet_name, archetype_name);
    return r;
}

extraction::meta_model::artefact
formatter::format(const text_template& tt) const {
    BOOST_LOG_SEV(lg, debug) << "Formatting text template.";

    const auto& ss(tt.properties().stitching_properties());
    const auto stream_variable_name(ss.stream_variable_name());
    if (stream_variable_name.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_stream_name;
        BOOST_THROW_EXCEPTION(formatting_error(empty_stream_name));
    }

    helpers::kvp_resolver rs(tt.supplied_kvps());
    std::ostringstream s;
    {
        const auto& id(ss.inclusion_dependencies());
#ifdef USE_NEW_DECORATION
        const auto preamble(rs.resolve(decoration_preamble_key));
        if (!preamble.empty())
            s << preamble;

        for (const auto& inc : id)
            s << include << inc << std::endl;

        if (!id.empty())
            s << masd::dogen::extraction::manage_blank_lines << std::endl;
#else
        masd::dogen::extraction::cpp::scoped_boilerplate_formatter
            sbf(s, tt.properties().decoration_properties(), id,
                empty_header_guard);
#endif

        masd::dogen::extraction::cpp::scoped_namespace_formatter snf(
            s, ss.containing_namespaces(), false/*create_anonymous_namespace*/,
            true/*add_new_line_*/, true/*nested_namespaces*/);

        for (const auto& l : tt.body().lines()) {
            if (l.blocks().empty()) {
                BOOST_LOG_SEV(lg, error) << empty_line;
                BOOST_THROW_EXCEPTION(formatting_error(empty_line));
            } else if (l.blocks().size() == 1)
                format_line_with_single_block(stream_variable_name, l, rs, s);
            else
                format_mixed_content_line(stream_variable_name, l, s);
        }

#ifdef USE_NEW_DECORATION
        const auto postamble(rs.resolve(decoration_postamble_key));
        if (!postamble.empty())
            s << postamble << std::endl;
#endif
    }

    extraction::meta_model::artefact r;
    r.overwrite(true);
    r.content(s.str());
    if (!tt.output_path().empty())
        r.path(tt.output_path());

    BOOST_LOG_SEV(lg, debug) << "Formatted template.";

    return r;
}

}
