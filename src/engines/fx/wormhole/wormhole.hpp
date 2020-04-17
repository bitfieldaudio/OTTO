#pragma once

#include "core/engine/engine.hpp"

#include "itc/itc.hpp"

namespace otto::engines::wormhole {

  using namespace core::props;

  struct Screen;
  struct Audio;

  struct Props {
    itc::GAProp<struct filter_tag, float> filter = {0, limits(0, 1), step_size(0.01)};
    itc::GAProp<struct shimmer_tag, float> shimmer = {0, limits(0, 1), step_size(0.01)};
    itc::GAProp<struct length_tag, float> length = {0.5, limits(0, 1), step_size(0.01)};
    itc::GAProp<struct damping_tag, float> damping = {0.4, limits(0, 0.99), step_size(0.01)};

    DECL_REFLECTION(Props, filter, shimmer, length, damping);
  };

  struct Wormhole : core::engine::EffectEngine<Wormhole> {
    static constexpr util::string_ref name = "Wormhole";
    Wormhole();

    void encoder(core::input::EncoderEvent e) override;

    core::ui::ScreenAndInput screen() override;

    std::unique_ptr<Audio> audio;
    std::unique_ptr<Screen> screen_;

    Props props;
  };

} // namespace otto::engines::wormhole
