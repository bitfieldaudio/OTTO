#pragma once

#include "core/engine/engine.hpp"

namespace otto::engines {

    using namespace core;
    using namespace core::engine;
    using namespace props;

    struct Arp : SequencerEngine {

        enum struct Playmode {
          up,
          down,

          //Number of modes
          n_modes
        };

        struct Props : Properties<> {
            Property<Playmode,wrap> playmode = {this, "Playmode", Playmode::up, has_limits::init(Playmode{0},Playmode::n_modes)};


        } props;

        Arp();

        audio::ProcessData<0> process(audio::ProcessData<0> data);


        std::vector<int> notes = {21 ,21, 22, 24};

    private:
        int _samples_per_beat = 22050 / 4;
        int _counter = _samples_per_beat;
        int _current_note = 0;
        int note = -1;
    };



}
