#pragma once

#include "core/engine/engine.hpp"

#include "itc/itc.hpp"

namespace otto::engines::wormhole {

  using namespace core::props;

  struct Screen;
  struct Audio;

  using Sndr = core::engine::EngineSender<Audio, Screen>;

  struct Props {
    Sndr sender;

    Sndr::Prop<struct filter_tag, float> filter = {sender, 0, limits(0, 1), step_size(0.01)};
    Sndr::Prop<struct shimmer_tag, float> shimmer = {sender, 0, limits(0, 1), step_size(0.01)};
    Sndr::Prop<struct length_tag, float> length = {sender, 0.5, limits(0, 1), step_size(0.01)};
    Sndr::Prop<struct damping_tag, float> damping = {sender, 0.4, limits(0, 0.99), step_size(0.01)};

    DECL_REFLECTION(Props, filter, shimmer, length, damping);
  };

  struct Wormhole : core::engine::EffectEngine<Wormhole> {
    static constexpr util::string_ref name = "Wormhole";
    Wormhole();

    void encoder(core::input::EncoderEvent e) override;

    core::ui::ScreenAndInput screen() override;

    std::unique_ptr<Audio> audio;
    std::unique_ptr<Screen> screen_;

    Props props = {{*audio, *screen_}};
  };

} // namespace otto::engines::wormhole
