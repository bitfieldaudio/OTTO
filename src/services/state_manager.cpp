#include "state_manager.hpp"

#include "services/application.hpp"
#include "services/log_manager.hpp"

#include "util/exception.hpp"
#include "util/jsonfile.hpp"

namespace otto::services {

  struct DefaultStateManager : StateManager {
    DefaultStateManager();
    ~DefaultStateManager();

    util::JsonFile data_file;

    void load() override;
    void save() override;
    void attach(std::string name, Loader load, Saver save) override;

    void detach(std::string name) override;
  };

  std::unique_ptr<StateManager> StateManager::create_default()
  {
    return std::make_unique<DefaultStateManager>();
  }

  DefaultStateManager::DefaultStateManager()
    : data_file(Application::current().data_dir / "state.json")
  {
    Application::current().events.post_init.connect([this] { load(); });
    Application::current().events.pre_exit.connect([this] { save(); });
  }

  DefaultStateManager::~DefaultStateManager() {}

  void DefaultStateManager::load()
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

    for (const auto&& [name, client] : _clients) {
      try {
        client.load(data[name]);
      } catch (std::exception& e) {
        LOGE("Exception while loading state for {}: {}", name, e.what());
      }
    }

    _loaded = true;
  }

  void DefaultStateManager::save()
  {
    if (!_loaded) {
      return;
    }

    auto& data = data_file.data();

    data.clear();

    for (const auto&& [name, client] : _clients) {
      data[name] = client.save();
    }

    data_file.write();
  }

  void DefaultStateManager::attach(std::string name, Loader load, Saver save)
  {
    if (_clients.find(name) != _clients.end()) {
      throw util::exception("Tried to attach a state client with the same name as another: " +
                            name);
    }

    // cannot move load, used below
    _clients.insert_or_assign(name, Client{name, load, std::move(save)});

    if (_loaded) {
      auto& data = data_file.data();
      load(data[name]);
    }
  }

  void DefaultStateManager::detach(std::string name)
  {
    if (_clients.find(name) == _clients.end()) {
      throw util::exception("Tried to detach a state client that was never attached: " + name);
    }

    _clients.erase(name);
  }

} // namespace otto::services
