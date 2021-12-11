#include "ottofm.hpp"

#include "lib/engine.hpp"
#include "lib/itc/itc.hpp"
#include "lib/voices/voice_manager.hpp"

#include "app/input.hpp"
#include "app/services/controller.hpp"
#include "app/services/logic_thread.hpp"


namespace otto::engines::ottofm {

  struct Logic final : ILogic, itc::Producer<State> {
    using Producer::Producer;

    Logic(itc::Context& c) : Producer(c), voices_logic(voices::make_voices_logic(c)) {}

  private:
    std::unique_ptr<ILogic> voices_logic;
  };

  std::unique_ptr<ILogic> make_logic(itc::Context& c)
  {
    return std::make_unique<Logic>(c);
  }

  ScreenWithHandler make_voices_screen(itc::Context& c)
  {
    return voices::make_voices_screen(c);
  }

} // namespace otto::engines::ottofm
