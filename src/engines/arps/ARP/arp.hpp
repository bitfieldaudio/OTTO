#pragma once

#include <foonathan/array/small_array.hpp>

#include "core/engine/engine.hpp"
#include "itc/itc.hpp"

namespace otto::engines::arp {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  BETTER_ENUM(Playmode, std::int8_t, up, down, updown, downup, updowninc, downupinc, manual, chord);

  BETTER_ENUM(OctaveMode, std::int8_t, standard, octaveup, octaveupunison, fifthunison, octavedownup);

  struct Screen;
  struct Audio;
  using Sender = EngineSender<Audio, Screen>;

  struct Actions {
    using graphics_outdated = itc::Action<struct graphics_outdated_tag, std::atomic<bool>&>;
  };

  struct Props {
    Sender sender;
    Sender::Prop<struct playmode_tag, Playmode, wrap> playmode = {sender, Playmode::up};
    Sender::Prop<struct octavemode_tag, OctaveMode, wrap> octavemode = {sender, OctaveMode::standard};
    Sender::Prop<struct note_length_tag, float> note_length = {sender, 0.2f, limits(0.01f, 0.97f), step_size(0.01)};
    Sender::Prop<struct subdivision_tag, int, wrap> subdivision = {sender, 1, limits(1, 4)};

    DECL_REFLECTION(Props, playmode, octavemode, note_length);
  };

  struct Arp : core::engine::ArpeggiatorEngine<Arp> {
    static constexpr util::string_ref name = "Arp";

    Arp();

    void encoder(core::input::EncoderEvent e) override;

    core::ui::ScreenAndInput screen() override;

    const std::unique_ptr<Audio> audio;

    DECL_REFLECTION(Arp, props);

  private:
    const std::unique_ptr<Screen> screen_;

    Sender sender_ = {*audio, *screen_};
    Props props{sender_};

    // Variables shared between audio and graphics
    std::atomic<bool> graphics_outdated_ = false;
  };

} // namespace otto::engines::arp

#include "audio.hpp"
#include "screen.hpp"
