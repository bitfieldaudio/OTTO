#include "clock_manager.hpp"

#include "util/type_traits.hpp"

#include "services/audio_manager.hpp"

namespace otto::services {

  using namespace core;
  using namespace core::clock;

  // Initialization //

  ClockManager::ClockManager() noexcept
  {
    Application::current().events.post_init.connect([this] { set_bpm(120.f); });
  }

  // Accessors //

  float ClockManager::bpm() const noexcept
  {
    return props.bpm.get();
  }

  int ClockManager::samples_pr_beat() const noexcept
  {
    return samples_pr_beat_;
  }

  bool ClockManager::running() const noexcept
  {
    return running_;
  }

  // Modifiers //

  void ClockManager::set_bpm(float bpm) noexcept
  {
    props.bpm = bpm;
    samples_pr_beat_ = AudioManager::current().samplerate() / (bpm / 60.f);
  }

  ClockRange ClockManager::step_frames(int nframes)
  {
    if (running()) {
      counter_.step((notes::beat * nframes + remainder_) / samples_pr_beat_);
      remainder_ = (notes::beat * nframes + remainder_) % samples_pr_beat_;
    }
    return counter_.current();
  }

  void ClockManager::start() noexcept
  {
    running_ = true;
  }
  void ClockManager::stop(bool reset) noexcept
  {
    running_ = false;
    if (reset) this->reset();
  }
  void ClockManager::reset() noexcept
  {
    counter_.reset();
  }

} // namespace otto::services
