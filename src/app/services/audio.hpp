#pragma once

#include <tl/optional.hpp>
#include "app/services/runtime.hpp"
#include "lib/itc/executor.hpp"
#include "lib/itc/executor_provider.hpp"
#include "lib/itc/itc.hpp"
#include "lib/midi.hpp"
#include "lib/util/any_ptr.hpp"
#include "lib/util/audio_buffer.hpp"

#include "lib/core/service.hpp"

#include "app/drivers/audio_driver.hpp"

namespace otto::services {

  struct Audio final : core::Service<Audio>, itc::ExecutorProvider {
    using CallbackData = drivers::IAudioDriver::CallbackData;
    using Callback = drivers::IAudioDriver::Callback;
    template<itc::AState... States>
    struct Consumer;

    Audio(util::any_ptr<drivers::IAudioDriver>::factory&& d = drivers::IAudioDriver::make_default);

    void set_process_callback(Callback&& cb) noexcept;
    util::AudioBufferPool& buffer_pool() noexcept;
    void enqueue_midi(midi::MidiEvent e) noexcept;
    void set_midi_handler(util::any_ptr<midi::IMidiHandler> h) noexcept;
    unsigned buffer_count() noexcept;
    void wait_for_n_buffers(int n) noexcept;

  private:
    void loop_func(CallbackData data) noexcept;

    [[no_unique_address]] core::ServiceAccessor<Runtime> runtime;

    util::any_ptr<drivers::IAudioDriver> driver_;
    Callback callback_ = nullptr;
    moodycamel::ConcurrentQueue<midi::MidiEvent> midi_queue_;
    util::any_ptr<midi::IMidiHandler> midi_handler_;
    tl::optional<util::AudioBufferPool> abp_ = tl::nullopt;
    std::atomic<unsigned> buffer_count_ = 0;
  };


  /// A {@ref itc::Consumer} with the executor hardcoded to `Audio::executor()`
  template<itc::AState... States>
  struct Audio::Consumer : itc::Consumer<States...> {
    Consumer(itc::ChannelGroup& c) : itc::Consumer<States>(c, audio->executor())... {}

    using itc::Consumer<States>::state...;
    using itc::Consumer<States>::channel...;

  private:
    [[no_unique_address]] core::ServiceAccessor<Audio> audio;
  };

} // namespace otto::services
