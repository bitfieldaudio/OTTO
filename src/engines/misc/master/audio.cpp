#include "audio.hpp"

#include "services/audio_manager.hpp"

namespace otto::engines::master {

  Audio::Audio() noexcept
  {
    
  }

  void Audio::action(itc::prop_change<&Props::volume>, float v) noexcept
  {
    volume_square_ = v * v;
  }

  void Audio::action(itc::prop_change<&Props::tempo>, int t) noexcept
  {
    tempo_ = t;
  }

  audio::ProcessData<2> Audio::process(audio::ProcessData<2> data) noexcept
  {
    for (auto&& l : data.audio[0]) {
      l = util::math::fastatan( l * volume_square_ );
    }
    for (auto&& r : data.audio[1]) {
      r = util::math::fastatan( r * volume_square_ );
    }

    return data;
  }

} // namespace otto::engines::wormhole
