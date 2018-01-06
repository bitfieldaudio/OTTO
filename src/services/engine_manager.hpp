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

  /// Error codes. Thrown with exceptions
  enum struct ErrorCode {
    no_such_engine,
    no_such_preset,
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
  audio::ProcessData<2> process(audio::ProcessData<1> external_in);

  /// Get an engine by name
  ///
  /// \returns `nullptr` if no such engine was found
  AnyEngine* const by_name(const std::string& name) noexcept;

  /// (Re)load preset files
  ///
  /// Invoked by [init](). Call to reload all preset files.
  ///
  /// \throws [filesystem::filesystem_error]() 
  void load_preset_files();

  /// Get the names of presets for an engine
  ///
  /// These presets can be applied using
  /// [apply_preset(AnyEngine&, const std::string&)]() or
  /// [apply_preset(AnyEngine&, int)]()
  ///
  /// \throws [exception]() with [ErrorCode::no_such_engine]() if no matching
  /// engine was found.
  ///
  /// \remarks This design is chosen so the engine manager has complete control
  /// over the actual preset data. Also it makes sense for the
  /// [otto::engines::EngineSelectorScreen](), which is probably the only place
  /// that really needs access
  const std::vector<std::string>& preset_names(const std::string& engine_name);

  /// Apply preset to engine
  ///
  /// \effects Apply preset identified by `name` to `engine`
  ///
  /// \throws [exception]() with [ErrorCode::no_such_preset]() if no matching
  /// preset was found.
  void apply_preset(AnyEngine& engine, const std::string& name);

  /// Apply preset to engine
  ///
  /// \effects Apply preset identified by `idx` to `engine`
  ///
  /// \throws [exception]() with [ErrorCode::no_such_preset]() if no matching
  /// preset was found.
  void apply_preset(AnyEngine& engine, int idx);

} // namespace otto::engines
