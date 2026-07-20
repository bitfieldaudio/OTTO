#include "application.hpp"

#include <fcntl.h>
#include <memory>
#include <sys/file.h>
#include <unistd.h>

#include <argparse/argparse.hpp>
#include "lib/engines/synthdispatcher/synthdispatcher.hpp"
#include "lib/globals.hpp"
#include "lib/voices/voice_manager.hpp"

#include "app/engines/desktop/desktop_kit.hpp"
#include "app/engines/master/master.hpp"
#include "app/engines/midi-fx/arp/arp.hpp"
#include "app/engines/slots/slots.hpp"
#include "app/engines/stubs/stubs.hpp"
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

#if defined(__APPLE__)
    // Single-instance guard — leftover otto processes previously crashed CoreAudio.
    static int instance_lock_fd = -1;
    instance_lock_fd = ::open("/tmp/otto-desktop.lock", O_CREAT | O_RDWR, 0644);
    if (instance_lock_fd >= 0) {
      if (::flock(instance_lock_fd, LOCK_EX | LOCK_NB) != 0) {
        LOGE("Another OTTO instance is already running (lock /tmp/otto-desktop.lock).");
        LOGE("Quit it or: pkill -f 'bin/otto'");
        return 1;
      }
    }
#endif

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
#if defined(__APPLE__)
    // Persist AudioDriver / MidiDriver choices across runs.
    confman.ensure_file_path("./ottoconf.json");
#endif
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

    // Transport: play/record toggle globally (layer after nav so it wins those keys);
    // sigma opens the status screen.
    auto transport_model = std::make_shared<engines::stubs::TransportModel>();
    engines::stubs::TransportLayer transport_layer{transport_model};
    layers.add_layer(transport_layer);
    static auto transport_screen = engines::stubs::make_transport_screen(transport_model);
    nav_km.bind_nav_key(Key::sigma, transport_screen);

    // Desktop kit: sequencer, delay, saturator, mixer, presets
    auto delay_fx = std::make_shared<engines::desktop::DelayFx>();
    auto sat_fx = std::make_shared<engines::desktop::SaturatorFx>();
    auto mix_gain = std::make_shared<engines::desktop::MixerGain>();
    auto step_seq = std::make_shared<engines::desktop::StepSequencer>();
    step_seq->transport = transport_model;
    step_seq->target = midifx_eng.audio.get();
    delay_fx->set_sample_rate(static_cast<unsigned>(audio.driver().sample_rate()));
    step_seq->set_timing(static_cast<unsigned>(audio.driver().sample_rate()),
                         static_cast<unsigned>(audio.driver().buffer_size()));

    static auto seq_screen = engines::desktop::make_seq_screen(step_seq);
    static auto delay_screen = engines::desktop::make_delay_screen(delay_fx);
    static auto sat_screen = engines::desktop::make_saturator_screen(sat_fx);
    static auto mixer_screen = engines::desktop::make_mixer_screen(mix_gain);
    static auto preset_screen = engines::desktop::make_preset_screen(
      engines::desktop::list_fm_presets(data_dir), [&](const std::filesystem::path& path) {
        // FM is registered first → index 0
        synth.logic->select_engine(0);
        auto state = engines::desktop::load_ottofm_preset_file(path);
        if (synth.logic->current().logic) {
          engines::ottofm::apply_state(*synth.logic->current().logic, state);
        }
      });

    nav_km.bind_nav_key(Key::sequencer, seq_screen);
    nav_km.bind_nav_key(Key::fx1, delay_screen);
    nav_km.bind_nav_key(Key::fx2, sat_screen);
    nav_km.bind_nav_key(Key::mixer, mixer_screen);
    nav_km.bind_nav_key(Key::settings, preset_screen);

    // Remaining placeholders (skips keys already bound above)
    engines::stubs::bind_missing_nav_keys(nav_km);

    // Drivers
    RtMidiDriver rt_midi_driver(audio.midi(), confman.make_conf<MidiDriverConfig>());
    LedManager ledman(controller.port_writer());

    // Scope: stop audio/midi/input/graphics before engine teardown / state write.
    {
      auto stop_midi = audio.set_midi_handler(&*midifx_eng.audio);
      auto stop_audio = audio.set_process_callback([&](Audio::CallbackData data) {
        midifx_eng.audio->process();
        const auto res = synth.audio->process();
        stdr::copy(util::zip(res, res), data.output.begin());
        delay_fx->set_sample_rate(static_cast<unsigned>(audio.driver().sample_rate()));
        delay_fx->process(data.output);
        sat_fx->process(data.output);
        mix_gain->process(data.output);
        // Sequencer after synth: MIDI inject before process() races voices.
        step_seq->set_timing(static_cast<unsigned>(audio.driver().sample_rate()),
                             static_cast<unsigned>(audio.driver().buffer_size()));
        step_seq->process();
      });
      auto stop_input = controller.set_input_handler(layers);

      auto stop_graphics = graphics.show([&](skia::Canvas& ctx) {
        ledman.process(layers);
        ctx.save();
        nav_km.nav().draw(ctx);
        ctx.restore();
      });

      stateman.read_from_file();

      // Playable default: land on the synth screen if nothing was restored.
      if (nav_km.nav().current_screen().screen == nullptr) {
        nav_km.nav().navigate_to(synth.main_screen);
      }
      LOGI("Tip: Hold Option (⌥) and tap Z–M / Q–P to play notes. ⌘Q to quit.");

      // Seed ottoconf.json so audio/midi choices are remembered even if quit is forced.
      if (confman.has_file_path()) {
        confman.write_to_file();
      }

      // Run
      LOGI("Init done!");
#if defined(__APPLE__)
      // GLFW/AppKit require window creation and event polling on the main thread.
      // (Polling every frame; no glfwPostEmptyEvent — calling it from GCD was racy.)
      graphics.run_until_stop();
#else
      rt.wait_for_stop();
#endif
      LOGI("Shutting down");
    }

    stateman.write_to_file();

    // Persist config (including any defaults materialized by make_conf) when a path is known,
    // or when --write-config was passed.
    if (args.get<bool>("--write-config") || confman.has_file_path()) {
      confman.write_to_file();
    }
    return 0;
  }

} // namespace otto
