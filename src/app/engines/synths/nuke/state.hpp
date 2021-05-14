#pragma once

#include "lib/util/visitor.hpp"
#include "lib/util/with_limits.hpp"

namespace otto::engines::nuke {


  struct State {
    util::StaticallyBounded<float, 0, 1> param0 = 0;
    util::StaticallyBounded<float, 0, 1> param1 = 0;
    util::StaticallyBounded<float, 0, 1> param2 = 0;
    util::StaticallyBounded<float, 0, 1> param3 = 0;


    util::StaticallyBounded<float, 0, 1> envparam0 = 0;
    util::StaticallyBounded<float, 0, 1> envparam1 = 0;
    util::StaticallyBounded<float, 0, 1> envparam2 = 0;
    util::StaticallyBounded<float, 0, 1> envparam3 = 0;
    bool shift = false;

    DECL_VISIT(param0, param1, param2, param3, envparam0, envparam1, envparam2, envparam3);
  };

} // namespace otto::engines::nuke
