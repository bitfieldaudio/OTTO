#pragma once

#include <memory>

#include "core/audio/processor.hpp"
#include "core/service.hpp"
#include "services/debug_ui.hpp"
#include "util/event.hpp"

#include "services/application.hpp"

namespace otto::services {

  struct AudioManager : core::Service {
    struct Events {
      util::Event<> pre_init;
    } events;

    /// Use this to get audio buffers. There are currently a maximum of 4 avaliable, so make sure to
    /// release them when you're done with them!
    core::audio::AudioBufferPool& buffer_pool() noexcept;

    /// Get the current samplerate
    virtual int samplerate() noexcept = 0;

    /// Process the final output
    ///
    /// Currently only used for debugging
    virtual void process_audio_output(core::audio::ProcessData<2> audio_output);

    /// Fires Events::pre_init and generates midi frequency table.
    ///
    /// @note @ref _buffer_pool is constructed
    /// with a buffer size of 1. The subclass needs to change this using
    /// AudioBufferPool::set_buffer_size as soon as possible
    AudioManager();

    /// Start audio processing
    ///
    /// \postconditions `running() == true`
    virtual void start() noexcept;

    /// Check if audio should be processed
    ///
    /// \returns `true` if start() has been called
    virtual bool running() noexcept;

    /// Send a midi event into the system.
    ///
    /// The `core::midi` namespace has some nice utils for constructing events.
    virtual void send_midi_event(core::midi::AnyMidiEvent) noexcept = 0;

  protected:
    core::audio::AudioBufferPool _buffer_pool {1};
    std::atomic_bool _running{false};
  };

} // namespace otto::services
