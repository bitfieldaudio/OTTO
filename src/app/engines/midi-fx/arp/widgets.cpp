#include "widgets.hpp"

namespace otto::engines::arp {

  void NoteLength::do_draw(skia::Canvas& ctx)
  {
    // Box rounding
    float r = 5.f;
    // Status bar
    SkRect rect = SkRect::MakeXYWH(0, 0, bounding_box.width(), bounding_box.height());
    SkRRect rrect = SkRRect::MakeRectXY(rect, r, r);
    ctx.drawRRect(rrect, paints::fill(colors::red.mix(colors::black, fade_)));
    // Covering square
    SkRect black_rect =
      SkRect::MakeLTRB(bounding_box.width() * length_, 0, bounding_box.width(), bounding_box.height());
    ctx.drawRect(black_rect, paints::fill(colors::black));
    // Outline
    ctx.drawRRect(rrect, paints::stroke(colors::red.mix(colors::black, fade_), 3.f));
  }

  void Subdivision::do_draw(skia::Canvas& ctx)
  {
    float step_size = bounding_box.width() / 6;
    float height = bounding_box.height() / 2.f;
    for (int i = 0; i < num_dots_; i++) {
      ctx.drawCircle({i * step_size, height}, 5.f, paints::fill(colors::yellow.fade(fade_)));
    }
  }

  void VisualDots::update_dots() noexcept
  {
    // Calculate notes
    //
    dots.clear();
    dummy_state.reset();
    do {
      dots.push_back(octavemode_func_(dummy_state, notes, playmode_func_));
    } while (dummy_state.count != 0);
    if (dots.size() > 1) dots.pop_back();
    dummy_state.reset();

    // Graphics options
    float y_bot = 175;
    float y_size = 110;
    float x_step_width = 30;

    // Calculate dots from notes
    //
    int num_steps = dots.size();
    int min = 88;
    int max = 0;
    // Find minimum and maximum key values
    for (auto& s : dots) {
      auto current_min = s[0];
      min = min > current_min ? current_min : min;
      auto current_max = s.back();
      max = max < current_max ? current_max : max;
    }
    // Calculate new dot values
    dots_coords.clear();
    // Possibly, there are too many steps and we must rescale in the x-direction
    if (num_steps > 10) x_step_width = x_step_width * 10 / num_steps;

    for (int i = 0; i < num_steps; i++) {
      for (auto& note : dots[i]) {
        skia::Point p;
        p.fX = skia::width / 2.f + (2 * i + 1 - num_steps) * x_step_width / 2.f;
        if (min != max)
          p.fY = y_bot - ((float) note - (float) min) / ((float) max - (float) min) * y_size;
        else
          p.fY = y_bot - y_size / 2;

        // Check if original
        constexpr std::array<int, 3> orig_notes = {40, 44, 47};
        bool is_original = std::ranges::find(orig_notes, note) != orig_notes.end();
        dots_coords.push_back({p, is_original});
      }
    }
  }
  void VisualDots::do_draw(skia::Canvas& ctx)
  {
    for (auto& p : dots_coords) ctx.drawCircle(p.first, 5, paints::fill(p.second ? colors::white : colors::green));
  }

} // namespace otto::engines::arp