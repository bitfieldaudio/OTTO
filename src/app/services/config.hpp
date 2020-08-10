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

  template<typename Derived>
  struct Config : IConfig {
    util::string_ref get_name() const noexcept final
    {
      if constexpr (requires {
                      {
                        Derived::name
                      }
                      ->std::convertible_to<util::string_ref>;
                    }) {
        return Derived::name;
      } else {
        return util::qualified_name_of<Derived>;
      }
    }

    void to_toml(toml::value& val) const override
    {
      if constexpr (util::AVisitable<Derived>) {
        static_cast<const Derived&>(*this).visit([&](util::string_ref name, const auto& v) { //
          val[name.c_str()] = v;
        });
      } else {
        OTTO_UNREACHABLE("{} must either implement visit or override to_toml and from_toml", util::name_of<Derived>);
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
        OTTO_UNREACHABLE("{} must either implement visit or override to_toml and from_toml", util::name_of<Derived>);
      }
    }
  };

  template<typename T>
  concept AConfig = std::is_base_of_v<IConfig, T>;

  namespace services {

    struct ConfigManager : core::Service<ConfigManager> {
      ConfigManager() = default;
      ConfigManager(toml::value config_data) : config_data_(std::move(config_data)) {}
      ConfigManager(std::filesystem::path config_path)
        : ConfigManager(toml::parse<toml::preserve_comments>(config_path))
      {}

      template<AConfig Conf>
      const Conf& register_config() noexcept
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
      bool is_registered() const noexcept
      {
        return configs_.contains(key_of<Conf>());
      }

      /// Get registered config object
      template<AConfig Conf>
      const Conf& get() const
      {
        return static_cast<Conf&>(*configs_.at(key_of<Conf>()));
      }

    private:
      template<AConfig Conf>
      static constexpr const char* key_of() noexcept
      {
        return util::qualified_name_of<Conf>.c_str();
      }

      toml::value config_data_;
      std::pmr::unordered_map<const char*, std::unique_ptr<IConfig>> configs_;
    };

  } // namespace services

} // namespace otto
