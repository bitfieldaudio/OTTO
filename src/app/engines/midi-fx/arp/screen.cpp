#include <algorithm>
#include <string>

#include <choreograph/Choreograph.h>
#include <fmt/format.h>

#include "lib/util/eventdivider.hpp"
#include "lib/util/with_limits.hpp"

#include "lib/itc/itc.hpp"
#include "lib/skia/anim.hpp"
#include "lib/skia/skia.hpp"
#include "lib/widget.hpp"

#include "app/input.hpp"
#include "app/services/config.hpp"
#include "app/services/graphics.hpp"
#include "app/services/ui_manager.hpp"

#include "arp.hpp"
#include "widgets.hpp"

namespace otto::engines::arp {

  util::string_ref display(PlayMode pm) noexcept
  {
    switch (pm) {
      case PlayMode::up: return "UP";
      case PlayMode::down: return "DOWN";
      case PlayMode::updown: return "UP/DOWN";
      case PlayMode::downup: return "DOWN/UP";
      case PlayMode::updowninc: return "UP/DOWN INC.";
      case PlayMode::downupinc: return "DOWN/UP INC.";
      case PlayMode::manual: return "MANUAL";
      case PlayMode::chord: return "CHORD";
      case PlayMode::random: return "RANDOM";
    };
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
  }

  struct Handler final : InputReducer<State>, IInputLayer {
    using InputReducer::InputReducer;

    [[nodiscard]] util::enum_bitset<Key> key_mask() const noexcept override
    {
      return key_groups::enc_clicks + Key::shift;
    }

    void reduce(EncoderEvent e, State& state) noexcept final
    {
      switch (e.encoder) {
        case Encoder::blue: {
          if (e.steps > 0) {
            state.playmode++;
          } else {
            state.playmode--;
          }
        } break;
        case Encoder::green: {
          if (e.steps > 0) {
            state.octavemode++;
          } else {
            state.octavemode--;
          }
        } break;
        case Encoder::yellow: {
          state.subdivision += e.steps;
        } break;
        case Encoder::red: {
          state.note_length += e.steps * 0.01;
        } break;
      }
    }
  };

  struct Screen final : itc::Consumer<State>, ScreenBase {
    using Consumer::Consumer;

    static constexpr float fade_in_time = 0.15f;
    static constexpr float hold_time = 1.f;
    static constexpr float fade_back_time = 0.4f;

    PlayMode old_playmode = PlayMode::up;
    skia::KeyValueFade<float> blue_fade = {fade_in_time, hold_time, fade_back_time};

    OctaveMode old_octavemode = OctaveMode::standard;
    skia::KeyValueFade<float> green_fade = {fade_in_time, hold_time, fade_back_time};

    int old_subdivision = 1;
    Subdivision subdivision_widget;
    skia::KeyValueFade<float> yellow_fade = {fade_in_time, hold_time, fade_back_time};

    float old_note_length = 0.3;
    NoteLength note_length_widget;
    skia::KeyValueFade<float> red_fade = {fade_in_time, hold_time, fade_back_time};

    using Dots = util::local_vector<NoteVector, 24>;
    using DotCoords = util::local_vector<std::pair<skia::Point, bool>, 48>;

    PlayModeFunc playmode_func_ = play_modes::up;
    OctaveModeFunc octavemode_func_ = octave_modes::standard;
    ArpeggiatorState dummy_state;
    NoteArray notes;
    Dots dots;
    DotCoords dots_coords;


    void update_dots(PlayModeFunc playmode_func_,
                     OctaveModeFunc octavemode_func_,
                     ArpeggiatorState state,
                     NoteArray notes,
                     DotCoords& dots_coords) noexcept
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

    void draw_dots(skia::Canvas& ctx, DotCoords& coords)
    {
      for (auto& p : coords) ctx.drawCircle(p.first, 5, paints::fill(p.second ? colors::white : colors::green));
    }

    Screen(itc::ChannelGroup& c) : Consumer(c)
    {
      // Insert notes to visualize
      notes.push_back({44, 0});
      notes.push_back({40, 1});
      notes.push_back({47, 2});
    }

    void on_state_change(const State& s) noexcept override
    {
      // Playmode
      if (old_playmode != s.playmode) {
        blue_fade.trigger();
        old_playmode = s.playmode;
        playmode_func_ = play_modes::func(s.playmode);
      }
      // Octavemode
      if (old_octavemode != s.octavemode) {
        green_fade.trigger();
        old_octavemode = s.octavemode;
        octavemode_func_ = octave_modes::func(s.octavemode);
      }
      // Subdivision
      if (old_subdivision != s.subdivision) {
        yellow_fade.trigger();
        subdivision_widget.num_dots_ = s.subdivision;
        old_subdivision = s.subdivision;
      }
      // Note length
      if (old_note_length != s.note_length) {
        red_fade.trigger();
        note_length_widget.length_ = s.note_length;
        old_note_length = s.note_length;
      }
      update_dots(playmode_func_, octavemode_func_, dummy_state, notes, dots_coords);
    }

    void draw(skia::Canvas& ctx) noexcept override
    {
      constexpr float x_pad = 10;
      constexpr float y_pad = 10;
      const auto font = fonts::regular(20);

      // BLUE/STYLE
      skia::Point blue_position = {x_pad, 240 - y_pad};
      skia::place_text(ctx, "STYLE", font, colors::blue.fade(blue_fade.key()), blue_position, anchors::bottom_left);
      skia::place_text(ctx, display(state().playmode), font, colors::blue.fade(blue_fade.value()), blue_position,
                       anchors::bottom_left);

      // GREEN/OCTAVE
      skia::Point green_position = {x_pad, y_pad};
      skia::place_text(ctx, "OCTAVE", font, colors::green.fade(green_fade.key()), green_position, anchors::top_left);
      skia::place_text(ctx, display(state().octavemode), font, colors::green.fade(green_fade.value()), green_position,
                       anchors::top_left);

      constexpr float box_width = 70.f;
      constexpr float box_height = 15.f;
      // RED/LENGTH
      skia::Point red_position = {320 - x_pad, y_pad};

      note_length_widget.fade_ = red_fade.value();
      note_length_widget.bounding_box.move_to({320 - box_width - x_pad, y_pad});
      note_length_widget.bounding_box.resize({box_width, box_height});
      note_length_widget.draw(ctx);
      skia::place_text(ctx, "LENGTH", font, colors::red.fade(red_fade.key()), red_position, anchors::top_right);

      // YELLOW/SPEED
      skia::Point yellow_position = {320 - x_pad, 240 - y_pad};
      skia::place_text(ctx, "SPEED", font, colors::yellow.fade(yellow_fade.key()), yellow_position,
                       anchors::bottom_right);
      subdivision_widget.fade_ = yellow_fade.value();
      subdivision_widget.bounding_box.move_to({320 - 50 - x_pad, 240 - box_height - y_pad});
      subdivision_widget.bounding_box.resize({box_width, box_height});
      subdivision_widget.draw(ctx);

      draw_dots(ctx, dots_coords);
    }
  };

  ScreenWithHandler make_screen(itc::ChannelGroup& chan)
  {
    return {
      .screen = std::make_unique<Screen>(chan),
      .input = std::make_unique<Handler>(chan),
    };
  }

} // namespace otto::engines::arp
