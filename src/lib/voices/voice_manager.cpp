#include "voice_manager.hpp"

#include "lib/engine.hpp"
#include "lib/itc/itc.hpp"

#include "app/input.hpp"
#include "app/services/controller.hpp"
#include "app/services/logic_thread.hpp"

namespace otto::voices {
  struct Logic final : ILogic, itc::Producer<VoicesState> {
    using Producer::Producer;
  };

  std::unique_ptr<ILogic> make_voices_logic(itc::Context& c)
  {
    return std::make_unique<Logic>(c);
  }
} // namespace otto::voices
