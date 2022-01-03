#include "widgets.hpp"

namespace otto::engines::ottofm {

  void Operators::do_draw(skia::Canvas& ctx)
  {
    // Anchor is TopLeft
    const float width = bounding_box.width();
    const float height = bounding_box.height();
    const float operator_size = width / 2.f;
    const float operator_radius = operator_size / 2.f;
    constexpr float square_scale = 0.9f;
    float space = (height - operator_size) / 3.f;

    // Draw lines between operators
    float x_middle = width / 2.f;
    constexpr float line_shift = 0.f;
    float x_left = x_middle - operator_radius - line_shift;
    float x_right = x_middle + operator_radius + line_shift;
    for (auto&& line : algorithms[algorithm_idx].operator_lines) {
      SkPath path;
      if (line.side == Drawside::left) {
        float y_start = operator_size / 2.f + (3.f - line.start) * space;
        float y_end = operator_size / 2.f + (3.f - line.end) * space;
        path.moveTo(x_left, y_start);
        path.lineTo(0, y_start);
        path.lineTo(0, y_end);
        path.lineTo(x_left, y_end);
      } else if (line.side == Drawside::right) {
        float y_start = operator_size / 2.f + (3 - line.start) * space;
        float y_end = operator_size / 2.f + (3 - line.end) * space;
        path.moveTo(x_right, y_start);
        path.lineTo(width, y_start);
        path.lineTo(width, y_end);
        path.lineTo(x_right, y_end);
      } else {
        float y_start = operator_size + (3 - line.start) * space;
        float y_end = (3 - line.end) * space;
        path.moveTo(x_middle, y_start);
        path.lineTo(x_middle, y_end);
      }
      ctx.drawPath(path, paints::stroke(colors::white, 6.f));
    }

    // draw operators
    for (int i = 0; i < 4; i++) {
      float level = activity_levels[i];
      bool active = i == cur_op;
      // Choose colour
      const auto color = operator_colours[i].mix(colors::white, 0.5f * static_cast<float>(active));

      if (algorithms[algorithm_idx].modulator_flags[i]) { // draw modulator
        SkRect rect = SkRect::MakeXYWH(x_middle - operator_radius * square_scale, static_cast<float>(3 - i) * space,
                                       operator_size * square_scale, operator_size * square_scale);
        if (active) ctx.drawRect(rect, paints::fill(colors::white));
        ctx.drawRect(rect, paints::stroke(color, 4.f));
        // Draw activity level
        rect.inset(operator_radius * square_scale * (1 - level), operator_radius * square_scale * (1 - level));
        ctx.drawRect(rect, paints::fill(color));

      } else { // draw carrier
        float y_pos = operator_radius + static_cast<float>(3 - i) * space;
        if (active) ctx.drawCircle(x_middle, y_pos, operator_radius, paints::fill(colors::white));
        ctx.drawCircle(x_middle, y_pos, operator_radius, paints::stroke(color, 4.f));
        // Draw activity level
        ctx.drawCircle(x_middle, y_pos, operator_radius * level, paints::fill(color));
      }
    }

    // draw arrowheads
    float side_length = 5;
    SkPath path;
    for (auto&& line : algorithms[algorithm_idx].operator_lines) {
      if (line.side == Drawside::left) {
        float y = operator_radius + (3.f - line.end) * space;
        path.moveTo(x_left, y);
        path.lineTo(x_left - side_length, y - side_length);
        path.lineTo(x_left - side_length, y + side_length);
        path.close();
      } else if (line.side == Drawside::right) {
        float y = operator_radius + (3.f - line.end) * space;
        path.moveTo(x_right, y);
        path.lineTo(x_right + side_length, y - side_length);
        path.lineTo(x_right + side_length, y + side_length);
        path.close();
      } else {
        float y = (3 - line.end) * space;
        path.moveTo(x_middle, y);
        path.lineTo(x_middle + side_length, y - side_length);
        path.lineTo(x_middle - side_length, y - side_length);
        path.close();
      }
      ctx.drawPath(path, paints::stroke_and_fill(colors::white, 4.f));
    }
  }

  namespace {
    skia::Box get_content_box(float expansion)
    {
      auto bounds = skia::Box().resized({40, 20 + expansion * 20});
      return interpolate(bounds, bounds.resized({bounds.width(), bounds.height() - 14}), expansion);
    }
    skia::Box draw_label(skia::Canvas& ctx,
                         std::string_view label,
                         skia::Color color,
                         float expansion,
                         skia::Vector offset = {0, 0})
    {
      auto bounds = get_content_box(expansion);
      auto point = bounds.point(anchors::bottom_center) + skia::Point{0, 2};
      return skia::place_text(ctx, label, fonts::regular(12), color.fade(1 - expansion), point, anchors::top_center);
    }
  } // namespace

  void FractionGraphic::do_draw(skia::Canvas& ctx)
  {
    bounding_box.resize({40, 20 + expansion * 20});
    auto content_box = get_content_box(expansion);
    const auto color = active ? colors::green : colors::grey50;

    const float width = bounding_box.width();
    draw_label(ctx, "RATIO", color, expansion);

    // Text
    auto font = fonts::regular(numerator >= 10 ? 16 : 20);
    auto num_box = skia::place_text(ctx, std::to_string(numerator), font, paints::fill(color), content_box,
                                    interpolate(anchors::middle_left, anchors::top_left, expansion));
    font = fonts::regular(denominator >= 10 ? 16 : 20);
    float denominator_y = content_box.height();
    auto den_box = skia::place_text(ctx, std::to_string(denominator), font, color, content_box,
                                    interpolate(anchors::middle_right, anchors::bottom_right, expansion));

    //  Line
    SkPath path;
    // It's hard to align text. Use this to adjust manually
    constexpr float pad = 10.f;
    auto middle = interpolate(num_box.width(), den_box.x(), 0.5);
    path.moveTo(interpolate(middle, width - pad, expansion), 0);
    path.lineTo(interpolate(middle, pad, expansion), denominator_y);
    ctx.drawPath(path, paints::stroke(color, 3.f));
  }

  void DetuneGraphic::do_draw(skia::Canvas& ctx)
  {
    bounding_box.resize({40, 20 + expansion * 20});
    auto color = active ? colors::green : colors::grey50;

    std::string prefix;
    int int_val = static_cast<int>(std::round(value * 0.99f * 100.f));
    if (int_val == 0) {
      prefix = "±";
    } else if (int_val > 0) {
      prefix = "+";
    } else {
      prefix = "-";
    }

    const auto content_box = get_content_box(expansion);

    draw_label(ctx, "DTUNE", color, expansion);
    const auto font = fonts::regular(20);
    const auto alloc = skia::measureText(font, "+.00").aligned(content_box, anchors::center);
    const auto pref_width = skia::measureText(font, "+").width();
    skia::place_text(ctx, prefix, font, color, alloc.resized({pref_width, alloc.height()}), anchors::center);
    skia::place_text(ctx, fmt::format(".{:02}", std::abs(int_val)), font, color, alloc.moved_by({pref_width, 0}),
                     anchors::middle_left);
  }

  void LevelGraphic::do_draw(skia::Canvas& ctx)
  {
    bounding_box.resize({40, 20 + expansion * 20});
    float rotation_scale = interpolate(180.f, 260.f, expansion);
    skia::Point center = bounding_box.point(interpolate(anchors::bottom_center, anchors::center, expansion));

    const float radius = bounding_box.width() / 2.f;
    const float radius_line1 = radius * 0.9f;
    // const float radius_line2 = radius * 0.6f;
    const auto color = active ? colors::yellow : colors::grey50;

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

    draw_label(ctx, "LVL", color, expansion);
  }

  // WaveShapeGraphic

  WaveShapeGraphic::WaveShapeGraphic()
  {
    int i = 0;
    for (auto& w : sinewave) {
      w = sin(2.f * M_PI * (float) i / 30.f);
      i++;
    }
    i = 0;
    for (auto& w : right_harmonics) {
      w = -0.5 * sin(4 * M_PI * (float) i / 30.f) + 0.33 * sin(6.f * M_PI * (float) i / 30.f) -
          0.25 * sin(8.f * M_PI * (float) i / 30.f);
      i++;
    }
    i = 0;
    for (auto& w : left_harmonics) {
      w = 0.33f * sin(6.f * M_PI * (float) i / 30.f) + 0.2f * sin(10.f * M_PI * (float) i / 30.f) +
          0.14f * sin(14.f * M_PI * (float) i / 30.f);
      i++;
    }
  }

  void WaveShapeGraphic::do_draw(skia::Canvas& ctx)
  {
    bounding_box.resize({40, 20 + expansion * 20});
    const auto content_box = get_content_box(expansion);
    // skia::Point diff = bounding_box.get_diff(anchors::top_left,
    // anchors::middle_left); ctx.save(); ctx.translate(diff[0], diff[1]);

    float step = content_box.width() / sinewave.size();
    l_value = std::max(0.f, (0.5f - value) * 2.f);
    r_value = std::max(0.f, (value - 0.5f) * 2.f);
    float scale = 0.5f * content_box.height();
    SkPath path;
    path.moveTo(0, scale);
    float x = 0;
    int i = 0;
    for (auto& s : sinewave) {
      path.lineTo(x, scale * (1 + (s + l_value * left_harmonics[i] + r_value * right_harmonics[i]) / (1 + r_value)));
      x += step;
      i++;
    }
    auto color = active ? colors::red : colors::grey50;
    ctx.drawPath(path, paints::stroke(color, 3.f));

    // Bottom Text
    draw_label(ctx, "SHAPE", color, expansion);
  }
} // namespace otto::engines::ottofm
