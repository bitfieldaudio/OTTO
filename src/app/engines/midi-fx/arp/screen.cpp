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
    OTTO_UNREACHABLE();
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
      case OctaveMode::multiply: return "TWICE";
    };
    OTTO_UNREACHABLE();
  }

  struct Handler final : LogicDomain, InputReducer<State>, IInputLayer {
    using InputReducer::InputReducer;

    [[nodiscard]] util::enum_bitset<Key> key_mask() const noexcept override
    {
      return key_groups::enc_clicks + Key::shift;
    }

    // TODO: Move this to the dispatcher!
    void reduce(KeyPress e, State& state) noexcept final
    {
      switch (e.key) {
        case Key::blue_enc_click: [[fallthrough]];
        case Key::green_enc_click: [[fallthrough]];
        case Key::yellow_enc_click: [[fallthrough]];
        case Key::red_enc_click: state.active = !state.active; break;
        default: break;
      }
    }

    void reduce(EncoderEvent e, State& state) noexcept final
    {
      switch (e.encoder) {
        case Encoder::blue: {
          state.playmode += pm_divider(e);
        } break;
        case Encoder::green: {
          state.octavemode += om_divider(e);
        } break;
        case Encoder::yellow: {
          // state.subdivision += sd_divider(e);
          state.bpm += e.steps;
        } break;
        case Encoder::red: {
          state.note_length += e.steps * 0.01;
        } break;
      }
    }

  private:
    otto::util::EventDivider<4> pm_divider;
    otto::util::EventDivider<4> om_divider;
    otto::util::EventDivider<4> sd_divider;
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

    // int old_subdivision = 1;
    // Subdivision subdivision_widget;
    int old_bpm = 480;
    skia::KeyValueFade<float> yellow_fade = {fade_in_time, hold_time, fade_back_time};

    float old_note_length = 0.3;
    NoteLength note_length_widget;
    skia::KeyValueFade<float> red_fade = {fade_in_time, hold_time, fade_back_time};

    VisualDots visual_dots;

    Screen(itc::Context& c) : Consumer(c)
    {
      // Insert notes to visualize
      visual_dots.notes.push_back({44, 0});
      visual_dots.notes.push_back({40, 1});
      visual_dots.notes.push_back({47, 2});
    }

    void on_state_change(const State& s) noexcept override
    {
      // Playmode
      if (old_playmode != s.playmode) {
        blue_fade.trigger();
        old_playmode = s.playmode;
        visual_dots.playmode_func_ = play_modes::func(s.playmode);
      }
      // Octavemode
      if (old_octavemode != s.octavemode) {
        green_fade.trigger();
        old_octavemode = s.octavemode;
        visual_dots.octavemode_func_ = octave_modes::func(s.octavemode);
      }
      // Subdivision
      // if (old_subdivision != s.subdivision) {
      //   yellow_fade.trigger();
      //   subdivision_widget.num_dots_ = s.subdivision;
      //   old_subdivision = s.subdivision;
      // }
      if (old_bpm != s.bpm) {
        yellow_fade.trigger();
        old_bpm = s.bpm;
      }
      // Note length
      if (old_note_length != s.note_length) {
        red_fade.trigger();
        note_length_widget.length_ = s.note_length;
        old_note_length = s.note_length;
      }
      visual_dots.update_dots();
    }

    void draw(skia::Canvas& ctx) noexcept override
    {
      // TODO: Move this to an enginedispatcher!
      if (!state().active) {
        const auto font = fonts::black(50);
        skia::place_text(ctx, "OFF", font, colors::red, {320 / 2, 240 / 2}, anchors::center);
        return;
      }


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
      // subdivision_widget.fade_ = yellow_fade.value();
      // subdivision_widget.bounding_box.move_to({320 - 50 - x_pad, 240 - box_height - y_pad});
      // subdivision_widget.bounding_box.resize({box_width, box_height});
      // subdivision_widget.draw(ctx);
      skia::place_text(ctx, fmt::format("{:1}", state().bpm), font, colors::yellow.fade(yellow_fade.value()),
                       yellow_position, anchors::bottom_right);


      visual_dots.draw(ctx);
    }
  };

  ScreenWithHandler make_screen(itc::Context& chan)
  {
    return {
      .screen = std::make_unique<Screen>(chan),
      .input = std::make_unique<Handler>(chan),
    };
  }

} // namespace otto::engines::arp
