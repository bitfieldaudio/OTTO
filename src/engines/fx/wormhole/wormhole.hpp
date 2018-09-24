#pragma once

#include "core/engines/engine.hpp"

#include "core/audio/faust.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engines;
  using namespace props;

  struct Wormhole : EffectEngine {

    struct Props : Properties<> {

      Property<float> mix     = {this, "MIX",     0.5,  has_limits::init(0, 1),    steppable::init(0.01)};
      Property<float> shimmer = {this, "SHIMMER", 0,  has_limits::init(0, 1.2), steppable::init(0.01)};
      Property<float> length  = {this, "LENGTH",  1,  has_limits::init(0, 1),    steppable::init(0.01)};
      Property<float> shape   = {this, "SHAPE",  4000, has_limits::init(100, 14000),   steppable::init(100)};

    } props;

    Wormhole();

    audio::ProcessData<2> process(audio::ProcessData<2>) override;

  private:
    audio::FaustWrapper<2, 2> faust_;
  };

} // namespace otto::engines
