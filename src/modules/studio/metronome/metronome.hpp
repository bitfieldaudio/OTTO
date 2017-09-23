#pragma once

#include "core/modules/module.hpp"
#include "core/ui/base.hpp"
#include "core/ui/drawing.hpp"
#include "core/ui/module-ui.hpp"
#include "core/audio/faust.hpp"
#include "util/audio.hpp"

namespace top1::modules {

  using BeatPos = int;

  class MetronomeScreen; // FWDCL

  class Metronome : public Module, audio::FaustWrapper {

    std::unique_ptr<MetronomeScreen> screen;
    audio::RTBuffer<float> buf;

    using audio::FaustWrapper::process;

  public:
    struct Props : public modules::Properties {
      Property<float> bpm     = {this, "BPM", 120, {40, 320, 1}};
      Property<float> gain    = {this, "GAIN", 0, {0, 1, 0.01}};
      Property<int>   tone    = {this, "TONE", 12, {0, 24, 1}};
      Property<bool, mode::def,
        false> trigger = {this, "TRIGGER", false};
    } props;

    audio::Graph graph;

    Metronome();
    ~Metronome();

    void process(const audio::ProcessData&);
    void display() override;

    // Formalities are over

    unsigned getBarTime(BeatPos bar);
    unsigned getBarTimeRel(BeatPos bar);
    BeatPos closestBar(unsigned time);
  };

}
