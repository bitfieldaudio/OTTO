#pragma once

#include "core/engine/engine.hpp"

#define MAXIMUM_LPC_ORDER 50

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct LPC : EffectEngine {
    struct Props : Properties<> {
      Property<float> pitch = {this, "PITCH", 0, has_limits::init(-24, 24), steppable::init(1)};
      Property<float> pitch_tracking = {this, "PITCH TRACKING", 1, has_limits::init(0, 1),
                                        steppable::init(0.01)};
      Property<float> detune = {this, "DETUNE", 0, has_limits::init(-24, 24),
                                steppable::init(0.01)};
      Property<float> snr = {this, "SNR", 0.5, has_limits::init(0, 1), steppable::init(0.01)};

      Property<int> order = {this, "ORDER", 10, has_limits::init(1, MAXIMUM_LPC_ORDER),
                             steppable::init(1)};
      Property<int> framerate = {this, "FRAMERATE", 0.5, has_limits::init(0, 1),
                                 steppable::init(0.01)};

    } props;

    LPC();

    audio::ProcessData<2> process(audio::ProcessData<2>) override;

  private:
    void makeSha(gsl::span<float> buffer, float sha_frequency, int lag);
  };

} // namespace otto::engines
