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

    struct Logic final : itc::Producer<State> {
      Logic(itc::TypedChannel<State>& c) : itc::Producer<State>(c) {}
    };

    struct Handler final : InputReducer<State>, IInputLayer {
      [[nodiscard]] KeySet key_mask() const noexcept override
      {
        return key_groups::enc_clicks;
      }
      void reduce(EncoderEvent e, State& state) noexcept final
      {
        state.freq += e.steps;
      }
    };

    struct Audio final : itc::Consumer<State>, core::ServiceAccessor<services::Audio>, AudioDomain {
      Audio(itc::TypedChannel<State>& c) : Consumer(c) {}

      void on_state_change(const State& d) noexcept override
      {
        osc.freq(state().freq);
      }
      util::audio_buffer process() noexcept
      {
        auto buf = service<services::Audio>().buffer_pool().allocate();
        std::ranges::generate(buf, osc);
        return buf;
      }
      gam::Sine<> osc;
    };

    struct Screen final : itc::Consumer<State>, core::ServiceAccessor<services::Graphics>, ScreenBase {
      Screen(itc::TypedChannel<State>& c) : Consumer(c) {}
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
  auto app = start_app(core::make_handle<ConfigManager>(), //
                       LogicThread::make(),                //
                       Controller::make(),                 //
                       Audio::make(),                      //
                       Graphics::make()                    //
  );

  itc::TypedChannel<otto::engines::Simple::State> chan;
  engines::Simple::Logic l(chan);
  engines::Simple::Audio a(chan);
  engines::Simple::Screen s(chan);
  engines::Simple::Handler h;
  itc::set_producer(h, l);

  app.service<Audio>().set_process_callback([&](Audio::CallbackData data) {
    const auto res = a.process();
    std::ranges::copy(util::zip(res, res), data.output.begin());
  });
  app.service<Graphics>().show([&](SkCanvas& ctx) { s.draw(ctx); });
  app.service<Controller>().set_input_handler(h);

  app.wait_for_stop();
}
