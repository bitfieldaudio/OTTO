#include "pingpong.hpp"

#include "core/service.hpp"
#include "engines/misc/master/master.hpp"
#include "services/application.hpp"
#include "services/audio_manager.hpp"
#include "services/clock_manager.hpp"
#include "services/log_manager.hpp"
#include "services/ui_manager.hpp"
#include "util/math.hpp"

namespace otto::engines::pingpong {

  PingPong::PingPong()
    : audio(std::make_unique<Audio>()), screen_(std::make_unique<Screen>()), props{{*audio, *screen_}}
  {
    // Extra observers for when delaytime should change
    props.timetype.observe(this, [&](bool tt) {
      props.delaytime.set(calculate_delaytime(props.timetype, props.free_time, props.subdivision));
    });
    services::ClockManager::current().props.bpm.observe(this, [&](float b) {
      props.delaytime.set(calculate_delaytime(props.timetype, props.free_time, props.subdivision));
    });
  }

  using namespace core::input;

  bool PingPong::keypress(Key key)
  {
    switch (key) {
      case Key::blue_click: props.timetype = !props.timetype; break;
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
  float PingPong::calculate_delaytime(bool type, float free, SubdivisionEnum sd)
  {
    if (type) {
      // Using subdivisions. Result is sec. per bar (whole note)
      auto res = 240.f / services::ClockManager::current().bpm();
      // Identification of the subdivisions
      switch (sd) {
        case SubdivisionEnum::thirtysecondth: res *= 1.f / 32.f; break;
        case SubdivisionEnum::sixteenth: res *= 1.f / 16.f; break;
        case SubdivisionEnum::eighthtriplet: res *= 1.f / 12.f; break;
        case SubdivisionEnum::eighth: res *= 1.f / 8.f; break;
        case SubdivisionEnum::doteighth: res *= 3.f / 16.f; break;
        case SubdivisionEnum::quartertriplet: res *= 1.f / 6.f; break;
        case SubdivisionEnum::quarter: res *= 1.f / 4.f; break;
        case SubdivisionEnum::dotquarter: res *= 3.f / 8.f; break;
        case SubdivisionEnum::halftriplet: res *= 1.f / 3.f; break;
        case SubdivisionEnum::half: res *= 1.f / 2.f; break;
        case SubdivisionEnum::dothalf: res *= 3.f / 4.f; break;
        case SubdivisionEnum::whole: break;
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
