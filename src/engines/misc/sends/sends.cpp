#include "sends.hpp"

#include "core/input.hpp"
#include "screen.hpp"

namespace otto::engines::sends {

  using namespace services;
  using namespace core::input;

  LED led_for(ChannelEnum ce)
  {
    switch (+ce) {
      case ChannelEnum::internal: return LED{Key::synth};
      case ChannelEnum::external_stereo: return LED{Key::external};
      case ChannelEnum::external_left: return LED{Key::external};
      case ChannelEnum::external_right: return LED{Key::external};
      case ChannelEnum::sampler0: return LED{Key::S0};
      case ChannelEnum::sampler1: return LED{Key::S1};
      case ChannelEnum::sampler2: return LED{Key::S2};
      case ChannelEnum::sampler3: return LED{Key::S3};
      case ChannelEnum::sampler4: return LED{Key::S4};
      case ChannelEnum::sampler5: return LED{Key::S5};
      case ChannelEnum::sampler6: return LED{Key::S6};
      case ChannelEnum::sampler7: return LED{Key::S7};
      case ChannelEnum::sampler8: return LED{Key::S8};
      case ChannelEnum::sampler9: return LED{Key::S9};
    }
    OTTO_UNREACHABLE;
  }

  Sends::Sends(core::ui::Icon i)
    : audio(std::make_unique<Audio>()), screen_(std::make_unique<Screen>(i)), props{{*audio, *screen_}}
  {
    props.dry.observe(this, [&](float a) {
      if (is_recursive) return;
      set(a, props.stored_levels.dry, props.stored_levels.fx1, props.stored_levels.fx2);
    });
    props.fx1.observe(this, [&](float a) {
      if (is_recursive) return;
      set(a, props.stored_levels.fx1, props.stored_levels.dry, props.stored_levels.fx2);
    });
    props.fx2.observe(this, [&](float a) {
      if (is_recursive) return;
      set(a, props.stored_levels.fx2, props.stored_levels.dry, props.stored_levels.fx1);
    });
  }

  void Sends::step_scale(int steps)
  {
    set_scale(std::clamp(props.stored_levels.s + 0.01f * steps, 0.f, 1.f));
  }

  void Sends::set_scale(float x)
  {
    props.stored_levels.s = x;
    is_recursive = true;
    props.fx1 = props.stored_levels.fx1 * props.stored_levels.s;
    props.fx2 = props.stored_levels.fx2 * props.stored_levels.s;
    props.dry = props.stored_levels.dry * props.stored_levels.s;
    is_recursive = false;
  };

  void Sends::set(float value, float& changed, float& other1, float& other2)
  {
    if (value < threshold && ((other1 < threshold && other2 < threshold) ||
                              props.stored_levels.s < threshold)) { // Manually take care of "all 0" edge case
      other1 = 1.f;
      other2 = 1.f;
      changed = 1.f;
      props.stored_levels.s = 0.f;
    } // Main function body below
    else if (value >= other1 * props.stored_levels.s && value >= other2 * props.stored_levels.s) { // Now the largest
      changed = 1;
      other2 = other2 * props.stored_levels.s / value;
      other1 = other1 * props.stored_levels.s / value;
      props.stored_levels.s = value;
    } else if (changed > other1 && changed > other2) { // Was largest, now not
      float new_largest = std::max(other1, other2);
      changed = value / (new_largest * props.stored_levels.s);
      other1 = other1 / new_largest;
      other2 = other2 / new_largest;
      props.stored_levels.s = new_largest;
    } else { // Was not the largest, remained so
      changed = value / props.stored_levels.s;
    }
  }

  void Sends::encoder(EncoderEvent ev)
  {
    if (services::Controller::current().is_pressed(Key::shift) && ev.encoder != +Encoder::red) {
      step_scale(ev.steps);
      return;
    }

    switch (ev.encoder) {
      case Encoder::blue: props.fx1.step(ev.steps); break;
      case Encoder::green: props.fx2.step(ev.steps); break;
      case Encoder::yellow: props.dry.step(ev.steps); break;
      case Encoder::red: props.pan.step(ev.steps); break;
    }
  }

  core::ui::ScreenAndInput Sends::screen()
  {
    return {*screen_, *this};
  }
} // namespace otto::engines::sends
