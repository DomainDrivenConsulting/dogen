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
#include "dogen.engine/types/transforms/context.hpp"

namespace dogen::engine::transforms {

context::context(
    const dogen::variability::transforms::context& variability_context,
    const dogen::injection::transforms::context& injection_context,
    const dogen::assets::transforms::context& assets_context,
    const dogen::generation::transforms::context& generation_context,
    const dogen::extraction::transforms::context& extraction_context)
    : variability_context_(variability_context),
      injection_context_(injection_context),
      assets_context_(assets_context),
      generation_context_(generation_context),
      extraction_context_(extraction_context) { }

const dogen::variability::transforms::context& context::variability_context() const {
    return variability_context_;
}

dogen::variability::transforms::context& context::variability_context() {
    return variability_context_;
}

void context::variability_context(const dogen::variability::transforms::context& v) {
    variability_context_ = v;
}

void context::variability_context(const dogen::variability::transforms::context&& v) {
    variability_context_ = std::move(v);
}

const dogen::injection::transforms::context& context::injection_context() const {
    return injection_context_;
}

dogen::injection::transforms::context& context::injection_context() {
    return injection_context_;
}

void context::injection_context(const dogen::injection::transforms::context& v) {
    injection_context_ = v;
}

void context::injection_context(const dogen::injection::transforms::context&& v) {
    injection_context_ = std::move(v);
}

const dogen::assets::transforms::context& context::assets_context() const {
    return assets_context_;
}

dogen::assets::transforms::context& context::assets_context() {
    return assets_context_;
}

void context::assets_context(const dogen::assets::transforms::context& v) {
    assets_context_ = v;
}

void context::assets_context(const dogen::assets::transforms::context&& v) {
    assets_context_ = std::move(v);
}

const dogen::generation::transforms::context& context::generation_context() const {
    return generation_context_;
}

dogen::generation::transforms::context& context::generation_context() {
    return generation_context_;
}

void context::generation_context(const dogen::generation::transforms::context& v) {
    generation_context_ = v;
}

void context::generation_context(const dogen::generation::transforms::context&& v) {
    generation_context_ = std::move(v);
}

const dogen::extraction::transforms::context& context::extraction_context() const {
    return extraction_context_;
}

dogen::extraction::transforms::context& context::extraction_context() {
    return extraction_context_;
}

void context::extraction_context(const dogen::extraction::transforms::context& v) {
    extraction_context_ = v;
}

void context::extraction_context(const dogen::extraction::transforms::context&& v) {
    extraction_context_ = std::move(v);
}

}
