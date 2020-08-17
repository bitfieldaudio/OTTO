#pragma once

#include <memory_resource>
#include <unordered_map>

#include "lib/toml.hpp"
#include "lib/util/crtp.hpp"
#include "lib/util/string_ref.hpp"
#include "lib/util/visitor.hpp"

#include "lib/core/service.hpp"

namespace otto {
  template<typename Conf>
  struct ConfHandle;

  /// CRTP Base class for Config objects.
  template<typename Derived>
  struct Config {
    using Handle = ConfHandle<Derived>;
    /// The name as it will be shown in the config file
    ///
    /// Can be overridden in `Derived` by defining a similar constant.
    static constexpr util::string_ref name = util::qualified_name_of<Derived>;

    // TODO: BUG IN GCC 10.1 - https://godbolt.org/z/qeTM6P
    // This is just there to disable aggregate initialization
    // to circumvent the bug.
    // We should require GCC 10.2 as soon as poky (yocto) uses it
    virtual ~Config() = default;

    util::string_ref get_name() const noexcept
    {
      return Derived::name;
    }

    void to_toml(toml::value& val) const
    {
      static_assert(util::AVisitable<Derived>, "Config types must be visitable. Add DECL_VISIT(members...)");
      static_cast<const Derived&>(*this).visit([&](util::string_ref name, const auto& v) { //
        val[name.c_str()] = v;
      });
    }

    void from_toml(const toml::value& val)
    {
      static_assert(util::AVisitable<Derived>, "Config types must be visitable. Add DECL_VISIT(members...)");
      static_cast<Derived&>(*this).visit([&](util::string_ref name, auto& v) { //
        try {
          v = toml::find<std::remove_reference_t<decltype(v)>>(val, name.c_str());
        } catch (std::out_of_range& e) {
          LOGI("Using default value for option {}.{}", get_name(), name);
        }
      });
    }

    toml::value into_toml() const
    {
      toml::value v;
      static_cast<Derived&>(*this).to_toml(v);
      return v;
    }
  };

  template<typename T>
  concept AConfig = std::is_base_of_v<Config<T>, T>;

  namespace services {

    struct ConfigManager : core::Service<ConfigManager> {
      ConfigManager() = default;
      /// Initialize the configurations from a toml object
      ConfigManager(toml::value config_data);
      /// Initialize the configurations from a toml file
      ConfigManager(std::filesystem::path config_path);

      /// Construct a config type, and initialize it from the config data
      ///
      /// Also adds the constructed data back to the stored toml
      template<AConfig Conf>
      Conf make_conf() noexcept;

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
    };
  } // namespace services


  template<AConfig Conf>
  struct ConfHandle<Conf> {
    ConfHandle() noexcept
      : ConfHandle([&] {
          OTTO_ASSERT(confman.is_active(), "{} constructed with no ConfigManager active",
                      util::qualified_name_of<Conf>);
          return confman->make_conf<Conf>();
        }())
    {}
    ConfHandle(Conf c) noexcept : conf(std::move(c)) {}

    const Conf* operator->() const noexcept
    {
      return &conf;
    }

    const Conf& operator*() const noexcept
    {
      return conf;
    }

  private:
    [[no_unique_address]] core::UnsafeServiceAccessor<services::ConfigManager> confman;
    Conf conf;
  };

} // namespace otto

namespace toml {}

// Implementations:
namespace otto::services {

  inline ConfigManager::ConfigManager(toml::value config_data) : config_data_(std::move(config_data)) {}
  inline ConfigManager::ConfigManager(std::filesystem::path config_path)
    : ConfigManager(toml::parse<toml::preserve_comments>(config_path))
  {}

  inline toml::value ConfigManager::into_toml() const
  {
    return config_data_;
  }

  template<AConfig Conf>
  Conf ConfigManager::make_conf() noexcept
  {
    Conf res;
    auto& data = config_data_[res.get_name().c_str()];
    try {
      res.from_toml(data);
    } catch (const std::exception& e) {
      LOGW("Error in config {}, using default: ", res.get_name());
      LOGW("{}", e.what());
    }
    try {
      res.to_toml(data);
    } catch (const std::exception& e) {
      data = toml::value();
      res.to_toml(data);
    }
    return res;
  }

  template<AConfig Conf>
  constexpr const char* ConfigManager::key_of() noexcept
  {
    return util::qualified_name_of<Conf>.c_str();
  }

} // namespace otto::services
