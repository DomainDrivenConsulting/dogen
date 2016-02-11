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
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <functional>
#include <boost/throw_exception.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/repository/include/qi_distinct.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/io/name_tree_io.hpp"
#include "dogen/yarn/types/parsing_error.hpp"
#include "dogen/yarn/types/name_tree_builder.hpp"
#include "dogen/yarn/types/name_tree_parser.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.name_tree_parser"));

const std::string error_msg("Failed to parse string: ");
using namespace boost::spirit;

using dogen::yarn::name_tree_builder;

namespace distinct {

namespace spirit = boost::spirit;
namespace ascii = boost::spirit::ascii;
namespace repo = boost::spirit::repository;

namespace traits {

template <typename Tail>
struct distinct_spec
    : spirit::result_of::terminal<repo::tag::distinct(Tail)> {};

template <typename String>
struct char_spec
    : spirit::result_of::terminal<spirit::tag::ascii::char_(String)> {};

}

template <typename Tail>
inline typename traits::distinct_spec<Tail>::type
distinct_spec(Tail const& tail) { return repo::distinct(tail); }

template <typename String>
inline typename traits::char_spec<String>::type
char_spec(String const& str) { return ascii::char_(str); }

typedef traits::char_spec<std::string>::type charset_tag_type;
typedef traits::distinct_spec<charset_tag_type>::type keyword_tag_type;

const std::string keyword_spec("0-9a-zA-Z_");
const keyword_tag_type keyword = distinct_spec(char_spec(keyword_spec));

}

template<typename Iterator>
struct grammar : qi::grammar<Iterator> {
    std::shared_ptr<name_tree_builder> builder;
    qi::rule<Iterator, std::string()> name_tree, name, nondigit, alphanum,
        primitive, signable_primitive;
    qi::rule<Iterator> identifier, scope_operator, type_name, template_id,
        templated_name, template_argument_list, template_argument;

    std::function<void()> start_template_, next_type_argument_, end_template_;
    std::function<void(const std::string&)> add_name_tree_, add_primitive_;

    void add_name_tree(const std::string& s) { builder->add_name(s); }
    void add_primitive(const std::string& s) { builder->add_primitive(s); }
    void start_template() { builder->start_children(); }
    void next_type_argument() { builder->next_child(); }
    void end_template() { builder->end_children(); }

    void setup_functors() {
        add_name_tree_ = std::bind(&grammar::add_name_tree, this,
            std::placeholders::_1);
        add_primitive_ = std::bind(&grammar::add_primitive, this,
            std::placeholders::_1);
        start_template_ = std::bind(&grammar::start_template, this);
        next_type_argument_ = std::bind(&grammar::next_type_argument, this);
        end_template_ = std::bind(&grammar::end_template, this);
    }

    grammar(std::shared_ptr<name_tree_builder> b)
        : grammar::base_type(type_name), builder(b) {
        setup_functors();
        using qi::on_error;
        using qi::fail;
        using boost::spirit::qi::labels::_val;
        using boost::spirit::qi::_1;
        using boost::spirit::ascii::string;

        using boost::phoenix::val;
        using boost::phoenix::at_c;
        using boost::phoenix::push_back;
        using boost::phoenix::construct;

        alphanum = boost::spirit::qi::alnum | string("_");
        nondigit = boost::spirit::qi::alpha | string("_");
        name %= lexeme[nondigit >> *(alphanum)];
        scope_operator = "::";
        name_tree = name[add_name_tree_]
            >> *(scope_operator >> name[add_name_tree_]);
        signable_primitive =
            -(string("unsigned") >> string(" ")) >>
            (
                distinct::keyword[string("short")] |
                distinct::keyword[string("wchar_t")] |
                distinct::keyword[string("char")] |
                distinct::keyword[string("int")] |
                (
                    string("long") >> -(string(" ") >> string("long"))));
        primitive =
            distinct::keyword[string("bool")] |
            signable_primitive |
            distinct::keyword[string("float")] |
            distinct::keyword[string("double")] |
            distinct::keyword[string("void")];
        type_name %= primitive[add_primitive_] |
            (name_tree >> -(templated_name));

        templated_name = qi::lit("<")[start_template_]
            >> template_argument_list >> qi::lit(">")[end_template_];
        template_argument_list %= type_name
            >> *(qi::lit(",")[next_type_argument_] >> *qi::space >> type_name);

        on_error<fail>
            (
                type_name,
                std::cout << val("Error! Expecting ")
                << _4                             // what failed?
                << val(" here: \"")
                << construct<std::string>(_3, _2) // iterators to error-pos, end
                << val("\"")
                << std::endl
                );
    }
};

}

namespace dogen {
namespace yarn {

name_tree_parser::name_tree_parser() :
    top_level_modules_(std::unordered_set<std::string>()),
    model_location_(location()) { }

name_tree_parser::
name_tree_parser(const std::unordered_set<std::string>& top_level_modules,
    const location& model_location)
    : top_level_modules_(top_level_modules), model_location_(model_location) { }

name_tree name_tree_parser::parse(const std::string& s) const {
    BOOST_LOG_SEV(lg, debug) << "parsing name: " << s;

    auto builder(std::make_shared<name_tree_builder>(
            top_level_modules_, model_location_));
    grammar<std::string::const_iterator> g(builder);

    std::string::const_iterator i(s.begin());
    std::string::const_iterator end(s.end());
    const bool ok(boost::spirit::qi::parse(i, end, g));

    if (!ok || i != end) {
        BOOST_LOG_SEV(lg, error) << error_msg << s;
        BOOST_THROW_EXCEPTION(parsing_error(error_msg + s));
    }

    auto r(builder->build());
    BOOST_LOG_SEV(lg, debug) << "result: " << r;
    return r;
}

} }
