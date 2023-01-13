#include "testing.t.hpp"

#include "app/engines/synths/ottofm/ottofm.hpp"

#include "lib/util/with_limits.hpp"

#include "lib/engine.hpp"
#include "lib/graphics.hpp"
#include "lib/itc/itc.hpp"
#include "lib/itc/reducer.hpp"

#include "app/layers/navigator.hpp"
#include "app/layers/piano_key_layer.hpp"
#include "app/services/audio.hpp"
#include "app/services/config.hpp"
#include "app/services/controller.hpp"
#include "app/services/graphics.hpp"
#include "app/services/logic_thread.hpp"
#include "app/services/ui_manager.hpp"

using namespace otto;

TEST_CASE ("ottofm", "[.interactive][engine]") {
  using namespace services;
  RuntimeController rt;
  auto confman = ConfigManager::make_default();
  LogicThread logic_thread;
  Controller controller(rt, confman);
  Graphics graphics(rt);

  itc::Context ctx;
  auto eng = engines::ottofm::factory.make_without_audio(ctx);

  // app.service<Audio>().set_midi_handler(&eng.audio->midi_handler());
  // app.service<Audio>().set_process_callback([&](Audio::CallbackData data) {
  //   const auto res = eng.audio->process();
  //   std::ranges::copy(util::zip(res, res), data.output.begin());
  // });
  auto stop_graphics = graphics.show([&](SkCanvas& ctx) { eng.main_screen.screen->draw(ctx); });
  auto stop_controller = controller.set_input_handler(*eng.main_screen.input);
  rt.wait_for_stop();
}

TEST_CASE ("ottofm-env", "[.interactive][engine]") {
  using namespace services;
  RuntimeController rt;
  auto confman = ConfigManager::make_default();
  LogicThread logic_thread;
  Controller controller(rt, confman);
  Graphics graphics(rt);

  itc::Context ctx;
  auto eng = engines::ottofm::factory.make_without_audio(ctx);

  // app.service<Audio>().set_midi_handler(&eng.audio->midi_handler());
  // app.service<Audio>().set_process_callback([&](Audio::CallbackData data) {
  //  const auto res = eng.audio->process();
  //  std::ranges::copy(util::zip(res, res), data.output.begin());
  // });
  auto stop_graphics = graphics.show([&](SkCanvas& ctx) { eng.mod_screen.screen->draw(ctx); });
  auto stop_controller = controller.set_input_handler(*eng.mod_screen.input);

  rt.wait_for_stop();
}

TEST_CASE ("ottofm-all", "[.interactive][engine]") {
  using namespace services;
  RuntimeController rt;
  auto confman = ConfigManager::make_default();
  LogicThread logic_thread;
  Controller controller(rt, confman);
  Graphics graphics(rt);

  Audio audio(confman);
  itc::Context ctx;
  auto eng = engines::ottofm::factory.make_all(ctx);

  LayerStack layers;
  auto piano = layers.make_layer<PianoKeyLayer>(audio.midi());
  auto nav_km = layers.make_layer<NavKeyMap>(confman);
  nav_km.bind_nav_key(Key::synth, eng.main_screen);
  nav_km.bind_nav_key(Key::envelope, eng.mod_screen);

  auto stop_midi = audio.set_midi_handler(&eng.audio->midi_handler());
  auto stop_audio = audio.set_process_callback([&](Audio::CallbackData data) {
    const auto res = eng.audio->process();
    std::ranges::copy(util::zip(res, res), data.output.begin());
  });

  auto stop_graphics = graphics.show(nav_km.nav());
  auto stop_controller = controller.set_input_handler(layers);

  rt.wait_for_stop();
}

TEST_CASE ("ottofm-no-audio", "[.interactive][engine]") {
  using namespace services;
  RuntimeController rt;
  auto confman = ConfigManager::make_default();
  LogicThread logic_thread;
  Controller controller(rt, confman);
  Graphics graphics(rt);

  itc::Context ctx;
  auto eng = engines::ottofm::factory.make_without_audio(ctx);

  // app.service<Audio>().set_midi_handler(&eng.audio->midi_handler());
  // app.service<Audio>().set_process_callback([&](Audio::CallbackData data) {
  //   const auto res = eng.audio->process();
  //   std::ranges::copy(util::zip(res, res), data.output.begin());
  // });

  LayerStack layers;
  // auto piano = layers.make_layer<PianoKeyLayer>(app.service<Audio>().midi());
  auto nav_km = layers.make_layer<NavKeyMap>(confman);
  nav_km.bind_nav_key(Key::synth, eng.main_screen);
  nav_km.bind_nav_key(Key::envelope, eng.mod_screen);

  auto stop_graphics = graphics.show(nav_km.nav());
  auto stop_controller = controller.set_input_handler(layers);

  rt.wait_for_stop();
}
