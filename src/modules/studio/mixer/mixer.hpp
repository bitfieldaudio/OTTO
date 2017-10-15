#pragma once

#include <fmt/format.h>

#include "core/modules/module.hpp"
#include "core/ui/canvas.hpp"
#include "core/ui/module-ui.hpp"

#include "util/algorithm.hpp"
#include "util/audio.hpp"

namespace otto::modules {
  class MixerScreen;

  class Mixer final : public modules::Module {
    std::unique_ptr<MixerScreen> screen;

    audio::ProcessBuffer<2> proc_buf;
  public:

    struct Props : public Properties {
      struct TrackInfo : public Properties {
        Property<float> level = {this, "LEVEL", 0.5, {0, 1, 0.01}};
        Property<float> pan = {this, "PAN", 0, {-1, 1, 0.1}};
        Property<bool> muted = {this, "MUTE", false};
        using Properties::Properties;
      };

      std::array<TrackInfo, 4> tracks = util::generate_sequence<4>(
        [this] (int n) {
          return TrackInfo(this, fmt::format("Track {}", n + 1));
        });
    } props;

    std::array<util::audio::Graph, 4> graphs;

    Mixer();

    void display();

    audio::ProcessData<2> process_tracks(audio::ProcessData<4>);
    audio::ProcessData<2> process_engine(audio::ProcessData<1>);
  };

  class MixerScreen : public ui::ModuleScreen<Mixer> {

    void draw(ui::drawing::Canvas& ctx) override;

    bool keypress(ui::Key key) override;
    bool keyrelease(ui::Key key) override;
    void rotary(ui::RotaryEvent) override;

    // TODO: Convert to Widget
    void drawMixerSegment(ui::drawing::Canvas& ctx, int track, float x, float y);

  public:
    using ModuleScreen<Mixer>::ModuleScreen;
  };

} // otto::modules
