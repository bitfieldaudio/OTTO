#pragma once

#include "core/engines/engine.hpp"
#include "core/engines/engine_dispatcher.hpp"

#include "core/audio/processor.hpp"

#include "util/result.hpp"

namespace otto::service::engines {

  /// Type used to identify position on tape
  using TapeTime = int;
  /// Type used to identify time by bars
  using BeatPos = int;

  /// Error codes. Thrown with exceptions
  enum struct ErrorCode {
    no_such_engine,
  };

  /// EngineManager exceptions. Contain an [ErrorCode]()
  using exception = util::as_exception<ErrorCode>;

  namespace tape_state {
    int position();
    float playSpeed();
    bool playing();
  } // namespace tape_state

  namespace metronome_state {
    TapeTime bar_time(BeatPos bar);
    TapeTime bar_time_rel(BeatPos bar);
    float bar_for_time(std::size_t time);
    std::size_t time_for_bar(float time);
  } // namespace metronome_state

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
  core::audio::ProcessData<2> process(core::audio::ProcessData<1> external_in);

  /// Get an engine by name
  ///
  /// \returns `nullptr` if no such engine was found
  core::engines::AnyEngine* const by_name(const std::string& name) noexcept;

} // namespace otto::service::engines
