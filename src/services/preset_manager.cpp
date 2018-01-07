#include "preset_manager.hpp"

#include "core/globals.hpp"

namespace otto::presets {

  namespace {
    struct PresetNamesDataPair {
      std::vector<std::string> names;
      std::vector<nlohmann::json> data;
    };

    // Key is engine name.
    // This design is chosen because we want to expose the names vector
    // separately.
    std::map<std::string, PresetNamesDataPair> _preset_data;

    const fs::path presets_dir = global::data_dir / "presets";
  }

  const std::vector<std::string>& preset_names(const std::string& engine_name)
  {
    auto eg_found = _preset_data.find(engine_name);
    if (eg_found == _preset_data.end()) {
      throw exception(ErrorCode::no_such_engine, "No presets for engine: {}", engine_name);
    }
    return eg_found->second.names;
  }

  const std::string& name_of_idx(const std::string& engine_name, int idx)
  {
    auto& names = preset_names(engine_name);
    if (idx < 0 || static_cast<std::size_t>(idx) >= names.size()) {
      throw exception(ErrorCode::no_such_preset,
                      "Preset index {} is out range for engine '{}'", idx,
                      engine_name);
    }
    return names[idx];
  }

  int idx_of_name(const std::string& engine_name, const std::string& name)
  {
    auto& names = preset_names(engine_name);
    auto found = util::find(names, name);
    if (found == names.end()) {
      throw exception(ErrorCode::no_such_preset,
                      "No preset named '{}' for engine '{}'", name,
                      engine_name);
    }
    return found - names.begin();
  }

  void apply_preset(engines::AnyEngine& engine, const std::string& name, bool no_enable_callback)
  {
    auto& pd   = _preset_data[engine.name()];
    auto niter = util::find(pd.names, name);
    if (niter == pd.names.end()) {
      throw exception(ErrorCode::no_such_preset,
                      "No preset named '{}' for engine '{}'", name,
                      engine.name());
    }
    DLOGI("Applying preset {} to engine {}", name, engine.name());
    int idx = niter - pd.names.begin();
    engine.props().from_json(pd.data[idx]);
    engine.current_preset(idx);
    if (!no_enable_callback) engine.on_enable();
  }

  void apply_preset(engines::AnyEngine& engine, int idx, bool no_enable_callback)
  {
    auto& pd = _preset_data[engine.name()];
    if (idx < 0 || static_cast<std::size_t>(idx) >= pd.data.size()) {
      throw exception(ErrorCode::no_such_preset,
                      "Preset index {} is out range for engine '{}'", idx,
                      engine.name());
    }
    DLOGI("Applying preset {} to engine {}", pd.names[idx], engine.name());
    engine.props().from_json(pd.data[idx]);
    engine.current_preset(idx);
    if (!no_enable_callback) engine.on_enable();
  }

  void load_preset_files()
  {
    LOG_SCOPE_FUNCTION(INFO);
    if (!fs::exists(presets_dir)) {
      DLOGI("Creating preset directory");
      fs::create_directories(presets_dir);
    }
    decltype(_preset_data) new_preset_data;
    DLOGI("Loading presets");
    for (auto&& de : fs::recursive_directory_iterator(presets_dir)) {
      LOGI_SCOPE("Loading preset file {}", de.path());
      if (de.is_regular_file() || de.is_symlink()) {
        util::JsonFile jf{de.path()};
        jf.read();
        auto&& engine = jf.data()["engine"];
        auto&& name   = jf.data()["name"];
        auto& pd      = new_preset_data[engine];
        pd.names.push_back(name);
        pd.data.emplace_back(std::move(jf.data()["props"]));
        DLOGI("Loaded preset '{}' for engine '{}", name, engine);
      }
    }
    _preset_data = std::move(new_preset_data);
  }


}
