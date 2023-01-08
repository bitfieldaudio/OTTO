#pragma once

#include "lib/util/visitor.hpp"

#include "lib/audio.hpp"
#include "lib/graphics.hpp"

namespace otto {

  struct EngineMetaData {
    std::string name;
  };

  namespace synth_dispatcher_cmd {
    struct SelectEngine {
      int index = 0;
    };
    using Type = std::variant<SelectEngine>;
  } // namespace synth_dispatcher_cmd

  /// Commands sent from graphics to logic
  using SynthDispatcherCommand = synth_dispatcher_cmd::Type;

  struct SynthDispatcherState {
    int active_engine = 0;
    std::string name;
    ISynthAudio* audio;
    ScreenWithHandlerPtr main_screen;
    ScreenWithHandlerPtr mod_screen;
    ScreenWithHandlerPtr voices_screen;
    std::vector<EngineMetaData> all_engines;
  };

} // namespace otto
