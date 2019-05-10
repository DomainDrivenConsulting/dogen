# -*- mode: python; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.
#
for layer in dia.active_display().diagram.data.layers:
    for object in layer.objects:
        #
        # Theme: UML elements
        #
        if object.type.name == "UML - Note":
            object.properties["fill_colour"] = "#F0E68C"
            continue;

        if object.type.name == "UML - LargePackage":
            stereotype = object.properties["stereotype"].value
            if "masd::decoration::modeline_group" in stereotype:
                object.properties["fill_colour"] = "#FFEFFE"
            else:
                object.properties["fill_colour"] = "#F5F5F5"
            continue;

        if object.type.name != "UML - Class":
            continue;

        name = object.properties["name"].value
        stereotype = object.properties["stereotype"].value
        #
        # Theme: ORM
        #
        if "masd::orm::object" in stereotype:
            object.properties["fill_colour"] = "#98FB98"
        elif "masd::orm::value" in stereotype:
            object.properties["fill_colour"] = "#DDA0DD"
        #
        # Theme: Manually generated
        #
        elif "masd::handcrafted::typeable" in stereotype:
            object.properties["fill_colour"] = "#FFFACD"
        elif "masd::cpp::header_only" in stereotype:
            object.properties["fill_colour"] = "#FFFACD"
        elif "masd::cpp::implementation_only" in stereotype:
            object.properties["fill_colour"] = "#EEFACD"

        #
        # Theme: Decorations
        #
        elif "masd::decoration::modeline" in stereotype:
            object.properties["fill_colour"] = "#DDB7B7"
        elif "masd::decoration::licence" in stereotype:
            object.properties["fill_colour"] = "#DDB7DD"
        elif "masd::decoration::generation_marker" in stereotype:
            object.properties["fill_colour"] = "#ACACBB"

        #
        # Theme: variability
        #
        elif "masd::variability::profile_template" in stereotype:
            object.properties["fill_colour"] = "#EDE6F2"
        elif "masd::variability::feature_bundle" in stereotype:
            object.properties["fill_colour"] = "#B2E2E2"
        elif "masd::variability::feature_template_initializer" in stereotype:
            object.properties["fill_colour"] = "#B2E2E2"

        #
        # Theme: Core meta-elements
        #
        elif "masd::enumeration" in stereotype:
            object.properties["fill_colour"] = "#FFEFD5"
        elif "masd::primitive" in stereotype:
            object.properties["fill_colour"] = "#B0C4DE"
        elif "masd::exception" in stereotype:
            object.properties["fill_colour"] = "#FFDAB9"
        elif "masd::object_template" in stereotype:
            object.properties["fill_colour"] = "#EED2DE"
        elif "masd::object_template" in stereotype:
            object.properties["fill_colour"] = "#EED2DE"
        else:
            object.properties["fill_colour"] = "#F5FFFA"
