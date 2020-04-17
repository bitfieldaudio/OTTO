#pragma once

#include "audio.hpp"
#include "core/ui/screen.hpp"
#include "ottofm.hpp"

namespace otto::engines::ottofm {

  using namespace itc;

  template<int I>
  using OperatorActions = meta::list<itc::prop_change<&Props::OperatorProps<I>::feedback>,
                                     itc::prop_change<&Props::OperatorProps<I>::attack>,
                                     itc::prop_change<&Props::OperatorProps<I>::decay_release>,
                                     itc::prop_change<&Props::OperatorProps<I>::suspos>,
                                     itc::prop_change<&Props::OperatorProps<I>::detune>,
                                     itc::prop_change<&Props::OperatorProps<I>::ratio_idx>,
                                     itc::prop_change<&Props::OperatorProps<I>::out_level>>;

  struct OttofmScreen : ui::Screen,
                        ActionReceiver< //
                          OperatorActions<0>,
                          OperatorActions<1>,
                          OperatorActions<2>,
                          OperatorActions<3>,
                          itc::prop_change<&Props::algorithm_idx>,
                          itc::prop_change<&Props::cur_op>,
                          itc::prop_change<&Props::fm_amount>> //
  {
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

    template<int I>
    struct OperatorHelper : ActionReceiver<OperatorActions<I>> {
      OperatorHelper(OperatorData& data) : data(data) {}

      void action(itc::prop_change<&Props::OperatorProps<I>::feedback>, float f) noexcept final
      {
        data.feedback = f / 0.4;
      }
      void action(itc::prop_change<&Props::OperatorProps<I>::attack>, float a) noexcept final
      {
        data.attack = a;
      }
      void action(itc::prop_change<&Props::OperatorProps<I>::decay_release>, float dr) noexcept final
      {
        data.decay_release = dr;
      }
      void action(itc::prop_change<&Props::OperatorProps<I>::suspos>, float s) noexcept final
      {
        data.suspos = s;
      }
      void action(itc::prop_change<&Props::OperatorProps<I>::detune>, float d) noexcept final
      {
        data.detune = d;
      }
      void action(itc::prop_change<&Props::OperatorProps<I>::ratio_idx>, int ri) noexcept final
      {
        data.ratio_idx = ri;
      }
      void action(itc::prop_change<&Props::OperatorProps<I>::out_level>, float ol) noexcept final
      {
        data.out_level = ol;
      }
      OperatorData& data;
    };

    OttofmScreen(std::array<itc::Shared<float>, 4> activity) : shared_activity(activity)
    {
      for (auto&& [i, w] : util::view::indexed(sinewave)) w = sin(M_2PI * (float) i / 30.f);
      for (auto&& [i, w] : util::view::indexed(harmonics))
        w = -0.5 * sin(2.f * M_2PI * (float) i / 30.f) + 0.33 * sin(3.f * M_2PI * (float) i / 30.f) -
            0.25 * sin(4.f * M_2PI * (float) i / 30.f);
    }

    void draw(nvg::Canvas& ctx) override;
    void draw_with_shift(nvg::Canvas& ctx);
    void draw_no_shift(nvg::Canvas& ctx);
    void draw_operators(nvg::Canvas& ctx);
    void draw_envelope(nvg::Canvas& ctx);


    void action(itc::prop_change<&Props::algorithm_idx>, int a) noexcept final
    {
      for (auto&& [op, mod] : util::zip(ops, algorithms[a].modulator_flags)) {
        op.modulator = mod;
      }
      algorithm_idx = a;
    }

    void action(itc::prop_change<&Props::cur_op>, int idx) noexcept final
    {
      cur_op = idx;
    }

    void action(itc::prop_change<&Props::fm_amount>, float fm) noexcept final
    {
      fm_amount = fm;
    }

#define OTTOFM_FWD_TO_HELPERS(PropName, ArgType, I)                                                                    \
  void action(itc::prop_change<&Props::OperatorProps<I>::PropName>, ArgType a) noexcept final                          \
  {                                                                                                                    \
    util::for_each(operator_helpers, [&](auto& op) {                                                                   \
      itc::try_call_receiver(op, itc::prop_change<&Props::OperatorProps<I>::PropName>::data(a));                       \
    });                                                                                                                \
  }

    OTTOFM_FWD_TO_HELPERS(feedback, float, 0)
    OTTOFM_FWD_TO_HELPERS(attack, float, 0)
    OTTOFM_FWD_TO_HELPERS(decay_release, float, 0)
    OTTOFM_FWD_TO_HELPERS(suspos, float, 0)
    OTTOFM_FWD_TO_HELPERS(detune, float, 0)
    OTTOFM_FWD_TO_HELPERS(ratio_idx, int, 0)
    OTTOFM_FWD_TO_HELPERS(out_level, float, 0)
    OTTOFM_FWD_TO_HELPERS(feedback, float, 1)
    OTTOFM_FWD_TO_HELPERS(attack, float, 1)
    OTTOFM_FWD_TO_HELPERS(decay_release, float, 1)
    OTTOFM_FWD_TO_HELPERS(suspos, float, 1)
    OTTOFM_FWD_TO_HELPERS(detune, float, 1)
    OTTOFM_FWD_TO_HELPERS(ratio_idx, int, 1)
    OTTOFM_FWD_TO_HELPERS(out_level, float, 1)
    OTTOFM_FWD_TO_HELPERS(feedback, float, 2)
    OTTOFM_FWD_TO_HELPERS(attack, float, 2)
    OTTOFM_FWD_TO_HELPERS(decay_release, float, 2)
    OTTOFM_FWD_TO_HELPERS(suspos, float, 2)
    OTTOFM_FWD_TO_HELPERS(detune, float, 2)
    OTTOFM_FWD_TO_HELPERS(ratio_idx, int, 2)
    OTTOFM_FWD_TO_HELPERS(out_level, float, 2)
    OTTOFM_FWD_TO_HELPERS(feedback, float, 3)
    OTTOFM_FWD_TO_HELPERS(attack, float, 3)
    OTTOFM_FWD_TO_HELPERS(decay_release, float, 3)
    OTTOFM_FWD_TO_HELPERS(suspos, float, 3)
    OTTOFM_FWD_TO_HELPERS(detune, float, 3)
    OTTOFM_FWD_TO_HELPERS(ratio_idx, int, 3)
    OTTOFM_FWD_TO_HELPERS(out_level, float, 3)

#undef OTTOFM_FWD_TO_HELPERS
  private:
    bool shift = false;
    int cur_op = 0;
    float fm_amount = 0;
    int algorithm_idx = 0;

    std::array<itc::Shared<float>, 4> shared_activity;

    std::array<OperatorData, 4> ops;
    std::tuple<OperatorHelper<0>, OperatorHelper<1>, OperatorHelper<2>, OperatorHelper<3>> operator_helpers = {
      {ops[0]},
      {ops[1]},
      {ops[2]},
      {ops[3]}};

    std::array<float, 30> sinewave;
    std::array<float, 30> harmonics;
  };

  static_assert(
    itc::is_action_receiver_v<OttofmScreen::OperatorHelper<1>, itc::prop_change<&Props::OperatorProps<1>::feedback>>);
  static_assert(itc::is_action_receiver_v<OttofmScreen, itc::prop_change<&Props::OperatorProps<1>::feedback>>);
} // namespace otto::engines::ottofm
