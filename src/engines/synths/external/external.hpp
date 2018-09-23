#pragma once

#include "core/engines/engine.hpp"

#include "core/audio/faust.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engines;
  using namespace props;

  struct External : SynthEngine {
    struct Props : Properties<> {
      Property<float> gain = {this, "GAIN", 0.5, has_limits::init(0, 1), steppable::init(0.01)};
    } props;

    External();

    audio::ProcessData<1> process(audio::ProcessData<1>) override;

    util::audio::Graph graph;
  };

} // namespace otto::engines
