#pragma once

#include <fmt/format.h>

#include "core/engines/engine.hpp"
#include "core/ui/canvas.hpp"

#include "util/algorithm.hpp"
#include "util/audio.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engines;

  struct Mixer final : Engine<EngineType::studio> {
    Mixer();

    audio::ProcessData<2> process_tracks(audio::ProcessData<4>);
    audio::ProcessData<2> process_engine(audio::ProcessData<1>);

    struct Props : public Properties {
      struct TrackInfo : public Properties {
        Property<float> level = {this, "LEVEL", 0.5, {0, 1, 0.01}};
        Property<float> pan   = {this, "PAN", 0, {-1, 1, 0.1}};
        Property<bool> muted  = {this, "MUTE", false};
        using Properties::Properties;
      };

      std::array<TrackInfo, 4> tracks =
        util::generate_sequence<4>([this](int n) {
          return TrackInfo(this, fmt::format("Track {}", n + 1));
        });
    } props;

    std::array<util::audio::Graph, 4> graphs;

  private:
    audio::ProcessBuffer<2> proc_buf;
  };

}  // namespace otto::engines
