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

      switch (e.encoder) {
        case Encoder::blue: {
          updater.algorithm_idx() += e.steps;
          return;
        } break;
        case Encoder::green: {
          if (!shift) {
            updater.operators.get<3>().ratio_idx() += e.steps;
            return;
          } else {
            updater.operators.get<3>().detune() += e.steps * 0.01;
            return;
          }
        } break;
        case Encoder::yellow: {
          if (!shift) {
            updater.operators.get<3>().level() += e.steps * 0.01;
            return;
          } else {
            produce([steps = e.steps](State& s) {
              for (auto& op : s.operators) op.level += steps * 0.01;
            });
            return;
          }
        } break;
        case Encoder::red: {
          if (!shift) {
            updater.operators.get<3>().feedback() += e.steps * 0.01;
            return;
          } else {
            produce([steps = e.steps](State& s) {
              for (auto& op : s.operators) op.feedback += steps * 0.01;
            });
            return;
          }
        } break;
      }
    }
  };

} // namespace otto::engines::ottofm
