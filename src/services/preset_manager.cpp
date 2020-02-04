#include "preset_manager.hpp"

#include "services/debug_ui.hpp"

#include "util/flat_map.hpp"

namespace otto::services {

  struct DefaultPresetManager final : PresetManager {

    /// Initialize preset manager
    ///
    /// \effects `load_preset_files()`
    DefaultPresetManager();

    /// Get the names of presets for an engine
    ///
    /// These presets can be applied using @ref apply_preset(AnyEngine&, const std::string_view) or
    /// @ref apply_preset(AnyEngine&, int)
    ///
    /// \throws @ref exception with @ref ErrorCode::no_such_engine if no matching
    /// engine was found.
    ///
    /// \remarks This design is chosen so the engine manager has complete control
    /// over the actual preset data. Also it makes sense for the
    /// @ref otto::engines::EngineSelectorScreen, which is probably the only place
    /// that really needs access
    const std::vector<std::string>& preset_names(util::string_ref engine_name) override;

    /// Get the name of preset with indx `idx`
    ///
    /// \throws @ref exception with @ref ErrorCode::no_such_preset if no matching
    /// preset was found, or @ref ErrorCode::no_such_engine if no matching engine
    /// was found
    const std::string& name_of_idx(util::string_ref engine_name, int idx) override;

    /// Get the index of preset with name `name`
    ///
    /// \throws @ref exception with @ref ErrorCode::no_such_preset if no matching
    /// preset was found, or @ref ErrorCode::no_such_engine if no matching engine
    /// was found
    int idx_of_name(util::string_ref engine_name, std::string_view name) override;

    /// Apply preset to engine
    ///
    /// \effects Apply preset identified by `name` to `engine`
    ///
    /// \throws @ref exception with @ref ErrorCode::no_such_preset if no matching
    /// preset was found.
    void apply_preset(core::engine::IEngine& engine,
                      std::string_view name,
                      bool no_enable_callback = false) override;

    /// Apply preset to engine
    ///
    /// \effects Apply preset identified by `idx` to `engine`
    ///
    /// \throws @ref exception with @ref ErrorCode::no_such_preset if no matching
    /// preset was found.
    void apply_preset(core::engine::IEngine& engine, int idx, bool no_enable_callback = false) override;

    void create_preset(util::string_ref engine_name,
                       std::string_view preset_name,
                       const nlohmann::json& preset_data) override;

  private:

    /// (Re)load preset files
    ///
    /// Invoked by @ref init. Call to reload all preset files.
    ///
    /// \throws @ref filesystem::filesystem_error
    void load_preset_files();

    struct PresetNamesDataPair {
      std::vector<std::string> names;
      std::vector<nlohmann::json> data;
    };

    // Key is engine name.
    // This design is chosen because we want to expose the names vector
    // separately.
    util::flat_map<std::string, PresetNamesDataPair> _preset_data;

    const fs::path presets_dir = Application::current().data_dir / "presets";
  };

  std::unique_ptr<PresetManager> PresetManager::create_default() {
    return std::make_unique<DefaultPresetManager>();
  }

  DefaultPresetManager::DefaultPresetManager()
  {
    load_preset_files();
  }

  const std::vector<std::string>& DefaultPresetManager::preset_names(util::string_ref engine_name)
  {
    auto eg_found = _preset_data.find(engine_name);
    if (eg_found == _preset_data.end()) {
      eg_found = _preset_data.insert(std::string(engine_name), PresetNamesDataPair{}).first;
    }
    return eg_found->second.names;
  }

  const std::string& DefaultPresetManager::name_of_idx(util::string_ref engine_name, int idx)
  {
    auto& names = preset_names(engine_name);
    if (idx < 0 || static_cast<std::size_t>(idx) >= names.size()) {
      throw exception(ErrorCode::no_such_preset, "Preset index {} is out range for engine '{}'",
                      idx, engine_name);
    }
    return names[idx];
  }

  int DefaultPresetManager::idx_of_name(util::string_ref engine_name, std::string_view name)
  {
    auto& names = preset_names(engine_name);
    auto found = nano::find(names, name);
    if (found == names.end()) {
      throw exception(ErrorCode::no_such_preset, "No preset named '{}' for engine '{}'", name,
                      engine_name);
    }
    return found - names.begin();
  }

  void DefaultPresetManager::apply_preset(core::engine::IEngine& engine,
                                   std::string_view name,
                                   bool no_enable_callback)
  {
    auto pd_iter = _preset_data.find(engine.name());
    if (pd_iter == _preset_data.end()) {
      throw exception(ErrorCode::no_such_engine, "No engine named '{}'", engine.name());
    }
    auto niter = nano::find(pd_iter->second.names, name);
    if (niter == pd_iter->second.names.end()) {
      throw exception(ErrorCode::no_such_preset, "No preset named '{}' for engine '{}'", name,
                      engine.name());
    }
    DLOGI("Applying preset {} to engine {}", name, engine.name());
    int idx = niter - pd_iter->second.names.begin();
    engine.from_json(pd_iter->second.data[idx]);
    engine.current_preset(idx);
  }

  void DefaultPresetManager::apply_preset(core::engine::IEngine& engine, int idx, bool no_enable_callback)
  {
    auto pd_iter = _preset_data.find(engine.name());
    if (pd_iter == _preset_data.end()) {
      throw exception(ErrorCode::no_such_engine, "No engine named '{}'", engine.name());
    }
    auto& pd = pd_iter->second;
    if (idx < 0 || static_cast<std::size_t>(idx) >= pd.data.size()) {
      throw exception(ErrorCode::no_such_preset, "Preset index {} is out range for engine '{}'",
                      idx, engine.name());
    }
    DLOGI("Applying preset {} to engine {}", pd.names[idx], engine.name());
    try {
      engine.from_json(pd.data[idx]);
    } catch(std::exception& e) {
      LOGE("Error applying preset: {}", e.what());
      return;
    }
    engine.current_preset(idx);
  }

  void DefaultPresetManager::load_preset_files()
  {
    LOGI_SCOPE(__PRETTY_FUNCTION__);
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
        std::string engine = jf.data().at("engine");
        std::string name = jf.data().at("name");
        auto pd_iter = _preset_data.insert(engine, {}).first;
        auto& pd = pd_iter->second;
        if (auto found = nano::find(pd.names, name); found != pd.names.end()) {
          pd.data[found - pd.names.begin()] = std::move(jf.data().at("props"));
          DLOGI("Reloaded preset '{}' for engine '{}", name, engine);
        } else {
          pd.names.push_back(name);
          pd.data.emplace_back(std::move(jf.data()["props"]));
          DLOGI("Loaded preset '{}' for engine '{}", name, engine);
        }
      }
    }
  }

  void DefaultPresetManager::create_preset(util::string_ref engine_name,
                                    std::string_view preset_name,
                                    const nlohmann::json& preset_data)
  {
    LOGI_SCOPE(__PRETTY_FUNCTION__);
    util::JsonFile jf{presets_dir / engine_name.c_str() / (std::string(preset_name) + ".json")};

    jf.data() = nlohmann::json::object();
    jf.data()["engine"] = engine_name;
    jf.data()["name"] = preset_name;
    jf.data()["props"] = preset_data;

    jf.write(util::JsonFile::OpenOptions::create);

    load_preset_files();
  }

} // namespace otto::services
