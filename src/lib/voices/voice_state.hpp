#pragma once

#include <type_traits>

#include "lib/util/with_limits.hpp"

namespace otto::voices {

  enum struct PlayMode { poly, mono, unison, interval };
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
    float portamento = 0.f;

    util::StaticallyBounded<float, 0, 1> rand = 0;
    int interval = 0;
    util::StaticallyBounded<float, 0, 1> sub = 0;
    util::StaticallyBounded<float, 0, 1> detune = 0;
  };

} // namespace otto::voices
