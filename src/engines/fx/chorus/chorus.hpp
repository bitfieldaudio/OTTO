#pragma once

#include "core/engine/engine.hpp"

#include <Gamma/Filter.h>
#include <Gamma/Oscillator.h>
#include "core/voices/voice_manager.hpp"
#include "util/dsp/chorus.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct Chorus : EffectEngine<Chorus> {
    static constexpr util::string_ref name = "Chorus";

    struct Props {
      Property<float> delay = {0.8, limits(0, 1), step_size(0.01)};
      Property<float> depth = {0.5, limits(0, 1), step_size(0.01)};
      Property<float> feedback = {0, limits(-0.99, 0.99), step_size(0.01)};
      Property<float> rate = {0, limits(0, 2), step_size(0.1)};

      float phase_value = 0;

      DECL_REFLECTION(Props, delay, depth, feedback, rate);
    } props;

    Chorus();

    audio::ProcessData<2> process(audio::ProcessData<1>) override;

  private:
    ChorusEffect<> chorus;
    gam::AccumPhase<> phase;





  };

} // namespace otto::engines
