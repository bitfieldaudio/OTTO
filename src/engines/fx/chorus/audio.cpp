#include "audio.hpp"

#include "services/audio_manager.hpp"

namespace otto::engines::chorus {

  Audio::Audio(itc::Shared<float> shared_phase) noexcept : shared_phase(shared_phase)
  {
    // Set proper size of phase accumulator for graphics
    phase.radius(1);
  }

  void Audio::action(itc::prop_change<&Props::delay>, float d) noexcept
  {
    //G oes from minimal to around 20 ms nominal delay.
    chorus.center(d * d * 0.020 + 0.0005);
    //N aturally, the new nominal delay changes the maximum for the play head movement
    chorus.depth(depth_ * chorus.center());
  }
  void Audio::action(itc::prop_change<&Props::depth>, float d) noexcept
  {
    chorus.depth(d * chorus.center());
    depth_ = d;
  }
  void Audio::action(itc::prop_change<&Props::feedback>, float f) noexcept
  {
    chorus.fbk(f);
  }
  void Audio::action(itc::prop_change<&Props::rate>, float r) noexcept
  {
    chorus.rate(r * 0.5f);
    phase.freq(r * 0.5f);
  }

  audio::ProcessData<2> Audio::process(audio::ProcessData<1> data) noexcept
  {
    auto buf = Application::current().audio_manager->buffer_pool().allocate_multi<2>();
    for (auto&& [dat, bufL, bufR] : util::zip(data.audio, buf[0], buf[1])) {
      chorus(dat, bufL, bufR);
      shared_phase = phase.nextPhase();
    }
    return data.with(buf);
  }

} // namespace otto::engines::chorus
