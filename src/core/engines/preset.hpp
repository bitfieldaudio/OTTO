#pragma once

/// \file
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
///     "/* Type */": {
///       "Engine": "/* Engine */",
///       "Data": "/* Engine specific data */"
///     },
///     "/* Type */": {
///       "Engine": "/* Engine */",
///       "Data": "/* Engine specific data */"
///     },
///   }
/// }
/// ```
///
///  - `Version` is a file format version number, currently at `0`
///  - `Type` is one of the types `"Drums"`, `"Synth"` or `"Effect"`. Each
///  - preset can define one engine in each group
///  - `Engine` is an engine id string, as if by [AnyEngine::name()]()
///  - `Data` is the serialized data for the engine, as if by
///    [AnyEngine::to_json()]()
///
/// At some point it will be possible to embed similar data in a sample file,
/// but currently you need to supply both a sample file and a preset file

#include "core/engines/engine.hpp"

namespace otto::engines {

  struct NameJsonPair {
    std::string name;
    nlohmann::json data;
  };

  std::vector<NameJsonPair>& presets_for_engine(const AnyEngine&);

  struct PresetFile : util::JsonFile {
    using util::JsonFile::ErrorCode;
    using util::JsonFile::exception;
    using util::JsonFile::OpenOptions;

    /// Constructor
    ///
    /// \effects delegate to `util::JsonFile(p)`
    /// \postconditions as `util::JsonFile(p)`, and
    /// `validate() == ErrorCode::none`
    /// \remarks remember to `read()` after construction
    explicit PresetFile(const fs::path& p);

    /// Confirm the presence of the header and `Engines` section, as well as the
    /// version number.
    ErrorCode validate() const noexcept override;

    /// Get the name of this preset
    std::string name() const;

    /// Get a json object refering to the `Engines` section.
    nlohmann::json& json_engines();

    /// Get a json object refering to the `Engines` section.
    std::vector<EnginePatch> engines() const;

    /// Get a json object with an engine, defined by its group
    EnginePatch engine(EngineType group);

    /// Get a json object with an engine, defined by its group
    const nlohmann::json& engine(const std::string& group) const;

    /// Get a json object with an engine, defined by its group
    nlohmann::json& operator[](const std::string& group);

    /// Get a json object with an engine, defined by its group
    const nlohmann::json& operator[](const std::string& group) const;
  };

} // namespace otto::engines
