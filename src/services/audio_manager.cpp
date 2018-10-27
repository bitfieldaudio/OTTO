#include "audio_manager.hpp"

namespace otto::services {

  AudioManager::AudioManager()
  {
    events.pre_init.fire();
    core::midi::generateFreqTable(440);
  }

  core::audio::AudioBufferPool& AudioManager::buffer_pool() noexcept
  {
    return _buffer_pool;
  }

  void AudioManager::start() noexcept
  {
    _running = true;
  }

  bool AudioManager::running() noexcept
  {
    return _running;
  }

  void AudioManager::send_midi_event(core::midi::AnyMidiEvent evt) noexcept
  {
    midi_bufs.outer().emplace_back(std::move(evt));
  }

  void AudioManager::process_audio_output(core::audio::ProcessData<2> audio_output) {}

} // namespace otto::services
