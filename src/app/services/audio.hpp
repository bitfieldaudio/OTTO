#pragma once

#include <tl/optional.hpp>

#include "lib/util/audio_buffer.hpp"
#include "lib/util/smart_ptr.hpp"

#include "lib/core/service.hpp"
#include "lib/itc/executor.hpp"
#include "lib/itc/executor_provider.hpp"
#include "lib/itc/itc.hpp"
#include "lib/midi.hpp"

#include "app/drivers/audio_driver.hpp"
#include "app/services/runtime.hpp"

namespace otto::services {
  namespace detail {
    struct audio_domain_tag;
  }

  struct Audio final : core::Service<Audio>, itc::ExecutorProvider<detail::audio_domain_tag> {
    using CallbackData = drivers::IAudioDriver::CallbackData;
    using Callback = drivers::IAudioDriver::Callback;

    Audio(util::smart_ptr<drivers::IAudioDriver>::factory&& d = drivers::IAudioDriver::make_default);

    void set_process_callback(Callback&& cb) noexcept;
    util::AudioBufferPool& buffer_pool() noexcept;
    void enqueue_midi(midi::MidiEvent e) noexcept;
    void set_midi_handler(util::smart_ptr<midi::IMidiHandler> h) noexcept;
    unsigned buffer_count() noexcept;
    void wait_for_n_buffers(int n) noexcept;

  private:
    void loop_func(CallbackData data) noexcept;

    [[no_unique_address]] core::ServiceAccessor<Runtime> runtime;

    util::smart_ptr<drivers::IAudioDriver> driver_;
    Callback callback_ = nullptr;
    moodycamel::ConcurrentQueue<midi::MidiEvent> midi_queue_;
    util::smart_ptr<midi::IMidiHandler> midi_handler_;
    tl::optional<util::AudioBufferPool> abp_ = tl::nullopt;
    std::atomic<unsigned> buffer_count_ = 0;
  };
} // namespace otto::services

namespace otto {

  struct AudioDomain : itc::StaticDomain<services::detail::audio_domain_tag> {};

} // namespace otto
