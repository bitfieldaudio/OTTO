#pragma once

#include "core/engine/engine.hpp"
#include "itc/itc.hpp"

namespace otto::engines::sends {

  using namespace core::props;

  struct Screen;

  using Sender = services::UISender<Screen>;

  struct Props {
    Sender sender;

    Sender::Prop<struct mix_tag, float> mix = {sender, 0, limits(0, 1), step_size(0.01)};
    Sender::Prop<struct sendAB_tag, float> sendAB = {sender, 0, limits(0, 1), step_size(0.01)};
    Sender::Prop<struct pan_tag, float> pan = {sender, 0, limits(0, 1), step_size(0.01)};
    Sender::Prop<struct volume_tag, float> volume = {sender, 0.4, limits(0, 1), step_size(0.01)};

    DECL_REFLECTION(Props, mix, sendAB, pan, volume);
  };

  struct Sends : core::engine::MiscEngine<Sends> {
    static constexpr util::string_ref name = "Sends";

    Sends();

    void encoder(core::input::EncoderEvent e) override;

    void recalculate();

    core::ui::ScreenAndInput screen() override;

    std::unique_ptr<Screen> screen_;

    Props props;

    /// Actual values used in the enginemanager
    float dryL = 1;
    float dryR = 1;
    float to_fx1 = 0;
    float to_fx2 = 0;

  };
} // namespace otto::engines::sends

#include "screen.hpp"