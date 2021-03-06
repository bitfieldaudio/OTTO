#include <csignal>

#include "lib/util/unix_signals.hpp"
#include "lib/util/with_limits.hpp"

#include "lib/engine.hpp"
#include "lib/graphics.hpp"
#include "lib/itc/itc.hpp"
#include "lib/itc/reducer.hpp"
#include "lib/voices/voice_manager.hpp"

#include "app/application.hpp"
#include "app/engines/midi-fx/arp/arp.hpp"
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
#include "app/services/state.hpp"
#include "app/services/ui_manager.hpp"

#include "board/midi_driver.hpp"

using namespace otto;

int main(int argc, char* argv[])
{
  using namespace services;
  RuntimeController rt;
  auto confman = ConfigManager::make_default();
  LogicThread logic_thread;
  Controller controller(rt, confman);
  Graphics graphics(rt);

  Audio audio;
  StateManager stateman("data/state.json");

  itc::ChannelGroup chan;
  auto eng = engines::ottofm::factory.make_all(chan);
  stateman.add("EngineChannel", std::ref(chan));

  auto voices_logic = voices::make_voices_logic(chan);
  auto voices_screen = voices::make_voices_screen(chan);

<<<<<<< Updated upstream
=======
  auto midifx_eng = engines::arp::factory.make_all(chan);

  app.service<Audio>().set_midi_handler(&eng.audio->midi_handler());
  app.service<Audio>().set_process_callback([&](Audio::CallbackData data) {
    const auto res = eng.audio->process();
    std::copy(util::zip(res, res), data.output.begin());
  });

>>>>>>> Stashed changes
  LayerStack layers;
  auto piano = layers.make_layer<PianoKeyLayer>(audio.midi());
  auto nav_km = layers.make_layer<NavKeyMap>(confman);
  nav_km.bind_nav_key(Key::synth, eng.main_screen);
  nav_km.bind_nav_key(Key::envelope, eng.mod_screen);
  nav_km.bind_nav_key(Key::voices, voices_screen);
<<<<<<< Updated upstream
  // nav_km.bind_nav_key(Key::arp, midifx_eng.screen);
  stateman.add("Navigation", std::ref(nav_km));

  RtMidiDriver rt_midi_driver(audio.midi());
=======
  nav_km.bind_nav_key(Key::arp, midifx_eng.screen);
>>>>>>> Stashed changes

  LedManager ledman(controller.port_writer());

  auto stop_midi = audio.set_midi_handler(&eng.audio->midi_handler());
  auto stop_audio = audio.set_process_callback([&](Audio::CallbackData data) {
    const auto res = eng.audio->process();
    stdr::copy(util::zip(res, res), data.output.begin());
  });
  auto stop_input = controller.set_input_handler(layers);
  auto stop_graphics = graphics.show([&](skia::Canvas& ctx) {
    ledman.process(layers);
    nav_km.nav().draw(ctx);
  });

  stateman.read_from_file();
  rt.wait_for_stop();
  LOGI("Shutting down");
  stateman.write_to_file();
  return 0;
}
