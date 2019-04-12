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
#include <unordered_map>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "masd.dogen.utility/types/io/optional_io.hpp"
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.variability/types/entry_selector.hpp"
#include "masd.dogen.variability/types/type_repository_selector.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.coding/types/meta_model/licence.hpp"
#include "masd.dogen.coding/types/meta_model/modeline_group.hpp"
#include "masd.dogen.coding/types/helpers/meta_name_factory.hpp"
#include "masd.dogen.coding/io/meta_model/decoration_io.hpp"
#include "masd.dogen.coding/io/meta_model/technical_space_io.hpp"
#include "masd.dogen.coding/hash/meta_model/technical_space_hash.hpp"
#include "masd.dogen.generation/types/traits.hpp"
#include "masd.dogen.generation/io/meta_model/model_io.hpp"
#include "masd.dogen.generation/types/transforms/transformation_error.hpp"
#include "masd.dogen.generation/types/helpers/decoration_repository_factory.hpp"
#include "masd.dogen.generation/types/formatters/decoration_formatter.hpp"
#include "masd.dogen.generation/io/transforms/decoration_configuration_io.hpp"
#include "masd.dogen.generation/types/transforms/decoration_transform.hpp"

namespace {

const std::string transform_id("generation.transforms.decoration_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string empty;

const std::string licence_not_found("Licence not found: ");
const std::string modeline_group_not_found("Modeline group not found: ");
const std::string modeline_not_found("Modeline not found: ");
const std::string generation_marker_not_found("Generation marker not found: ");
const std::string technical_space_not_found("Technical space not found: ");

}

namespace masd::dogen::generation::transforms {

decoration_transform::type_group decoration_transform::
make_type_group(const variability::type_repository& atrp) {
    type_group r;
    const variability::type_repository_selector s(atrp);

    r.enabled = s.select_type_by_name(traits::decoration::enabled());
    r.copyright_notice =
        s.select_type_by_name(traits::decoration::copyright_notice());
    r.licence_name = s.select_type_by_name(traits::decoration::licence_name());;
    r.modeline_group_name =
        s.select_type_by_name(traits::decoration::modeline_group_name());;
    r.marker_name = s.select_type_by_name(traits::decoration::marker_name());;

    return r;
}

boost::optional<decoration_configuration>
decoration_transform::read_decoration_configuration(const type_group& tg,
    const variability::annotation& a) {

    bool has_configuration(false);
    const variability::entry_selector s(a);
    decoration_configuration r;
    if (s.has_entry(tg.enabled)) {
        r.enabled(s.get_boolean_content(tg.enabled));
        has_configuration = true;
    }

    if (s.has_entry(tg.copyright_notice)) {
        r.copyright_notices(s.get_text_collection_content(tg.copyright_notice));
        has_configuration = true;
    }

    if (s.has_entry(tg.licence_name)) {
        r.licence_name(s.get_text_content(tg.licence_name));
        has_configuration = true;
    }

    if (s.has_entry(tg.modeline_group_name)) {
        r.modeline_group_name(s.get_text_content(tg.modeline_group_name));
        has_configuration = true;
    }

    if (s.has_entry(tg.marker_name)) {
        r.marker_name(s.get_text_content(tg.marker_name));
        has_configuration = true;
    }

    if (has_configuration) {
        BOOST_LOG_SEV(lg, debug) << "Read decoration configuration: " << r;
        return r;
    }

    return boost::optional<decoration_configuration>();
}

bool decoration_transform::
is_generatable(const coding::meta_model::name& meta_name) {
    // FIXME: massive hack for now.
    using mnf = coding::helpers::meta_name_factory;
    static const auto otn(mnf::make_object_template_name());
    static const auto ln(mnf::make_licence_name());
    static const auto mln(mnf::make_modeline_name());
    static const auto mgn(mnf::make_modeline_group_name());
    static const auto gmn(mnf::make_generation_marker_name());

    const auto id(meta_name.qualified().dot());
    return
        id != otn.qualified().dot() &&
        id != ln.qualified().dot() &&
        id != mln.qualified().dot() &&
        id != mgn.qualified().dot() &&
        id != gmn.qualified().dot();
}

boost::optional<coding::meta_model::decoration>
decoration_transform::make_decoration(const std::string& licence_text,
    const boost::shared_ptr<coding::meta_model::modeline> ml,
    const boost::shared_ptr<coding::meta_model::generation_marker> gm,
    const std::list<std::string>& copyright_notices,
    const coding::meta_model::technical_space ts) {

    /*
     * Create the preamble and postamble for the decoration, taking
     * into account the element's technical space.
     */
    using formatters::comment_style;
    using coding::meta_model::technical_space;

    std::ostringstream preamble_stream;
    formatters::decoration_formatter df;
    if (ts == technical_space::cpp) {
        df.format_preamble(preamble_stream,
            comment_style::cpp_style/*single line*/,
            comment_style::c_style/*multi-line*/,
            licence_text, copyright_notices,  ml, gm);
    } else if (ts == technical_space::csharp) {
        df.format_preamble(preamble_stream,
            comment_style::csharp_style,
            licence_text, copyright_notices,  ml, gm);
    } else if (ts == technical_space::cmake || ts == technical_space::odb) {
        df.format_preamble(preamble_stream,
            comment_style::shell_style, licence_text,
            copyright_notices,  ml, gm);
    } else if (ts == technical_space::xml) {
        df.format_preamble(preamble_stream,
            comment_style::xml_style, licence_text,
            copyright_notices,  ml, gm);
    }

    std::ostringstream postamble_stream;
    if (ts == technical_space::cpp)
        df.format_postamble(postamble_stream, comment_style::c_style, ml);
    else if (ts == technical_space::csharp)
        df.format_postamble(postamble_stream, comment_style::csharp_style, ml);

    coding::meta_model::decoration r;
    r.preamble(preamble_stream.str());
    r.postamble(postamble_stream.str());
    return r;
}

std::string decoration_transform::
get_short_form_licence(const helpers::decoration_repository drp,
    const std::string& licence_name) {

    if (licence_name.empty())
        return empty;

    const auto& map(drp.licences_by_name());
    const auto i(map.find(licence_name));
    if (i == map.end()) {
        BOOST_LOG_SEV(lg, error) << licence_not_found << licence_name;
        BOOST_THROW_EXCEPTION(
            transformation_error(licence_not_found + licence_name));
    }
    return i->second->short_form();
}

boost::shared_ptr<coding::meta_model::modeline>
decoration_transform::get_modeline(const helpers::decoration_repository drp,
    const std::string& modeline_group_name,
    const coding::meta_model::technical_space ts) {

    if (modeline_group_name.empty())
        return boost::shared_ptr<coding::meta_model::modeline>();

    const auto& mg_map(drp.modelines_by_modeline_group_by_technical_space());
    const auto i(mg_map.find(modeline_group_name));
    if (i == mg_map.end()) {
        BOOST_LOG_SEV(lg, error) << modeline_group_not_found
                                 << modeline_group_name;
        BOOST_THROW_EXCEPTION(transformation_error(
                modeline_group_not_found + modeline_group_name));
    }

    const auto& ts_map(i->second);
    const auto j(ts_map.find(ts));
    if (j == ts_map.end()) {
        const auto s(boost::lexical_cast<std::string>(ts));
        BOOST_LOG_SEV(lg, error) << technical_space_not_found
                                 << s << " For modeline group: "
                                 << modeline_group_name;
        BOOST_THROW_EXCEPTION(
            transformation_error(technical_space_not_found + s));
    }
    return j->second;
}

boost::shared_ptr<coding::meta_model::generation_marker>
decoration_transform::
get_generation_marker(const helpers::decoration_repository drp,
    const std::string& generation_marker_name) {

    if (generation_marker_name.empty())
        return boost::shared_ptr<coding::meta_model::generation_marker>();

    const auto& map(drp.generation_markers_by_name());
    const auto i(map.find(generation_marker_name));
    if (i == map.end()) {
        BOOST_LOG_SEV(lg, error) << generation_marker_not_found
                                 << generation_marker_name;
        BOOST_THROW_EXCEPTION(transformation_error(generation_marker_not_found
                + generation_marker_name));
    }
    return i->second;
}

boost::optional<coding::meta_model::decoration> decoration_transform::
make_global_decoration(const helpers::decoration_repository drp,
    const boost::optional<decoration_configuration> root_dc,
    const coding::meta_model::technical_space ts) {
    /*
     * If there is no decoration configuration there shall be no
     * decoration either.
     */
    if (!root_dc)
        return boost::optional<coding::meta_model::decoration>();

    /*
     * If the user did not specifically enable decoration in the
     * configuration, there shall be no decoration. Its somewhat
     * confusing that "enabled" is optional here. This makes no sense
     * at the global level, since not supplying the flag is the same
     * as set it to false. However, we also need to cater for the
     * local usage, where we need to be able to distinguish between
     * not supplying the flag versus supplying it and setting it to
     * false.
     */
    const auto& dc(*root_dc);
    if (!dc.enabled() || !(*dc.enabled()))
        return boost::optional<coding::meta_model::decoration>();

    /*
     * Obtain all decoration inputs and create the decoration.
     */
    const auto l(get_short_form_licence(drp, dc.licence_name()));
    const auto ml(get_modeline(drp, dc.modeline_group_name(), ts));
    const auto gm(get_generation_marker(drp, dc.marker_name()));
    const auto r(make_decoration(l, ml, gm, dc.copyright_notices(), ts));

    BOOST_LOG_SEV(lg, trace) << "Created global decoration: " << r;
    return r;
}

boost::optional<coding::meta_model::decoration>
decoration_transform::make_local_decoration(
    const helpers::decoration_repository drp,
    const boost::optional<decoration_configuration> root_dc,
    const boost::optional<coding::meta_model::decoration> global_decoration,
    const boost::optional<decoration_configuration> element_dc,
    const coding::meta_model::technical_space ts) {

    BOOST_LOG_SEV(lg, trace) << "Creating local decoration.";

    /*
     * If there is no local decoration configuration, we just default
     * to the global one whatever it may be - i.e. it may itself not
     * exist either.
     */
    if (!element_dc) {
        BOOST_LOG_SEV(lg, trace) << "No element decoration. "
                                 << "Using global decoration.";
        return global_decoration;
    }

    /*
     * If the user specifically disabled decoration for this modeling
     * element, or if decorations are not enabled locally or globally,
     * there's nothing to do.
     */
    const auto& dc(*element_dc);
    const bool enabled_locally(dc.enabled() && *dc.enabled());
    const bool disabled_locally(dc.enabled() && !(*dc.enabled()));
    const bool enabled_globally(root_dc && root_dc->enabled() &&
        *root_dc->enabled());
    if (disabled_locally || (!enabled_locally && !enabled_globally)) {
        BOOST_LOG_SEV(lg, trace) << "Decoration not enabled. "
                                 << " enabled_locally: " << enabled_locally
                                 << " disabled_locally: " << disabled_locally
                                 << " enabled_globally: " << enabled_globally;
        return boost::optional<coding::meta_model::decoration>();
    }

    /*
     * If there are no local overrides, then just use the global
     * decoration. User just got confused.
     */
    if (dc.copyright_notices().empty() &&
        dc.licence_name().empty() && dc.modeline_group_name().empty() &&
        dc.marker_name().empty()) {
        BOOST_LOG_SEV(lg, trace) << "No overiddes. Using global decoration.";
        return global_decoration;
    }

    /*
     * Retrieve the local decoration inputs.
     */
    const auto ol(get_short_form_licence(drp, dc.licence_name()));
    const auto oml(get_modeline(drp, dc.modeline_group_name(), ts));
    const auto ogm(get_generation_marker(drp, dc.marker_name()));

    /*
     * If we do not have a global decoration configuration, we do not
     * have to worry about overrides, just with processing local
     * decoration configuration.
     */
    if (!root_dc) {
        const auto r(make_decoration(ol, oml, ogm, dc.copyright_notices(), ts));
        BOOST_LOG_SEV(lg, trace) << "Created local decoration without "
                                 << "overrides: " << r;
        return r;
    }

    /*
     * Handle the global overrides.
     */
    const auto overriden_licence(!ol.empty() ? ol :
        get_short_form_licence(drp, root_dc->licence_name()));
    const auto overriden_modeline(oml ? oml :
        get_modeline(drp, root_dc->modeline_group_name(), ts));
    const auto overriden_marker(ogm ? ogm :
        get_generation_marker(drp, root_dc->marker_name()));
    const auto overriden_copyright_notices(!dc.copyright_notices().empty() ?
        dc.copyright_notices() : root_dc->copyright_notices());
    const auto r(make_decoration(overriden_licence, overriden_modeline,
            overriden_marker, overriden_copyright_notices, ts));

    BOOST_LOG_SEV(lg, trace) << "Created local decoration with overrides: " << r;
    return r;
}

void decoration_transform::apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "decoration transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    /*
     * We start by setting up the decoration repository, which has all
     * the required information to build decorations, indexed by the
     * keys we need.
     */
    helpers::decoration_repository_factory f;
    const auto drp(f.make(m));
    BOOST_LOG_SEV(lg, debug) << "Created decoration repository factory.";

    /*
     * Then we obtain the decoration configuration for the root
     * module, which is the default decoration configuration for all
     * model elements.
     */
    const auto tg(make_type_group(*ctx.type_repository()));
    auto& rm(*m.root_module());
    const auto& ra(rm.annotation());
    const auto root_dc(read_decoration_configuration(tg, ra));

    /*
     * With the default configuration, we can create the global
     * decoration for each of the required technical spaces. We can
     * also apply the global configuration to the root module. Note
     * that we know that the root module does not need a technical
     * space override, so we can safely default it to the model
     * technical space.
     */
    const auto mts(m.output_technical_space());
    std::unordered_map<coding::meta_model::technical_space,
                       boost::optional<coding::meta_model::decoration>
                       > root_decorations;
    BOOST_LOG_SEV(lg, trace) << "Generating all global decorations";
    for (const auto ts : m.all_technical_spaces()) {
        BOOST_LOG_SEV(lg, trace) << "Generating global decoration for "
                                 <<  "technical space: " << ts;

        const auto gd(make_global_decoration(drp, root_dc, ts));
        root_decorations[ts] = gd;

        if (ts == mts) {
            BOOST_LOG_SEV(lg, trace) << "Populating the root module "
                                     <<  "decoration.";
            rm.decoration(gd);
        }
    }
    BOOST_LOG_SEV(lg, trace) << "Generated all global decorations.";

    /*
     * Now we loop through all model elements. We obtain each
     * element's decoration configuration, if any, and use it and the
     * root decoration configuration to build the elements decoration.
     */
    const auto root_id(rm.name().qualified().dot());
    const auto ats(coding::meta_model::technical_space::agnostic);
    for (auto e : m.elements()) {
        const auto id(e->name().qualified().dot());
        BOOST_LOG_SEV(lg, trace) << "Processing element: " << id;

        if (e->origin_type() != coding::meta_model::origin_types::target) {
            BOOST_LOG_SEV(lg, trace) << "Element is not in target model.";
            continue;
        }

        /*
         * If the meta-element is intrinsically not generatable, there
         * is no point in creating a decoration for it.
         */
        if (!is_generatable(e->meta_name())) {
            BOOST_LOG_SEV(lg, trace) << "Element is not generatable: "
                                     << e->meta_name().qualified().dot();
            continue;
        }

        /*
         * The root module decoration was already handled and it is
         * different from the rest of the model elements; if we detect
         * it, we need to skip it.
         */
        if (e->name().qualified().dot() == root_id) {
            BOOST_LOG_SEV(lg, trace) << "Element is root module, skipping.";
            continue;
        }

        /*
         * Model elements may not belong to the dominant technical
         * space. If that's the case, we need to ensure we use the
         * element's technical space instead.
         */
        const auto its(e->intrinsic_technical_space());
        const auto ts(its == ats ? mts : its);
        BOOST_LOG_SEV(lg, trace) << "Element intrinsic technical space: " << its
                                 << " Model technical space: " << mts;

        const auto i(root_decorations.find(ts));
        if (i == root_decorations.end()) {
            const auto s(boost::lexical_cast<std::string>(ts));
            BOOST_LOG_SEV(lg, error) << technical_space_not_found << s;
            BOOST_THROW_EXCEPTION(
                transformation_error(technical_space_not_found +s ));
        }
        const auto& gd(i->second);

        /*
         * For all elements (other than the root module), we need to
         * build the decoration based on the local configuration, and
         * the global configuration.
         */
        const auto& a(e->annotation());
        const auto element_dc(read_decoration_configuration(tg, a));
        e->decoration(make_local_decoration(drp, root_dc, gd, element_dc, ts));
    }
    stp.end_transform(m);
}

}
