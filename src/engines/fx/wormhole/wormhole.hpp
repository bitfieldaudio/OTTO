#pragma once

#include "core/engine/engine.hpp"

#include "util/dsp/transpose.hpp"

/// Reverb Engine
namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct Wormhole : EffectEngine<Wormhole> {
    static constexpr util::string_ref name = "Wormhole";
    struct Props {
      Property<float> filter = {0, limits(0, 1), step_size(0.01)};
      Property<float> shimmer = {0, limits(0, 1), step_size(0.01)};
      Property<float> length = {0.5, limits(0, 1), step_size(0.01)};
      Property<float> damping = {0.4, limits(0, 0.99), step_size(0.01)};

      DECL_REFLECTION(Props, filter, shimmer, length, damping);
    } props;

    Wormhole();

    audio::ProcessData<2> process(audio::ProcessData<1>) override;

  private:
    float last_sample = 0;
    float shimmer_amount = 0;
    gam::ReverbMS<> reverb;
    dsp::SimplePitchShift pitchshifter;
    std::array<gam::Delay<>, 2> output_delay;
    gam::Biquad<> shimmer_filter;
    gam::BlockDC<> dc_block;
    gam::Biquad<> pre_filter;
  };

} // namespace otto::engines
