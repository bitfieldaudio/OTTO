#pragma once

#include "core/engine/engine.hpp"
#include "itc/itc.hpp"

namespace otto::engines::master {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct Screen;
  struct Audio;
  using Sender = EngineSender<Audio, Screen>;

  struct Props {
      Sender sender;

      Sender::Prop<struct volume_tag, float> volume = {sender, 0.5, limits(0, 1), step_size(0.01)};
      Sender::Prop<struct tempo_tag, float> tempo = {sender, 120, limits(40, 220), step_size(0.5)};

      DECL_REFLECTION(Props, volume, tempo);
  };

  struct Master : core::engine::MiscEngine<Master> {
    static constexpr util::string_ref name = "Master";

    Master();

    void encoder(core::input::EncoderEvent e) override;

    core::ui::ScreenAndInput screen() override;

    const std::unique_ptr<Audio> audio;

    DECL_REFLECTION(Master, props);

  private:
    const std::unique_ptr<Screen> screen_;

    Sender sender_ = {*audio, *screen_};
    Props props{sender_};
  };

} // namespace otto::engines::master

#include "audio.hpp"
#include "screen.hpp"
