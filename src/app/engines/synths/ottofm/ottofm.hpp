#pragma once

#include "lib/audio.hpp"
#include "lib/graphics.hpp"
#include "lib/midi.hpp"
#include "lib/util/local_vector.hpp"
#include "lib/util/visitor.hpp"
#include "lib/util/with_limits.hpp"

#include "app/services/graphics.hpp"

#include "state.hpp"

using namespace otto;

namespace otto::engines::ottofm {
  struct ILogic {
    virtual ~ILogic() = default;
  };

  struct ISynthAudio : IAudioProcessor<util::audio_buffer()> {
    virtual midi::IMidiHandler& midi_handler() noexcept = 0;
  };

  struct SynthEngineInstance {
    std::unique_ptr<ILogic> logic;
    std::unique_ptr<ISynthAudio> audio;
    ScreenWithHandler main_screen;
    ScreenWithHandler mod_screen;
  };

  ScreenWithHandler make_main_screen(itc::ChannelGroup&);
  ScreenWithHandler make_mod_screen(itc::ChannelGroup&);
  std::unique_ptr<ISynthAudio> make_audio(itc::ChannelGroup&);

  SynthEngineInstance make(itc::ChannelGroup&);
} // namespace otto::engines::ottofm
