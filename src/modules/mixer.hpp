#pragma once

#include "core/modules/module.hpp"
#include "core/ui/canvas.hpp"
#include "core/ui/module-ui.hpp"

#include "util/audio.hpp"

namespace top1::module {
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

    audio::Graph trackGraph[4];

    MixerModule();

    void display();

    void process(audio::ProcessData&);
  };

  class MixerScreen : public ui::ModuleScreen<MixerModule> {

    enum {
      Pan,
      Level
    } numDisplay = Level;

    virtual void draw(ui::drawing::Canvas& ctx) override;

    virtual bool keypress(ui::Key key) override;
    virtual bool keyrelease(ui::Key key) override;

    // TODO: Convert to Widget
    void drawMixerSegment(ui::drawing::Canvas& ctx, int track, float x, float y);

  public:
    MixerScreen(MixerModule *module) : ui::ModuleScreen<MixerModule>(module) {}
  };

} // top1::module
