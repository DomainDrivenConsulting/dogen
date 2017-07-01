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
#include "dogen/yarn/types/descriptor.hpp"

namespace dogen {
namespace yarn {

descriptor::descriptor(descriptor&& rhs)
    : path_(std::move(rhs.path_)) { }

descriptor::descriptor(const boost::filesystem::path& path)
    : path_(path) { }

void descriptor::swap(descriptor& other) noexcept {
    using std::swap;
    swap(path_, other.path_);
}

bool descriptor::operator==(const descriptor& rhs) const {
    return path_ == rhs.path_;
}

descriptor& descriptor::operator=(descriptor other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const boost::filesystem::path& descriptor::path() const {
    return path_;
}

boost::filesystem::path& descriptor::path() {
    return path_;
}

void descriptor::path(const boost::filesystem::path& v) {
    path_ = v;
}

void descriptor::path(const boost::filesystem::path&& v) {
    path_ = std::move(v);
}

} }
