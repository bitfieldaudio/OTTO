#include "lib/itc/itc.hpp"
#include "app/input.hpp"
#include "app/services/controller.hpp"
#include "app/services/logic_thread.hpp"

#include "ottofm.hpp"

using namespace otto;

namespace otto::engines::ottofm {

  struct Logic final : itc::Producer<State> {
    Logic(itc::Channel<State>& c) : itc::Producer<State>(c) {}
  };

  struct Handler final : InputHandler {
    Handler(Logic& l) : logic(l) {}
    Logic& logic;

    void handle(KeyPress e) noexcept final {
      switch (e.key) {
        case Key::blue_enc_click: logic.produce(itc::set(&State::cur_op, 3)); break;
        case Key::green_enc_click: logic.produce(itc::set(&State::cur_op, 2)); break;
        case Key::yellow_enc_click: logic.produce(itc::set(&State::cur_op, 1)); break;
        case Key::red_enc_click: logic.produce(itc::set(&State::cur_op, 0)); break;
        default: break;
      }
    }

    void handle(EncoderEvent e) noexcept final
    {
      // TODO
      bool shift = false;

      switch (e.encoder) {
        case Encoder::blue: logic.produce(itc::increment(&State::algorithm_idx, e.steps)); break;
        case Encoder::green: {
          if (!shift) { logic.produce([this, steps = e.steps](State& s){s.operators[logic.state().cur_op].ratio_idx += steps;}); }
          else { logic.produce([this, steps = e.steps](State& s){s.operators[logic.state().cur_op].detune += steps * 0.01;}); }
          break;
        }
        case Encoder::yellow: {
          if (!shift)  { logic.produce([this, steps = e.steps](State& s){s.operators[logic.state().cur_op].level += steps * 0.01;}); }
          else { logic.produce([this, steps = e.steps](State& s){for (auto& op : s.operators) op.level += steps * 0.01;});}
          break;
        }
        case Encoder::red: {
          if (!shift)  { logic.produce([this, steps = e.steps](State& s){s.operators[logic.state().cur_op].feedback += steps * 0.01;}); }
          else { logic.produce([this, steps = e.steps](State& s){for (auto& op : s.operators) op.feedback += steps * 0.01;});}
          break;
        } 
      }
    }
  };

}