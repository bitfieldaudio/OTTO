#pragma once

#include "../module.h"
#include "../ui/base.h"
#include "../util/tapebuffer.h"


class MixerModule : public Module {

  struct {
    float level = 0.5;
    float pan = 0;
    bool muted = false;
  } trackInfo[4];

  ui::ModuleScreen<MixerModule> *screen;

public:

  MixerModule();

  void display();

  void process(uint nframes);

  bool trackMuted(int track) const;
  bool trackMuted(int track, bool newVal);

  float trackPan(int track) const;
  float trackPan(int track, float newVal);

  float trackLevel(int track) const;
  float trackLevel(int track, float newVal);

  void mute(int track) { trackMuted(track, true); }
  void unmute(int track) { trackMuted(track, false); }
  void toggleMute(int track) { trackMuted(track, !trackMuted(track)); }

  void levelUp(int track) { trackLevel(track, trackLevel(track) + 0.01); }
  void levelDown(int track) { trackLevel(track, trackLevel(track) - 0.01); }

  void panLeft(int track) { trackPan(track, trackPan(track) - 0.1); }
  void panRight(int track) { trackPan(track, trackPan(track) + 0.1); }
};

class MixerScreen : public ui::ModuleScreen<MixerModule> {

  enum {
    PAN,
    LEVEL
  } numDisplay = LEVEL;

  virtual void draw(NanoCanvas::Canvas& ctx) override;

  virtual bool keypress(ui::Key key) override;
  virtual bool keyrelease(ui::Key key) override;

  void drawMixerSegment(NanoCanvas::Canvas& ctx, int track, float x, float y);

public:
  MixerScreen(MixerModule *module) : ui::ModuleScreen<MixerModule>(module) {}
};
