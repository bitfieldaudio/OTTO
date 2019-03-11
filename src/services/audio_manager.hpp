#pragma once

#include <memory>

#include "core/audio/processor.hpp"
#include "core/service.hpp"
#include "services/debug_ui.hpp"
#include "util/event.hpp"
#include "util/locked.hpp"

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

    /// Wait at least until the current process call is done
    void wait_one() const noexcept;

    /// Start audio processing
    ///
    /// \postconditions `running() == true`
    void start() noexcept;

    /// Check if audio should be processed
    ///
    /// \returns `true` if start() has been called
    bool running() noexcept;

    /// The amount of cpu time spent on average since the last call to this function
    float cpu_time() noexcept;

    struct Events {
      util::Event<> pre_init;
    } events;

  protected:
    util::atomic_swap<core::midi::shared_vector<core::midi::AnyMidiEvent>> midi_bufs = {{}, {}};
    std::atomic_int _samplerate = 48000;
    std::atomic_uint _buffer_size = 256;
    std::atomic_uint _buffer_number = 0;
    util::audio::Graph _cpu_time;
  private:
    core::audio::AudioBufferPool _buffer_pool{1};
    std::atomic_bool _running{false};
  };

} // namespace otto::services
