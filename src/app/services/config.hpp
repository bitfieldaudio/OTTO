#pragma once

#include <filesystem>
#include <memory_resource>
#include <unordered_map>

#include "lib/util/crtp.hpp"
#include "lib/util/name_of.hpp"
#include "lib/util/serialization.hpp"
#include "lib/util/string_ref.hpp"
#include "lib/util/visitor.hpp"

#include "lib/json.hpp"

namespace otto {
  /// CRTP Base class for Config objects.
  template<typename Derived>
  struct Config {
    /// The name as it will be shown in the config file
    ///
    /// Can be overridden in `Derived` by defining a similar constant.
    static constexpr util::string_ref name = util::qualified_name_of<Derived>;

    [[nodiscard]] util::string_ref get_name() const noexcept
    {
      return Derived::name;
    }
  };

  template<typename T>
  concept AConfig = std::is_base_of_v<Config<T>, T>&& util::ASerializable<T>;

  namespace services {

    struct ConfigManager {
      ConfigManager() = default;
      /// Initialize the configurations from a json object
      ConfigManager(json::value config_data);
      /// Initialize the configurations from a json file
      ConfigManager(const std::filesystem::path& config_path);

      ~ConfigManager();

      void write_to_file();

      /// Construct a config type, and initialize it from the config data
      ///
      /// Also adds the constructed data back to the stored json
      template<AConfig Conf>
      Conf make_conf() noexcept;

      template<AConfig Conf>
      operator Conf() noexcept
      {
        return make_conf<Conf>();
      }

      /// Attempts to read the default config file `./ottoconf.json`.
      ///
      /// If this file is not found, simply runs the default constructor
      static ConfigManager make_default()
      {
        std::filesystem::path config_path = "./ottoconf.json";
        if (std::filesystem::is_regular_file(config_path)) {
          return ConfigManager(config_path);
        }
        LOGI("Config file {} not found", config_path.c_str());
        return ConfigManager();
      }

      [[nodiscard]] json::value into_json() const;

    private:
      template<AConfig Conf>
      static constexpr const char* key_of() noexcept;

      std::filesystem::path file_path = "";
      json::value config_data_ = json::object();
    };
  } // namespace services

} // namespace otto

// Implementations:
namespace otto::services {

  inline ConfigManager::ConfigManager(json::value config_data) : config_data_(std::move(config_data)) {}

  inline ConfigManager::ConfigManager(const std::filesystem::path& config_path)
  try : ConfigManager(json::parse_file(config_path)) {
    file_path = config_path;
  } catch (std::runtime_error& e) {
    LOGE("Error reading config file:");
    LOGE("{}", e.what());
  }

  inline void ConfigManager::write_to_file()
  {
    if (file_path.empty()) return;
    LOGI("Writing config to {}", file_path.c_str());
    json::write_to_file(into_json(), file_path);
  }

  inline ConfigManager::~ConfigManager()
  {
    if (!file_path.empty()) write_to_file();
  }

  inline json::value ConfigManager::into_json() const
  {
    return config_data_;
  }

  template<AConfig Conf>
  Conf ConfigManager::make_conf() noexcept
  {
    Conf res;
    auto& data = config_data_[res.get_name().c_str()];
    try {
      util::deserialize_from(data, res);
    } catch (const std::out_of_range& e) {
      LOGI("Error in config {}, using default: ", res.get_name());
      LOGI("{}", e.what());
    } catch (const std::exception& e) {
      LOGW("Error in config {}, using default: ", res.get_name());
      LOGW("{}", e.what());
    }
    try {
      util::serialize_into(data, res);
    } catch (const std::exception& e) {
      LOGW("Error serializing config, overwriting");
      data = util::serialize(res);
    }
    return res;
  }

  template<AConfig Conf>
  constexpr const char* ConfigManager::key_of() noexcept
  {
    return util::qualified_name_of<Conf>.c_str();
  }

} // namespace otto::services
