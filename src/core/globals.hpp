#pragma once

#include "filesystem.hpp"
#include "util/event.hpp"

#include "core/engines/engine.hpp"
#include "core/engines/engine_dispatcher.hpp"

#include "engines/studio/input_selector/input_selector.hpp"
#include "engines/studio/metronome/metronome.hpp"
#include "engines/studio/mixer/mixer.hpp"
#include "engines/studio/tapedeck/tapedeck.hpp"

namespace otto {
  namespace global {
    enum struct ErrorCode {
      none = 0,
      ui_closed,
      user_exit,
      audio_error,
      graphics_error,
      input_error
    };

    using exception = util::as_exception<ErrorCode>;

    inline const filesystem::path data_dir {"data"};

    namespace event {
      inline util::EventDispatcher<> pre_init;
      inline util::EventDispatcher<> post_init;
      inline util::EventDispatcher<> pre_exit;
      inline util::EventDispatcher<> post_exit;
      inline util::EventDispatcher<unsigned> buffersize_change;
      inline util::EventDispatcher<unsigned> samplerate_change;
    }

    inline engines::EngineDispatcher<engines::EngineType::synth> synth;
    inline engines::EngineDispatcher<engines::EngineType::drums> drums;
    inline engines::EngineDispatcher<engines::EngineType::effect> effect;
    inline engines::Tapedeck tapedeck;
    inline engines::Mixer mixer;
    inline engines::Metronome metronome;
    inline engines::InputSelector selector;

    void init();

    void exit(ErrorCode ec) noexcept;

    bool running() noexcept;

    ErrorCode error() noexcept;
  }

}
