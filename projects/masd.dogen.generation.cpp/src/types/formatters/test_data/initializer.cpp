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
#include "masd.dogen.generation.cpp/types/formatters/test_data/traits.hpp"
#include "masd.dogen.generation.cpp/types/formatters/master_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/builtin_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/primitive_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/primitive_implementation_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/class_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/class_implementation_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/enum_header_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/enum_implementation_formatter.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/associative_container_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/bool_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/char_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/date_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/domain_type_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/number_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/optional_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/pair_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/path_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/ptime_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/ptree_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/sequence_container_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/smart_pointer_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/string_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/time_duration_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/variant_helper.hpp"
#include "masd.dogen.generation.cpp/types/formatters/test_data/initializer.hpp"

namespace masd::dogen::generation::cpp::formatters::test_data {

void initializer::initialize(registrar& rg) {
    register_formatter<master_header_formatter>(rg, traits::facet());
    register_formatter<builtin_header_formatter>(rg);
    register_formatter<primitive_header_formatter>(rg);
    register_formatter<primitive_implementation_formatter>(rg);
    register_formatter<class_header_formatter>(rg);
    register_formatter<class_implementation_formatter>(rg);
    register_formatter<enum_header_formatter>(rg);
    register_formatter<enum_implementation_formatter>(rg);
    register_helper_formatter<associative_container_helper>(rg);
    register_helper_formatter<bool_helper>(rg);
    register_helper_formatter<char_helper>(rg);
    register_helper_formatter<date_helper>(rg);
    register_helper_formatter<domain_type_helper>(rg);
    register_helper_formatter<number_helper>(rg);
    register_helper_formatter<optional_helper>(rg);
    register_helper_formatter<pair_helper>(rg);
    register_helper_formatter<path_helper>(rg);
    register_helper_formatter<ptime_helper>(rg);
    register_helper_formatter<ptree_helper>(rg);
    register_helper_formatter<sequence_container_helper>(rg);
    register_helper_formatter<smart_pointer_helper>(rg);
    register_helper_formatter<string_helper>(rg);
    register_helper_formatter<time_duration_helper>(rg);
    register_helper_formatter<variant_helper>(rg);
}

}
