#pragma once

#include "core/engine/engine.hpp"

#include <Gamma/Effects.h>
#include "core/voices/voice_manager.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct Chorus : EffectEngine {
    static constexpr std::string_view name = "Chorus";

    struct Props : Properties<> {
          Property<float> delay       = {this, "delay",       0.0001,        has_limits::init(0.0001, 1),     steppable::init(0.0001)};
          Property<float> rate        = {this, "rate",        0,        has_limits::init(0, 100),   steppable::init(0.1)};
          Property<float> deviation   = {this, "deviation",   0.01,        has_limits::init(0, 0.9),     steppable::init(0.01)};
          Property<float> depth       = {this, "depth",       0.0001,   has_limits::init(0.0001, 1),     steppable::init(0.0001)};
    } props;

    Chorus();

    audio::ProcessData<2> process(audio::ProcessData<1>) override;

    private:
        gam::Chorus<> chorus;
    };

} // namespace otto::engines
