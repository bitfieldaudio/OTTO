#include "application.hpp"

#include "lib/voices/voice_manager.hpp"

#include "app/engines/master/master.hpp"
#include "app/engines/midi-fx/arp/arp.hpp"
#include "app/engines/slots/slots.hpp"
#include "app/engines/synths/nuke/nuke.hpp"
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
    // Services
    RuntimeController rt;
    auto confman = ConfigManager::make_default();
    LogicThread logic_thread;
    Controller controller(rt, confman);
    Graphics graphics(rt);
    Audio audio;
    StateManager stateman("data/state.json");

    // Key/LED Layers
    LayerStack layers;
    auto piano = layers.make_layer<PianoKeyLayer>(audio.midi());
    auto nav_km = layers.make_layer<NavKeyMap>(confman);
    stateman.add("Navigation", std::ref(nav_km));

    // Context
    itc::Context ctx;
    stateman.add("Context", std::ref(ctx));

    // OTTOFM
    auto eng = engines::nuke::factory.make_all(ctx["synth"]);
    auto voices_logic = voices::make_voices_logic(ctx["synth"]);
    auto voices_screen = voices::make_voices_screen(ctx["synth"]);
    nav_km.bind_nav_key(Key::synth, eng.main_screen);
    nav_km.bind_nav_key(Key::envelope, eng.mod_screen);
    nav_km.bind_nav_key(Key::voices, voices_screen);

    // ARP
    auto midifx_eng = engines::arp::factory.make_all(ctx["midifx"]);
    midifx_eng.audio->set_target(&eng.audio->midi_handler());
    nav_km.bind_nav_key(Key::arp, midifx_eng.screen);

    // Master
    auto master = engines::master::Master::make(ctx["master"], audio.driver().mixer());
    nav_km.bind_nav_key(Key::master, master.screen);

    // Sound slots
    itc::Context soundslots_ctx;
    auto sound_slots = engines::slots::SoundSlots::make(soundslots_ctx);
    sound_slots.logic->set_managed(std::ref(ctx));
    nav_km.bind_nav_key(Key::slots, sound_slots.overlay_screen);
    stateman.add("Sound Slots", std::ref(soundslots_ctx));

    // Drivers
    RtMidiDriver rt_midi_driver(audio.midi());
    LedManager ledman(controller.port_writer());

    // Start services
    auto stop_midi = audio.set_midi_handler(&*midifx_eng.audio);
    auto stop_audio = audio.set_process_callback([&](Audio::CallbackData data) {
      midifx_eng.audio->process();
      const auto res = eng.audio->process();
      stdr::copy(util::zip(res, res), data.output.begin());
    });
    auto stop_input = controller.set_input_handler(layers);
    auto stop_graphics = graphics.show([&](skia::Canvas& ctx) {
      ledman.process(layers);
      nav_km.nav().draw(ctx);
    });

    stateman.read_from_file();

    // Run
    rt.wait_for_stop();
    LOGI("Shutting down");

    stateman.write_to_file();
    return 0;
  }

} // namespace otto
