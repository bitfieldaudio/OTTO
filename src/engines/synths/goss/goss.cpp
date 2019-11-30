#include "goss.hpp"

#include "audio.hpp"
#include "screen.hpp"

namespace otto::engines::goss {

  using namespace core::input;

  GossEngine::GossEngine()
    : audio(std::make_unique<Audio>()),
      screen_(std::make_unique<GossScreen>()),
      props({*audio, *screen_, voice_screen_, env_screen_})
  {
    props.sender.push(Actions::rotation_variable::data(rotation_));
  }

  void GossEngine::encoder(EncoderEvent e)
  {
    switch (e.encoder) {
      case Encoder::blue: props.model.step(e.steps); break;
      case Encoder::green: props.drawbar2.step(e.steps); break;
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
