#pragma once

#include "lib/util/audio_buffer.hpp"

namespace otto {

  template<util::function_sig Func>
  struct IAudioProcessor;

  template<typename Ret, typename... Args>
  struct IAudioProcessor<Ret(Args...)> {
    virtual ~IAudioProcessor() = default;
    virtual Ret process(Args...) = 0;
  };
} // namespace otto
