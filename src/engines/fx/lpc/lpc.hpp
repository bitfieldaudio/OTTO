#pragma once
#include <vector>
#include "core/audio/processor.hpp"
#include "core/engine/engine.hpp"
#include "Gamma/Noise.h"

#define MAXIMUM_LPC_ORDER 50
#define MAXIMUM_BLOCK_SIZE 1024
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

    audio::ProcessData<2> process(audio::ProcessData<1>) override;

  private:
    void makeSha(gsl::span<float> buffer, int sha_period);
    float acov[MAXIMUM_BLOCK_SIZE];
    float sigmaAndCoeffs[MAXIMUM_LPC_ORDER];
    float scratchBuffer[2*MAXIMUM_LPC_ORDER];
    float prev_exciter_data[MAXIMUM_LPC_ORDER];

    NoiseWhite<> white;
    int lag = 0;
  };

} // namespace otto::engines
