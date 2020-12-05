#include "widgets.hpp"

namespace otto::engines::ottofm {

  void ADSR::do_draw(skia::Canvas& ctx)
  {
    // If your are using a different anchor/origin than TopLeft for the coordinate system, translate here
    // graphics::Point diff = bounding_box.get_diff(anchors::top_left,
    // anchors::top_left); ctx.translate(diff[0], diff[1]);

    const float width = bounding_box.width();
    const float height = bounding_box.height();
    const float spacing = width / 16.f;
    const float max_width = width / 3.f;
    const float aw = max_width * a;
    const float dw = max_width * d;
    const float sh = height * s;
    const float rw = max_width * r;

    const float arc_size = 0.9;

    SkPath p;
    p.moveTo(0, height);
    p.quadTo(aw * arc_size, height * arc_size, aw, 0); // curve
    p.lineTo(aw, height);
    p.close();
    ctx.drawPath(p, paints::fill(colors::blue));

    p.reset();

    p.moveTo(aw + spacing, height);
    p.lineTo(aw + spacing, 0);
    p.quadTo(aw + spacing + dw * (1 - arc_size), (height - sh) * arc_size, aw + spacing + dw, height - sh); // curve
    p.lineTo(aw + spacing + dw, height);
    p.close();
    ctx.drawPath(p, paints::fill(colors::green));

    p.reset();

    p.moveTo(aw + spacing + dw + spacing, height - sh);
    p.lineTo(width - spacing - rw, height - sh);
    p.lineTo(width - spacing - rw, height);
    p.lineTo(aw + spacing + dw + spacing, height);
    p.close();
    ctx.drawPath(p, paints::fill(colors::yellow));

    p.reset();

    p.moveTo(width - rw, height);
    p.lineTo(width - rw, height - sh);
    p.quadTo(width - rw * arc_size, height - sh * (1 - arc_size), width, height);
    p.close();
    ctx.drawPath(p, paints::fill(colors::red));
  }

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
        float y_end = operator_size + (3 - line.end) * space;
        path.moveTo(x_middle, y_start);
        path.lineTo(x_middle, y_end);
        path.lineTo(x_middle, y_end);
        path.lineTo(x_middle, y_end);
      }
      ctx.drawPath(path, paints::stroke(colors::white, 6.f));
    }

    // draw operators
    for (int i = 0; i < 4; i++) {
      float level = activity_levels[i];
      // Choose colour
      const auto color = operator_colours[i].mix(colors::white, 0.5f * static_cast<float>(i == cur_op));

      if (algorithms[algorithm_idx].modulator_flags[i]) { // draw modulator
        SkRect rect = SkRect::MakeXYWH(x_middle - operator_radius * square_scale, static_cast<float>(3 - i) * space,
                                       operator_size * square_scale, operator_size * square_scale);
        if (i == cur_op) ctx.drawRect(rect, paints::fill(colors::white));
        ctx.drawRect(rect, paints::stroke(color, 4.f));
        // Draw activity level
        rect.inset(operator_radius * square_scale * (1 - level), operator_radius * square_scale * (1 - level));
        ctx.drawRect(rect, paints::fill(color));

      } else { // draw carrier
        float y_pos = operator_radius + static_cast<float>(3 - i) * space;
        if (i == cur_op) ctx.drawCircle(x_middle, y_pos, operator_radius, paints::fill(colors::white));
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

  void FractionGraphic::do_draw(skia::Canvas& ctx)
  {
    bounding_box.resize({40, 20 + expansion * 20});
    const auto color = active ? colors::blue : colors::grey50;

    const float width = bounding_box.width();

    // Bottom Text
    auto ratio_bounds = skia::place_text(ctx, "RATIO", fonts::regular(12), color.fade(1 - expansion),
                                         bounding_box.point(anchors::bottom_center),
                                         interpolate(anchors::top_center, anchors::bottom_center, expansion));

    // Text
    skia::place_text(ctx, std::to_string(numerator), fonts::regular(20), paints::fill(color), {0, 0},
                     anchors::top_left);
    auto font = fonts::regular(denominator >= 10 ? 16 : 20);
    float denominator_y = ratio_bounds.y(anchors::top_left) - 6.f;
    skia::place_text(ctx, std::to_string(denominator), font, color, {width, denominator_y}, anchors::bottom_right);

    //  Line
    SkPath path;
    // It's hard to align text. Use this to adjust manually
    constexpr float pad = 10.f;
    path.moveTo(interpolate(width * 0.5f, width - pad, expansion), 0);
    path.lineTo(interpolate(width * 0.5f, pad, expansion), denominator_y);
    ctx.drawPath(path, paints::stroke(color, 3.f));

    // paint.setColor(mix(colors::black, paint.getColor(), expansion));
  }

  void DetuneGraphic::do_draw(skia::Canvas& ctx)
  {
    skia::Paint paint;
    if (active) {
      paint = paints::fill(colors::blue);
    } else {
      paint = paints::fill(colors::grey50);
    }

    sk_sp<SkTextBlob> val;
    if (value == 0) {
      val = SkTextBlob::MakeFromString("±.0", fonts::regular(20));
    } else if (value > 0) {
      val = SkTextBlob::MakeFromString(fmt::format("+.{}", (int) std::abs(value * 10)).c_str(), fonts::regular(20));
    } else {
      val = SkTextBlob::MakeFromString(fmt::format("-.{}", (int) std::abs(value * 10)).c_str(), fonts::regular(20));
    }
    sk_sp<SkTextBlob> dtune = SkTextBlob::MakeFromString("DTUNE", fonts::regular(12));
    SkRect rect = SkRect();
    auto font = fonts::regular(20);
    font.measureText("3", 1, SkTextEncoding(), &rect, &paint);
    ctx.drawTextBlob(val.get(), 0,
                     rect.height() + expansion * (0.6f * 0.5f * bounding_box.height() - rect.height() / 2.f), paint);
    paint.setColor(skia::Color(paint.getColor()).fade(1.f - expansion));
    ctx.drawTextBlob(dtune.get(), 0, bounding_box.height(), paint);
  }

  void LevelGraphic::do_draw(skia::Canvas& ctx)
  {
    float rotation_scale = 270.f * expansion + 180.f * (1 - expansion);
    // Anchor is center
    skia::Point diff = bounding_box.diff(anchors::top_left, anchors::center);
    skia::translate(ctx, diff);

    const float radius = bounding_box.width() / 2.f;
    const float radius_line1 = radius * 0.9f;
    // const float radius_line2 = radius * 0.6f;
    auto color = active ? colors::green : colors::grey50;

    // Arc
    skia::Rect rect = SkRect::MakeXYWH(-radius_line1, -radius_line1, 2.f * radius_line1, 2.f * radius_line1);
    skia::Path path;
    path.arcTo(rect, -90.f - 0.5f * rotation_scale, rotation_scale, false);
    ctx.drawPath(path, paints::stroke(color.fade(0.7), 4.f));

    // Level indicator
    ctx.drawCircle({0, 0}, 3.f, paints::fill(color));
    {
      ctx.save();
      ctx.rotate((value - 0.5f) * rotation_scale);
      skia::Path path;
      path.moveTo(0, 0);
      path.lineTo(0, -radius);
      ctx.drawPath(path, paints::stroke(color, 3));
      ctx.restore();
    }

    // Text
    skia::place_text(ctx, "LVL", fonts::regular(12), colors::green.fade(1 - expansion), {0, radius},
                     anchors::bottom_center);
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
    // skia::Point diff = bounding_box.get_diff(anchors::top_left,
    // anchors::middle_left); ctx.save(); ctx.translate(diff[0], diff[1]);

    float step = bounding_box.width() / sinewave.size();
    float scale = 0.5f * (bounding_box.height() * 0.5f * (1 - expansion) + bounding_box.height() * 0.6f * expansion);
    l_value = std::max(0.f, (0.5f - value) * 2.f);
    r_value = std::max(0.f, (value - 0.5f) * 2.f);

    SkPath path;
    path.moveTo(0, scale);
    float x = 0;
    int i = 0;
    for (auto& s : sinewave) {
      path.lineTo(x, scale * (1 + s + l_value * left_harmonics[i] + r_value * right_harmonics[i]));
      x += step;
      i++;
    }
    auto color = active ? colors::yellow : colors::grey50;
    ctx.drawPath(path, paints::stroke(color, 3.f));

    // Bottom Text
    sk_sp<SkTextBlob> shape_text = SkTextBlob::MakeFromString("SHAPE", fonts::regular(12));
    // paint.setColor(mix(colors::black, paint.getColor(), expansion));
    ctx.drawTextBlob(shape_text.get(), 0, bounding_box.height(), paints::fill(colors::yellow.fade(1 - expansion)));
  }
} // namespace otto::engines::ottofm
