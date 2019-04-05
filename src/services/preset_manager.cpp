#include "preset_manager.hpp"

#include "services/debug_ui.hpp"

namespace otto::services {

  PresetManager::PresetManager()
  {
    load_preset_files();
  }

  const std::vector<std::string>& PresetManager::preset_names(util::string_ref engine_name)
  {
    auto eg_found = _preset_data.find(engine_name);
    if (eg_found == _preset_data.end()) {
      eg_found = _preset_data.insert(std::string(engine_name), PresetNamesDataPair{}).iter();
    }
    return eg_found->value.names;
  }

  const std::string& PresetManager::name_of_idx(util::string_ref engine_name, int idx)
  {
    auto& names = preset_names(engine_name);
    if (idx < 0 || static_cast<std::size_t>(idx) >= names.size()) {
      throw exception(ErrorCode::no_such_preset, "Preset index {} is out range for engine '{}'",
                      idx, engine_name);
    }
    return names[idx];
  }

  int PresetManager::idx_of_name(util::string_ref engine_name, std::string_view name)
  {
    auto& names = preset_names(engine_name);
    auto found = util::find(names, name);
    if (found == names.end()) {
      throw exception(ErrorCode::no_such_preset, "No preset named '{}' for engine '{}'", name,
                      engine_name);
    }
    return found - names.begin();
  }

  void PresetManager::apply_preset(core::engine::IEngine& engine,
                                   std::string_view name,
                                   bool no_enable_callback)
  {
    auto pd_iter = _preset_data.find(engine.name());
    if (pd_iter == _preset_data.end()) {
      throw exception(ErrorCode::no_such_engine, "No engine named '{}'", engine.name());
    }
    auto niter = util::find(pd_iter->value.names, name);
    if (niter == pd_iter->value.names.end()) {
      throw exception(ErrorCode::no_such_preset, "No preset named '{}' for engine '{}'", name,
                      engine.name());
    }
    DLOGI("Applying preset {} to engine {}", name, engine.name());
    int idx = niter - pd_iter->value.names.begin();
    engine.from_json(pd_iter->value.data[idx]);
    engine.current_preset(idx);
  }

  void PresetManager::apply_preset(core::engine::IEngine& engine, int idx, bool no_enable_callback)
  {
    auto pd_iter = _preset_data.find(engine.name());
    if (pd_iter == _preset_data.end()) {
      throw exception(ErrorCode::no_such_engine, "No engine named '{}'", engine.name());
    }
    auto& pd = pd_iter->value;
    if (idx < 0 || static_cast<std::size_t>(idx) >= pd.data.size()) {
      throw exception(ErrorCode::no_such_preset, "Preset index {} is out range for engine '{}'",
                      idx, engine.name());
    }
    DLOGI("Applying preset {} to engine {}", pd.names[idx], engine.name());
    try {
      engine.from_json(pd.data[idx]);
    } catch(std::exception& e) {
      throw util::exception("Error applying preset: {}", e.what());
    }
    engine.current_preset(idx);
  }

  void PresetManager::load_preset_files()
  {
    LOG_SCOPE_FUNCTION(INFO);
    if (!fs::exists(presets_dir)) {
      DLOGI("Creating preset directory");
      fs::create_directories(presets_dir);
    }
    DLOGI("Loading presets");
    for (auto&& de : fs::recursive_directory_iterator(presets_dir)) {
      if (de.is_directory()) continue;
      auto filename = de.path().filename().string();
      if (filename.size() == 0 || filename.c_str()[0] == '.') continue;
      LOGI_SCOPE("Loading preset file {}", de.path());
      if (de.is_regular_file() || de.is_symlink()) {
        util::JsonFile jf{de.path()};
        jf.read();
        std::string engine = jf.data()["engine"];
        std::string name = jf.data()["name"];
        auto pd_iter = _preset_data.emplace(engine).iter();
        auto& pd = pd_iter->value;
        if (auto found = util::find(pd.names, name); found != pd.names.end()) {
          pd.data[found - pd.names.begin()] = std::move(jf.data()["props"]);
          DLOGI("Reloaded preset '{}' for engine '{}", name, engine);
        } else {
          pd.names.push_back(name);
          pd.data.emplace_back(std::move(jf.data()["props"]));
          DLOGI("Loaded preset '{}' for engine '{}", name, engine);
        }
      }
    }
  }

  void PresetManager::create_preset(util::string_ref engine_name,
                                    std::string_view preset_name,
                                    const nlohmann::json& preset_data)
  {
    LOG_SCOPE_FUNCTION(INFO);
    util::JsonFile jf{presets_dir / engine_name.c_str() / (std::string(preset_name) + ".json")};

    jf.data() = nlohmann::json::object();
    jf.data()["engine"] = engine_name;
    jf.data()["name"] = preset_name;
    jf.data()["props"] = preset_data;

    jf.write(util::JsonFile::OpenOptions::create);

    load_preset_files();
  }

} // namespace otto::services
