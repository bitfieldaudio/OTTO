#include "audio_manager.hpp"

#include <Gamma/Domain.h>

namespace otto::services {

  AudioManager::AudioManager()
  {
    events.pre_init.emit();
    core::midi::generateFreqTable(440);
  }

  core::audio::AudioBufferPool& AudioManager::buffer_pool() noexcept
  {
    return _buffer_pool;
  }

  core2::PushOnlyActionQueue& AudioManager::action_queue() noexcept
  {
    return action_queue_;
  }

  void AudioManager::start() noexcept
  {
    _running = true;
  }

  bool AudioManager::running() noexcept
  {
    return _running;
  }

  void AudioManager::wait_one() const noexcept
  {
    auto last = buffer_number();
    if (last == 0) return;
    while (last >= (buffer_number() - 1))
      ;
  }

  void AudioManager::send_midi_event(core::midi::AnyMidiEvent evt) noexcept
  {
    midi_bufs.outer().emplace_back(std::move(evt));
  }

  float AudioManager::cpu_time() noexcept
  {
    float res = _cpu_time;
    _cpu_time.clear();
    return res;
  }

  void AudioManager::pre_process_tasks() noexcept
  {
    _buffer_number++;
    auto running = this->running() && Application::current().running();
    if (running) {
      action_queue_.pop_call_all();
    }
  }

} // namespace otto::services
