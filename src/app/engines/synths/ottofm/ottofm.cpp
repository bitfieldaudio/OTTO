#include "ottofm.hpp"

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

  struct Handler final : LinkedInputHandler<Logic> {
    using LinkedInputHandler::LinkedInputHandler;

    void handle(KeyPress e) noexcept final
    {
      switch (e.key) {
        case Key::blue_enc_click: produce(itc::set(&State::cur_op_idx, 3)); break;
        case Key::green_enc_click: produce(itc::set(&State::cur_op_idx, 2)); break;
        case Key::yellow_enc_click: produce(itc::set(&State::cur_op_idx, 1)); break;
        case Key::red_enc_click: produce(itc::set(&State::cur_op_idx, 0)); break;
        default: break;
      }
    }
#define GET_MEMBER(...) [](auto& self) -> decltype(auto) { return self.__VA_ARGS__; }

    void handle(EncoderEvent e) noexcept final
    {
      // TODO
      bool shift = false;

      switch (e.encoder) {
        case Encoder::blue: {
          state().algorithm_idx += e.steps;
          update(GET_MEMBER(algorithm_idx));
          return;
        } break;
        case Encoder::green: {
          if (!shift) {
            state().current_op().ratio_idx += e.steps;
            update(GET_MEMBER(current_op().ratio_idx));
            return;
          } else {
            state().current_op().detune += e.steps * 0.01;
            update(GET_MEMBER(current_op().detune));
            return;
          }
        } break;
        case Encoder::yellow: {
          if (!shift) {
            state().current_op().level += e.steps * 0.01;
            update(GET_MEMBER(current_op().level));
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
            state().current_op().feedback += e.steps * 0.01;
            update(GET_MEMBER(current_op().feedback));
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
