#include "presets.hpp"

#include "core/globals.hpp"
#include "services/debug_ui.hpp"

namespace otto::service::presets {

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

  static void draw_debug_info();

  void init() {
    debug_ui::add_info(draw_debug_info);

    load_preset_files();
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

  void apply_preset(core::engines::AnyEngine& engine, const std::string& name, bool no_enable_callback)
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
    engine.props().as<core::props::serializable>().from_json(pd.data[idx]);
    engine.current_preset(idx);
    if (!no_enable_callback) engine.on_enable();
  }

  void apply_preset(core::engines::AnyEngine& engine, int idx, bool no_enable_callback)
  {
    auto& pd = _preset_data[engine.name()];
    if (idx < 0 || static_cast<std::size_t>(idx) >= pd.data.size()) {
      throw exception(ErrorCode::no_such_preset,
                      "Preset index {} is out range for engine '{}'", idx,
                      engine.name());
    }
    DLOGI("Applying preset {} to engine {}", pd.names[idx], engine.name());
    engine.props().as<core::props::serializable>().from_json(pd.data[idx]);
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
        std::string name   = jf.data()["name"];
        auto& pd           = _preset_data[engine];
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

  static void create_preset(const std::string& engine_name,
                            const std::string& preset_name,
                            const nlohmann::json& preset_data)
  {
    LOG_SCOPE_FUNCTION(INFO);
    util::JsonFile jf{presets_dir / engine_name / (preset_name + ".json")};

    jf.data() = nlohmann::json::object();
    jf.data()["engine"] = engine_name;
    jf.data()["name"] = preset_name;
    jf.data()["props"] = preset_data;

    jf.write(util::JsonFile::OpenOptions::create);
  }

}
// Debug UI /////////////////////////////////////////////////////////////////

#if OTTO_DEBUG_UI

#include "services/ui.hpp"
#include "services/engines.hpp"

namespace otto::service::presets {

  static void draw_debug_info()
  {
    ImGui::Begin("Presets");

    static std::string engine_name;
    static char preset_name[256] = "";
    static nlohmann::json preset_data;

    if (ImGui::Button("Create preset")) {
      auto engine = engines::by_name(ui::selected_engine_name());
      if (engine != nullptr) {
        engine_name = engine->name();
        preset_data = engine->props().as<core::props::serializable>().to_json();
        ImGui::OpenPopup("New preset");
      }
    }
    if (ImGui::BeginPopup("New preset")) {
      ImGui::Text("Engine: %s", engine_name.c_str());
      ImGui::InputText("Preset Name", preset_name, 256);
      if (ImGui::Button("Create preset")) {
        create_preset(engine_name, std::string(preset_name), preset_data);
        load_preset_files();
        ImGui::CloseCurrentPopup();
      }
      if (ImGui::Button("Cancel")) {
        ImGui::CloseCurrentPopup();
      }

      ImGui::EndPopup();
    }

    ImGui::End();
  }
}

#else

namespace otto::service::presets {
  static void draw_debug_info() {}
}
#endif
