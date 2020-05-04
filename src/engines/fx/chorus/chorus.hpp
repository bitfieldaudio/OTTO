#pragma once

#include "core/engine/engine.hpp"
#include "itc/action_bus.hpp"
#include "itc/itc.hpp"

namespace otto::engines::chorus {

  using namespace core::props;

  struct Screen;
  struct Audio;

  struct Props : core::props::Properties<Props> {
    itc::GAProp<struct delay_tag, float> delay = {0.8, limits(0, 1), step_size(0.01)};
    itc::GAProp<struct rate_tag, float> rate = {0, limits(0, 2), step_size(0.02)};
    itc::GAProp<struct feedback_tag, float> feedback = {0, limits(-0.99, 0.99), step_size(0.02)};
    itc::GAProp<struct depth_tag, float> depth = {0.5, limits(0, 1), step_size(0.01)};
    REFLECT_PROPS(Props, delay, depth, feedback, rate);
  };

  struct Chorus : core::engine::EffectEngine<Chorus>, itc::ActionReceiverOnBus<itc::LogicBus> {
    static constexpr util::string_ref name = "Chorus";
    Chorus(itc::ActionChannel);

    void encoder(core::input::EncoderEvent e) override;

    core::ui::ScreenAndInput screen() override;

  private:
    itc::Shared<float>::Storage shared_phase_;

  public:
    const std::unique_ptr<Audio> audio;
    Props props;

  private:
    const std::unique_ptr<Screen> screen_;
  };

} // namespace otto::engines::chorus
