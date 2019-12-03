#include "ottofm.hpp"

#include "audio.hpp"
#include "screen.hpp"
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
    auto shift = services::Controller::current().is_pressed(Key::shift);
    if (e.encoder == +Encoder::red){
      if (!shift) props.fmAmount.step(e.steps);
      else props.algN.step(e.steps);
    } else {
      int i = 0;
      util::tuple_for_each(props.operators, [&](auto& op){
        if (i == props.cur_op.get()) {
          switch (e.encoder) {
          case Encoder::blue:
            if (!shift) op.ratio_idx.step(e.steps);
            else op.detune.step(e.steps);
            break;
          case Encoder::green:
            if (!shift) op.outLev.step(e.steps);
            else op.mSuspos.step(e.steps);
            break;
          case Encoder::yellow:
            if (!shift) {
              op.feedback.step(e.steps);
              op.mAtt.step(e.steps);
            } else op.mDecrel.step(e.steps);
            break;
          default: break;
          }
          i++;
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

}