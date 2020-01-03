#pragma once

#include "core/engine/engine.hpp"
#include "itc/itc.hpp"

namespace otto::engines::external {

  using namespace core::props;

  struct Screen;
  struct Audio;

  using Sender = services::UISender<Audio, Screen>;

  struct Props {
    Sender sender;

    /// Input gain
    Sender::Prop<struct gain_tag, float> gain = {sender, 0.5, limits(0, 1), step_size(0.01)};
    /// On/off control
    Sender::Prop<struct enabled_tag, bool> enabled = {sender, true};
    /// Stereo balance of the sound mixed down and sent to the effects. 0: L -> FX. 0.5: L+R -> FX, 1: R -> FX.
    /// Audio to dry is just normal sound (panned by sends)
    Sender::Prop<struct balance_tag, float> stereo_balance = {sender, 0.5, limits(0, 1), step_size(0.01)};
    /// TBD: Possible uses would be how to mix down to effects, such as L+R -> FX1, FX2 or L->FX1, R->FX
    /// The property `stereo_balance` could then be the deviation from the 'simple' L+R to all FX
    Sender::Prop<struct routing_tag, int, wrap> stereo_routing = {sender, 0, limits(0, 2)};


    DECL_REFLECTION(Props, gain, enabled, stereo_routing, stereo_balance);
  };

  struct External : core::engine::MiscEngine<External> {
    static constexpr util::string_ref name = "External";

    External();

    void encoder(core::input::EncoderEvent e) override;

    core::ui::ScreenAndInput screen() override;

    std::unique_ptr<Audio> audio;
    std::unique_ptr<Screen> screen_;

    Props props;
  };
} // namespace otto::engines::external

#include "audio.hpp"
#include "screen.hpp"