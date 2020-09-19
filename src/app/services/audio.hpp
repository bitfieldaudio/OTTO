#pragma once

#include "lib/itc/executor.hpp"
#include "lib/util/audio_buffer.hpp"

#include "lib/core/service.hpp"

namespace otto::services {

  struct Audio : core::Service<Audio> {
    struct CallbackData {
      const util::stereo_audio_buffer& input;
      util::stereo_audio_buffer& output;
    };
    using Callback = fu2::unique_function<void(CallbackData& in)>;

    virtual void set_process_callback(Callback&& cb) noexcept = 0;
    virtual itc::IExecutor& executor() noexcept = 0;

    [[nodiscard]] static core::ServiceHandle<Audio> make_board();

    virtual util::AudioBufferPool& buffer_pool() noexcept = 0;
  };
} // namespace otto::services
