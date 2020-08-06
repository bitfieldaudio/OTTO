#pragma once

#include "lib/core/service.hpp"

namespace otto::app {

  struct Config {
    virtual ~Config() = default;
  };

  template<typename T>
  concept AConfig = std::is_base_of_v<Config, T>;

  namespace services {

    struct ConfigManager : lib::core::Service<ConfigManager> {
      template<AConfig Conf>
      void register_config() noexcept
      {

      }
    };

  } // namespace services

} // namespace otto::app
