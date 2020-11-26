#pragma once

#include "app/drivers/audio_driver.hpp"

namespace otto::stubs {
  struct StubAudioDriver : drivers::IAudioDriver {
    void set_callback(Callback&& cb) override
    {
      callback = std::move(cb);
    }
    void start() override {}
    [[nodiscard]] std::size_t buffer_size() const override
    {
      return 64;
    }
    [[nodiscard]] std::size_t sample_rate() const override
    {
      return 44100;
    }

    Callback callback;
  };
} // namespace otto::stubs
