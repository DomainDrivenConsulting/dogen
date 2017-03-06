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
#ifndef DOGEN_TEST_MODELS_ALL_PATH_AND_DIRECTORY_SETTINGS_SERIALIZATION_DIR_CLASS_0_0_3_6_THE_SERIALIZATION__HXX
#define DOGEN_TEST_MODELS_ALL_PATH_AND_DIRECTORY_SETTINGS_SERIALIZATION_DIR_CLASS_0_0_3_6_THE_SERIALIZATION__HXX

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/test_models/all_path_and_directory_settings/types_dir/class_0_0_5_7_the_types..hxx"

namespace boost {
namespace serialization {

template<class Archive>
void save(Archive& ar, const dogen::test_models::all_path_and_directory_settings::class_0& v, unsigned int version);

template<class Archive>
void load(Archive& ar, dogen::test_models::all_path_and_directory_settings::class_0& v, unsigned int version);

} }

#endif
