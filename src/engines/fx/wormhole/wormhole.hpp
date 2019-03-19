#pragma once

#include "core/engine/engine.hpp"
#include "core/voices/voice_manager.hpp"

#include "util/dsp/transpose.hpp"

constexpr unsigned num_taps = 4;

/// Reverb Engine
namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct KratosReverb : EffectEngine<KratosReverb> {
    static constexpr util::string_ref name = "Kratos";
    struct Props {
      Property<float> filter = {0, limits(0, 1), step_size(0.01)};
      Property<float> shimmer = {0, limits(0, 1), step_size(0.01)};
      Property<float> length = {0.5, limits(0, 1), step_size(0.01)};
      Property<float> damping = {0.4, limits(0, 0.99), step_size(0.01)};

      DECL_REFLECTION(Props, filter, shimmer, length, damping);
    } props;

    KratosReverb();

    audio::ProcessData<2> process(audio::ProcessData<1>) override;

  private:
    gam::ReverbMS<> reverb;
    dsp::SimplePitchShift pitchshifter;
    float last_sample = 0;
    float shimmer_amount = 0;
    std::array<gam::Delay<>, 2> output_delay;
    gam::Biquad<> shimmer_filter;
    gam::BlockDC<> dc_block;
    gam::Biquad<> pre_filter;
  };

} // namespace otto::engines
