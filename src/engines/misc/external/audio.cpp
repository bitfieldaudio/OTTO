#include "audio.hpp"

namespace otto::engines::external {

  using namespace core;

  void Audio::recalculate() noexcept
  {
    switch (mode_) {
      case ModeEnum::disabled: {
        gainL = 0;
        gainR = 0;
        break;
      }
      case ModeEnum::stereo: {
        gainL = stereo_gain_ * (1 - stereo_balance_);
        gainR = stereo_gain_ * stereo_balance_;
        break;
      }
      case ModeEnum::dual_mono: {
        gainL = left_gain_;
        gainR = right_gain_;
        break;
      }
      default: OTTO_UNREACHABLE;
    }
  }

  void Audio::action(itc::prop_change<&Props::mode>, ModeEnum m) noexcept
  {
    mode_ = m;
    recalculate();
  }
  void Audio::action(itc::prop_change<&Props::stereo_gain>, float g) noexcept
  {
    stereo_gain_ = g;
    recalculate();
  }
  void Audio::action(itc::prop_change<&Props::stereo_balance>, float b) noexcept
  {
    stereo_balance_ = b;
    recalculate();
  }
  void Audio::action(itc::prop_change<&Props::left_gain>, float g) noexcept
  {
    left_gain_ = g;
    recalculate();
  }
  void Audio::action(itc::prop_change<&Props::right_gain>, float g) noexcept
  {
    right_gain_ = g;
    recalculate();
  }
  void Audio::action(itc::prop_change<&Props::active_send>, int a) noexcept
  {
    active_send_ = a;
  }

  using abh = core::audio::AudioBufferHandle;
  void Audio::apply_sends(abh& inL, abh& inR, abh& fx1_bus, abh& fx2_bus) noexcept
  {
    if (mode_ == +ModeEnum::stereo) {
      for (auto&& [extL, extR, fx1, fx2] : util::zip(inL, inR, fx1_bus, fx2_bus)) {
        float mix = extL + extR;
        fx1 = mix * send_stereo.to_fx1;
        fx2 = mix * send_stereo.to_fx2;
        // Change external input in-place
        extL = extL * send_stereo.dryL;
        extR = extL * send_stereo.dryR;
      }
    } else if (mode_ == +ModeEnum::dual_mono) {
      for (auto&& [extL, extR, fx1, fx2] : util::zip(inL, inR, fx1_bus, fx2_bus)) {
        fx1 = extL * send_left.to_fx1 + extR * send_right.to_fx1;
        fx2 = extL * send_left.to_fx2 + extR * send_right.to_fx2;
        // Change external input in-place
        extL = extL * send_left.dryL + extR * send_right.dryL;
        extR = extL * send_left.dryR + extR * send_right.dryR;
      }
    } else {
      nano::fill(fx1_bus, 0.f);
      nano::fill(fx2_bus, 0.f);
    }
  }

} // namespace otto::engines::external
