#include "audio.hpp"

#include "services/audio_manager.hpp"

namespace otto::engines::pingpong {

  Audio::Audio() noexcept
  {
    for (auto& dl : delay_line) dl.maxDelay(6.f);
    output_delay.maxDelay(spread_max);
    input_filter.set_position(0.6f);
  }

  void Audio::action(itc::prop_change<&Props::delaytime>, float t) noexcept
  {
    for (auto& d : delay_line) d.delay(t);
  }

  void Audio::action(itc::prop_change<&Props::feedback>, float f) noexcept
  {
    feedback_ = f;
  }

  void Audio::action(itc::prop_change<&Props::filter>, float f) noexcept
  {
    input_filter.set_position(f);
    for (auto& lf : loop_filter) lf.set_position(f);
  }

  void Audio::action(itc::prop_change<&Props::stereo>, float s) noexcept
  {
    spread_ = std::max(1.f - 2.f * s, 0.f);
    spread_ *= spread_;
    output_delay.delaySamplesR(1.f + spread_ * spread_max_samples);
    pingpong_ = std::max(0.f, 2.f * s - 1.f);
  }

  void Audio::action(itc::prop_change<&Props::stereo_invert>, bool inv) noexcept
  {
    invert_ = inv;
  }

  audio::ProcessData<2> Audio::process(audio::ProcessData<1> data) noexcept
  {
    auto buf = services::AudioManager::current().buffer_pool().allocate_multi<2>();
    for (auto&& [dat, bufL, bufR] : util::zip(data.audio, buf[0], buf[1])) {
      auto in = input_filter(dat); // Filter
      // Read next value from first delay line - don't input new one yet
      auto out0 = delay_line[0]();
      auto out1 = delay_line[1](feedback_ * loop_filter[0](out0));
      delay_line[0](in + feedback_ * loop_filter[1](out1));

      // Transform outputs to left/right signals
      bufL = output_delay(out0 + (1.f - pingpong_) * out1);
      bufR = (1.f - pingpong_) * out0 + out1;  

      if (invert_) std::swap(bufL, bufR);
    }
    return data.with(buf);
  }

} // namespace otto::engines::pingpong
