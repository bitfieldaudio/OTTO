#pragma once

#include "core/engine/engine.hpp"
#include "itc/action_bus.hpp"
#include "itc/itc.hpp"

namespace otto::engines::master {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct Screen;
  struct Audio;

  struct Props : core::props::Properties<Props> {
      itc::GAProp<struct volume_tag, float> volume = {0.5, limits(0, 1), step_size(0.01)};
      itc::GAProp<struct tempo_tag, float> tempo = {120, limits(40, 220), step_size(0.5)};

      REFLECT_PROPS(Props, volume, tempo);
  };

  struct Master : core::engine::MiscEngine<Master>, itc::ActionReceiverOnBus<itc::LogicBus> {
    static constexpr util::string_ref name = "Master";

    Master(itc::ActionChannel);

    void encoder(core::input::EncoderEvent e) override;

    core::ui::ScreenAndInput screen() override;

    const std::unique_ptr<Audio> audio;

    Props props;

    DECL_REFLECTION(Master, props);
  private:
    const std::unique_ptr<Screen> screen_;
  };

} // namespace otto::engines::master
