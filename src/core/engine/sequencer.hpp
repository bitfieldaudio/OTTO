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

        struct Channel {
            Sampler sampler;
            std::array<bool, 16> triggers = {false};

        };

        std::array<Channel, number_of_channels> channels;

        Sequencer();

    };
};


