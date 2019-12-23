#pragma once

#include "core/ui/icons.hpp"
#include "core/ui/vector_graphics.hpp"
#include "engine_dispatcher.hpp"

namespace otto::core::engine {

  void placeholder_engine_icon(ui::IconData& i, nvg::Canvas& ctx);

  struct EngineSelectorData {
    util::string_ref name;
    ui::Icon icon = {placeholder_engine_icon};
    std::vector<std::string> presets = name == "Potion"
                                         ? std::vector<std::string>{"Last state"}
                                         : std::vector<std::string>{
                                             "Last State", "Yard",     "Wren", "Orange", "Smash",  "Pies", "Desire",
                                             "Base",       "Religion", "Tent", "Branch", "Needle", "Egg",
                                           };
  };

  struct EngineSelectorScreen : ui::Screen {
    void draw(nvg::Canvas& ctx) override;

    void action(SelectedEngine::action, int selected);
    void action(SelectedPreset::action, int selected);
    void action(CurrentScreen::action, int screen);
    void action(PublishEngineNames::action, gsl::span<const util::string_ref>);

    std::vector<EngineSelectorData> engines = {};

  private:
    bool first_engine_is_off_ = false;
    int selected_engine_ = 0;
    ch::Output<float> engine_scroll_ = 0;
    ch::Output<float> page_flip_ = 0;
    int selected_preset_ = 0;
    ch::Output<float> preset_scroll_ = 0;
    ch::Output<float> new_indicator_transparency_ = 0;
  };
} // namespace otto::core::engine
