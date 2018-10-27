#include "arp.hpp"

#include "core/globals.hpp"
#include "core/ui/vector_graphics.hpp"

namespace otto::engines {

    using namespace ui;
    using namespace ui::vg;

    struct ArpScreen : EngineScreen<Arp> {
        void draw(Canvas& ctx) override{}

        using EngineScreen::EngineScreen;
    };

    audio::ProcessData<0> Arp::process(audio::ProcessData<0> data)
    {
        auto next_beat = _samples_per_beat - _counter;

        if (next_beat <= data.nframes) {
            note = notes[_current_note];
            data.midi.push_back(midi::NoteOnEvent(note));
            data.midi.push_back(midi::NoteOffEvent(note));
            _current_note += 1;
            _current_note %= 4;

        };

        _counter += data.nframes;
        _counter %= _samples_per_beat;

        return data;
    }

    Arp::Arp() : SequencerEngine("Arp", props, std::make_unique<ArpScreen>(this)){}
}



