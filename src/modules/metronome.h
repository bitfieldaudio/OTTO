#pragma once

#include "../module.h"
#include "../ui/base.h"
#include "../faust.h"
#include "../util/tapebuffer.h"

using BeatPos = int;

namespace module {

class Metronome : public Module, FaustWrapper {
  std::shared_ptr<ui::ModuleScreen<Metronome>> screen;
public:
  struct Data : public module::Data {
    Opt<float> bpm    = {this, "BPM", 120, 40, 320, 1};
    Opt<float> gain   = {this, "GAIN", 0, 0, 1, 0.01};
    Opt<float> tone   = {this, "TONE", 0, 0, 1, 0.01};
    Opt<bool> trigger = {this, "TRIGGER", false, false};
  } data;

  top1::AudioAverage graph;

  Metronome();

  void process(uint nframes) override;
  void display() override;

  void postBuffers(uint nframes) override;

  // Formalities are over

  top1::TapeTime getBarTime(BeatPos bar);
  top1::TapeTime getBarTimeRel(BeatPos bar);
  BeatPos closestBar(top1::TapeTime time);
};

class MetronomeScreen : public ui::ModuleScreen<Metronome> {

  void drawMetronome(NanoCanvas::Canvas &);

public:
  bool keypress(ui::Key) override;

  void draw(NanoCanvas::Canvas &) override;

  using ui::ModuleScreen<Metronome>::ModuleScreen;
};

}
