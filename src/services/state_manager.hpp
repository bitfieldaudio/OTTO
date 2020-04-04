#pragma once

#include <functional>
#include <json.hpp>
#include <string>

#include "core/service.hpp"
#include "services/application.hpp"
#include "util/flat_map.hpp"

namespace otto::services {

  struct StateManager : core::Service {
    /// Decoder
    using Loader = std::function<void(nlohmann::json& json)>;
    /// Encoder
    using Saver = std::function<nlohmann::json()>;

    /// Read `data/state.json` and invoke attached loaders
    virtual void load() = 0;

    /// Invoke attached savers and write `data/state.json`
    virtual void save() = 0;

    /// Attach state handler with a name
    ///
    /// \throws [otto::util::exception]() If a handler has already been attached
    /// with the name `name`
    virtual void attach(std::string name, Loader load, Saver save) = 0;

    /// Detach a state handler
    ///
    /// \throws [otto::util::exception]() If no such handler is attached
    virtual void detach(std::string name) = 0;

    static std::unique_ptr<StateManager> create_default();

  protected:

    struct Client {
      std::string name;
      Loader load;
      Saver save;
    };

    bool _loaded = false;
    util::flat_map<std::string, Client> _clients;
  };

} // namespace otto::services
