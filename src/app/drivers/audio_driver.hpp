#pragma once

#include <function2/function2.hpp>

#include "lib/util/audio_buffer.hpp"

namespace otto::drivers {
  struct IAudioDriver {
    struct CallbackData {
      const util::stereo_audio_buffer& input;
      util::stereo_audio_buffer& output;
    };
    using Callback = fu2::unique_function<void(CallbackData in)>;

    virtual ~IAudioDriver() = default;

    virtual void set_callback(Callback&&) = 0;
    virtual void start() = 0;
    [[nodiscard]] virtual std::size_t buffer_size() const = 0;
    [[nodiscard]] virtual std::size_t sample_rate() const = 0;

    static std::unique_ptr<IAudioDriver> make_default();
  };
} // namespace otto::drivers
