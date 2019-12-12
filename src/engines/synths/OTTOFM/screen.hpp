#pragma once

#include "audio.hpp"
#include "core/ui/screen.hpp"
#include "ottofm.hpp"

namespace otto::engines::ottofm {

  using namespace itc;

  struct OttofmScreen : ui::Screen {
    struct OperatorData {
      float feedback;
      float attack;
      float decay_release;
      float suspos;
      // Oscillator
      float detune;
      int ratio_idx;
      // Amp
      float out_level;
      bool modulator;
    };

    void draw(nvg::Canvas& ctx) override;
    void draw_with_shift(nvg::Canvas& ctx);
    void draw_no_shift(nvg::Canvas& ctx);
    void draw_operators(nvg::Canvas& ctx);
    void draw_envelope(nvg::Canvas& ctx);


    void action(itc::prop_change<&Props::algorithm_idx>, int a) noexcept
    {
      for (auto&& [op, mod] : util::zip(ops, algorithms[a].modulator_flags)) {
        op.modulator = mod;
      }
      algorithm_idx = a;
    }

    void action(itc::prop_change<&Props::cur_op>, int idx) noexcept
    {
      cur_op = idx;
    }

    void action(itc::prop_change<&Props::fm_amount>, float fm) noexcept
    {
      fm_amount = fm;
    }

    // Operator handlers

    template<int I>
    void action(itc::prop_change<&Props::OperatorProps<I>::feedback>, float f) noexcept
    {
      ops[I].feedback = f;
    }
    template<int I>
    void action(itc::prop_change<&Props::OperatorProps<I>::attack>, float a) noexcept
    {
      ops[I].attack = a;
    }
    template<int I>
    void action(itc::prop_change<&Props::OperatorProps<I>::decay_release>, float dr) noexcept
    {
      ops[I].decay_release = dr;
    }
    template<int I>
    void action(itc::prop_change<&Props::OperatorProps<I>::suspos>, float s) noexcept
    {
      ops[I].suspos = s;
    }
    template<int I>
    void action(itc::prop_change<&Props::OperatorProps<I>::detune>, float d) noexcept
    {
      ops[I].detune = d;
    }
    template<int I>
    void action(itc::prop_change<&Props::OperatorProps<I>::ratio_idx>, int ri) noexcept
    {
      ops[I].ratio_idx = ri;
    }
    template<int I>
    void action(itc::prop_change<&Props::OperatorProps<I>::out_level>, float ol) noexcept
    {
      ops[I].out_level = ol;
    }

  private:
    bool shift = false;
    int cur_op = 0;
    float fm_amount = 0;
    int algorithm_idx = 0;

    std::array<OperatorData, 4> ops;
  };
} // namespace otto::engines::ottofm
