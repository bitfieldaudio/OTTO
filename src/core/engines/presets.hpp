#pragma once

#include "util/jsonfile.hpp"

#include "core/engines/engine.hpp"

namespace otto::engines {

  /// # OTTO Preset format
  ///
  /// OTTO Presets are defined in a json file with the following layout:
  ///
  /// ```json
  /// {
  ///   "OTTO Preset": {
  ///     "Version": 0,
  ///     "Name": "/* Name */"
  ///   },
  ///   "Engines": {
  ///     "/* Group */": {
  ///       "Engine": "/* Engine */",
  ///       "Data": "/* Engine specific data */"
  ///     },
  ///     "/* Group */": {
  ///       "Engine": "/* Engine */",
  ///       "Data": "/* Engine specific data */"
  ///     },
  ///   }
  /// }
  /// ```
  ///
  ///  - `Version` is a file format version number, currently at `0`
  ///  - `Group` is one of `"Drums"`, `"Synth"` or `"Effect"`. Each preset can
  ///    define one engine in each group
  ///  - `Engine` is an engine id string, as it is registered in
  ///    `EngineRegistry`
  ///  - `Data` is the serialized data for the engine, normally an object.
  ///
  /// At some point it will be possible to embed similar data in a sample file,
  /// but currently you need to supply both a sample file and a preset file
  struct PresetFile : util::JsonFile {
    using util::JsonFile::ErrorCode;
    using util::JsonFile::OpenOptions;
    using util::JsonFile::exception;

    /// Constructor
    ///
    /// \effects delegate to `util::JsonFile(p)`
    /// \postconditions as `util::JsonFile(p)`, and `validate() ==
    /// ErrorCode::none` \remarks remember to `read()` after construction
    explicit PresetFile(const fs::path& p);

    /// Confirm the presence of the header and `Engines` section, as well as the
    /// version number.
    ErrorCode validate() const noexcept override;

    /// Get the name of this preset
    std::string name() const;

    /// Get a json object refering to the `Engines` section.
    nlohmann::json& json_engines();

    /// Get a json object refering to the `Engines` section.
    std::vector<EngineData> engines() const;

    /// Get a json object with an engine, defined by its group
    EngineData engine(EngineType group);

    /// Get a json object with an engine, defined by its group
    const nlohmann::json& engine(const std::string& group) const;

    /// Get a json object with an engine, defined by its group
    nlohmann::json& operator[](const std::string& group);

    /// Get a json object with an engine, defined by its group
    const nlohmann::json& operator[](const std::string& group) const;
  };
}
