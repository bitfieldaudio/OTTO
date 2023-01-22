#pragma once

#include "lib/util/visitor.hpp"
#include "lib/util/with_limits.hpp"

namespace otto::engines::nuke {


  struct State {
    util::StaticallyBounded<float, 0, 1> osc2_pitch = 0.5f;
    util::StaticallyBounded<float, 0, 1> osc_mix = 0.5;
    util::StaticallyBounded<int, 0, 3> mode = 0;
    util::StaticallyBounded<float, 0, 1> cutoff = 0.7f;
    util::StaticallyBounded<float, 0, 1> resonance = 0.2f;

    // Volume envelope
    util::StaticallyBounded<float, 0, 1> attack = 0.f;
    util::StaticallyBounded<float, 0, 1> decay = 0.f;
    util::StaticallyBounded<float, 0, 1> sustain = 1.f;
    util::StaticallyBounded<float, 0, 1> release = 0.1f;
    // Filter envelope
    util::StaticallyBounded<float, 0, 1> filter_attack = 0.1f;
    util::StaticallyBounded<float, 0, 1> filter_decay = 0.1f;
    util::StaticallyBounded<float, 0, 1> filter_sustain = 0.5f;
    util::StaticallyBounded<float, 0, 1> filter_amount = 0.f;
    // LFO
    util::StaticallyBounded<float, 0, 1> lfo_speed = 0.2f;
    util::StaticallyBounded<int, 0, 7> lfo_type = 0;
    util::StaticallyBounded<float, 0, 1> lfo_attack = 0.f;
    util::StaticallyBounded<float, 0, 1> lfo_decay = 1.f;
    // LFO Targets
    util::StaticallyBounded<float, -1, 1> lfo_pitch_amount = 0.0f;
    util::StaticallyBounded<float, 0, 1> lfo_volume_amount = 0.f;
    util::StaticallyBounded<float, 0, 1> lfo_filter_amount = 0.f;
    util::StaticallyBounded<float, 0, 1> lfo_osc2_pitch_amount = 0.f;

    int active_idx = 0;
    bool shift = false;

    DECL_VISIT(osc2_pitch,
               osc_mix,
               mode,
               cutoff,
               resonance,
               attack,
               decay,
               sustain,
               release,
               filter_attack,
               filter_decay,
               filter_sustain,
               filter_amount,
               lfo_speed,
               lfo_type,
               lfo_attack,
               lfo_decay,
               lfo_pitch_amount,
               lfo_volume_amount,
               lfo_filter_amount,
               lfo_osc2_pitch_amount,
               active_idx);
  };

} // namespace otto::engines::nuke
