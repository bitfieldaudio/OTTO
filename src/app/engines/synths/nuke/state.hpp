#pragma once

#include "lib/util/visitor.hpp"
#include "lib/util/with_limits.hpp"

namespace otto::engines::nuke {


  struct State {
    util::StaticallyBounded<float, 0, 1> param0 = 0;
    util::StaticallyBounded<float, -1, 1> param1 = 0;
    util::StaticallyBounded<float, 0, 1> param2 = 0;
    util::StaticallyBounded<float, 0, 1> param3 = 0;

    // Volume envelope
    util::StaticallyBounded<float, 0, 1> envparam0_0 = 0;
    util::StaticallyBounded<float, 0, 1> envparam0_1 = 0;
    util::StaticallyBounded<float, 0, 1> envparam0_2 = 0;
    util::StaticallyBounded<float, 0, 1> envparam0_3 = 0;
    // Filter envelope
    util::StaticallyBounded<float, 0, 1> envparam1_0 = 0;
    util::StaticallyBounded<float, 0, 1> envparam1_1 = 0;
    util::StaticallyBounded<float, 0, 1> envparam1_2 = 0;
    util::StaticallyBounded<float, 0, 1> envparam1_3 = 0;
    // LFO
    util::StaticallyBounded<float, 0, 1> envparam2_0 = 0;
    util::StaticallyBounded<int, 0, 9> envparam2_1 = 0;
    util::StaticallyBounded<float, 0, 1> envparam2_2 = 0;
    util::StaticallyBounded<float, 0, 1> envparam2_3 = 0;
    //
    util::StaticallyBounded<float, 0, 1> envparam3_0 = 0;
    util::StaticallyBounded<float, 0, 1> envparam3_1 = 0;
    util::StaticallyBounded<float, 0, 1> envparam3_2 = 0;
    util::StaticallyBounded<float, 0, 1> envparam3_3 = 0;

    int active_idx = 0;
    bool shift = false;

    DECL_VISIT(param0,
               param1,
               param2,
               param3,
               envparam0_0,
               envparam0_1,
               envparam0_2,
               envparam0_3,
               envparam1_0,
               envparam1_1,
               envparam1_2,
               envparam1_3,
               envparam2_0,
               envparam2_1,
               active_idx);
  };

} // namespace otto::engines::nuke
