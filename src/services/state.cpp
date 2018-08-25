#include "core/globals.hpp"
#include "services/logger.hpp"
#include "state.hpp"
#include "util/exception.hpp"
#include "util/jsonfile.hpp"

namespace otto::service::state {
  namespace {
    struct Client {
      std::string name;
      Loader load;
      Saver save;
    };

    struct State {
      std::map<std::string, Client> clients;
      util::JsonFile data_file{global::data_dir / "state.json"};
      bool loaded = false;

      State() = default;

      static State& instance()
      {
        static State instance{};
        return instance;
      }

      void load()
      {
        data_file.read(util::JsonFile::OpenOptions::create);

        auto& data = data_file.data();

        if (data.is_null()) {
          data = nlohmann::json::object();
        }
        if (!data.is_object()) {
          LOGF("Got unexpected json from {}", data_file.path());
          data = {};
        }

        for (const auto& [name, client] : clients) {
          try {
            client.load(data[name]);
          } catch (util::exception& e) {
            LOGE("Exception while loading state for {}: {}", name, e.what());
          }
        }

        loaded = true;
      }

      void save()
      {
        if (!loaded) {
          return;
        }

        auto& data = data_file.data();

        data.clear();

        for (const auto& [name, client] : clients) {
          data[name] = client.save();
        }

        data_file.write();
      }

      void attach(const std::string& name, Loader&& load, Saver&& save)
      {
        if (clients.find(name) != clients.end()) {
          throw util::exception("Tried to attach a state client with the same name as another: " +
                                name);
        }

        clients[name] = {name, load, std::move(save)};

        if (loaded) {
          auto& data = data_file.data();
          load(data[name]);
        }
      }

      void detach(const std::string& name)
      {
        if (clients.find(name) == clients.end()) {
          throw util::exception("Tried to detach a state client that was never attached: " + name);
        }

        clients.erase(name);
      }
    };
  } // namespace

  void load()
  {
    State::instance().load();
  }

  void save()
  {
    State::instance().save();
  }

  void attach(std::string name, Loader load, Saver save)
  {
    State::instance().attach(std::move(name), std::move(load), std::move(save));
  }

  void detach(const std::string& name)
  {
    State::instance().detach(name);
  }
} // namespace otto::service::state
