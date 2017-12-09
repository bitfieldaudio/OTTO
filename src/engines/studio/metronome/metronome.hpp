#pragma once

#include "core/engines/engine.hpp"
#include "core/ui/base.hpp"
#include "core/ui/drawing.hpp"
#include "core/ui/engine-ui.hpp"
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
    std::size_t time_for_bar(float time) const;

    class BarIterImpl {
    public:
      using value_type = std::size_t;
      using iterator_category = std::random_access_iterator_tag;

      BarIterImpl(const Metronome& m, value_type val)
        : m (m), val (val)
      {}

      void advance(int n)
      {
        float bar_time = m.bar_for_time(val);
        float flt_prt = std::fmod(bar_time, 1);
        bar_time += std::trunc(flt_prt + n);
        val = m.time_for_bar(bar_time);
      }

      int compare(BarIterImpl& r)
      {
        return val == r.val;
      }

      value_type dereference()
      {
        return val;
      }

    private:
      const Metronome& m;
      value_type val;
    };

    using iterator = util::iterator_adaptor<BarIterImpl>;

    iterator iter(std::size_t time) const
    {
      return {*this, time};
    }
  };

}
