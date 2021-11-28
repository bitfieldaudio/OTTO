#include "widgets.hpp"

namespace otto::engines::nuke {

  void FourParams::do_draw(skia::Canvas& ctx)
  {
    // A simple starting point for showing 4 parameters

    const float width = bounding_box.width();
    const float height = bounding_box.height();
    const float spacing = height / 4.0;

    skia::place_text(ctx, title, fonts::regular(24), colors::white, {width / 2.0, 0}, anchors::top_center);

    skia::place_text(ctx, params[0], fonts::regular(24), colors::blue, {0, spacing}, anchors::top_left);
    skia::place_text(ctx, fmt::format("{:1.2}", a), fonts::regular(24), colors::blue, {width, spacing},
                     anchors::top_right);

    skia::place_text(ctx, params[1], fonts::regular(24), colors::green, {0, 2 * spacing}, anchors::top_left);
    skia::place_text(ctx, fmt::format("{:1.2}", b), fonts::regular(24), colors::green, {width, 2 * spacing},
                     anchors::top_right);

    skia::place_text(ctx, params[2], fonts::regular(24), colors::yellow, {0, 3 * spacing}, anchors::top_left);
    skia::place_text(ctx, fmt::format("{:1.2}", c), fonts::regular(24), colors::yellow, {width, 3 * spacing},
                     anchors::top_right);

    skia::place_text(ctx, params[3], fonts::regular(24), colors::red, {0, 4 * spacing}, anchors::top_left);
    skia::place_text(ctx, fmt::format("{:1.2}", d), fonts::regular(24), colors::red, {width, 4 * spacing},
                     anchors::top_right);
  }

  void FourParams::set(const std::array<float, 4>& t)
  {
    a = t[0];
    b = t[1];
    c = t[2];
    d = t[3];
  }

} // namespace otto::engines::nuke
