#pragma once

#include "core/engine/engine.hpp"

#include <Gamma/Filter.h>

namespace otto::engines {

    using namespace core;
    using namespace core::engine;
    using namespace props;

    struct ExampleFX : EffectEngine<ExampleFX> {
        static constexpr util::string_ref name = "ExampleFX";

        struct Props {
            Property<float> flt_freq = {0.8, limits(0, 1), step_size(0.01)};

            DECL_REFLECTION(Props, flt_freq);
        } props;

        ExampleFX();

        // Must take mono and output stereo.
        audio::ProcessData<2> process(audio::ProcessData<1>) override;

    private:
        gam::Biquad<> filter;

    };

} // namespace otto::engines
