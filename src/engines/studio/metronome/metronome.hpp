#pragma once

#include "core/engines/engine.hpp"
#include "core/ui/widget.hpp"
#include "core/ui/drawing.hpp"
#include "core/audio/faust.hpp"
#include "util/audio.hpp"
#include "util/iterator.hpp"

namespace otto::engines {

  using BeatPos = int;

  struct Metronome : Engine<EngineType::studio>, private audio::FaustWrapper<0, 1> {

    using audio::FaustWrapper<0, 1>::process;

    struct Props : public engines::Properties {
      Property<float> bpm  = {this, "BPM", 120, {40, 320, 1}};
      Property<float> gain = {this, "GAIN", 0, {0, 1, 0.01}};
      Property<int> tone   = {this, "TONE", 12, {0, 24, 1}};
      Property<bool, mode::def, false> trigger = {this, "TRIGGER", false};
    } props;

    util::audio::Graph graph;

    Metronome();
    ~Metronome();

    audio::ProcessData<1> process(audio::ProcessData<0>);

    // TODO: Move this into core
    /* Bar iteration */

    unsigned getBarTime(BeatPos bar);
    unsigned getBarTimeRel(BeatPos bar);
    BeatPos closestBar(unsigned time);

    float bar_for_time(std::size_t time) const;
    std::size_t time_for_bar(float bar) const;
  };
}
