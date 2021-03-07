#pragma once

#include "lib/util/local_vector.hpp"
#include "lib/util/visitor.hpp"
#include "lib/util/with_limits.hpp"

#include "lib/audio.hpp"
#include "lib/engine.hpp"
#include "lib/graphics.hpp"
#include "lib/midi.hpp"

#include "app/services/graphics.hpp"

#include "state.hpp"

using namespace otto;

namespace otto::engines::arp {
  struct ILogic {
    virtual ~ILogic() = default;
  };

  struct IMidiFXAudio {
    virtual midi::IMidiHandler& midi_handler() noexcept = 0;
  };

  struct MidiFXEngineInstance {
    std::unique_ptr<ILogic> logic;
    std::unique_ptr<IMidiFXAudio> audio;
    ScreenWithHandler screen;
  };

  struct MidiFXEngineFactory {
    fu2::unique_function<std::unique_ptr<ILogic>(itc::ChannelGroup&) const> make_logic;
    fu2::unique_function<std::unique_ptr<IMidiFXAudio>(itc::ChannelGroup&) const> make_audio;
    fu2::unique_function<ScreenWithHandler(itc::ChannelGroup&) const> make_screen;

    MidiFXEngineInstance make_all(itc::ChannelGroup& chan) const
    {
      return {
        .logic = make_logic(chan),
        .audio = make_audio(chan),
        .screen = make_screen(chan),
      };
    }

    MidiFXEngineInstance make_without_audio(itc::ChannelGroup& chan) const
    {
      return {
        .logic = make_logic(chan),
        .audio = nullptr,
        .screen = make_screen(chan),
      };
    }

    MidiFXEngineInstance make_without_screen(itc::ChannelGroup& chan) const
    {
      return {
        .logic = make_logic(chan),
        .audio = make_audio(chan),
        .screen = {nullptr, nullptr},
      };
    }
  };

  std::unique_ptr<ILogic> make_logic(itc::ChannelGroup&);
  ScreenWithHandler make_screen(itc::ChannelGroup&);
  std::unique_ptr<IMidiFXAudio> make_audio(itc::ChannelGroup&);

  // NOLINTNEXTLINE
  inline const MidiFXEngineFactory factory = {
    .make_logic = make_logic,
    .make_audio = make_audio,
    .make_screen = make_screen,
  };

} // namespace otto::engines::arp