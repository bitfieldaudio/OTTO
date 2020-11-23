#include "lib/engine.hpp"
#include "lib/itc/reducer.hpp"
#include "testing.t.hpp"

#include "lib/itc/itc.hpp"

#include <Gamma/Oscillator.h>

#include "app/services/audio.hpp"
#include "app/services/config.hpp"
#include "app/services/controller.hpp"
#include "app/services/graphics.hpp"
#include "app/services/logic_thread.hpp"
#include "app/services/runtime.hpp"

#include "system/simple_engine.gen.hpp"

using namespace otto;

namespace otto::engines {
  struct IDrawable {
    virtual void draw(SkCanvas& ctx) noexcept = 0;
  };

  struct IScreen : IDrawable {};

  namespace simple {

    struct Logic final : itc::Producer<State> {
      Logic(itc::Channel<State>& c) : itc::Producer<State>(c) {}
    };

    struct Handler final : InputReducer<State> {
      void reduce(EncoderEvent e, itc::Updater<State> updater) noexcept final
      {
        updater.freq() += e.steps;
      }
    };

    struct Audio final : itc::Consumer<State>, core::ServiceAccessor<services::Audio> {
      Audio(itc::Channel<State>& c) : itc::Consumer<State>(c, service<services::Audio>().executor()) {}

      void on_state_change(itc::Diff<State> d) noexcept override
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
                       LogicThread::make(),                //
                       Controller::make(),                 //
                       Audio::make(),                      //
                       Graphics::make()                    //
  );

  itc::Channel<otto::engines::Simple::State> chan;
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
