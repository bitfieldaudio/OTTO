#pragma once

#include "lib/util/local_vector.hpp"
#include "lib/util/visitor.hpp"
#include "lib/util/with_limits.hpp"

#include "lib/graphics.hpp"

namespace otto::engines::ottofm {

  // Envelopes
  // step_sizes 0.1
  struct ADSRState {
    util::StaticallyBounded<float, 0, 1> attack = 0.2;
    util::StaticallyBounded<float, 0, 1> decay = 0.2;
    util::StaticallyBounded<float, 0, 1> sustain = 0.7;
    util::StaticallyBounded<float, 0, 1> release = 0.2;

    DECL_VISIT(attack, decay, sustain, release);
  };

  struct OperatorState {
    ADSRState envelope;
    util::StaticallyBounded<float, 0, 1> shape = 0.5f;
    util::StaticallyBounded<float, 0, 1> level = 1;
    // Oscillator
    util::StaticallyBounded<float, -1, 1> detune = 0;
    util::StaticallyBounded<int, 0, 30> ratio_idx = 13;

    DECL_VISIT(envelope, shape, level, detune, ratio_idx);
  };

  struct State {
    util::StaticallyBounded<int, 0, 10, util::bounds_policies::wrap> algorithm_idx = 0;
    util::StaticallyBounded<float, 0, 1> fm_amount = 1;
    std::array<OperatorState, 4> operators;
    util::StaticallyBounded<int, 0, 4> cur_op_idx = 0;

    bool shift = false;

    DECL_VISIT(algorithm_idx, fm_amount, operators, cur_op_idx);

    OperatorState& current_op()
    {
      return operators[cur_op_idx];
    }
  };

  /// The state returned from the audio
  struct AudioState {
    std::array<float, 4> activity = {0, 0, 0, 0};
    std::array<float, 4> stage = {0, 0, 0, 0};
  };

  /// For defining frequency ratios
  struct Fraction {
    int numerator;
    int denominator;

    constexpr Fraction(int n = 1, int d = 1) noexcept : numerator(n), denominator(d) {}

    operator float() const
    {
      return float(numerator) / float(denominator);
    }

    [[nodiscard]] std::string to_string() const
    {
      if (numerator == 0) {
        return fmt::format("0");
      }
      return fmt::format("{}/{}", numerator, denominator);
    }
  };
  constexpr std::array<Fraction, 31> fractions = {
    {{0, 1},  {1, 64}, {1, 32}, {1, 16},  {3, 32}, {1, 8},  {5, 32}, {1, 4},  {5, 16}, {7, 16}, {1, 2},
     {5, 8},  {3, 4},  {1, 1},  {17, 12}, {3, 2},  {13, 8}, {7, 4},  {2, 1},  {5, 2},  {19, 7}, {3, 1},
     {22, 7}, {7, 2},  {4, 1},  {5, 1},   {6, 1},  {7, 1},  {8, 1},  {16, 1}, {32, 1}}};
  static_assert(std::is_trivially_copyable_v<State>);


  /// Used for graphics. Defined here for the Algorithm definitions below.
  enum struct Drawside {
    left,
    middle,
    right,
    // Number of sides
    n_sides,
  };

  struct Operatorline {
    float start = 1;
    float end = 2;
    Drawside side = Drawside::middle;
  };

  struct Algorithm {
    std::array<bool, 4> modulator_flags = {false, false, false, false};
    util::local_vector<Operatorline, 4> operator_lines;

    Algorithm(std::initializer_list<int> modulator_idx = {}, std::initializer_list<Operatorline> op_lines = {}) noexcept
      : operator_lines(op_lines)
    {
      for (auto&& idx : modulator_idx) {
        modulator_flags[idx] = true;
      }
    }
  };

  /// Defines the algorithms and gives instructions on how to draw them
  inline const std::array<Algorithm, 11> algorithms = {{
    Algorithm{
      {1, 2, 3},
      {{3, 2, Drawside::middle}, {2, 1, Drawside::middle}, {1, 0, Drawside::middle}},
    },
    Algorithm{
      {1, 2, 3},
      {{3, 1, Drawside::left}, {2, 1, Drawside::right}, {1, 0, Drawside::middle}},
    },
    Algorithm{
      {1, 2, 3},
      {{3, 0, Drawside::left}, {2, 1, Drawside::middle}, {1, 0, Drawside::middle}},
    },
    Algorithm{
      {1, 2, 3},
      {{3, 2, Drawside::left}, {3, 1, Drawside::left}, {2, 0, Drawside::right}, {1, 0, Drawside::right}},
    },
    Algorithm{
      {2, 3},
      {{3, 2, Drawside::middle}, {2, 1, Drawside::left}, {2, 0, Drawside::left}},
    },
    Algorithm{
      {2, 3},
      {{3, 2, Drawside::middle}, {2, 1, Drawside::middle}},
    },
    Algorithm{
      {1, 2, 3},
      {{3, 0, Drawside::left}, {2, 0, Drawside::right}, {1, 0, Drawside::middle}},
    },
    Algorithm{
      {1, 3},
      {{3, 2, Drawside::middle}, {1, 0, Drawside::middle}},
    },
    Algorithm{
      {3},
      {{3, 2, Drawside::middle}, {3, 1, Drawside::right}, {3, 0, Drawside::left}},
    },
    Algorithm{
      {3},
      {{3, 2, Drawside::middle}},
    },
    Algorithm{},
  }};


} // namespace otto::engines::ottofm
