#include "state.hpp"
#include "core/globals.hpp"
#include "util/jsonfile.hpp"
#include "util/exception.hpp"
#include "services/logger.hpp"

namespace otto::services::state {
  namespace {
    struct Client {
      std::string name;
      loader load;
      saver save;
    };

    struct State {
      std::map<std::string, Client> clients;
      util::JsonFile data_file{global::data_dir / "state.json"};
      bool loaded = false;

      static State& instance()
      {
        static State* pInstance;

        if (!pInstance) {
          pInstance = new State();
        }

        return *pInstance;
      }

      void load()
      {
        data_file.read(util::JsonFile::OpenOptions::create);

        auto& data = data_file.data();

        if (!data.is_object()) {
          LOG_F(ERROR, "Got unexpected json from {}", data_file.path());
          data = {};
        }

        loaded = true;

        for (const auto & [ name, client ] : clients) {
          client.load(data[name]);
        }
      }

      void save()
      {
        if (!loaded) {
          return;
        }

        auto& data = data_file.data();

        data.clear();

        for (const auto & [ name, client ] : clients) {
          data[name] = client.save();
        }

        data_file.write();
      }

      void attach(std::string name, loader load, saver save)
      {
        if (clients.find(name) != clients.end()) {
          throw util::exception("Tried to attach a state client with the same name as another: " + name);
        }

        clients[name] = {name, load, save};

        if (loaded) {
          auto& data = data_file.data();
          load(data[name]);
        }
      }

      void detach(std::string name)
      {
        if (clients.find(name) == clients.end()) {
          throw util::exception(
            "Tried to detach a state client that was never attached: " + name);
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

  void attach(std::string name, loader load, saver save)
  {
    State::instance().attach(name, load, save);
  }

  void detach(std::string name)
  {
    State::instance().detach(name);
  }
} // namespace otto::services::state
