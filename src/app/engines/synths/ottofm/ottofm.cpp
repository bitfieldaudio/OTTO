#include "app/engines/synths/ottofm/ottofm.gen.hpp"

#include "lib/engine.hpp"
#include "lib/itc/itc.hpp"

#include "app/input.hpp"
#include "app/services/controller.hpp"
#include "app/services/logic_thread.hpp"

using namespace otto;

namespace otto::engines::ottofm {

  struct Logic final : itc::Producer<State> {
    Logic(itc::Channel<State>& c) : itc::Producer<State>(c) {}
  };

  struct Handler final : InputReducer<State> {
    void reduce(KeyPress e, itc::Updater<State> updater) noexcept final
    {
      switch (e.key) {
        case Key::blue_enc_click: updater.cur_op_idx() = 3; break;
        case Key::green_enc_click: updater.cur_op_idx() = 2; break;
        case Key::yellow_enc_click: updater.cur_op_idx() = 1; break;
        case Key::red_enc_click: updater.cur_op_idx() = 0; break;
        default: break;
      }
    }

    void reduce(EncoderEvent e, itc::Updater<State> updater) noexcept final
    {
      // TODO
      bool shift = false;

      auto f = [&]<int Idx>(meta::c<Idx>, int cur) {
        if (cur != Idx) return;
        switch (e.encoder) {
          case Encoder::blue: {
            updater.algorithm_idx() += e.steps;
          } break;
          case Encoder::green: {
            if (!shift) {
              std::get<Idx>(updater.operators).ratio_idx() += e.steps;
            } else {
              std::get<Idx>(updater.operators).detune() += e.steps * 0.01;
            }
          } break;
          case Encoder::yellow: {
            if (!shift) {
              std::get<Idx>(updater.operators).level() += e.steps * 0.01;
            } else {
              for (auto& op : updater.operators()) op.level += e.steps * 0.01;
            }
          } break;
          case Encoder::red: {
            if (!shift) {
              std::get<Idx>(updater.operators).feedback() += e.steps * 0.01;
            } else {
              for (auto& op : updater.operators()) op.feedback += e.steps * 0.01;
            }
          } break;
        }
      };
      f(meta::c<0>(), updater.cur_op_idx.get());
      f(meta::c<1>(), updater.cur_op_idx.get());
      f(meta::c<2>(), updater.cur_op_idx.get());
      f(meta::c<3>(), updater.cur_op_idx.get());
    }
  };

} // namespace otto::engines::ottofm
