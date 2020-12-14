#include "app/input/navigator.hpp"
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
#include "app/services/ui_manager.hpp"

#include "app/input/distributor.hpp"
#include "app/input/seq_to_midi.hpp"

using namespace otto;

TEST_CASE ("ottofm", "[.interactive][engine]") {
  using namespace services;
  auto app = start_app(ConfigManager::make_default(), //
                       LogicThread::make(),           //
                       Controller::make(),            //
                       Graphics::make());

  itc::ChannelGroup chan;
  auto eng = engines::ottofm::factory.make_without_audio(chan);

  // app.service<Audio>().set_midi_handler(&eng.audio->midi_handler());
  // app.service<Audio>().set_process_callback([&](Audio::CallbackData data) {
  //   const auto res = eng.audio->process();
  //   std::ranges::copy(util::zip(res, res), data.output.begin());
  // });
  app.service<Graphics>().show([&](SkCanvas& ctx) { eng.main_screen.screen->draw(ctx); });
  app.service<Controller>().set_input_handler(*eng.main_screen.handler);

  app.wait_for_stop();
}

TEST_CASE ("ottofm-env", "[.interactive][engine]") {
  using namespace services;
  auto app = start_app(ConfigManager::make_default(), //
                       LogicThread::make(),           //
                       Controller::make(),            //
                       Graphics::make()               //
  );

  itc::ChannelGroup chan;
  auto eng = engines::ottofm::factory.make_without_audio(chan);

  // app.service<Audio>().set_midi_handler(&eng.audio->midi_handler());
  // app.service<Audio>().set_process_callback([&](Audio::CallbackData data) {
  //  const auto res = eng.audio->process();
  //  std::ranges::copy(util::zip(res, res), data.output.begin());
  // });
  app.service<Graphics>().show([&](SkCanvas& ctx) { eng.mod_screen.screen->draw(ctx); });
  app.service<Controller>().set_input_handler(*eng.mod_screen.handler);

  app.wait_for_stop();
}

TEST_CASE ("ottofm-all", "[.interactive][engine]") {
  using namespace services;
  auto app = start_app(ConfigManager::make_default(), //
                       LogicThread::make(),           //
                       Controller::make(),            //
                       Audio::make(),                 //
                       Graphics::make()               //
  );

  itc::ChannelGroup chan;
  auto eng = engines::ottofm::factory.make_all(chan);

  app.service<Audio>().set_midi_handler(&eng.audio->midi_handler());
  app.service<Audio>().set_process_callback([&](Audio::CallbackData data) {
    const auto res = eng.audio->process();
    std::ranges::copy(util::zip(res, res), data.output.begin());
  });

  EventDistributor handlers;
  handlers.add_handler(std::make_unique<KeyboardKeysHandler>());
  auto& nav_km = handlers.add_handler(std::make_unique<NavKeyMap>(std::make_unique<Navigator>()));
  nav_km.bind_nav_key(Key::synth, eng.main_screen);
  nav_km.bind_nav_key(Key::envelope, eng.mod_screen);

  app.service<Graphics>().show(nav_km.nav());
  app.service<Controller>().set_input_handler(handlers);

  app.wait_for_stop();
}

TEST_CASE ("ottofm-no-audio", "[.interactive][engine]") {
  using namespace services;
  auto app = start_app(ConfigManager::make_default(), //
                       LogicThread::make(),           //
                       Controller::make(),            //
                       Graphics::make()               //
  );

  itc::ChannelGroup chan;
  auto eng = engines::ottofm::factory.make_without_audio(chan);

  // app.service<Audio>().set_midi_handler(&eng.audio->midi_handler());
  // app.service<Audio>().set_process_callback([&](Audio::CallbackData data) {
  //  const auto res = eng.audio->process();
  //  std::ranges::copy(util::zip(res, res), data.output.begin());
  //});

  EventDistributor handlers;
  // handlers.add_handler(std::make_unique<KeyboardKeysHandler>());
  auto& nav_km = handlers.add_handler(std::make_unique<NavKeyMap>(std::make_unique<Navigator>()));
  nav_km.bind_nav_key(Key::synth, eng.main_screen);
  nav_km.bind_nav_key(Key::envelope, eng.mod_screen);

  app.service<Graphics>().show(nav_km.nav());
  app.service<Controller>().set_input_handler(handlers);

  app.wait_for_stop();
}
