#pragma once

#include "core/ui/icons.hpp"
#include "core/ui/vector_graphics.hpp"
#include "engine_dispatcher.hpp"

namespace otto::core::engine {

  using namespace std::literals;

  struct WriterUI {
    static constexpr std::array character_groups = {
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"sv,
      "abcdefghijklmnopqrstuvwxyz"sv,
      "0123456789,.-=<>()[]{}*#? "sv,
    };

    std::int8_t cursor() const noexcept
    {
      return char_idx_;
    }

    void step_idx(std::int8_t delta = 1) noexcept;
    void cycle_group(std::int8_t delta = 1) noexcept;
    void cycle_char(std::int8_t delta = 1) noexcept;

    std::string to_string(bool trim = false) const noexcept;

  private:
    struct GroupCharPair {
      std::int8_t group = 2;
      std::int8_t character = 25;
    };
    std::int8_t char_idx_ = 0;
    std::array<GroupCharPair, 12> characters_;
    // TODO:
    std::string cached_str_;
  };

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

  using EngineDispatcherReturnChannel = itc::DynamicActionSender<SelectedEngine::action, SelectedPreset::action>;

  struct EngineSelectorScreen : ui::Screen {
    using Subscreen = ESSSubscreen;

    EngineSelectorScreen(EngineDispatcherReturnChannel ret) : return_channel(std::move(ret)) {}

    void draw(nvg::Canvas& ctx) override;

    void action(input::EncoderAction, input::EncoderEvent e);

    void action(SelectedEngine::action, int selected);
    void action(SelectedPreset::action, int selected);
    void action(PublishEngineNames::action, gsl::span<const util::string_ref>);
    void navigate_to(Subscreen screen);

    std::vector<EngineSelectorData> engines = {};

  private:
    EngineDispatcherReturnChannel return_channel;
    bool first_engine_is_off_ = false;
    int selected_engine_ = 0;
    int selected_preset_ = 0;
    ESSSubscreen current_screen = ESSSubscreen::engine_selection;
    WriterUI preset_name_writer;
    ch::Output<float> engine_scroll_ = 0;
    ch::Output<float> page_flip_ = 0;
    ch::Output<float> preset_scroll_ = 0;
    ch::Output<float> new_indicator_transparency_ = 0;
  };
} // namespace otto::core::engine
