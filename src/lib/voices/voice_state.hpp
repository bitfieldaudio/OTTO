#pragma once

#include <type_traits>

#include "lib/util/with_limits.hpp"

namespace otto::voices {

  enum struct PlayMode { poly, mono, unison, duo };
  template<typename Voice>
  struct VoiceBase;

  template<typename T>
  concept AVoice = std::is_base_of_v<VoiceBase<T>, T>;

  template<AVoice Voice, std::size_t N>
  struct VoiceManager;

  struct VoicesState {
    PlayMode play_mode = PlayMode::poly;
    bool legato = false;
    bool retrig = false;
    float pitch_bend = 1;
    bool sustain = false;
    util::StaticallyBounded<float, 0, 1> portamento = 0.1f;

    util::StaticallyBounded<float, 0, 1> rand = 0;
    util::StaticallyBounded<int, -12, 12> interval = 0;
    util::StaticallyBounded<float, 0, 1> sub = 0;
    util::StaticallyBounded<float, 0, 1> detune = 0;
  };

} // namespace otto::voices
