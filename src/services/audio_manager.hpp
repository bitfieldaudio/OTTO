#pragma once

#include <memory>

#include "core/audio/processor.hpp"
#include "core/service.hpp"
#include "services/debug_ui.hpp"
#include "util/signals.hpp"
#include "util/locked.hpp"
#include "itc/action_queue.hpp"

#include "services/application.hpp"

namespace otto::services {

  struct AudioManager : core::Service {

    /// Fires Events::pre_init and generates midi frequency table.
    ///
    /// @note @ref _buffer_pool is constructed
    /// with a buffer size of 1. The subclass needs to change this using
    /// AudioBufferPool::set_buffer_size as soon as possible
    AudioManager();

    /// Use this to get audio buffers. There are currently a maximum of 4 avaliable, so make sure to
    /// release them when you're done with them!
    core::audio::AudioBufferPool& buffer_pool() noexcept;

    /// Push-only access to the action queue
    /// 
    /// This queue is consumed at the start of each buffer.
    itc::PushOnlyActionQueue& action_queue() noexcept;

    /// Make an {@ref ActionQueueHelper} for the audio action queue
    template<typename... Recievers>
    auto make_aqh(Recievers&...) noexcept;

    /// Send a midi event into the system.
    ///
    /// The `core::midi` namespace has some nice utils for constructing events.
    void send_midi_event(core::midi::AnyMidiEvent) noexcept;

    /// Get the samplerate
    int samplerate() const noexcept { return _samplerate; }

    /// Get the buffer size
    int buffer_size() const noexcept { return _buffer_size; }

    /// Get the current buffer number
    /// 
    /// i.e. number of {@ref buffer_size()} chunks of samples since the start
    /// 
    /// Can be used to wait until the current process call is over
    unsigned buffer_number() const noexcept { return _buffer_number; }

    /// Block at least until the current process call is done
    void wait_one() const noexcept;

    /// Start audio processing
    ///
    /// Sets `running() = true`
    void start() noexcept;

    /// Check if audio should be processed
    ///
    /// \returns `true` if start() has been called
    bool running() noexcept;

    /// The amount of cpu time spent on average since the last call to this function
    float cpu_time() noexcept;

    /// Get the current instance of this service
    /// 
    /// Alias to `Application::current().audio_manager`
    static AudioManager& current() noexcept {
      return Application::current().audio_manager;
    }

    struct Events {
      /// Triggered first in constructor
      util::Signal<> pre_init;
    } events;

  protected:
    /// Must be called by implementations before the actual processing is performed
    /// 
    /// Executes the items in the action queue, and increments the buffer number
    void pre_process_tasks() noexcept;

    util::double_buffered<core::midi::shared_vector<core::midi::AnyMidiEvent>> midi_bufs = {{}, {}};
    std::atomic_int _samplerate = 48000;
    std::atomic_uint _buffer_size = 256;
    std::atomic_uint _buffer_number = 0;
    util::audio::Graph _cpu_time;
    itc::ActionQueue action_queue_;
  private:
    core::audio::AudioBufferPool _buffer_pool{1};
    std::atomic_bool _running{false};
  };

  // IMPLEMENTATION //

  template<typename... Recievers>
  auto AudioManager::make_aqh(Recievers&... recievers) noexcept {
    return itc::ActionQueueHelper(action_queue_, recievers...);
  }

} // namespace otto::services
