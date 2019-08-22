#pragma once
#include <vector>
#include "core/audio/processor.hpp"
#include "core/engine/engine.hpp"
#include <Gamma/Noise.h>

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct LPC : EffectEngine<LPC> {
    static constexpr util::string_ref name = "LPC";

    static constexpr int max_order = 50;

    struct Props {
      Property<float> pitch = {0, limits(-24, 24), step_size(1)};
      Property<float> pitch_tracking = {1, limits(0, 1), step_size(0.01)};
      Property<float> detune = {0, limits(-24, 24), step_size(0.01)};
      Property<float> snr = {0.5, limits(0, 1), step_size(0.01)};
      Property<int> order = {10, limits(1, max_order), step_size(1)};
      Property<int> framerate = {0.5, limits(0, 1), step_size(0.01)};

      DECL_REFLECTION(Props, pitch, pitch_tracking, detune,
              snr, order, framerate);
      } props;

    LPC();

    audio::ProcessData<2> process(audio::ProcessData<1>) override;

  private:
    void make_sha(gsl::span<float> buffer, int sha_period);
    std::array<float, max_order> sigmaAndCoeffs;
    std::array<float, 2*max_order> scratchBuffer;
    std::array<float, max_order> prev_exciter_data;

    gam::NoiseWhite<> white;
    int lag = 0;
  };

} // namespace otto::engines
