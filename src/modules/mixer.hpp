#pragma once

#include "../module.h"
#include "../ui/base.h"
#include "../util/tapebuffer.h"

class MixerScreen;

class MixerModule : public module::Module {
  std::shared_ptr<MixerScreen> screen;
public:

  struct Data : module::Data {
    struct TrackInfo : module::Data {
      module::Opt<float> level = {this, "LEVEL", 0.5, 0, 0.99, 0.01};
      module::Opt<float> pan = {this, "PAN", 0, -0.9, 0.9, 0.1};
      module::Opt<bool> muted = {this, "MUTE", false};
    } track[4];

    Data() {
      subGroup("TRACK1", track[0]);
      subGroup("TRACK2", track[1]);
      subGroup("TRACK3", track[2]);
      subGroup("TRACK4", track[3]);
    }
  } data;

  top1::AudioAverage trackGraph[4];

  MixerModule();

  void display();

  void process(uint nframes);
};

class MixerScreen : public ui::ModuleScreen<MixerModule> {

  enum {
    PAN,
    LEVEL
  } numDisplay = LEVEL;

  virtual void draw(drawing::Canvas& ctx) override;

  virtual bool keypress(ui::Key key) override;
  virtual bool keyrelease(ui::Key key) override;

  void drawMixerSegment(drawing::Canvas& ctx, int track, float x, float y);

public:
  MixerScreen(MixerModule *module) : ui::ModuleScreen<MixerModule>(module) {}
};
