#pragma once

#include "core/engine/engine.hpp"

#include "itc/itc.hpp"

namespace otto::engines::wormhole {

  using namespace core::props;

  struct Screen;
  struct Audio;

  using GraphicsSndr = itc::ActionSender<Screen>;
  using AudioSndr = itc::ActionSender<Audio>;
  using Sndr = itc::JoinedActionSender<GraphicsSndr, AudioSndr>;

  struct Props {
    Sndr* sndr;

    Sndr::Prop<struct filter_tag, float> filter = {sndr, 0, limits(0, 1), step_size(0.01)};
    Sndr::Prop<struct shimmer_tag, float> shimmer = {sndr, 0, limits(0, 1), step_size(0.01)};
    Sndr::Prop<struct length_tag, float> length = {sndr, 0.5, limits(0, 1), step_size(0.01)};
    Sndr::Prop<struct damping_tag, float> damping = {sndr, 0.4, limits(0, 0.99), step_size(0.01)};

    DECL_REFLECTION(Props, filter, shimmer, length, damping);
  };

  struct Wormhole : core::engine::EffectEngine<Wormhole> {
    static constexpr util::string_ref name = "Wormhole";
    Wormhole();

    void encoder(core::input::EncoderEvent e) override;

    std::unique_ptr<Screen> screen;
    std::unique_ptr<Audio> audio;

    GraphicsSndr graphics_sndr_;
    AudioSndr audio_sndr_;
    Sndr sndr_ = {graphics_sndr_, audio_sndr_};

    Props props = {&sndr_};
  };

} // namespace otto::engines::wormhole
