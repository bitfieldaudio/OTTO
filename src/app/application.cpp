#include "application.hpp"

#include <argparse/argparse.hpp>

#include "lib/engines/synthdispatcher/synthdispatcher.hpp"
#include "lib/globals.hpp"
#include "lib/voices/voice_manager.hpp"

#include "app/engines/master/master.hpp"
#include "app/engines/midi-fx/arp/arp.hpp"
#include "app/engines/slots/slots.hpp"
#include "app/engines/synths/nuke/nuke.hpp"
#include "app/engines/synths/ottofm/ottofm.hpp"
#include "app/layers/navigator.hpp"
#include "app/layers/piano_key_layer.hpp"
#include "app/services/audio.hpp"
#include "app/services/config.hpp"
#include "app/services/controller.hpp"
#include "app/services/dev_console.hpp"
#include "app/services/graphics.hpp"
#include "app/services/led_manager.hpp"
#include "app/services/logic_thread.hpp"
#include "app/services/runtime.hpp"
#include "app/services/state.hpp"
#include "app/services/ui_manager.hpp"

#include "board/midi_driver.hpp"

#ifdef OTTO_BOARD_PARTS_CONTROLLER_EMULATOR
#include "board/emulator.hpp"
#endif

namespace otto {
  using namespace services;

  // NOLINTNEXTLINE
  int main(int argc, char* argv[])
  {
    argparse::ArgumentParser args("otto-core");

    args
      .add_argument("-l", "--log-level") //
      .help("Set log level. Options: trace, debug, info, warning, error, critical, off")
      .default_value(std::string("info"));

    args
      .add_argument("-d", "--data-dir") //
      .help("Set the data directory")
      .default_value(std::filesystem::path("./data"));

    args
      .add_argument("-r", "--resources-dir") //
      .help("Set the location of resource files")
      .default_value(std::filesystem::path("./resources"));

#ifdef OTTO_BOARD_PARTS_CONTROLLER_EMULATOR
    args
      .add_argument("-e", "--emulator") //
      .help("Show emulator")
      .default_value(false)
      .implicit_value(true);
#endif

    args
      .add_argument("--dev-console") //
      .help("Start with dev console")
      .default_value(false)
      .implicit_value(true);

    args
      .add_argument("-o", "--option") //
      .default_value<std::vector<std::string>>({})
      .append()
      .help("Set a config option. format: /option/path=json_value");

    args
      .add_argument("-c", "--config") //
      .help("Config file path");

    args
      .add_argument("--write-config") //
      .help("Write config file on exit. This will include options set in the file when read, default options, and "
            "options passed on the command line")
      .default_value(false)
      .implicit_value(true);

    try {
      args.parse_args(argc, argv);
    } catch (std::runtime_error& e) {
      std::cerr << e.what() << std::endl;
      std::cerr << args;
      return 1;
    }

    log::init();
    log::set_level(log::level::from_str(args.get<std::string>("--log-level")));

    auto data_dir = args.get<std::filesystem::path>("--data-dir");
    auto resources_dir = args.get<std::filesystem::path>("--resources-dir");
    globals::init::data_dir(data_dir);
    globals::init::resource_dir(resources_dir);

    std::unique_ptr<drivers::IGraphicsDriver> graphics_driver;
#ifdef OTTO_BOARD_PARTS_CONTROLLER_EMULATOR
    if (args.get<bool>("--emulator")) {
      graphics_driver = std::make_unique<board::Emulator>();
    } else
#endif
    {
      graphics_driver = drivers::IGraphicsDriver::make_default();
    }

    // Services
    RuntimeController rt;
    auto confman = [&] {
      if (auto conf = args.present("--config")) {
        return ConfigManager(std::filesystem::path(*conf));
      }
      return ConfigManager::make_default();
    }();
    for (const auto& opt : args.get<std::vector<std::string>>("--option")) {
      auto [path, val] = util::split_string(opt, '=');
      confman.set_option(json::pointer(std::string(path)), json::value::parse(val));
    }

    LogicThread logic_thread;
    Controller controller(rt, confman);
    Graphics graphics(rt, std::move(graphics_driver));
    Audio audio(drivers::IAudioDriver::make_default(confman));
    StateManager stateman(data_dir / "state.json");
    tl::optional<DevConsole> dev_console;
    if (args.get<bool>("--dev-console")) {
      dev_console.emplace(rt);
    }

    // Key/LED Layers
    LayerStack layers;
    auto piano = layers.make_layer<PianoKeyLayer>(audio.midi());
    auto nav_km = layers.make_layer<NavKeyMap>(confman);
    stateman.add("navigation", std::ref(nav_km));

    // Context
    itc::Context ctx;
    itc::PersistanceProvider persistance(ctx);
    stateman.add("context", std::ref(persistance));

    // Sound slots
    auto sound_slots = engines::slots::SoundSlots::make(ctx);
    nav_km.bind_nav_key(Key::slots, sound_slots.overlay_screen);

    // Synth Dispatcher
    auto synth = otto::make_synthdispatcher(sound_slots.logic->managed_ctx());
    synth.logic->register_engine(std::move(engines::ottofm::factory));
    synth.logic->register_engine(std::move(engines::nuke::factory));

    nav_km.bind_nav_key(Key::synth, synth.main_screen);
    nav_km.bind_nav_key(Key::envelope, synth.mod_screen);
    nav_km.bind_nav_key(Key::voices, synth.voices_screen);

    nav_km.bind_nav_key(Key::synth, synth.selector_screen, true);

    // ARP
    auto midifx_eng = engines::arp::factory.make_all(sound_slots.logic->managed_ctx());
    midifx_eng.audio->set_target(&synth.audio->midi_handler());
    nav_km.bind_nav_key(Key::arp, midifx_eng.screen);

    // Master
    auto master = engines::master::Master::make(ctx["master"], audio.driver().mixer());
    nav_km.bind_nav_key(Key::master, master.screen);

    // Drivers
    RtMidiDriver rt_midi_driver(audio.midi());
    LedManager ledman(controller.port_writer());

    // Start services
    auto stop_midi = audio.set_midi_handler(&*midifx_eng.audio);
    auto stop_audio = audio.set_process_callback([&](Audio::CallbackData data) {
      midifx_eng.audio->process();
      const auto res = synth.audio->process();
      stdr::copy(util::zip(res, res), data.output.begin());
    });
    auto stop_input = controller.set_input_handler(layers);

    auto stop_graphics = graphics.show([&](skia::Canvas& ctx) {
      ledman.process(layers);
      ctx.save();
      nav_km.nav().draw(ctx);
      ctx.restore();
    });

    stateman.read_from_file();

    // Run
    LOGI("Init done!");
    rt.wait_for_stop();
    LOGI("Shutting down");

    stateman.write_to_file();


    if (args.get<bool>("--write-config")) {
      confman.write_to_file();
    }
    return 0;
  }

} // namespace otto
