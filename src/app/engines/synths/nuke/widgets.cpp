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

  namespace {
    skia::Box get_content_box(float expansion)
    {
      auto bounds = skia::Box().resized({50, 15 + expansion * 35});
      return interpolate(bounds, bounds.resized({bounds.width(), bounds.height() - 8}), expansion);
    }
    skia::Box draw_label(skia::Canvas& ctx,
                         std::string_view label,
                         skia::Color color,
                         float expansion,
                         skia::Vector offset = {0, 0})
    {
      auto bounds = get_content_box(expansion);
      auto point = bounds.point(anchors::bottom_center) + skia::Point{0, 2};
      return skia::place_text(ctx, label, fonts::regular(16), color.fade(1 - expansion), point, anchors::top_center);
    }
  } // namespace

  void Level::do_draw(skia::Canvas& ctx)
  {
    bounding_box.resize({50, 15 + expansion * 35});
    float rotation_scale = interpolate(180.f, 260.f, expansion);
    skia::Point center = bounding_box.point(interpolate(anchors::bottom_center, anchors::center, expansion));

    const float radius = bounding_box.width() / 2.f;
    const float radius_line1 = radius * 0.9f;
    // const float radius_line2 = radius * 0.6f;
    const auto color = active ? color_ : colors::grey50;

    // Arc
    const auto box = skia::Box().resized({radius_line1 * 2, radius_line1 * 2}).moved_to(center, anchors::center);
    skia::Path path;
    path.arcTo(box, -90.f - 0.5f * rotation_scale, rotation_scale, false);
    ctx.drawPath(path, paints::stroke(color.fade(0.7), 4.f));

    // Level indicator
    ctx.drawCircle(center, 3.f, paints::fill(color));
    skia::saved(ctx, [&] {
      skia::rotate(ctx, (value - 0.5f) * rotation_scale, center);
      skia::Path path;
      path.moveTo(center);
      path.lineTo(center - skia::Vector{0, radius});
      ctx.drawPath(path, paints::stroke(color, 3));
    });

    draw_label(ctx, title_.c_str(), color, expansion);
  }

} // namespace otto::engines::nuke
