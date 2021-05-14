#include "nuke.hpp"

#include "lib/engine.hpp"
#include "lib/itc/itc.hpp"

#include "app/input.hpp"
#include "app/services/controller.hpp"
#include "app/services/logic_thread.hpp"

namespace otto::engines::nuke {

  struct Logic final : ILogic, itc::Producer<State> {
    using Producer::Producer;
  };

  std::unique_ptr<ILogic> make_logic(itc::Channel& c)
  {
    return std::make_unique<Logic>(c);
  }

} // namespace otto::engines::nuke
