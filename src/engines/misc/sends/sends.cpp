#include "sends.hpp"

#include "screen.hpp"

namespace otto::engines::sends {

  using namespace services;
  using namespace core::input;

  LED led_for(ChannelEnum ce) {
    switch (+ce) {
      case ChannelEnum::internal: return LED{Key::synth};
      case ChannelEnum::external: return LED{Key::external};
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

  Sends::Sends() : screen_(std::make_unique<Screen>()), props{{*screen_}} {}

  void Sends::encoder(EncoderEvent ev)
  {
    switch (ev.encoder) {
      case Encoder::blue: props.volume.step(ev.steps); break;
      case Encoder::green: props.sendAB.step(ev.steps); break;
      case Encoder::yellow: props.pan.step(ev.steps); break;
      case Encoder::red: props.mix.step(ev.steps); break;
    }
    recalculate();
  }

  void Sends::recalculate() 
  {
    dryL = props.volume * (1 - props.pan) * (1 - props.mix);
    dryR = props.volume * props.pan * (1 - props.mix);
    to_fx1 = props.volume * (1 - props.sendAB) * props.mix;
    to_fx2 = props.volume * (1 - props.sendAB) * props.mix;
  }

  core::ui::ScreenAndInput Sends::screen()
  {
    return {*screen_, *this};
  }
}


