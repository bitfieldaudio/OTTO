#include "testing.t.hpp"

#include "app/engines/synths/ottofm/ottofm.hpp"

#include "lib/engine.hpp"
#include "lib/itc/itc.hpp"
#include "lib/itc/reducer.hpp"
#include "lib/util/with_limits.hpp"

#include "lib/graphics.hpp"

#include "app/services/audio.hpp"
#include "app/services/config.hpp"
#include "app/services/controller.hpp"
#include "app/services/graphics.hpp"
#include "app/services/logic_thread.hpp"
#include "app/services/runtime.hpp"

using namespace otto;

TEST_CASE ("ottofm", "[.interactive][engine]") {
  using namespace services;
  auto app = start_app(core::make_handle<ConfigManager>(), //
                       LogicThread::make(),                //
                       Controller::make(),                 //
                       // Audio::make(),                      //
                       Graphics::make() //
  );

  itc::ChannelGroup chan;
  auto eng = engines::ottofm::make(chan);

  // app.service<Audio>().set_midi_handler(&eng.audio->midi_handler());
  // app.service<Audio>().set_process_callback([&](Audio::CallbackData data) {
  //  const auto res = eng.audio->process();
  //  std::ranges::copy(util::zip(res, res), data.output.begin());
  //});
  app.service<Graphics>().show([&](SkCanvas& ctx) { eng.main_screen.screen->draw(ctx); });
  app.service<Controller>().set_input_handler(*eng.main_screen.handler);

  app.wait_for_stop();
}
