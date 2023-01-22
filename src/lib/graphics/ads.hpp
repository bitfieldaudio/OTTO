#pragma once

#include "lib/skia/anim.hpp"
#include "lib/widget.hpp"

namespace otto::graphics {

  struct ADS : Widget<ADS> {
    float a = 0;
    float d = 0;
    float s = 0;
    float x = 0; // "Amount"
    bool active = false;
    float expanded = 0;
    float active_segment = 0;

    void do_draw(skia::Canvas& ctx)
    {
      const float width = bounding_box.width();
      const float height = bounding_box.height();
      const float spacing = width / 16.f;
      const float max_width = width / 3.f;
      const float aw = max_width * a;
      const float dw = max_width * d;
      const float sh = height * s;
      const float rw = max_width * 0.7f;

      const float arc_size = 0.2f * expanded + 0.5f;
      const float attack_arc_size = 0.5f - 0.5f * expanded;

      const float a_active = std::clamp(1 - active_segment, 0.f, 1.f);
      const float d_active = active_segment < 1 ? 0 : std::clamp(1 - (active_segment - 1), 0.f, 1.f);
      const float s_active = active_segment < 2 ? 0 : std::clamp(1 - (active_segment - 2), 0.f, 1.f);

      SkPath p;
      p.moveTo(0, height);
      p.quadTo(aw * attack_arc_size, height * arc_size, aw, 0); // curve
      p.lineTo(aw, height);
      p.close();
      ctx.drawPath(
        p, paints::stroke_and_fill(
             colors::blue.mix(colors::black, static_cast<float>(!active) * 0.7f).mix(colors::white, a_active * 0.5f)));

      p.reset();

      p.moveTo(aw + spacing, height);
      p.lineTo(aw + spacing, 0);
      p.quadTo(aw + spacing + dw * (1 - arc_size), (height - sh) * arc_size, aw + spacing + dw, height - sh); // curve
      p.lineTo(aw + spacing + dw, height);
      p.close();
      ctx.drawPath(
        p, paints::stroke_and_fill(
             colors::green.mix(colors::black, static_cast<float>(!active) * 0.8f).mix(colors::white, d_active * 0.5f)));

      p.reset();

      p.moveTo(aw + spacing + dw + spacing, height - sh);
      p.lineTo(width - spacing - rw, height - sh);
      p.lineTo(width - spacing - rw, height);
      p.lineTo(aw + spacing + dw + spacing, height);
      p.close();
      ctx.drawPath(
        p,
        paints::stroke_and_fill(
          colors::yellow.mix(colors::black, static_cast<float>(!active) * 0.8f).mix(colors::white, s_active * 0.5f)));

      p.reset();

      // Amount
      skia::place_text(ctx, "AMT", fonts::black(20), paints::fill(colors::red.fade(1 - expanded)),
                       bounding_box.point(anchors::top_right), anchors::top_right);
      skia::place_text(ctx, fmt::format("{}", int(x * 100)), fonts::black(26),
                       paints::fill(colors::red.mix(colors::black, static_cast<float>(!active) * 0.8f)),
                       bounding_box.point(anchors::bottom_right), anchors::bottom_right);
    }
  };

} // namespace otto::graphics
