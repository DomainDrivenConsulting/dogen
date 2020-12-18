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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.org/io/entities/document_io.hpp"
#include "dogen.org/types/helpers/builder.hpp"
#include "dogen.org/types/transforms/string_to_document_transform.hpp"

namespace {

const std::string transform_id("org.transforms.string_to_document_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen::org::transforms {

std::istream&
string_to_document_transform::getline(std::istream& is, std::string& s) {
    std::ostringstream os;
    std::getline(is, s);
    os << s;

    /*
     * Try to detect if there was a newline on this line or not. There
     * is no easy way to preserve the original input in getline, so we
     * resort to this hack. The logic is that if we have not reached
     * the EOF, then there must have been a newline.
     */
    if(!is.eof() && !is.fail())
        os << std::endl;

    s = os.str();
    return is;
}

entities::document string_to_document_transform::
apply(boost::shared_ptr<tracing::tracer> tracer, const std::string& s) {
    tracing::scoped_transform_tracer stp(lg, "string to document",
        transform_id, "org_document", *tracer, s);

    /*
     * If there is no content, return an empty document.
     */
    if (s.empty()) {
        entities::document r;
        stp.end_transform(r);
        return r;
    }

    std::string line;
    std::istringstream is(s);
    helpers::builder b;
    while(getline(is, line)) {
        b.add_line(line);
    }

    const auto r(b.build());
    stp.end_transform(r);
    return r;
}

}
