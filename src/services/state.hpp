#pragma once

#include <functional>
#include <json.hpp>
#include <string>

namespace otto::services::state {
  using loader = std::function<void(nlohmann::json& json)>;
  using saver  = std::function<nlohmann::json()>;

  void load();
  void save();
  void attach(std::string name, loader load, saver save);
  void detach(std::string name);
} // namespace otto::services::state
