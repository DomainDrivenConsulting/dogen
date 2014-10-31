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
#include "dogen/cpp/types/abilities.hpp"
#include "dogen/cpp/types/aspect_types.hpp"
#include "dogen/cpp/types/building_error.hpp"
#include "dogen/cpp/types/class_aspects.hpp"
#include "dogen/cpp/types/class_info.hpp"
#include "dogen/cpp/types/class_types.hpp"
#include "dogen/cpp/types/cmakelists_info.hpp"
#include "dogen/cpp/types/concept_info.hpp"
#include "dogen/cpp/types/content_descriptor.hpp"
#include "dogen/cpp/types/content_descriptor_factory.hpp"
#include "dogen/cpp/types/content_types.hpp"
#include "dogen/cpp/types/cpp.hpp"
#include "dogen/cpp/types/cpp_settings.hpp"
#include "dogen/cpp/types/entity.hpp"
#include "dogen/cpp/types/entity_visitor.hpp"
#include "dogen/cpp/types/enum_info.hpp"
#include "dogen/cpp/types/enumerator_info.hpp"
#include "dogen/cpp/types/exception_info.hpp"
#include "dogen/cpp/types/facet_settings.hpp"
#include "dogen/cpp/types/file_info.hpp"
#include "dogen/cpp/types/file_types.hpp"
#include "dogen/cpp/types/flat_name_builder.hpp"
#include "dogen/cpp/types/formatter_dispatcher.hpp"
#include "dogen/cpp/types/formatters/boilerplate_formatter.hpp"
#include "dogen/cpp/types/formatters/class_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/cmakelists_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/enum_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/exception_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/formatters.hpp"
#include "dogen/cpp/types/formatters/forward_declarations_formatter.hpp"
#include "dogen/cpp/types/formatters/forward_declarations_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/hash/class_header_formatter.hpp"
#include "dogen/cpp/types/formatters/hash/class_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/hash/enricher.hpp"
#include "dogen/cpp/types/formatters/hash/enumeration_header_formatter.hpp"
#include "dogen/cpp/types/formatters/hash/enumeration_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/hash/hash.hpp"
#include "dogen/cpp/types/formatters/hash/traits.hpp"
#include "dogen/cpp/types/formatters/header_guard_formatter.hpp"
#include "dogen/cpp/types/formatters/include_cmakelists_formatter.hpp"
#include "dogen/cpp/types/formatters/include_formatter.hpp"
#include "dogen/cpp/types/formatters/includers_formatter.hpp"
#include "dogen/cpp/types/formatters/includers_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/io/class_header_formatter.hpp"
#include "dogen/cpp/types/formatters/io/class_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/io/enricher.hpp"
#include "dogen/cpp/types/formatters/io/enumeration_header_formatter.hpp"
#include "dogen/cpp/types/formatters/io/enumeration_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/io/io.hpp"
#include "dogen/cpp/types/formatters/io/traits.hpp"
#include "dogen/cpp/types/formatters/namespace_formatter.hpp"
#include "dogen/cpp/types/formatters/namespace_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/odb/class_header_formatter.hpp"
#include "dogen/cpp/types/formatters/odb/enricher.hpp"
#include "dogen/cpp/types/formatters/odb/odb.hpp"
#include "dogen/cpp/types/formatters/odb/odb_options_formatter.hpp"
#include "dogen/cpp/types/formatters/odb/settings.hpp"
#include "dogen/cpp/types/formatters/odb/settings_factory.hpp"
#include "dogen/cpp/types/formatters/odb/traits.hpp"
#include "dogen/cpp/types/formatters/odb_options_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/qname_formatter.hpp"
#include "dogen/cpp/types/formatters/registrar_formatter_interface.hpp"
#include "dogen/cpp/types/formatters/serialization/class_header_formatter.hpp"
#include "dogen/cpp/types/formatters/serialization/class_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/serialization/enricher.hpp"
#include "dogen/cpp/types/formatters/serialization/enumeration_header_formatter.hpp"
#include "dogen/cpp/types/formatters/serialization/enumeration_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/serialization/serialization.hpp"
#include "dogen/cpp/types/formatters/serialization/settings.hpp"
#include "dogen/cpp/types/formatters/serialization/settings_factory.hpp"
#include "dogen/cpp/types/formatters/serialization/traits.hpp"
#include "dogen/cpp/types/formatters/source_cmakelists_formatter.hpp"
#include "dogen/cpp/types/formatters/test_data/class_header_formatter.hpp"
#include "dogen/cpp/types/formatters/test_data/class_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/test_data/enricher.hpp"
#include "dogen/cpp/types/formatters/test_data/enumeration_header_formatter.hpp"
#include "dogen/cpp/types/formatters/test_data/enumeration_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/test_data/test_data.hpp"
#include "dogen/cpp/types/formatters/test_data/traits.hpp"
#include "dogen/cpp/types/formatters/types/class_header_formatter.hpp"
#include "dogen/cpp/types/formatters/types/class_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/types/enricher.hpp"
#include "dogen/cpp/types/formatters/types/enumeration_header_formatter.hpp"
#include "dogen/cpp/types/formatters/types/enumeration_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/types/exception_header_formatter.hpp"
#include "dogen/cpp/types/formatters/types/exception_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/types/namespace_header_formatter.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/types/types.hpp"
#include "dogen/cpp/types/formatters/types/visitor_header_formatter.hpp"
#include "dogen/cpp/types/formatters/types/visitor_implementation_formatter.hpp"
#include "dogen/cpp/types/formatters/visitor_formatter_interface.hpp"
#include "dogen/cpp/types/forward_declarations_info.hpp"
#include "dogen/cpp/types/includers_info.hpp"
#include "dogen/cpp/types/includes.hpp"
#include "dogen/cpp/types/inheritance.hpp"
#include "dogen/cpp/types/meta_data/building_error.hpp"
#include "dogen/cpp/types/meta_data/cpp_settings_factory.hpp"
#include "dogen/cpp/types/meta_data/facet_settings_factory.hpp"
#include "dogen/cpp/types/meta_data/traits.hpp"
#include "dogen/cpp/types/namespace_info.hpp"
#include "dogen/cpp/types/nested_type_info.hpp"
#include "dogen/cpp/types/new_class_info.hpp"
#include "dogen/cpp/types/odb_options_info.hpp"
#include "dogen/cpp/types/parent_info.hpp"
#include "dogen/cpp/types/primitive_info.hpp"
#include "dogen/cpp/types/project.hpp"
#include "dogen/cpp/types/property_info.hpp"
#include "dogen/cpp/types/registrar.hpp"
#include "dogen/cpp/types/registrar_error.hpp"
#include "dogen/cpp/types/registrar_info.hpp"
#include "dogen/cpp/types/settings_bundle.hpp"
#include "dogen/cpp/types/state.hpp"
#include "dogen/cpp/types/static_initializer.hpp"
#include "dogen/cpp/types/transformer.hpp"
#include "dogen/cpp/types/visitor_info.hpp"
#include "dogen/cpp/types/workflow.hpp"
