#pragma once

#include "core/engine/engine.hpp"

#include "core/audio/faust.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct Wormhole : EffectEngine<Wormhole> {
    static constexpr std::string_view name = "Wormhole";

    struct Props : Properties<faust_link> {
      Property<float, faust_link> spread = {this, "SPREAD", 0, has_limits::init(0, 1),
                                            steppable::init(0.01)};
      Property<float, faust_link> shimmer = {this, "SHIMMER", 0, has_limits::init(0, 0.8),
                                             steppable::init(0.01)};
      Property<float, faust_link> length = {this, "LENGTH", 0.5, has_limits::init(0, 1),
                                            steppable::init(0.01)};
      Property<float, faust_link> shape = {this, "SHAPE", 1, has_limits::init(0, 2),
                                           steppable::init(0.01)};

      DECL_REFLECTION(Props, spread, shimmer, length, shape);
    } props;

    Wormhole();

    audio::ProcessData<2> process(audio::ProcessData<1>) override;

  private:
    audio::FaustWrapper<1, 2> faust_;
  };

} // namespace otto::engines
