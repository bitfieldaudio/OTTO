#pragma once
#include "lib/util/with_limits.hpp"

#include "lib/util/visitor.hpp"

using namespace otto;

namespace otto::engines::ottofm {

  // Envelopes
  // step_sizes 0.1
  struct [[otto::reflect]] ADSRState {
    util::StaticallyBounded<float, 0, 1> attack = 0.2;
    util::StaticallyBounded<float, 0, 1> decay = 0.2;
    util::StaticallyBounded<float, 0, 1> sustain = 0.7;
    util::StaticallyBounded<float, 0, 1> release = 0.2;
  };

  struct [[otto::reflect]] OperatorState {
    ADSRState envelope;
    util::StaticallyBounded<float, 0, 1> feedback = 0;
    util::StaticallyBounded<float, 0, 1> level = 1;
    // Oscillator
    util::StaticallyBounded<float, -1, 1> detune = 0;
    util::StaticallyBounded<int, 0, 19> ratio_idx = 0;

    float current_level = 0;
  };

  struct [[otto::reflect]] State {
    util::StaticallyBounded<int, 0, 10, true> algorithm_idx = 0;
    util::StaticallyBounded<float, 0, 1> fm_amount = 1;
    std::array<OperatorState, 4> operators;
    util::StaticallyBounded<int, 0, 4> cur_op_idx = 0;

    OperatorState& current_op()
    {
      return operators[cur_op_idx];
    }
  };
} // namespace otto::engines::ottofm
