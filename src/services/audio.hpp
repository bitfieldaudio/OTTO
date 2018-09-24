#pragma once

#include <memory>

#include "core/audio/processor.hpp"
#include "services/debug_ui.hpp"
#include "util/event.hpp"

namespace otto::service::audio {

  using core::audio::ProcessData;
  using core::audio::AudioBufferHandle;
  using core::audio::AudioBufferPool;

  namespace events {
    util::Event<>& pre_init();
    util::Event<unsigned>& buffersize_change();
    util::Event<unsigned>& samplerate_change();
  }

  AudioBufferPool& buffer_pool() noexcept;

  /// Get the current samplerate
  int samplerate() noexcept;

  /// Process the final output
  ///
  /// Currently only used for debugging
  void process_audio_output(ProcessData<2> audio_output);

  /// Initialize components
  ///
  /// \effects
  ///  - Fire [events::pre_init]()
  ///  - Generate midi frequency table
  ///  - Initialize the audio driver
  void init();

  /// Start audio processing
  ///
  /// \postconditions `running() == true`
  void start() noexcept;

  /// Close the audio driver
  void shutdown();

  /// Check if audio is being processed
  ///
  /// \returns `true` if [start()]() has been called and [shutdown()]() hasn't
  bool running() noexcept;

  /// Send a midi event into the system.
  /// 
  /// The `core::midi` namespace has some nice utils for constructing events.
  void send_midi_event(core::midi::AnyMidiEvent) noexcept;
}
