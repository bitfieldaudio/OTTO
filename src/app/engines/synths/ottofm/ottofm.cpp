#include "ottofm.hpp"

#include "lib/engine.hpp"
#include "lib/itc/itc.hpp"

#include "app/input.hpp"
#include "app/services/controller.hpp"
#include "app/services/logic_thread.hpp"

namespace otto::engines::ottofm {

  struct Logic final : ILogic, itc::Producer<State> {
    using Producer::Producer;
  };

  SynthEngineInstance make(itc::ChannelGroup& chan)
  {
    return {
      .logic = std::make_unique<Logic>(chan),
      .audio = make_audio(chan),
      .main_screen = make_main_screen(chan),
      .mod_screen = make_mod_screen(chan),
    };
  }

} // namespace otto::engines::ottofm
