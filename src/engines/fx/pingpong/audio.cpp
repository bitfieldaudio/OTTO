#include "audio.hpp"

#include "services/audio_manager.hpp"

namespace otto::engines::pingpong {

  Audio::Audio() noexcept
  {
    delay_line.maxDelay(6.f);
    output_delay.maxDelay(1.f);
    input_filter.set_position(0.6f);
  }

  void Audio::action(itc::prop_change<&Props::delaytime>, float t) noexcept
  {
    delay_line.delay(t);
  }

  void Audio::action(itc::prop_change<&Props::feedback>, float f) noexcept
  {
    feedback_ = f;
  }

  void Audio::action(itc::prop_change<&Props::filter>, float f) noexcept
  {
    input_filter.set_position(f);
    loop_filter.set_position(f);
    DLOGI("LO: {}   HI: {}",input_filter.get_lo_freq(), input_filter.get_hi_freq());
  }

  audio::ProcessData<2> Audio::process(audio::ProcessData<1> data) noexcept
  {
    auto buf = services::AudioManager::current().buffer_pool().allocate_multi<2>();
    for (auto&& [dat, bufL, bufR] : util::zip(data.audio, buf[0], buf[1])) {
      auto in = input_filter(dat); // Filter
      // Read next value - don't input new one yet
      auto out0 = delay_line();
      auto loop0 = loop_filter(out0); // Filter
      delay_line(in + feedback_ * loop0);
      
      bufL = 1.f * out0;
      bufR = 1.f * out0;  
    }
    return data.with(buf);
  }

} // namespace otto::engines::wormhole
