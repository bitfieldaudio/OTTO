#pragma once

#include "core/engines/engine.hpp"

namespace otto::service::presets {

  /// Error codes. Thrown with exceptions
  enum struct ErrorCode {
    no_such_engine,
    no_such_preset,
  };

  /// EngineManager exceptions. Contain an [ErrorCode]()
  using exception = util::as_exception<ErrorCode>;

  /// Initialize preset manager
  ///
  /// \effects `load_preset_files()`
  void init();

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

  /// Get the name of preset with indx `idx`
  ///
  /// \throws [exception]() with [ErrorCode::no_such_preset]() if no matching
  /// preset was found, or [ErrorCode::no_such_engine]() if no matching engine
  /// was found
  const std::string& name_of_idx(const std::string& engine_name, int idx);

  /// Get the index of preset with name `name`
  ///
  /// \throws [exception]() with [ErrorCode::no_such_preset]() if no matching
  /// preset was found, or [ErrorCode::no_such_engine]() if no matching engine
  /// was found
  int idx_of_name(const std::string& engine_name, const std::string& name);

  /// Apply preset to engine
  ///
  /// \effects Apply preset identified by `name` to `engine`
  ///
  /// \throws [exception]() with [ErrorCode::no_such_preset]() if no matching
  /// preset was found.
  void apply_preset(core::engines::AnyEngine& engine, const std::string& name, bool no_enable_callback = false);

  /// Apply preset to engine
  ///
  /// \effects Apply preset identified by `idx` to `engine`
  ///
  /// \throws [exception]() with [ErrorCode::no_such_preset]() if no matching
  /// preset was found.
  void apply_preset(core::engines::AnyEngine& engine, int idx, bool no_enable_callback = false);
}
