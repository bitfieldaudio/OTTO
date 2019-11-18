#include "audio.hpp"

#include "services/audio_manager.hpp"

namespace otto::engines::wormhole {

  Audio::Audio() noexcept
  {
    // reverb.resize({1307, 1637, 1811, 1931}, {1051, 337, 113});
    reverb.resize(gam::JCREVERB);

    shimmer_filter.type(gam::LOW_PASS);
    shimmer_filter.freq(18000);

    pre_filter.type(gam::LOW_PASS);

    output_delay[0].maxDelay(211.f / gam::sampleRate());
    output_delay[1].maxDelay(179.f / gam::sampleRate());
  }

  void Audio::action(itc::prop_change<&Props::filter>, float flt) noexcept
  {
    pre_filter.freq(3000 + flt * flt * 17000);
  }

  void Audio::action(itc::prop_change<&Props::shimmer>, float sh) noexcept
  {
    shimmer_amount = sh * 0.03;
  }

  void Audio::action(itc::prop_change<&Props::length>, float len) noexcept
  {
    reverb.decay(3.f * len);
  }

  void Audio::action(itc::prop_change<&Props::damping>, float damp) noexcept
  {
    reverb.damping(damp);
  }

  audio::ProcessData<2> Audio::process(audio::ProcessData<1> data) noexcept
  {
    auto buf = services::AudioManager::current().buffer_pool().allocate_multi<2>();
    for (auto&& [dat, bufL, bufR] : util::zip(data.audio, buf[0], buf[1])) {
      auto frm = reverb(pre_filter(dat) + last_sample * shimmer_amount);
      last_sample = dc_block(shimmer_filter(pitchshifter(frm)));

      bufL = output_delay[0](frm);
      bufR = output_delay[1](frm);
    }
    return data.with(buf);
  }

} // namespace otto::engines::wormhole
