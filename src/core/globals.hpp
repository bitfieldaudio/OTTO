#pragma once

#include "filesystem.hpp"
#include "util/event.hpp"

#include "core/audio/main_audio.hpp"
#include "core/ui/mainui.hpp"

#include "core/modules/module-dispatcher.hpp"

#include "modules/studio/input_selector/input_selector.hpp"
#include "modules/studio/metronome/metronome.hpp"
#include "modules/studio/mixer/mixer.hpp"
#include "modules/studio/tapedeck/tapedeck.hpp"

namespace otto {

  namespace global {

    enum struct ErrorCode {
      none = 0,
      ui_closed,
      user_exit,
      audio_error
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

    inline audio::MainAudio audio;
    inline ui::MainUI ui;

    inline modules::SynthModuleDispatcher synth;
    inline modules::SynthModuleDispatcher drums;
    inline modules::EffectModuleDispatcher effect;
    inline modules::Tapedeck tapedeck;
    inline modules::Mixer mixer;
    inline modules::Metronome metronome;
    inline modules::InputSelector selector;

    void init();

    void exit(ErrorCode ec) noexcept;

    bool running() noexcept;

    ErrorCode error() noexcept;

    void read_data();

    void save_data();
  }

}
