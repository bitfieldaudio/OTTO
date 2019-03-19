#pragma once

#include "core/engine/engine.hpp"

#include <Gamma/Effects.h>
#include <Gamma/Filter.h>
#include "core/voices/voice_manager.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct Chorus : EffectEngine<Chorus> {
    static constexpr std::string_view name = "Chorus";

    struct Props {
      Property<float> delay = {0.0001, limits(0.0001, 0.01), step_size(0.0001)};
      Property<float> depth = {0.0001, limits(0.0001, 0.01), step_size(0.0001)};
      Property<float> feedback = {0.1, limits(0, 0.9), step_size(0.01)};
      Property<float> rate = {0, limits(0, 10), step_size(0.1)};

      DECL_REFLECTION(Props, delay, depth, feedback, rate);
    } props;

    Chorus();

    audio::ProcessData<2> process(audio::ProcessData<1>) override;

  private:
    gam::Chorus<> chorus;
    gam::OnePole<> lpf;
  };

} // namespace otto::engines
