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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/yarn/types/elements_traversal.hpp"
#include "dogen/quilt.csharp/types/fabric/decoration_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.csharp.fabric.decoration_expander"));

const std::string cs_modeline_name("cs");
const std::string xml_modeline_name("xml");

}

namespace dogen {
namespace quilt {
namespace csharp {
namespace fabric {

class decoration_updater {
public:
    decoration_updater(
        const dogen::formatters::decoration_properties_factory& dpf)
        : factory_(dpf) {}

private:
    void update(yarn::element& e,
        const std::string & modeline_name = cs_modeline_name) {
        BOOST_LOG_SEV(lg, debug) << "Processing element: " << e.name().id();
        auto& ep(e.element_properties());
        ep.decoration_properties(factory_.make(modeline_name));
    }

public:
    bool include_injected_elements() { return false; }
    void operator()(yarn::element& /*e*/) {  }
    void operator()(yarn::module& m) { update(m); }
    void operator()(yarn::concept& c) { update(c); }
    void operator()(yarn::builtin& b) { update(b); }
    void operator()(yarn::enumeration& e) { update(e); }
    void operator()(yarn::primitive& p) { update(p); }
    void operator()(yarn::object& o) { update(o); }
    void operator()(yarn::exception& e) { update(e); }
    void operator()(yarn::visitor& v) { update(v); }

private:
    const dogen::formatters::decoration_properties_factory& factory_;
};

void decoration_expander::
expand(const dogen::formatters::decoration_properties_factory& dpf,
    yarn::intermediate_model& im) const {

    BOOST_LOG_SEV(lg, debug) << "Populating decoration properties.";

    decoration_updater du(dpf);
    yarn::elements_traversal(im, du);

    BOOST_LOG_SEV(lg, debug) << "Finished populating decoration properties.";
}

} } } }
