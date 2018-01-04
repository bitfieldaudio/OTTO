#pragma once

#include "core/engines/engine.hpp"
#include "core/engines/engine_dispatcher.hpp"

#include "core/audio/processor.hpp"

#include "util/result.hpp"

namespace otto::engines {

  /// Type used to identify position on tape
  using TapeTime = int;
  /// Type used to identify time by bars
  using BeatPos = int;

  namespace tape_state {
    int position();
    float playSpeed();
    bool playing();
  }

  namespace metronome_state {
    TapeTime bar_time(BeatPos bar);
    TapeTime bar_time_rel(BeatPos bar);
    float bar_for_time(std::size_t time);
    std::size_t time_for_bar(float time);
  }

  /// Initialize engine manager
  ///
  /// \effects
  ///  - register engines.
  ///  - construct engines
  ///  - register key handlers
  ///  - attach state loader/saver
  void init();

  /// Mark engines as started
  ///
  /// \effects
  /// Invoke [AnyEngine::on_enable]() for all selected engines
  ///
  /// \requires [services::state::load]() must have been invoked
  void start();

  /// Destruct engines
  ///
  /// \effects Invoke [AnyEngine::on_disable]() for all enabled engines
  void shutdown();

  /// Process the engine audio chain
  audio::ProcessData<2> process(audio::ProcessData<1> external_in);

  /// Get an engine by name
  ///
  /// \returns `nullptr` if no such engine was found
  AnyEngine* const by_name(const std::string& name) noexcept;

} // namespace otto::engines

