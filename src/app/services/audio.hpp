#pragma once

#include "lib/itc/executor.hpp"
#include "lib/itc/itc.hpp"
#include "lib/midi.hpp"
#include "lib/util/any_ptr.hpp"
#include "lib/util/audio_buffer.hpp"

#include "lib/core/service.hpp"

namespace otto::services {

  struct Audio : core::Service<Audio> {
    /// A {@ref itc::Consumer} with the executor hardcoded to `Audio::executor()`
    template<itc::AState State>
    struct Consumer;
    struct CallbackData {
      const util::stereo_audio_buffer& input;
      util::stereo_audio_buffer& output;
    };
    using Callback = fu2::unique_function<void(CallbackData& in)>;

    virtual void set_process_callback(Callback&& cb) noexcept = 0;
    virtual itc::IExecutor& executor() noexcept = 0;

    [[nodiscard]] static core::ServiceHandle<Audio> make_board();

    virtual util::AudioBufferPool& buffer_pool() noexcept = 0;

    virtual void set_midi_handler(util::any_ptr<midi::IMidiHandler>) noexcept = 0;
    virtual void enqueue_midi(midi::MidiEvent) = 0;
  };


  template<itc::AState State>
  struct Audio::Consumer : itc::Consumer<State> {
    Consumer(itc::Channel<State>& c) : itc::Consumer<State>(c, audio->executor()) {}

  private:
    [[no_unique_address]] core::ServiceAccessor<Audio> audio;
  };
} // namespace otto::services
