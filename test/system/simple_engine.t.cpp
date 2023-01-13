#include "testing.t.hpp"

#include <Gamma/Oscillator.h>

#include "lib/util/with_limits.hpp"

#include "lib/engine.hpp"
#include "lib/graphics.hpp"
#include "lib/itc/itc.hpp"
#include "lib/itc/reducer.hpp"

#include "app/services/audio.hpp"
#include "app/services/config.hpp"
#include "app/services/controller.hpp"
#include "app/services/graphics.hpp"
#include "app/services/logic_thread.hpp"
#include "app/services/runtime.hpp"

using namespace otto;

namespace otto::engines {
  namespace simple {
    struct State {
      util::StaticallyBounded<float, 11, 880> freq = 340;
    };

    struct Logic final : ILogic, itc::Producer<State> {
      Logic(itc::Context& c) : itc::Producer<State>(c) {}
    };

    struct Handler final : LogicDomain, InputReducer<State>, IInputLayer {
      using InputReducer::InputReducer;
      [[nodiscard]] KeySet key_mask() const noexcept override
      {
        return key_groups::enc_clicks;
      }
      void reduce(EncoderEvent e, State& state) noexcept final
      {
        state.freq += e.steps;
      }
    };

    struct Audio final : itc::Consumer<State>, AudioDomain {
      Audio(itc::Context& c) : Consumer(c) {}

      void on_state_change(const State& d) noexcept override
      {
        osc.freq(state().freq);
      }
      [[nodiscard]] util::audio_buffer process() const noexcept
      {
        auto buf = buffer_pool().allocate();
        std::ranges::generate(buf, osc);
        return buf;
      }
      gam::Sine<> osc;
    };

    struct Screen final : itc::Consumer<State>, ScreenBase {
      Screen(itc::Context& c) : Consumer(c) {}
      void draw(SkCanvas& ctx) noexcept override
      {
        SkPaint paint;
        paint.setAntiAlias(true);
        paint.setColor(SK_ColorWHITE);
        paint.setStyle(SkPaint::kFill_Style);
        ctx.drawCircle({160, 120}, state().freq.normalize() * 100.f, paint);
      }
    };
  } // namespace simple

  struct Simple {
    using State = simple::State;
    using Logic = simple::Logic;
    using Audio = simple::Audio;
    using Screen = simple::Screen;
    using Handler = simple::Handler;
  };

}; // namespace otto::engines

TEST_CASE ("simple_engine", "[.interactive]") {
  using namespace services;

  RuntimeController rt;
  auto confman = ConfigManager::make_default();
  LogicThread logic_thread;
  Controller controller(rt, confman);
  Graphics graphics(rt);

  Audio audio(confman);
  itc::Context ctx;
  engines::Simple::Logic l(ctx);
  engines::Simple::Audio a(ctx);
  engines::Simple::Screen s(ctx);
  engines::Simple::Handler h(ctx);

  auto stop_audio = audio.set_process_callback([&](Audio::CallbackData data) {
    const auto res = a.process();
    std::ranges::copy(util::zip(res, res), data.output.begin());
  });
  auto stop_graphics = graphics.show([&](SkCanvas& ctx) { s.draw(ctx); });
  auto stop_controller = controller.set_input_handler(h);

  rt.wait_for_stop();
}
