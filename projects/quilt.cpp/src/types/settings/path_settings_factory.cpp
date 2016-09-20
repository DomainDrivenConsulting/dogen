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
#include "dogen/dynamic/types/field_selector.hpp"
#include "dogen/dynamic/types/repository_selector.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/types/settings/building_error.hpp"
#include "dogen/quilt.cpp/types/settings/path_settings_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.settings.path_settings_factory"));

const std::string empty_formatter_name("Formatter name is empty.");

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace settings {

path_settings_factory::
path_settings_factory(const dynamic::repository& rp,
    const std::forward_list<
    std::shared_ptr<formatters::file_formatter_interface>>& formatters)
    : field_definitions_(make_field_definitions(rp, formatters)) { }

void path_settings_factory::setup_top_level_fields(
    const dynamic::repository& rp, field_definitions& fd) const {

    const dynamic::repository_selector s(rp);
    const auto& idn(traits::cpp::include_directory_name());
    fd.include_directory_name = s.select_field_by_name(idn);

    const auto& sdn(traits::cpp::source_directory_name());
    fd.source_directory_name = s.select_field_by_name(sdn);

    const auto& hde(traits::cpp::header_file_extension());
    fd.header_file_extension = s.select_field_by_name(hde);

    const auto& ife(traits::cpp::implementation_file_extension());
    fd.implementation_file_extension = s.select_field_by_name(ife);

    const auto& dfd(traits::cpp::disable_facet_directories());
    fd.disable_facet_directories = s.select_field_by_name(dfd);
}

void path_settings_factory::setup_facet_fields(
    const dynamic::repository& rp,
    const std::string& facet_name,
    path_settings_factory::field_definitions& fd) const {

    const auto& fn(facet_name);
    const dynamic::repository_selector s(rp);

    auto dir(s.try_select_field_by_name(fn, traits::directory()));
    if (dir)
        fd.facet_directory = *dir;

    auto postfix(s.try_select_field_by_name(fn, traits::postfix()));
    if (postfix)
        fd.facet_postfix = *postfix;
}

void path_settings_factory::setup_formatter_fields(
    const dynamic::repository& rp,
    const std::string& formatter_name,
    path_settings_factory::field_definitions& fd) const {

    const auto& fn(formatter_name);
    const dynamic::repository_selector s(rp);
    fd.formatter_postfix = s.select_field_by_name(fn, traits::postfix());
}

path_settings_factory::field_definitions
path_settings_factory::make_field_definitions(
    const dynamic::repository& rp,
    const formatters::file_formatter_interface& f) const {

    field_definitions r;
    r.file_type = f.file_type();
    const auto oh(f.ownership_hierarchy());
    r.formatter_name = oh.formatter_name();
    setup_top_level_fields(rp, r);
    setup_facet_fields(rp, oh.facet_name(), r);
    setup_formatter_fields(rp, oh.formatter_name(), r);

    return r;
}

std::unordered_map<std::string, path_settings_factory::field_definitions>
path_settings_factory::make_field_definitions(
    const dynamic::repository& rp,
    const std::forward_list<
    std::shared_ptr<formatters::file_formatter_interface>>& formatters) const {
    std::unordered_map<std::string, field_definitions> r;

    for (const auto f : formatters) {
        const auto& oh(f->ownership_hierarchy());
        if (oh.formatter_name().empty()) {
            BOOST_LOG_SEV(lg, error) << empty_formatter_name;
            BOOST_THROW_EXCEPTION(building_error(empty_formatter_name));
        }
        r[oh.formatter_name()] = make_field_definitions(rp, *f);
    }

    return r;
}

path_settings path_settings_factory::
create_settings_for_formatter(const field_definitions& fd,
    const dynamic::object& o) const {

    path_settings r;
    r.file_type(fd.file_type);

    const dynamic::field_selector fs(o);

    if (fd.facet_directory)
        r.facet_directory(fs.get_text_content_or_default(*fd.facet_directory));

    if (fd.facet_postfix)
        r.facet_postfix(fs.get_text_content_or_default(*fd.facet_postfix));

    r.formatter_postfix(fs.get_text_content_or_default(fd.formatter_postfix));

    const auto& hfe(fd.header_file_extension);
    r.header_file_extension(fs.get_text_content_or_default(hfe));

    const auto& ife(fd.implementation_file_extension);
    r.implementation_file_extension(fs.get_text_content_or_default(ife));

    const auto& idn(fd.include_directory_name);
    r.include_directory_name(fs.get_text_content_or_default(idn));

    const auto& sdn(fd.source_directory_name);
    r.source_directory_name(fs.get_text_content_or_default(sdn));

    const auto& dfd(fd.disable_facet_directories);
    r.disable_facet_directories(fs.get_boolean_content_or_default(dfd));

    return r;
}

std::unordered_map<std::string, path_settings> path_settings_factory::
make(const dynamic::object& o) const {
    std::unordered_map<std::string, path_settings> r;
    for (const auto& pair : field_definitions_) {
        const auto& fd(pair.second);
        const auto s(create_settings_for_formatter(fd, o));
        r.insert(std::make_pair(fd.formatter_name, s));
    }
    return r;
}

} } } }
