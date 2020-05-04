#pragma once

#include "core/engine/engine.hpp"

#include "itc/itc.hpp"

namespace otto::engines::wormhole {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct Screen;
  struct Audio;

  struct Props : core::props::Properties<Props> {
    itc::GAProp<struct filter_tag, float> filter = {0, limits(0, 1), step_size(0.01)};
    itc::GAProp<struct shimmer_tag, float> shimmer = {0, limits(0, 1), step_size(0.01)};
    itc::GAProp<struct length_tag, float> length = {0.5, limits(0, 1), step_size(0.01)};
    itc::GAProp<struct damping_tag, float> damping = {0.4, limits(0, 0.99), step_size(0.01)};

    REFLECT_PROPS(Props, filter, shimmer, length, damping);
  };

  struct Wormhole : core::engine::EffectEngine<Wormhole>, itc::ActionReceiverOnBus<itc::LogicBus> {
    static constexpr util::string_ref name = "Wormhole";
    Wormhole(itc::ActionChannel);

    void encoder(core::input::EncoderEvent e) override;

    core::ui::ScreenAndInput screen() override;

    std::unique_ptr<Audio> audio;
    std::unique_ptr<Screen> screen_;

    Props props;
  };

} // namespace otto::engines::wormhole
