#pragma once

#include "core/ui/vector_graphics.hpp"
#include "core/engine/engine_dispatcher.hpp"

namespace otto::board::wifi {

  using namespace std::literals;

  // Connection Manager interface
  struct Network 
  {
    Network(std::string n) : name(n) {}
    std::string name;
    int strength = 1;
    int ID = 0;
  };

  struct WiFiManager
  {
    virtual ~WiFiManager() = default;
    virtual gsl::span<Network> get_networks() = 0;
  };

  BETTER_ENUM(WFSSSubscreen, //
              std::int8_t,
              network_selection,
              password);

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

    std::string to_string(bool trim = true) const noexcept;

    void clear() noexcept;

  private:
    struct GroupCharPair {
      std::int8_t group = 2;
      std::int8_t character = 25;
    };
    std::int8_t char_idx_ = 0;
    std::array<GroupCharPair, 12> characters_ = {};
    // TODO:
    std::string cached_str_;
  };

  void placeholder_network_icon(core::ui::IconData& i, nvg::Canvas& ctx);

  struct NetworkSelectorScreen : core::ui::Screen {
    using Subscreen = WFSSSubscreen;

    NetworkSelectorScreen(WiFiManager& wifiman) 
    {
      nano::copy(wifiman.get_networks(), nano::back_inserter(networks));
    }

    void draw(nvg::Canvas& ctx) override;

    void action(core::input::EncoderAction, core::input::EncoderEvent e);
    void action(core::input::KeyPressAction, core::input::Key);

    void navigate_to(Subscreen screen);

    core::ui::Icon strength_icons(int s);

    std::vector<Network> networks = {};

  private:
    int selected_network_ = 0;
    WFSSSubscreen current_screen = WFSSSubscreen::network_selection;
    WriterUI password_writer;
    ch::Output<float> network_scroll_ = 0;
    ch::Output<float> page_flip_ = 0;
    ch::Output<float> new_indicator_transparency_ = 0;
  };
} // namespace otto::core::engine
