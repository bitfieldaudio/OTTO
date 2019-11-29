#include "ottofm.hpp"

//#include "audio.hpp"
//#include "screen.hpp"
#include "services/audio_manager.hpp"
#include "services/ui_manager.hpp"

namespace otto::engines::ottofm {
  using namespace core::input;

  OttofmEngine::OttofmEngine() : audio(std::make_unique<Audio>()), screen_(std::make_unique<OttofmScreen>())
  {
    sender_ .push(Actions::activity0_variable::data(activity0_));
    sender_ .push(Actions::activity1_variable::data(activity1_));
    sender_ .push(Actions::activity2_variable::data(activity2_));
    sender_ .push(Actions::activity3_variable::data(activity3_));
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
    //Could this be done in the keypress method?
    //And it is probably done separately on the graphics thread?
    auto shift = services::Controller::current().is_pressed(Key::shift);

    auto& current = props.operators.at(props.cur_op);
    switch (e.encoder) {
    case Encoder::blue:
      if (!shift) {
        current.ratio_idx.step(e.steps);
      } else {
        current.detune.step(e.steps);
      }
      break;
    case Encoder::green:
      if (!shift) {
        current.outLev.step(e.steps);
      } else {
        current.mSuspos.step(e.steps);
      }
      break;
    case Encoder::yellow:
      if (!shift) {
        current.feedback.step(e.steps);
        current.mAtt.step(e.steps);
      } else {
        current.mDecrel.step(e.steps);
      }
      break;
    case Encoder::red:
      if (!shift) {
        props.fmAmount.step(e.steps);
      } else {
        props.algN.step(e.steps);
      }
      break;
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

}