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
  using namespace props;

  using BeatPos = int;
  using TapeTime = int;

  struct Metronome : Engine<EngineType::studio>
  {
    struct Props : public Properties<> {
      Property<float, has_limits> bpm = {
        this, "BPM", 120, has_limits::init(40, 320), steppable::init(1)};
      Property<float> gain = {this, "GAIN", 0, has_limits::init(0, 1),
                              steppable ::init(0.01)};
      Property<int> tone   = {this, "TONE", 12, has_limits::init(0, 24)};
      Property<bool, no_serialize> trigger = {this, "TRIGGER", false};
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
  private:
    audio::FaustWrapper<0, 1> faust_;
  };
}
