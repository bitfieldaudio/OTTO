#include "application.hpp"

#include "lib/voices/voice_manager.hpp"

#include "app/engines/master/master.hpp"
#include "app/engines/slots/slots.hpp"
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

namespace otto {
  using namespace services;

  // NOLINTNEXTLINE
  int main(int argc, char* argv[])
  {
    RuntimeController rt;
    auto confman = ConfigManager::make_default();
    LogicThread logic_thread;
    Controller controller(rt, confman);
    Graphics graphics(rt);

    Audio audio;
    StateManager stateman("data/state.json");

    LayerStack layers;
    auto piano = layers.make_layer<PianoKeyLayer>(audio.midi());
    auto nav_km = layers.make_layer<NavKeyMap>(confman);
    stateman.add("Navigation", std::ref(nav_km));

    itc::Context ctx;
    auto eng = engines::ottofm::factory.make_all(ctx);
    nav_km.bind_nav_key(Key::synth, eng.main_screen);
    nav_km.bind_nav_key(Key::envelope, eng.mod_screen);
    stateman.add("Engine", std::ref(ctx));

    auto voices_logic = voices::make_voices_logic(ctx);
    auto voices_screen = voices::make_voices_screen(ctx);
    nav_km.bind_nav_key(Key::voices, voices_screen);

    auto master = engines::master::Master::make(ctx, audio.driver().mixer());
    nav_km.bind_nav_key(Key::master, master.screen);

    // Sound slots
    auto sound_slots = engines::slots::SoundSlots::make(ctx);
    nav_km.bind_nav_key(Key::slots, sound_slots.overlay_screen);

    RtMidiDriver rt_midi_driver(audio.midi());

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

} // namespace otto
