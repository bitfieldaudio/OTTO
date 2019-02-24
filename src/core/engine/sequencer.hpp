#pragma once

#include <core/props/props.hpp>
#include "util/filesystem.hpp"
#include "core/props/props.hpp"
#include "engine.hpp"
#include "engines/synths/sampler/sampler.hpp"


namespace otto::engines {

    using namespace otto::core;
    using namespace otto::core::props;

    struct Sequencer : engine::MiscEngine {

        static constexpr int number_of_channels = 10;
        int current_channel = 0;

        struct Props : Properties<> {

        } props;

        struct Channel {
            Sampler sampler;
            std::array<bool, 16> triggers = {false};

        };

        std::array<Channel, number_of_channels> channels;

        Sequencer();

        audio::ProcessData<1> process(audio::ProcessData<0>);

    private:
        friend struct SequencerScreen;
        int _beat = 0;
        int _samples_per_beat = 22050 / 4;
        int _next_beat = _samples_per_beat;
        int _counter = _samples_per_beat;
        bool _should_run = false;
        bool _running = false;

    };
};


