#pragma once

#include <memory_resource>
#include <unordered_map>

#include "lib/toml.hpp"
#include "lib/util/crtp.hpp"
#include "lib/util/string_ref.hpp"
#include "lib/util/visitor.hpp"

#include "lib/core/service.hpp"

namespace otto {

  struct IConfig : toml::TomlSerializable {
    virtual ~IConfig() = default;
    virtual util::string_ref get_name() const noexcept = 0;
  };

  template<typename T>
  concept AConfig = std::is_base_of_v<IConfig, T>;

  namespace services {

    struct ConfigManager : core::Service<ConfigManager> {
      ConfigManager() = default;
      /// Initialize the configurations from a toml object
      ConfigManager(toml::value config_data);
      /// Initialize the configurations from a toml file
      ConfigManager(std::filesystem::path config_path);

      /// Register a config type, and initialize it from the config data
      template<AConfig Conf>
      const Conf& register_config() noexcept;

      /// Check whether a config type has been registered
      template<AConfig Conf>
      bool is_registered() const noexcept;

      /// Get registered config object
      template<AConfig Conf>
      const Conf& get() const;

      static core::ServiceHandle<ConfigManager> make_default()
      {
        std::filesystem::path config_path = "./ottoconf.toml";
        if (std::filesystem::is_regular_file(config_path)) {
          return core::make_handle<ConfigManager>(config_path);
        }
        return core::make_handle<ConfigManager>();
      }

      toml::value into_toml() const;

    private:
      template<AConfig Conf>
      static constexpr const char* key_of() noexcept;

      toml::value config_data_;
      std::pmr::unordered_map<const char*, std::unique_ptr<IConfig>> configs_;
    };
  } // namespace services

  /// CRTP Base class for Config objects.
  template<typename Derived>
  struct Config : IConfig {
    /// The name as it will be shown in the config file
    ///
    /// Can be overridden in `Derived` by defining a similar constant.
    static constexpr util::string_ref name = util::qualified_name_of<Derived>;

    util::string_ref get_name() const noexcept final
    {
      return Derived::name;
    }

    void to_toml(toml::value& val) const override
    {
      if constexpr (util::AVisitable<Derived>) {
        static_cast<const Derived&>(*this).visit([&](util::string_ref name, const auto& v) { //
          val[name.c_str()] = v;
        });
      } else {
        // Find a way to make this a compile time error?
        OTTO_UNREACHABLE("{} must either implement visit or override to_toml and from_toml",
                         util::qualified_name_of<Derived>);
      }
    }

    void from_toml(const toml::value& val) override
    {
      if constexpr (util::AVisitable<Derived>) {
        static_cast<Derived&>(*this).visit([&](util::string_ref name, auto& v) { //
          try {
            v = toml::find<std::remove_reference_t<decltype(v)>>(val, name.c_str());
          } catch (std::out_of_range& e) {
            LOGI("Using default value for option {}.{}", get_name(), name);
          }
        });
      } else {
        // Find a way to make this a compile time error?
        OTTO_UNREACHABLE("{} must either implement visit or override to_toml and from_toml",
                         util::qualified_name_of<Derived>);
      }
    }
  };

} // namespace otto

// Implementations:
namespace otto::services {


  inline ConfigManager::ConfigManager(toml::value config_data) : config_data_(std::move(config_data)) {}
  inline ConfigManager::ConfigManager(std::filesystem::path config_path)
    : ConfigManager(toml::parse<toml::preserve_comments>(config_path))
  {}

  inline toml::value ConfigManager::into_toml() const
  {
    toml::value res = config_data_;
    for (auto& [k, v] : configs_) {
      v->to_toml(res[v->get_name().c_str()]);
    }
    return res;
  }

  template<AConfig Conf>
  const Conf& ConfigManager::register_config() noexcept
  {
    auto ptr = std::make_unique<Conf>();
    auto& res = *ptr;
    try {
      res.from_toml(config_data_[res.get_name().c_str()]);
    } catch (const std::exception& e) {
      LOGW("Error in config {}, using default: ", res.get_name());
      LOGW("{}", e.what());
    }
    configs_[key_of<Conf>()] = std::move(ptr);
    return res;
  }

  template<AConfig Conf>
  bool ConfigManager::is_registered() const noexcept
  {
    return configs_.contains(key_of<Conf>());
  }
  template<AConfig Conf>
  const Conf& ConfigManager::get() const
  {
    return static_cast<Conf&>(*configs_.at(key_of<Conf>()));
  }
  template<AConfig Conf>
  constexpr const char* ConfigManager::key_of() noexcept
  {
    return util::qualified_name_of<Conf>.c_str();
  }

} // namespace otto::services
