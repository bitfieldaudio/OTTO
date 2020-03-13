#pragma once

#include <vector>

#include "arp.hpp"
#include "audio.hpp"
#include "core/ui/nvg/Canvas.hpp"
#include "core/ui/screen.hpp"
#include "util/local_vector.hpp"
#include "util/string_ref.hpp"

namespace otto::engines::arp {

  using namespace core;

  inline util::string_ref display(Playmode pm) noexcept;
  inline util::string_ref display(OctaveMode om) noexcept;

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
