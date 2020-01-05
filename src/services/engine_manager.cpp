#include "engine_manager.hpp"

#include "core/engine/engine_dispatcher.hpp"
#include "core/engine/engine_dispatcher.inl"
#include "core/ui/screen.hpp"
#include "core/ui/vector_graphics.hpp"
#include "engines/arps/ARP/arp.hpp"
#include "engines/fx/chorus/chorus.hpp"
#include "engines/fx/wormhole/wormhole.hpp"
#include "engines/misc/external/external_in.hpp"
#include "engines/misc/looper/screen.hpp"
#include "engines/misc/master/master.hpp"
#include "engines/misc/mixer/screen.hpp"
#include "engines/misc/sampler/screen.hpp"
#include "engines/misc/saveslots/screen.hpp"
#include "engines/misc/sends/sends.hpp"
#include "engines/misc/sequencer/screen.hpp"
#include "engines/synths/OTTOFM/ottofm.hpp"
#include "engines/synths/goss/goss.hpp"
#include "engines/twists/twist1/screen.hpp"
#include "engines/twists/twist2/screen.hpp"
#include "services/application.hpp"
#include "services/clock_manager.hpp"

namespace otto::services {

  using namespace core;
  using namespace core::engine;

  struct DefaultEngineManager final : EngineManager {
    DefaultEngineManager();

    void start() override;
    audio::ProcessData<2> process(audio::ProcessData<2> external_in) override;

  private:
    using EffectsDispatcher = EngineDispatcher< //
      EngineType::effect,
      engine::OffEngine<EngineType::effect>,
      engines::wormhole::Wormhole,
      engines::chorus::Chorus>;
    using ArpDispatcher = EngineDispatcher< //
      EngineType::arpeggiator,
      engine::OffEngine<EngineType::arpeggiator>,
      engines::arp::Arp>;
    using SynthDispatcher = EngineDispatcher< //
      EngineType::synth,
      engines::ottofm::OttofmEngine,
      engines::goss::GossEngine>;

    engines::external::External line_in;
    SynthDispatcher synth;
    EffectsDispatcher effect1;
    EffectsDispatcher effect2;
    ArpDispatcher arpeggiator;


    // Placeholder screens for future features
    engines::twist1::Screen twist1screen;
    engines::twist2::Screen twist2screen;
    engines::looper::Screen looperscreen;
    engines::sampler::Screen samplerscreen;
    engines::sequencer::Screen sequencerscreen;
    engines::mixer::Screen mixerscreen;
    engines::saveslots::Screen savescreen;

    engines::sends::Sends synth_send;
    engines::sends::Sends line_in_send_stereo;
    engines::sends::Sends line_in_send_left;
    engines::sends::Sends line_in_send_right;

    engines::master::Master master;
    // engines::Sequencer sequencer;
  };

  std::unique_ptr<EngineManager> EngineManager::create_default()
  {
    return std::make_unique<DefaultEngineManager>();
  }

  DefaultEngineManager::DefaultEngineManager()
  {
    auto& ui_manager = *Application::current().ui_manager;
    auto& state_manager = *Application::current().state_manager;
    auto& controller = *Application::current().controller;

    auto reg_ss = [&](auto se, auto&& f) { return ui_manager.register_screen_selector(se, f); };

    reg_ss(ScreenEnum::routing, [&]() { return (ui::ScreenAndInput){mixerscreen, mixerscreen.input}; });
    reg_ss(ScreenEnum::saveslots, [&]() { return (ui::ScreenAndInput){savescreen, savescreen.input}; });
    reg_ss(ScreenEnum::sends, [&]() { return synth_send.screen(); });
    reg_ss(ScreenEnum::fx1, [&]() { return effect1.engine_screen(); });
    reg_ss(ScreenEnum::fx1_selector, [&]() { return effect1.selector_screen(); });
    reg_ss(ScreenEnum::fx2, [&]() { return effect2.engine_screen(); });
    reg_ss(ScreenEnum::fx2_selector, [&]() { return effect2.selector_screen(); });
    reg_ss(ScreenEnum::looper, [&]() { return (ui::ScreenAndInput){looperscreen, looperscreen.input}; });
    reg_ss(ScreenEnum::arp, [&]() { return arpeggiator.engine_screen(); });
    reg_ss(ScreenEnum::arp_selector, [&]() { return arpeggiator.selector_screen(); });
    reg_ss(ScreenEnum::sequencer, [&]() { return (ui::ScreenAndInput){sequencerscreen, sequencerscreen.input}; });
    reg_ss(ScreenEnum::sampler, [&]() { return (ui::ScreenAndInput){samplerscreen, samplerscreen.input}; });
    reg_ss(ScreenEnum::master, [&]() { return master.screen(); });
    // reg_ss(ScreenEnum::sampler_envelope, [&]() -> auto& { return sequencer.envelope_screen(); });
    reg_ss(ScreenEnum::synth, [&]() { return synth.engine_screen(); });
    reg_ss(ScreenEnum::synth_selector, [&]() { return synth.selector_screen(); });
    reg_ss(ScreenEnum::synth_envelope, [&]() { return synth->envelope_screen(); });
    reg_ss(ScreenEnum::voices, [&]() { return synth->voices_screen(); });
    reg_ss(ScreenEnum::external, [&]() { return line_in.screen(); });
    reg_ss(ScreenEnum::twist1, [&]() { return (ui::ScreenAndInput){twist1screen, twist1screen.input}; });
    reg_ss(ScreenEnum::twist2, [&]() { return (ui::ScreenAndInput){twist2screen, twist2screen.input}; });


    ui_manager.state.current_screen.on_change().connect([&](auto new_val) {
      switch (new_val) {
        case ScreenEnum::synth: [[fallthrough]];
        case ScreenEnum::synth_envelope: [[fallthrough]];
        case ScreenEnum::synth_selector: [[fallthrough]];
        case ScreenEnum::voices: {
          if (ui_manager.state.active_channel != +ChannelEnum::internal) {
            ui_manager.state.active_channel = +ChannelEnum::internal;
            break;
          }
        }
        case ScreenEnum::external: {
          if (line_in.props.mode.get() == 2 && line_in.props.active_send.get() == 0)
            ui_manager.state.active_channel = +ChannelEnum::external_left;
          else if (line_in.props.mode.get() == 2 && line_in.props.active_send.get() == 1)
            ui_manager.state.active_channel = +ChannelEnum::external_right;
          else
            ui_manager.state.active_channel = +ChannelEnum::external_stereo;
          break;
        }
        default: break;
      }
    });

    controller.register_key_handler(input::Key::sequencer,
                                    [&](input::Key k) { ui_manager.display(ScreenEnum::sequencer); });

    controller.register_key_handler(input::Key::sampler,
                                    [&](input::Key k) { ui_manager.display(ScreenEnum::sampler); });

    controller.register_key_handler(input::Key::routing,
                                    [&](input::Key k) { ui_manager.display(ScreenEnum::routing); });

    controller.register_key_handler(input::Key::looper, [&](input::Key k) { ui_manager.display(ScreenEnum::looper); });

    controller.register_key_handler(input::Key::slots,
                                    [&](input::Key k) { ui_manager.display(ScreenEnum::saveslots); });

    controller.register_key_handler(input::Key::arp, [&](input::Key k) {
      if (controller.is_pressed(input::Key::shift)) {
        ui_manager.display(ScreenEnum::arp_selector);
      } else {
        ui_manager.display(ScreenEnum::arp);
      }
    });

    controller.register_key_handler(input::Key::synth, [&](input::Key k) {
      if (controller.is_pressed(input::Key::shift)) {
        ui_manager.display(ScreenEnum::synth_selector);
      } else {
        ui_manager.display(ScreenEnum::synth);
      }
    });

    controller.register_key_handler(input::Key::envelope, [&](input::Key k) {
      if (ui_manager.state.active_channel == ChannelEnum::internal) {
        if (controller.is_pressed(input::Key::shift)) {
          ui_manager.display(ScreenEnum::voices);
        } else {
          ui_manager.display(ScreenEnum::synth_envelope);
        }
      } else {
        ui_manager.display(ScreenEnum::sampler_envelope);
      }
    });

    controller.register_key_handler(input::Key::fx1, [&](input::Key k) {
      if (controller.is_pressed(input::Key::shift)) {
        ui_manager.display(ScreenEnum::fx1_selector);
      } else {
        ui_manager.display(ScreenEnum::fx1);
      }
    });

    controller.register_key_handler(input::Key::fx2, [&](input::Key k) {
      if (controller.is_pressed(input::Key::shift)) {
        ui_manager.display(ScreenEnum::fx2_selector);
      } else {
        ui_manager.display(ScreenEnum::fx2);
      }
    });

    controller.register_key_handler(input::Key::external,
                                    [&](input::Key k) { ui_manager.display(ScreenEnum::external); });

    controller.register_key_handler(input::Key::twist1, [&](input::Key k) { ui_manager.display(ScreenEnum::twist1); });
    controller.register_key_handler(input::Key::twist2, [&](input::Key k) { ui_manager.display(ScreenEnum::twist2); });

    static ScreenEnum master_last_screen = ScreenEnum::master;
    static ScreenEnum send_last_screen = ScreenEnum::sends;

    controller.register_key_handler(
      input::Key::master,
      [&](input::Key k) {
        master_last_screen = ui_manager.state.current_screen;
        ui_manager.display(ScreenEnum::master);
      },
      [&](input::Key k) {
        if (master_last_screen) ui_manager.display(master_last_screen);
      });

    controller.register_key_handler(
      input::Key::sends,
      [&](input::Key k) {
        send_last_screen = ui_manager.state.current_screen;
        ui_manager.display(ScreenEnum::sends);
      },
      [&](input::Key k) {
        if (send_last_screen) ui_manager.display(send_last_screen);
      });

    auto load = [&](nlohmann::json& data) {
      util::deserialize(synth, data["Synth"]);
      util::deserialize(effect1, data["Effect1"]);
      util::deserialize(effect2, data["Effect2"]);
      // master.from_json(data["Master"]);
      // arpeggiator.from_json(data["Arpeggiator"]);
      // sequencer.from_json(data["Sequencer"]);
    };

    auto save = [&] {
      return nlohmann::json({
        {"Synth", util::serialize(synth)}, //
        {"Effect1", util::serialize(effect1)},
        {"Effect2", util::serialize(effect2)},
        // {"Master", master.to_json()},
        // {"Arpeggiator", arpeggiator.to_json()},
        // {"Sequencer", sequencer.to_json()},
      });
    };

    state_manager.attach("Engines", load, save);
  }

  void DefaultEngineManager::start() {}

  audio::ProcessData<2> DefaultEngineManager::process(audio::ProcessData<2> external_in)
  {
    // Main processor function
    auto midi_in = external_in.midi_only();
    midi_in.clock = ClockManager::current().step_frames(external_in.nframes);
    auto arp_out = arpeggiator.process(midi_in);

    auto from_external = Application::current().audio_manager->buffer_pool().allocate();
    for (auto&& [ext_out, extL, extR] : util::zip(from_external, external_in.audio[0], external_in.audio[1])) {
      ext_out = extL + extR;
    }

    auto synth_out = synth.process(arp_out.with(from_external));

    auto fx1_bus = Application::current().audio_manager->buffer_pool().allocate();
    auto fx2_bus = Application::current().audio_manager->buffer_pool().allocate();

    for (auto&& [snth, fx1, fx2] : util::zip(synth_out.audio, fx1_bus, fx2_bus)) {
      fx1 = snth * synth_send.audio->to_fx1;
      fx2 = snth * synth_send.audio->to_fx2;
    }
    auto fx1_out = effect1.process(audio::ProcessData<1>(fx1_bus));
    auto fx2_out = effect2.process(audio::ProcessData<1>(fx2_bus));

    // Stereo output gathered in fx1_out
    for (auto&& [snth, fx1L, fx1R, fx2L, fx2R] :
         util::zip(synth_out.audio, fx1_out.audio[0], fx1_out.audio[1], fx2_out.audio[0], fx2_out.audio[1])) {
      fx1L += fx2L + snth * 0.5 * synth_send.audio->dryL;
      fx1R += fx2R + snth * 0.5 * synth_send.audio->dryR;
    }

    synth_out.audio.release();
    fx2_out.audio[0].release();
    fx2_out.audio[1].release();
    fx1_bus.release();
    fx2_bus.release();
    return master.audio->process(std::move(fx1_out));
  }

} // namespace otto::services
