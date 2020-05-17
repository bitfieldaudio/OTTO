#include "screen.hpp"

#include "core/ui/vector_graphics.hpp"
#include "engines/arps/ARP/arp.hpp"
#include "fmt/format.h"
#include "util/local_vector.hpp"
#include "util/string_conversions.hpp"
#include <nanorange.hpp>

namespace otto::engines::arp {

  using namespace itc;

  using namespace ui;
  using namespace ui::vg;

  constexpr float fadein_time = 100;
  constexpr float hold_time = 600;
  constexpr float fadeout_time = 300;

  Screen::Screen()
  {
    // Insert notes to visualize
    notes.push_back({44, 0});
    notes.push_back({40, 1});
    notes.push_back({47, 2});
  }

  util::string_ref display(Playmode pm) noexcept
  {
    switch (pm) {
      case Playmode::up: return "UP";
      case Playmode::down: return "DOWN";
      case Playmode::updown: return "UP/DOWN";
      case Playmode::downup: return "DOWN/UP";
      case Playmode::updowninc: return "UP/DOWN INC.";
      case Playmode::downupinc: return "DOWN/UP INC.";
      case Playmode::manual: return "MANUAL";
      case Playmode::chord: return "CHORD";
      case Playmode::random: return "RANDOM";
    };
    OTTO_UNREACHABLE;
  }
  util::string_ref display(OctaveMode om) noexcept
  {
    switch (om) {
      case OctaveMode::standard: return "STANDARD";
      case OctaveMode::octaveup: return "+1";
      case OctaveMode::doubleoctaveup: return "+2";
      case OctaveMode::octaveupunison: return "+1 UNISON";
      case OctaveMode::fifthunison: return "FIFTH";
      case OctaveMode::octavedownup: return "-1 & +1";
    };
    OTTO_UNREACHABLE;
  }

  void Screen::action(itc::prop_change<&Props::playmode>, Playmode pm) noexcept
  {
    playmode_ = display(pm);
    // TODO: Move this switch out to arp.hpp so they are shared between graphics and audio
    switch (pm) {
      case Playmode::up: playmode_func_ = play_modes::up; break;
      case Playmode::down: playmode_func_ = play_modes::down; break;
      case Playmode::updown: playmode_func_ = play_modes::updown; break;
      case Playmode::downup: playmode_func_ = play_modes::downup; break;
      case Playmode::updowninc: playmode_func_ = play_modes::updowninc; break;
      case Playmode::downupinc: playmode_func_ = play_modes::downupinc; break;
      case Playmode::manual: playmode_func_ = play_modes::manual; break;
      case Playmode::chord: playmode_func_ = play_modes::chord; break;
      case Playmode::random: playmode_func_ = play_modes::random; break;
    }
    update_dots(playmode_func_, octavemode_func_, dummy_state, notes, dots_coords);
    ui::vg::timeline()
      .apply(&blue_fade_key)
      .then<ch::RampTo>(1, fadein_time)
      .then<ch::Hold>(1, hold_time + fadeout_time)
      .then<ch::RampTo>(0, fadeout_time);
    ui::vg::timeline()
      .apply(&blue_fade_value)
      .then<ch::RampTo>(1, fadein_time)
      .then<ch::Hold>(1, hold_time)
      .then<ch::RampTo>(0, fadeout_time);
  }

  void Screen::action(itc::prop_change<&Props::octavemode>, OctaveMode om) noexcept
  {
    octavemode_ = display(om);
    // TODO: Move switch to function in arp.hpp
    switch (om) {
      case OctaveMode::standard: octavemode_func_ = octave_modes::standard; break;
      case OctaveMode::octaveupunison: octavemode_func_ = octave_modes::octaveupunison; break;
      case OctaveMode::fifthunison: octavemode_func_ = octave_modes::fifthunison; break;
      case OctaveMode::octaveup: octavemode_func_ = octave_modes::octaveup; break;
      case OctaveMode::doubleoctaveup: octavemode_func_ = octave_modes::doubleoctaveup; break;
      case OctaveMode::octavedownup: octavemode_func_ = octave_modes::octavedownup; break;
    }
    update_dots(playmode_func_, octavemode_func_, dummy_state, notes, dots_coords);
    ui::vg::timeline()
      .apply(&green_fade_key)
      .then<ch::RampTo>(1, fadein_time)
      .then<ch::Hold>(1, hold_time + fadeout_time)
      .then<ch::RampTo>(0, fadeout_time);
    ui::vg::timeline()
      .apply(&green_fade_value)
      .then<ch::RampTo>(1, fadein_time)
      .then<ch::Hold>(1, hold_time)
      .then<ch::RampTo>(0, fadeout_time);
  }

  void Screen::action(itc::prop_change<&Props::note_length>, float nl) noexcept
  {
    note_length_ = nl;
    ui::vg::timeline()
      .apply(&red_fade)
      .then<ch::RampTo>(1, fadein_time)
      .then<ch::Hold>(1, hold_time)
      .then<ch::RampTo>(0, fadeout_time);
  }

  void Screen::action(itc::prop_change<&Props::subdivision>, int s) noexcept
  {
    subdivision_ = s;
    ui::vg::timeline()
      .apply(&yellow_fade)
      .then<ch::RampTo>(1, fadein_time)
      .then<ch::Hold>(1, hold_time)
      .then<ch::RampTo>(0, fadeout_time);
  }

  void Screen::update_dots(PlayModeFunc playmode_func_,
                           OctaveModeFunc octavemode_func_,
                           ArpeggiatorState state,
                           NoteArray notes,
                           util::local_vector<std::pair<nvg::Point, bool>, 48>& dots_coords) noexcept
  {
    // Calculate notes
    //
    dots.clear();
    state.reset();
    do {
      dots.push_back(octavemode_func_(state, notes, playmode_func_));
    } while (state.count != 0);
    if (dots.size() > 1) dots.pop_back();
    state.reset();

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
        Point p;
        p.x = width / 2.f + (2 * i + 1 - num_steps) * x_step_width / 2.f;
        if (min != max)
          p.y = y_bot - ((float) note - (float) min) / ((float) max - (float) min) * y_size;
        else
          p.y = y_bot - y_size / 2;

        // Check if original
        constexpr std::array<int, 3> orig_notes = {40, 44, 47};
        bool is_original = nano::find(orig_notes, note) != orig_notes.end();
        dots_coords.push_back({p, is_original});
      }
    }
  }

  void Screen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    constexpr float x_pad = 10;
    constexpr float y_pad = 10;

    ctx.lineWidth(4.f);
    ctx.font(Fonts::Bold, 22.0);

    // BLUE/STYLE
    ctx.fillStyle(Colours::Blue.fade(blue_fade_key));
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Bottom);
    ctx.fillText("STYLE", x_pad, height - y_pad);

    ctx.fillStyle(Colours::Blue.fade(1 - blue_fade_value));
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Bottom);
    ctx.fillText(playmode_, x_pad, height - y_pad);

    // GREEN/OCTAVE
    ctx.fillStyle(Colours::Green.fade(green_fade_key));
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Top);
    ctx.fillText("OCTAVE", x_pad, y_pad);

    ctx.fillStyle(Colours::Green.fade(1 - green_fade_value));
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Top);
    ctx.fillText(octavemode_, x_pad, y_pad);

    // RED/LENGTH
    ctx.fillStyle(Colours::Red.fade(red_fade));
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Top);
    ctx.fillText("LENGTH", width - x_pad, y_pad);

    constexpr float con_width = 80.f;
    constexpr float con_height = 20.f;
    constexpr float con_r = 10.f;
    // Status bar
    ctx.beginPath();
    ctx.roundedRect(width - x_pad - con_width, y_pad, con_width, con_height, con_r);
    ctx.fill(Colours::Red.fade(1 - red_fade));
    // Covering square
    ctx.beginPath();
    ctx.rect(width - x_pad - (1 - note_length_) * con_width, y_pad, con_width, con_height);
    ctx.fill(Colours::Black.fade(1 - red_fade));
    // Outline
    ctx.beginPath();
    ctx.roundedRect(width - x_pad - con_width, y_pad, con_width, con_height, con_r);
    ctx.stroke(Colours::Red.fade(1 - red_fade));

    // YELLOW/SPEED
    ctx.fillStyle(Colours::Yellow.fade(yellow_fade));
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Bottom);
    ctx.fillText("SPEED", width - x_pad, height - y_pad);

    ctx.beginPath();
    ctx.roundedRect(width - x_pad - con_width, height - y_pad - con_height, con_width, con_height, con_r);
    ctx.stroke(Colours::Yellow.fade(1 - yellow_fade));
    // Draw speed dots
    constexpr float step_size = con_width / 6;
    for (int i = 0; i < subdivision_; i++) {
      ctx.beginPath();
      ctx.circle(width - x_pad - con_width + ((float) i + 1) * step_size, height - y_pad - 0.5 * con_height, 5);
      ctx.fill(Colours::Yellow.fade(1 - yellow_fade));
    }

    draw_dots(ctx, dots_coords);
  }

  void Screen::draw_dots(nvg::Canvas& ctx, util::local_vector<std::pair<nvg::Point, bool>, 48>& coords)
  {
    for (auto& p : coords) {
      ctx.beginPath();
      ctx.circle(p.first, 5);
      auto cl = p.second ? Colours::White : Colours::Green;
      ctx.fill(cl);
    }
  }

} // namespace otto::engines::arp
