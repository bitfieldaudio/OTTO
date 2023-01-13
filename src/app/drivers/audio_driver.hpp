#pragma once

#include <function2/function2.hpp>

#include "lib/util/audio_buffer.hpp"

#include "app/services/config.hpp"

namespace otto::drivers {
  struct IAudioDriver;
  struct IAudioMixer {
    virtual ~IAudioMixer() = default;

    virtual void set_volume(float) = 0;
    [[nodiscard]] virtual float get_volume() const = 0;

    static std::unique_ptr<IAudioMixer> make_default(IAudioDriver&);
    static std::unique_ptr<IAudioMixer> make_software(IAudioDriver&);
  };

  struct IAudioDriver {
    struct CallbackData {
      const util::stereo_audio_buffer& input;
      util::stereo_audio_buffer& output;
    };
    using Callback = fu2::unique_function<void(CallbackData in)>;

    virtual ~IAudioDriver() = default;

    virtual void set_callback(Callback&&) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    [[nodiscard]] virtual std::size_t buffer_size() const = 0;
    [[nodiscard]] virtual std::size_t sample_rate() const = 0;
    virtual IAudioMixer& mixer() = 0;

    static std::unique_ptr<IAudioDriver> make_default(services::ConfigManager&);
  };
} // namespace otto::drivers
