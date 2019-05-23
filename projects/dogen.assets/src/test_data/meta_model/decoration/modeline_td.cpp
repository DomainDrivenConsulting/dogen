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
#include "dogen.assets/test_data/meta_model/element_td.hpp"
#include "dogen.assets/test_data/meta_model/technical_space_td.hpp"
#include "dogen.assets/test_data/meta_model/decoration/editor_td.hpp"
#include "dogen.assets/test_data/meta_model/decoration/modeline_td.hpp"
#include "dogen.assets/test_data/meta_model/decoration/modeline_field_td.hpp"
#include "dogen.assets/test_data/meta_model/decoration/modeline_location_td.hpp"

namespace {

dogen::assets::meta_model::decoration::editor
create_dogen_assets_meta_model_decoration_editor(const unsigned int position) {
    return dogen::assets::meta_model::decoration::editor_generator::create(position);
}

dogen::assets::meta_model::decoration::modeline_location
create_dogen_assets_meta_model_decoration_modeline_location(const unsigned int position) {
    return dogen::assets::meta_model::decoration::modeline_location_generator::create(position);
}

dogen::assets::meta_model::decoration::modeline_field
create_dogen_assets_meta_model_decoration_modeline_field(const unsigned int position) {
    return dogen::assets::meta_model::decoration::modeline_field_generator::create(position);
}

std::list<dogen::assets::meta_model::decoration::modeline_field> create_std_list_dogen_assets_meta_model_decoration_modeline_field(unsigned int position) {
    std::list<dogen::assets::meta_model::decoration::modeline_field> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_assets_meta_model_decoration_modeline_field(position + i));
    }
    return r;
}

dogen::assets::meta_model::technical_space
create_dogen_assets_meta_model_technical_space(const unsigned int position) {
    return dogen::assets::meta_model::technical_space_generator::create(position);
}

}

namespace dogen::assets::meta_model::decoration {

modeline_generator::modeline_generator() : position_(0) { }

void modeline_generator::
populate(const unsigned int position, result_type& v) {
    dogen::assets::meta_model::element_generator::populate(position, v);
    v.editor(create_dogen_assets_meta_model_decoration_editor(position + 0));
    v.location(create_dogen_assets_meta_model_decoration_modeline_location(position + 1));
    v.fields(create_std_list_dogen_assets_meta_model_decoration_modeline_field(position + 2));
    v.technical_space(create_dogen_assets_meta_model_technical_space(position + 3));
}

modeline_generator::result_type
modeline_generator::create(const unsigned int position) {
    modeline r;
    modeline_generator::populate(position, r);
    return r;
}

modeline_generator::result_type*
modeline_generator::create_ptr(const unsigned int position) {
    modeline* p = new modeline();
    modeline_generator::populate(position, *p);
    return p;
}

modeline_generator::result_type
modeline_generator::operator()() {
    return create(position_++);
}

}