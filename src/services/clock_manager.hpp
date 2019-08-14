#pragma once

#include <array>
#include <memory>
#include <tl/optional.hpp>

#include "core/audio/clock.hpp"
#include "core/service.hpp"
#include "services/application.hpp"

namespace otto::services {

  /// The service managing the clock
  ///
  /// The clock can be started or stopped by an internal or external source,
  /// and should be used by the sequencer, the looper, and arpeggiators.
  struct ClockManager : core::Service {
    using ClockCounter = core::clock::ClockCounter;
    using ClockRange = core::clock::ClockRange;
    using Time = core::clock::Time;

    // Initialization //

    ClockManager() noexcept;

    static std::unique_ptr<ClockManager> create_default() noexcept
    {
      return std::make_unique<ClockManager>();
    }

    static ClockManager& current() noexcept {
      return *Application::current().clock_manager;
    }

    // Member funcs //

    // Accessors //

    float bpm() const noexcept;
    int samples_pr_beat() const noexcept;
    bool running() const noexcept;

    // Modifiers //

    void set_bpm(float bpm) noexcept;
    void start() noexcept;
    void stop(bool reset = true) noexcept;
    void reset() noexcept;

    ClockRange step_frames(int nframes);

  private:
    bool running_ = false;
    float bpm_ = 0;
    int samples_pr_beat_ = 0;
    ClockCounter counter_;
  };


} // namespace otto::services
