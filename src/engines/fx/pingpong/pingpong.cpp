#include "pingpong.hpp"

#include "core/service.hpp"
#include "services/application.hpp"
#include "services/audio_manager.hpp"
#include "services/clock_manager.hpp"
#include "services/log_manager.hpp"
#include "services/ui_manager.hpp"
#include "util/math.hpp"

namespace otto::engines::pingpong {

  PingPong::PingPong()
    : audio(std::make_unique<Audio>()), screen_(std::make_unique<Screen>()), props{{*audio, *screen_}}
  {}

  using namespace core::input;

  bool PingPong::keypress(Key key)
  {
    switch (key) {
      case Key::blue_click: {
        props.timetype = !props.timetype;
        props.delaytime.set(calculate_delaytime(props.timetype, props.free_time, props.subdivision));
        break;
      }
      case Key::red_click: props.stereo_invert = !props.stereo_invert; break;
      default: return false; ;
    }
    return true;
  }

  void PingPong::encoder(EncoderEvent ev)
  {
    switch (ev.encoder) {
      case Encoder::blue: {
        if (props.timetype) {
          props.subdivision.step(util::math::sgn(ev.steps));
        } else {
          props.free_time.step(ev.steps);
        }
        props.delaytime.set(calculate_delaytime(props.timetype, props.free_time, props.subdivision));
        break;
      }
      case Encoder::green: props.feedback.step(ev.steps); break;
      case Encoder::yellow: props.filter.step(ev.steps); break;
      case Encoder::red: props.stereo.step(ev.steps); break;
    }
  }

  core::ui::ScreenAndInput PingPong::screen()
  {
    return {*screen_, *this};
  }

  // TODO: This will NOT update when the bpm changes. It should do that.
  float PingPong::calculate_delaytime(bool type, float free, int sd)
  {
    if (type) {
      // Using subdivisions. Result is sec. per beat
      auto res = 60.f / services::ClockManager::current().bpm();
      // Identification of the subdivisions
      switch (sd) {
      case 0: res /= 4.f; break; //sixteenths 
      case 1: res /= 3.f; break; // eighthtriplets
      case 2: res *= 0.5f; break; // eights
      case 3: res *= 2.f/3.f; break; // quartertriplets
      case 4: break; // quarter step is equal to a beat
      case 5: res *= 2.f; break; // half measure (2 beats)
      case 6: res *= 4.f; break; // whole measure (4 beats)
      default: OTTO_UNREACHABLE;
      }
      return res;
    } else {
      // Using free time control
      auto fff = free * free * free;
      return 0.05f * (1.f - fff) + 6.f * fff;
    }
  }

} // namespace otto::engines::pingpong
