#pragma once

#include "core/modules/module.hpp"
#include "core/ui/base.hpp"
#include "core/ui/drawing.hpp"
#include "core/ui/module-ui.hpp"
#include "core/audio/faust.hpp"
#include "util/tapebuffer.hpp"
#include "util/audio.hpp"

namespace top1::modules {

  using BeatPos = int;

  class Metronome : public Module, audio::FaustWrapper {
    ui::ModuleScreen<Metronome>::ptr screen;
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

    void process(audio::ProcessData&) override;
    void display() override;

    void postBuffers(audio::ProcessData&) override;

    // Formalities are over

    top1::TapeTime getBarTime(BeatPos bar);
    top1::TapeTime getBarTimeRel(BeatPos bar);
    BeatPos closestBar(top1::TapeTime time);
  };

  class MetronomeScreen : public ui::ModuleScreen<Metronome> {

    void drawMetronome(ui::drawing::Canvas&);

  public:
    using ui::ModuleScreen<Metronome>::ModuleScreen;

    void rotary(ui::RotaryEvent) override;

    void draw(ui::drawing::Canvas&) override;

  };

}
