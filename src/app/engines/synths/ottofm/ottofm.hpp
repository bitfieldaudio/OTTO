#pragma once

#include "lib/util/local_vector.hpp"
#include "lib/util/visitor.hpp"
#include "lib/util/with_limits.hpp"

#include "lib/audio.hpp"
#include "lib/graphics.hpp"
#include "lib/midi.hpp"

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

  struct SynthEngineFactory {
    fu2::unique_function<std::unique_ptr<ILogic>(itc::ChannelGroup&) const> make_logic;
    fu2::unique_function<std::unique_ptr<ISynthAudio>(itc::ChannelGroup&) const> make_audio;
    fu2::unique_function<ScreenWithHandler(itc::ChannelGroup&) const> make_mod_screen;
    fu2::unique_function<ScreenWithHandler(itc::ChannelGroup&) const> make_main_screen;

    SynthEngineInstance make_all(itc::ChannelGroup& chan) const
    {
      return {
        .logic = make_logic(chan),
        .audio = make_audio(chan),
        .main_screen = make_main_screen(chan),
        .mod_screen = make_mod_screen(chan),
      };
    }

    SynthEngineInstance make_without_audio(itc::ChannelGroup& chan) const
    {
      return {
        .logic = make_logic(chan),
        .audio = nullptr,
        .main_screen = make_main_screen(chan),
        .mod_screen = make_mod_screen(chan),
      };
    }

    SynthEngineInstance make_without_screens(itc::ChannelGroup& chan) const
    {
      return {
        .logic = make_logic(chan),
        .audio = make_audio(chan),
        .main_screen = {nullptr, nullptr},
        .mod_screen = {nullptr, nullptr},
      };
    }
  };

  std::unique_ptr<ILogic> make_logic(itc::ChannelGroup&);
  ScreenWithHandler make_main_screen(itc::ChannelGroup&);
  ScreenWithHandler make_mod_screen(itc::ChannelGroup&);
  std::unique_ptr<ISynthAudio> make_audio(itc::ChannelGroup&);

  // NOLINTNEXTLINE
  inline const SynthEngineFactory factory = {
    .make_logic = make_logic,
    .make_audio = make_audio,
    .make_mod_screen = make_mod_screen,
    .make_main_screen = make_main_screen,
  };

  // Functions shared between graphics and audio
  // Duration of an envelope stage in seconds from underlying state member
  inline float envelope_stage_duration(const float d)
  {
    return 5 * d * d + 0.001f;
  }
} // namespace otto::engines::ottofm
