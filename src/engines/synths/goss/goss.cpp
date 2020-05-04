#include "goss.hpp"

#include "services/audio_manager.hpp"
#include "services/ui_manager.hpp"

#include "screen.hpp"
#include "audio.hpp"

namespace otto::engines::goss {

  using namespace core::input;

  GossEngine::GossEngine(itc::ActionChannel channel) : audio(std::make_unique<Audio>(rotation_)), screen_(std::make_unique<GossScreen>(rotation_))
  {
    set_children(props, audio, screen_);
    register_to(channel);
    props.send_actions();
  }

  void GossEngine::encoder(EncoderEvent e)
  {
    switch (e.encoder) {
      case Encoder::blue: props.model.step(e.steps); break;
      case Encoder::green: props.drive.step(e.steps); break;
      case Encoder::yellow: props.click.step(e.steps); break;
      case Encoder::red: props.leslie.step(e.steps); break;
    }
  }

  core::ui::ScreenAndInput GossEngine::screen()
  {
    return {*screen_, *this};
  }

  core::ui::ScreenAndInput GossEngine::envelope_screen()
  {
    return {env_screen_, props.envelope};
  }

  core::ui::ScreenAndInput GossEngine::voices_screen()
  {
    return {voice_screen_, props.settings};
  }

} // namespace otto::engines::goss
