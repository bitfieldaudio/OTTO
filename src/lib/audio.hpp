#pragma once

#include "lib/util/audio_buffer.hpp"

#include "lib/midi.hpp"

namespace otto {

  template<util::function_sig Func>
  struct IAudioProcessor;

  template<typename Ret, typename... Args>
  struct IAudioProcessor<Ret(Args...)> {
    virtual ~IAudioProcessor() = default;
    virtual Ret process(Args...) = 0;
  };

  struct ISynthAudio : IAudioProcessor<util::audio_buffer()> {
    virtual midi::IMidiHandler& midi_handler() noexcept = 0;
  };
} // namespace otto
