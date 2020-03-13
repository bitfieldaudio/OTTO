#include "audio.hpp"

#include "services/audio_manager.hpp"
#include "services/clock_manager.hpp"

namespace otto::engines::master {

  Audio::Audio() noexcept {}

  void Audio::action(itc::prop_change<&Props::volume>, float v) noexcept
  {
    services::AudioManager::current().output_vol(v);
  }

  void Audio::action(itc::prop_change<&Props::tempo>, float t) noexcept
  {
    tempo_ = t;
    services::ClockManager::current().set_bpm(t);
  }

  audio::ProcessData<2> Audio::process(audio::ProcessData<2> data) noexcept
  {
    for (auto&& l : data.audio[0]) {
      l = util::math::fastatan(l);
    }
    for (auto&& r : data.audio[1]) {
      r = util::math::fastatan(r);
    }

    return data;
  }

} // namespace otto::engines::master
