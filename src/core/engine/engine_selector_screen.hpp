#pragma once

#include "core/ui/vector_graphics.hpp"
#include "engine_dispatcher.hpp"

namespace otto::core::engine {

  using namespace std::literals;

  BETTER_ENUM(ESSSubscreen, //
              std::int8_t,
              engine_selection,
              preset_selection,
              new_preset);

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

  void placeholder_engine_icon(ui::IconData& i, nvg::Canvas& ctx);

  template<EngineSlot ES>
  struct EngineSelectorScreen : ui::Screen,
                                itc::ActionReceiverOnBus<itc::GraphicsBus,
                                                         input::EncoderAction,
                                                         input::KeyPressAction,
                                                         typename SelectedEngine<ES>::action,
                                                         typename SelectedPreset<ES>::action,
                                                         typename Actions<ES>::publish_engine_data> //

  {
    using Subscreen = ESSSubscreen;

    void draw(nvg::Canvas& ctx) override;

    void action(input::EncoderAction, input::EncoderEvent e) noexcept final;
    void action(input::KeyPressAction, input::Key) noexcept final;

    void action(typename SelectedEngine<ES>::action, int selected) noexcept final;
    void action(typename SelectedPreset<ES>::action, int selected) noexcept final;
    void action(typename Actions<ES>::publish_engine_data, EngineSelectorData data) noexcept final;
    void navigate_to(Subscreen screen);

    std::vector<EngineSelectorData> engines = {};

  private:
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

  extern template struct EngineSelectorScreen<EngineSlot::arp>;
  extern template struct EngineSelectorScreen<EngineSlot::synth>;
  extern template struct EngineSelectorScreen<EngineSlot::fx1>;
  extern template struct EngineSelectorScreen<EngineSlot::fx2>;

} // namespace otto::core::engine
