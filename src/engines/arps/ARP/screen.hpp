#pragma once

#include <vector>

#include "arp.hpp"
#include "audio.hpp"
#include "core/ui/nvg/Canvas.hpp"
#include "core/ui/screen.hpp"
#include "util/local_vector.hpp"

namespace otto::engines::arp {

  using namespace core;

  inline std::string to_string(Playmode pm) noexcept
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

  inline std::string to_string(OctaveMode om) noexcept
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

  struct Screen : ui::Screen {
    Screen();

    int min = 88;
    int max = 0;
    int num_steps = 0;

    std::string playmode_ = "UP";
    std::string octavemode_ = "STANDARD";
    float note_length_ = 0.f;
    int subdivision_ = 1;

    void draw(nvg::Canvas& ctx) override;

    void action(itc::prop_change<&Props::playmode>, Playmode pm) noexcept;
    void action(itc::prop_change<&Props::octavemode>, OctaveMode om) noexcept;
    void action(itc::prop_change<&Props::note_length>, float nl) noexcept;
    void action(itc::prop_change<&Props::subdivision>, int s) noexcept;

    using Dots = util::local_vector<NoteVector, 24>;
    void update_dots(PlayModeFunc playmode_func_,
                     OctaveModeFunc octavemode_func_,
                     ArpeggiatorState state,
                     NoteArray notes,
                     util::local_vector<std::pair<nvg::Point, bool>, 48>& dots_coords) noexcept;
    void draw_dots(nvg::Canvas& ctx, util::local_vector<std::pair<nvg::Point, bool>, 48>& coords);

  private:
    ch::Output<float> blue_fade_key = 0;
    ch::Output<float> blue_fade_value = 0;
    ch::Output<float> green_fade_key = 0;
    ch::Output<float> green_fade_value = 0;
    ch::Output<float> yellow_fade = 0;
    ch::Output<float> red_fade = 0;

    PlayModeFunc playmode_func_ = play_modes::up;
    OctaveModeFunc octavemode_func_ = octave_modes::standard;
    ArpeggiatorState dummy_state;
    NoteArray notes;
    Dots dots;
    util::local_vector<std::pair<nvg::Point, bool>, 48> dots_coords;
  };

} // namespace otto::engines::arp
