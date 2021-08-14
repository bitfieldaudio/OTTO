#include "testing.t.hpp"

#include "app/services/state.hpp"

#include "lib/util/unix_signals.hpp"
#include "lib/util/with_limits.hpp"

#include "lib/engine.hpp"
#include "lib/graphics.hpp"
#include "lib/itc/itc.hpp"
#include "lib/itc/reducer.hpp"
#include "lib/voices/voice_manager.hpp"

#include "app/engines/synths/ottofm/ottofm.hpp"
#include "app/layers/navigator.hpp"
#include "app/layers/piano_key_layer.hpp"
#include "app/services/audio.hpp"
#include "app/services/config.hpp"
#include "app/services/controller.hpp"
#include "app/services/graphics.hpp"
#include "app/services/led_manager.hpp"
#include "app/services/logic_thread.hpp"
#include "app/services/runtime.hpp"
#include "app/services/ui_manager.hpp"

#include "board/midi_driver.hpp"

using namespace otto;

TEST_CASE ("StateManager destruction", "[.interactive][system]") {
  using namespace services;
  RuntimeController rt;
  auto confman = ConfigManager::make_default();
  LogicThread logic_thread;
  Controller controller(rt, confman);
  Graphics graphics(rt);

  itc::Context ctx;
  auto eng = engines::ottofm::factory.make_without_audio(ctx);

  auto voices_logic = voices::make_voices_logic(ctx);
  auto voices_screen = voices::make_voices_screen(ctx);

  LayerStack layers;
  auto nav_km = layers.make_layer<NavKeyMap>(confman);
  nav_km.bind_nav_key(Key::synth, eng.main_screen);
  nav_km.bind_nav_key(Key::envelope, eng.mod_screen);
  nav_km.bind_nav_key(Key::voices, voices_screen);
  {
    StateManager stateman("data/state.json");
    // stateman.add("EngineChannel", std::ref(ctx));
    stateman.add("Navigation", std::ref(nav_km));

    LedManager ledman(controller.port_writer());
    auto stop_graphics = graphics.show([&](skia::Canvas& ctx) {
      ledman.process(layers);
      nav_km.nav().draw(ctx);
    });
    auto stop_controller = controller.set_input_handler(layers);

    stateman.read_from_file();
    rt.wait_for_stop();
    LOGI("Shutting down");
    stateman.write_to_file();
    // stateman.remove("Navigation");
  }
  LOGI("Done with state manager");
}
