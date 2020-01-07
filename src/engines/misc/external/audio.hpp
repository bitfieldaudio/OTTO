#pragma once

#include "core/audio/audio_buffer_pool.hpp"
#include "engines/misc/sends/audio.hpp"
#include "external.hpp"
#include "services/log_manager.hpp"

namespace otto::engines::external {

  using namespace core;

  struct Audio {
    Audio(sends::Audio& stereo, sends::Audio& left, sends::Audio& right) noexcept
      : send_stereo(stereo), send_left(left), send_right(right){};

    void recalculate()
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
          OTTO_UNREACHABLE;
      }
    }

    void action(itc::prop_change<&Props::mode>, ModeEnum m) noexcept
    {
      mode_ = m;
      recalculate();
    }
    void action(itc::prop_change<&Props::stereo_gain>, float g) noexcept
    {
      stereo_gain_ = g;
      recalculate();
    }
    void action(itc::prop_change<&Props::stereo_balance>, float b) noexcept
    {
      stereo_balance_ = b;
      recalculate();
    }
    void action(itc::prop_change<&Props::left_gain>, float g) noexcept
    {
      left_gain_ = g;
      recalculate();
    }
    void action(itc::prop_change<&Props::right_gain>, float g) noexcept
    {
      right_gain_ = g;
      recalculate();
    }
    void action(itc::prop_change<&Props::active_send>, int a) noexcept
    {
      active_send_ = a;
    }

    using abh = core::audio::AudioBufferHandle;
    void apply_sends(abh& inL, abh& inR, abh& fx1_bus, abh& fx2_bus) noexcept
    {
      if (mode_ == +ModeEnum::stereo) {
        for (auto&& [extL, extR, fx1, fx2] :
             util::zip(inL, inR, fx1_bus, fx2_bus)) {
          float mix = extL + extR;
          fx1 = mix * send_stereo.to_fx1;
          fx2 = mix * send_stereo.to_fx2;
          // Change external input in-place
          extL = extL * send_stereo.dryL;
          extR = extL * send_stereo.dryR;
        }
      } else if (mode_ == +ModeEnum::dual_mono) {
        for (auto&& [extL, extR, fx1, fx2] :
             util::zip(inL, inR, fx1_bus, fx2_bus)) {
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

    /// Actual values used in the enginemanager
    float gainL = 1;
    float gainR = 1;

    ModeEnum mode_ = ModeEnum::stereo;

  private:
    float stereo_gain_ = 0.5;
    float stereo_balance_ = 0.5;
    float left_gain_ = 0.5;
    float right_gain_ = 0.5;
    int active_send_ = 0;

    /// References to the Audio objects of the Sends owned by External.
    sends::Audio& send_stereo;
    sends::Audio& send_left;
    sends::Audio& send_right;
  };
} // namespace otto::engines::external