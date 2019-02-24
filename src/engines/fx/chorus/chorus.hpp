#pragma once

#include "core/engine/engine.hpp"

#include "core/audio/faust.hpp"

namespace otto::engines {

    using namespace core;
    using namespace core::engine;
    using namespace props;

    struct Chorus : EffectEngine {

        struct Props : Properties<> {

            Property<float> delay       = {this, "delay",     0,  has_limits::init(0, 1),    steppable::init(0.01)};
            Property<float> rate        = {this, "rate", 0,  has_limits::init(0, 0.8), steppable::init(0.01)};
            Property<float> deviation   = {this, "deviation",  1,  has_limits::init(0, 1),    steppable::init(0.01)};
            Property<float> depth       = {this, "depth",  1, has_limits::init(0, 1),   steppable::init(0.01)};

        } props;

        Chorus();

        audio::ProcessData<2> process(audio::ProcessData<1>) override;

    private:
        audio::FaustWrapper<1, 2> faust_;
    };

} // namespace otto::engines
