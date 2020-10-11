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

namespace otto::services {

  struct AudioDriver {
    struct CallbackData {
      const util::stereo_audio_buffer& input;
      util::stereo_audio_buffer& output;
    };
    using Callback = fu2::unique_function<void(CallbackData in)>;

    virtual ~AudioDriver() = default;

    virtual void set_callback(Callback&&) = 0;
    virtual void start() = 0;
    virtual std::size_t buffer_size() const = 0;
    virtual std::size_t sample_rate() const = 0;

    static std::unique_ptr<AudioDriver> make_default();
  };

  struct Audio final : core::Service<Audio>, itc::ExecutorProvider {
    using CallbackData = AudioDriver::CallbackData;
    using Callback = AudioDriver::Callback;
    /// A {@ref itc::Consumer} with the executor hardcoded to `Audio::executor()`
    template<itc::AState State>
    struct Consumer;

    Audio(util::any_ptr<AudioDriver>::factory&& d = AudioDriver::make_default);

    void set_process_callback(Callback&& cb) noexcept;
    util::AudioBufferPool& buffer_pool() noexcept;
    void enqueue_midi(midi::MidiEvent e) noexcept;
    void set_midi_handler(util::any_ptr<midi::IMidiHandler> h) noexcept;
    unsigned buffer_count() noexcept;
    void wait_for_n_buffers(int n) noexcept;

  private:
    void loop_func(CallbackData data) noexcept;

    [[no_unique_address]] core::ServiceAccessor<Runtime> runtime;

    util::any_ptr<AudioDriver> driver_;
    Callback callback_ = nullptr;
    moodycamel::ConcurrentQueue<midi::MidiEvent> midi_queue_;
    util::any_ptr<midi::IMidiHandler> midi_handler_;
    tl::optional<util::AudioBufferPool> abp_ = tl::nullopt;
    std::atomic<unsigned> buffer_count_ = 0;
  };


  template<itc::AState State>
  struct Audio::Consumer : itc::Consumer<State> {
    Consumer(itc::Channel<State>& c) : itc::Consumer<State>(c, audio->executor()) {}

  private:
    [[no_unique_address]] core::ServiceAccessor<Audio> audio;
  };

} // namespace otto::services
