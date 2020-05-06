#include "ottofm.hpp"

#include "audio.hpp"
#include "itc/action_receiver_registry.hpp"
#include "screen.hpp"
#include "services/audio_manager.hpp"
#include "services/ui_manager.hpp"

namespace otto::engines::ottofm {
  using namespace core::input;

  OttofmEngine::OttofmEngine(itc::ActionChannel channel)
    : screen_(std::make_unique<OttofmScreen>(std::array<itc::Shared<float>, 4>{
        activities_[0],
        activities_[1],
        activities_[2],
        activities_[3],
      })),
      audio(std::make_unique<Audio>(std::array<itc::Shared<float>, 4>{
        activities_[0],
        activities_[1],
        activities_[2],
        activities_[3],
      }))
  {
    set_children(props, audio, screen_, env_screen_, voice_screen_);
    register_to(channel);
    props.send_actions();
  }

  bool OttofmEngine::keypress(Key key)
  {
    switch (key) {
      case Key::blue_click: props.cur_op.set(3); break;
      case Key::green_click: props.cur_op.set(2); break;
      case Key::yellow_click: props.cur_op.set(1); break;
      case Key::red_click: props.cur_op.set(0); break;
      default: return false; ;
    }
    return true;
  }

  void OttofmEngine::encoder(EncoderEvent e)
  {
    auto shift = services::Controller::current().is_pressed(Key::shift);
    if (e.encoder == +Encoder::red) {
      if (!shift)
        props.fm_amount.step(e.steps);
      else
        props.algorithm_idx.step(e.steps);
    } else {
      util::indexed_for_each(props.operators, [&](int i, auto& op) {
        if (i == props.cur_op.get()) {
          switch (e.encoder) {
            case Encoder::blue:
              if (!shift)
                op.ratio_idx.step(e.steps);
              else
                op.detune.step(e.steps);
              break;
            case Encoder::green:
              if (!shift)
                op.out_level.step(e.steps);
              else
                op.suspos.step(e.steps);
              break;
            case Encoder::yellow:
              if (!shift) {
                op.feedback.step(e.steps);
                op.attack.step(e.steps);
              } else
                op.decay_release.step(e.steps);
              break;
            default: break;
          }
        }
      });
    }
  }

  core::ui::ScreenAndInput OttofmEngine::screen()
  {
    return {*screen_, *this};
  }

  core::ui::ScreenAndInput OttofmEngine::envelope_screen()
  {
    return {env_screen_, props.envelope};
  }

  core::ui::ScreenAndInput OttofmEngine::voices_screen()
  {
    return {voice_screen_, props.settings};
  }

} // namespace otto::engines::ottofm
