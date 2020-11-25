#include "ottofm.hpp"

#include "lib/engine.hpp"
#include "lib/itc/itc.hpp"

#include "app/input.hpp"
#include "app/services/controller.hpp"
#include "app/services/logic_thread.hpp"

namespace otto::engines::ottofm {

  struct Logic final : itc::Producer<State> {
    using Producer::Producer;
  };

} // namespace otto::engines::ottofm
