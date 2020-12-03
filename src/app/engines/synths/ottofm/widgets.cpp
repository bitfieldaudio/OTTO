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

    skia::Paint paint;
    paint.setStyle(skia::Paint::kStrokeAndFill_Style);

    const float arc_size = 0.9;

    SkPath p;
    p.moveTo(0, height);
    p.quadTo(aw * arc_size, height * arc_size, aw, 0); // curve
    p.lineTo(aw, height);
    p.close();
    paint.setColor(colors::blue);
    ctx.drawPath(p, paint);

    p.reset();

    p.moveTo(aw + spacing, height);
    p.lineTo(aw + spacing, 0);
    p.quadTo(aw + spacing + dw * (1 - arc_size), (height - sh) * arc_size, aw + spacing + dw, height - sh); // curve
    p.lineTo(aw + spacing + dw, height);
    p.close();
    paint.setColor(colors::green);
    ctx.drawPath(p, paint);

    p.reset();

    p.moveTo(aw + spacing + dw + spacing, height - sh);
    p.lineTo(width - spacing - rw, height - sh);
    p.lineTo(width - spacing - rw, height);
    p.lineTo(aw + spacing + dw + spacing, height);
    p.close();
    paint.setColor(colors::yellow);
    ctx.drawPath(p, paint);

    p.reset();

    p.moveTo(width - rw, height);
    p.lineTo(width - rw, height - sh);
    p.quadTo(width - rw * arc_size, height - sh * (1 - arc_size), width, height);
    p.close();
    paint.setColor(colors::red);
    ctx.drawPath(p, paint);
  }

  void Operators::do_draw(skia::Canvas& ctx)
  {
    // Anchor is TopLeft
    skia::Paint paint;
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
      paint.setColor(colors::white);
      ctx.drawPath(path, paint);
    }

    // draw operators
    skia::Paint fillPaint;
    skia::Paint strokePaint;
    fillPaint.setStyle(skia::Paint::kFill_Style);
    fillPaint.setColor(colors::white);
    for (int i = 0; i < 4; i++) {
      float level = activity_levels[i];
      // Choose colour
      strokePaint.setColor(operator_colours[i].mix(colors::white, 0.5f * static_cast<float>(i == cur_op)));

      if (algorithms[algorithm_idx].modulator_flags[i]) { // draw modulator
        SkRect rect = SkRect::MakeXYWH(x_middle - operator_radius * square_scale, static_cast<float>(3 - i) * space,
                                       operator_size * square_scale, operator_size * square_scale);
        if (i == cur_op) ctx.drawRect(rect, fillPaint);
        ctx.drawRect(rect, strokePaint);
        // Draw activity level
        fillPaint.setColor(operator_colours[i].mix(colors::white, 0.5f * static_cast<float>(i == cur_op)));
        rect.inset(operator_radius * square_scale * (1 - level), operator_radius * square_scale * (1 - level));
        ctx.drawRect(rect, fillPaint);

      } else { // draw carrier
        float y_pos = operator_radius + static_cast<float>(3 - i) * space;
        if (i == cur_op) ctx.drawCircle(x_middle, y_pos, operator_radius, fillPaint);
        ctx.drawCircle(x_middle, y_pos, operator_radius, strokePaint);
        // Draw activity level
        fillPaint.setColor(operator_colours[i].mix(colors::white, 0.5f * static_cast<float>(i == cur_op)));
        ctx.drawCircle(x_middle, y_pos, operator_radius * level, fillPaint);
      }
    }

    // draw arrowheads
    strokePaint.setStrokeWidth(4.f);
    strokePaint.setColor(colors::white);
    strokePaint.setStyle(skia::Paint::kStrokeAndFill_Style);
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
      ctx.drawPath(path, strokePaint);
    }
  }

  void FractionGraphic::do_draw(skia::Canvas& ctx)
  {
    skia::Paint paint;
    if (active) {
      paint.setColor(colors::blue);
    } else {
      paint.setColor(colors::grey50);
    }

    const float width = bounding_box.width();
    const float height = bounding_box.height();

    // Text
    paint.setStrokeWidth(2.f);
    paint.setStyle(skia::Paint::kStrokeAndFill_Style);
    sk_sp<SkTextBlob> n = SkTextBlob::MakeFromString(std::to_string(numerator).c_str(), SkFont(nullptr, 20));
    sk_sp<SkTextBlob> d = SkTextBlob::MakeFromString(std::to_string(denominator).c_str(), SkFont(nullptr, 20));
    // SkRect db = d.bounds();
    // paint.setTextAlign(SK_TextAlign::Left);
    SkRect rect = SkRect();
    SkFont font = SkFont(nullptr, 20);
    SkScalar wid = font.measureText("3", 1, SkTextEncoding(), &rect, &paint);
    ctx.drawTextBlob(n.get(), 0, rect.height(), paint);
    // float denominator_y = std::max(height, rect.height());
    float denominator_y = 0.6f * height * expansion + rect.height() * (1 - expansion);
    wid = font.measureText("2", 1, SkTextEncoding(), &rect, &paint);
    ctx.drawTextBlob(d.get(), width - rect.width(), denominator_y, paint);

    //  Line
    SkPath path;
    // It's hard to align text. Use this to adjust manually
    constexpr float fudge_factor = 0.5f;
    path.moveTo(width * 0.25f + width * 0.25f * (1 - expansion) + fudge_factor, denominator_y);
    path.lineTo(0.5f * width * (1 + 0.5f * expansion) + fudge_factor, 0);
    paint.setStrokeWidth(3.f);
    ctx.drawPath(path, paint);

    // Bottom Text
    paint.setStrokeWidth(1.f);
    sk_sp<SkTextBlob> ratio_text = SkTextBlob::MakeFromString("RATIO", SkFont(nullptr, 12));
    paint.setColor(SkColorSetRGB(22 * expansion, 184 * expansion, 254 * expansion));
    // paint.setColor(mix(colors::black, paint.getColor(), expansion));
    ctx.drawTextBlob(ratio_text.get(), 0, bounding_box.height(), paint);
  }

  void DetuneGraphic::do_draw(skia::Canvas& ctx)
  {
    skia::Paint paint;
    if (active) {
      paint.setColor(colors::blue);
    } else {
      paint.setColor(colors::grey50);
    }
    paint.setStrokeWidth(1.f);
    paint.setStyle(skia::Paint::kStrokeAndFill_Style);

    sk_sp<SkTextBlob> val;
    if (value == 0) {
      val = SkTextBlob::MakeFromString("±.0", SkFont(nullptr, 20));
    } else if (value > 0) {
      val = SkTextBlob::MakeFromString(fmt::format("+.{:1.0}", value * 10).c_str(), SkFont(nullptr, 20));
    } else {
      val = SkTextBlob::MakeFromString(fmt::format("-.{:1.0}", value * 10).c_str(), SkFont(nullptr, 20));
    }
    sk_sp<SkTextBlob> dtune = SkTextBlob::MakeFromString("DTUNE", SkFont(nullptr, 12));
    SkRect rect = SkRect();
    SkFont font = SkFont(nullptr, 20);
    // SkScalar wid = font.measureText("3", 1, SkTextEncoding(), &rect, &paint);
    ctx.drawTextBlob(val.get(), 0,
                     rect.height() + expansion * (0.6f * 0.5f * bounding_box.height() - rect.height() / 2.f), paint);
    paint.setColor(SkColorSetRGB(22 * expansion, 184 * expansion, 254 * expansion));
    // paint.setColor(mix(colors::black, paint.getColor(), expansion));
    ctx.drawTextBlob(dtune.get(), 0, bounding_box.height(), paint);
  }

  void LevelGraphic::do_draw(skia::Canvas& ctx)
  {
    float rotation_scale = 270.f * expansion + 180.f * (1 - expansion);
    // Anchor is center
    skia::Point diff = bounding_box.get_diff(anchors::top_left, anchors::center);
    ctx.save();
    skia::translate(ctx, diff);

    const float radius = bounding_box.width() / 2.f;
    const float radius_line1 = radius * 0.9f;
    // const float radius_line2 = radius * 0.6f;
    skia::Paint paint;
    if (active) {
      paint.setColor(colors::green);
    } else {
      paint.setColor(colors::grey50);
    }
    // Level indicator
    ctx.save();
    ctx.rotate((value - 0.5f) * rotation_scale);
    SkPath path;
    path.moveTo(0, 0);
    path.lineTo(0, -radius);
    ctx.drawPath(path, paint);
    ctx.restore();

    // Line1
    paint.setStrokeWidth(3.f);
    SkRect rect = SkRect::MakeXYWH(-radius_line1, -radius_line1, 2.f * radius_line1, 2.f * radius_line1);
    path.reset();
    path.arcTo(rect, -90.f - 0.5f * rotation_scale, rotation_scale, false);
    ctx.drawPath(path, paint);

    // Text
    paint.setStrokeWidth(1.f);
    paint.setColor(SkColorSetRGB(22 * expansion, 254 * expansion, 101 * expansion));
    sk_sp<SkTextBlob> val = SkTextBlob::MakeFromString("LVL", SkFont(nullptr, 12));
    SkFont font = SkFont(nullptr, 12);
    // SkScalar wid = font.measureText("LVL", 1, SkTextEncoding(), &rect, &paint);
    ctx.drawTextBlob(val.get(), -rect.width() - 2, radius, paint);

    ctx.restore();
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
    skia::Paint paint;
    paint.setStrokeWidth(3.f);
    if (active) {
      paint.setColor(colors::yellow);
    } else {
      paint.setColor(colors::grey50);
    }
    ctx.drawPath(path, paint);

    // Bottom Text
    paint.setStrokeWidth(1.f);
    sk_sp<SkTextBlob> shape_text = SkTextBlob::MakeFromString("SHAPE", SkFont(nullptr, 12));
    paint.setColor(skia::Color::bytes(254, 245, 22) * expansion);
    // paint.setColor(mix(colors::black, paint.getColor(), expansion));
    ctx.drawTextBlob(shape_text.get(), 0, bounding_box.height(), paint);

    ctx.restore();
  }
} // namespace otto::engines::ottofm
