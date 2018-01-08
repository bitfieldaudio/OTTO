#pragma once

#include <functional>
#include <json.hpp>
#include <string>

namespace otto::service::state {
  /// Decoder
  using Loader = std::function<void(nlohmann::json& json)>;
  /// Encoder
  using Saver = std::function<nlohmann::json()>;

  /// Read `data/state.json` and invoke attached loaders
  void load();

  /// Invoke attached savers and write `data/state.json`
  void save();

  /// Attach state handler with a name
  ///
  /// \throws [otto::util::exception]() If a handler has already been attached
  /// with the name `name`
  void attach(std::string name, Loader load, Saver save);

  /// Detach a state handler
  ///
  /// \throws [otto::util::exception]() If no such handler is attached
  void detach(std::string name);

} // namespace otto::service::state
