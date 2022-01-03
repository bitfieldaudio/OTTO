#pragma once

#include "lib/skia/anim.hpp"
#include "lib/widget.hpp"

namespace otto::graphics {

  struct ADSR : Widget<ADSR> {
    float a = 0;
    float d = 0;
    float s = 0;
    float r = 0;
    bool active = false;
    float expanded = 0;
    float active_segment = 0;
    void do_draw(skia::Canvas& ctx)
    {
      // If you are using a different anchor/origin than TopLeft for the coordinate system, translate here
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

      const float arc_size = 0.2f * expanded + 0.5f;
      const float attack_arc_size = 0.5f - 0.5f * expanded;

      const float a_active = std::clamp(1 - active_segment, 0.f, 1.f);
      const float d_active = active_segment < 1 ? 0 : std::clamp(1 - (active_segment - 1), 0.f, 1.f);
      const float s_active = active_segment < 2 ? 0 : std::clamp(1 - (active_segment - 2), 0.f, 1.f);
      const float r_active = active_segment < 3 ? 0 : std::clamp(1 - (active_segment - 3), 0.f, 1.f);

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

      p.moveTo(width - rw, height);
      p.lineTo(width - rw, height - sh);
      p.quadTo(width - rw * arc_size, height - sh * (1 - arc_size), width, height);
      p.close();
      ctx.drawPath(
        p, paints::stroke_and_fill(
             colors::red.mix(colors::black, static_cast<float>(!active) * 0.8f).mix(colors::white, r_active * 0.5f)));
    }
  };


} // namespace otto::graphics