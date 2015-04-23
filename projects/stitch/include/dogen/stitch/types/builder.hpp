/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_STITCH_TYPES_BUILDER_HPP
#define DOGEN_STITCH_TYPES_BUILDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <boost/optional.hpp>
#include "dogen/dynamic/schema/types/workflow.hpp"
#include "dogen/stitch/types/line.hpp"
#include "dogen/stitch/types/text_template.hpp"

namespace dogen {
namespace stitch {

class builder {
public:
    explicit builder(const dynamic::schema::workflow& w);

private:
    enum class state_types : unsigned int {
        in_text_block,
        in_standard_control_block,
        in_expression_control_block,
        in_directive
    };

private:
    void process_directive(const std::string& c);
    void add_segmented_content(const std::string& c);

public:
    void start_standard_control_block();
    void start_expression_control_block();
    void start_directive();
    void add_content(const std::string& content);
    void end_control_block();

public:
    text_template build();

private:
    const dynamic::schema::workflow& schema_workflow_;
    std::list<std::pair<std::string, std::string> > directives_;
    boost::optional<line> current_line_;
    state_types current_state_;
    text_template text_template_;
};

} }

#endif
