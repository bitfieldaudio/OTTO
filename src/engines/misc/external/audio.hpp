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

    void recalculate() noexcept;

    void action(itc::prop_change<&Props::mode>, ModeEnum m) noexcept;
    void action(itc::prop_change<&Props::stereo_gain>, float g) noexcept;
    void action(itc::prop_change<&Props::stereo_balance>, float b) noexcept;
    void action(itc::prop_change<&Props::left_gain>, float g) noexcept;
    void action(itc::prop_change<&Props::right_gain>, float g) noexcept;
    void action(itc::prop_change<&Props::active_send>, int a) noexcept;

    using abh = core::audio::AudioBufferHandle;
    void apply_sends(abh& inL, abh& inR, abh& fx1_bus, abh& fx2_bus) noexcept;

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