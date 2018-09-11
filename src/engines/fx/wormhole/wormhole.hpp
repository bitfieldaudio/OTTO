#pragma once

#include "core/engines/engine.hpp"

#include "core/audio/faust.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engines;
  using namespace props;

  struct Wormhole : EffectEngine {

    struct Props : Properties<> {

      Property<float> mix     = {this, "Mix",     0,  has_limits::init(0, 4),    steppable::init(0.01)};
      Property<float> shimmer = {this, "Shimmer", 2,  has_limits::init(0, 3.01), steppable::init(0.01)};
      Property<float> length  = {this, "Length",  0,  has_limits::init(0, 3),    steppable::init(0.01)};
      Property<float> shape   = {this, "shape",  20, has_limits::init(0, 99),   steppable::init(0.5)};

    } props;

    Wormhole();

    audio::ProcessData<2> process(audio::ProcessData<2>) override;

  private:
    audio::FaustWrapper<2, 2> faust_;
  };

} // namespace otto::engines
