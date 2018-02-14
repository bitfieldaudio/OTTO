#pragma once

#include "core/engines/engine.hpp"
#include "core/ui/screen.hpp"
#include "core/ui/vector_graphics.hpp"
#include "core/audio/faust.hpp"
#include "util/audio.hpp"
#include "util/iterator.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engines;

  using BeatPos = int;
  using TapeTime = int;

  struct Metronome : Engine<EngineType::studio>, private audio::FaustWrapper<0, 1> {

    using audio::FaustWrapper<0, 1>::process;

    struct Props : public props::Properties<> {
      // clang-format: off
      props::Property<float, props::has_limits> bpm = {
        has_name  ::init("BPM"),
        has_value ::init(120),
        has_limits::init(40, 320),
        steppable ::init(1)
      };
      props::Property<float> gain = {
        has_name  ::init("GAIN"),
        has_value ::init(0),
        has_limits::init(0, 1),
        steppable ::init(0.01)
      };
      props::Property<int> tone = { has_name::init("TONE"), 12, { 0, 24, 1 } };
      props::Property<bool, props::no_serialize> trigger = {
        has_name::init("TRIGGER"), has_value::init(false)
      };

      Props() : Properties(bpm, gain, tone, trigger) {}
      // clang-format: on
    } props;

    util::audio::Graph graph;

    Metronome();
    ~Metronome();

    audio::ProcessData<1> process(audio::ProcessData<0>);

    TapeTime getBarTime(BeatPos bar);
    TapeTime getBarTimeRel(BeatPos bar);
    BeatPos closestBar(TapeTime time);

    float bar_for_time(TapeTime time) const;
    std::size_t time_for_bar(float bar) const;
  };
}
