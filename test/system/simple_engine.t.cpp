#include "testing.t.hpp"

#include "lib/itc/itc.hpp"
#include "lib/util/with_limits.hpp"

#include <Gamma/Oscillator.h>

#include "app/services/audio.hpp"
#include "app/services/config.hpp"
#include "app/services/controller.hpp"
#include "app/services/graphics.hpp"
#include "app/services/impl/runtime.hpp"
#include "app/services/logic_thread.hpp"

using namespace otto;

namespace otto::engines {
  struct IDrawable {
    virtual void draw(SkCanvas& ctx) noexcept = 0;
  };

  struct IScreen : IDrawable {};

  namespace simple {
    struct State {
      util::StaticallyBounded<float, 11, 880> freq = 340;
    };

    struct Logic final : itc::Producer<State> {
      Logic(itc::Channel<State>& c) : itc::Producer<State>(c) {}
    };

    struct Handler final : InputHandler {
      Handler(Logic& l) : logic(l) {}
      Logic& logic;

      void handle(const EncoderEvent& e) noexcept final
      {
        logic.produce(itc::increment(&State::freq, e.steps));
      }
    };

    struct Audio final : itc::Consumer<State>, core::ServiceAccessor<services::Audio> {
      Audio(itc::Channel<State>& c) : itc::Consumer<State>(c, service<services::Audio>().executor()) {}

      void on_state_change(const State& s) noexcept override
      {
        osc.freq(s.freq);
      }
      util::audio_buffer process() noexcept
      {
        auto buf = service<services::Audio>().buffer_pool().allocate();
        std::ranges::generate(buf, osc);
        return buf;
      }
      gam::Sine<> osc;
    };

    struct Screen final : itc::Consumer<State>, core::ServiceAccessor<services::Graphics>, otto::engines::IScreen {
      Screen(itc::Channel<State>& c) : itc::Consumer<State>(c, service<services::Graphics>().executor()) {}
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

TEST_CASE (test::interactive() * "simple_engine") {
  using namespace services;
  auto app = start_app(core::make_handle<ConfigManager>(), //
                       LogicThread::make_default(),        //
                       Controller::make_board(),           //
                       Audio::make_board(),                //
                       Graphics::make_board()              //
  );

  itc::Channel<otto::engines::Simple::State> chan;
  engines::Simple::Logic l(chan);
  engines::Simple::Audio a(chan);
  engines::Simple::Screen s(chan);
  engines::Simple::Handler h(l);

  app.service<Audio>().set_process_callback([&](auto& data) {
    const auto res = a.process();
    std::ranges::copy(util::zip(res, res), data.output.begin());
  });
  app.service<Graphics>().show([&](SkCanvas& ctx) { s.draw(ctx); });
  app.service<Controller>().set_input_handler(h);

  app.wait_for_stop();
}
