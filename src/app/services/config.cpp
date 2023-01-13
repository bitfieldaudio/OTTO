#include "config.hpp"

#include <utility>

namespace otto::services {

  ConfigManager::ConfigManager(json::value config_data) : config_data_(std::move(config_data)) {}

  ConfigManager::ConfigManager(const std::filesystem::path& config_path)
  try : ConfigManager(json::parse_file(config_path)) {
    file_path = config_path;
  } catch (json::value::parse_error& e) {
    LOGW("Config file parse error!");
    LOGW("{}", e.what());
    auto new_path = config_path;
    new_path += ".corrupt";
    std::filesystem::rename(config_path, new_path);
    LOGW("Config file has been backed up as {}", new_path);
  } catch (std::runtime_error& e) {
    LOGW("Error reading config file:");
    LOGW("{}", e.what());
  }

  void ConfigManager::write_to_file()
  {
    if (file_path.empty()) return;
    LOGI("Writing config to {}", file_path.c_str());
    json::write_to_file(into_json(), file_path);
  }

  ConfigManager::~ConfigManager() = default;

  json::value ConfigManager::into_json() const
  {
    return config_data_;
  }

  void ConfigManager::set_option(const json::pointer& pointer, json::value value)
  {
    config_data_[pointer] = std::move(value);
  }
} // namespace otto::services
