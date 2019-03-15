#include "engine_manager.hpp"
#include "core/engine/engine_dispatcher.hpp"
#include "core/engine/engine_dispatcher.impl.hpp"

#include <engines/synths/goss/goss.hpp>
#include "core/engine/sequencer.hpp"
#include "engines/fx/chorus/chorus.hpp"
#include "engines/fx/pingpong/pingpong.hpp"
#include "engines/fx/wormhole/wormhole.hpp"
#include "engines/misc/master/master.hpp"
#include "engines/seq/euclid/euclid.hpp"
#include "engines/synths/OTTOFM/ottofm.hpp"
#include "engines/synths/rhodes/rhodes.hpp"
#include "engines/synths/sampler/sampler.hpp"

#include "services/application.hpp"

#include "core/ui/vector_graphics.hpp"

namespace otto::services {

  using namespace core;
  using namespace core::engine;

  struct DefaultEngineManager final : EngineManager {
    DefaultEngineManager();

    void start() override;
    audio::ProcessData<2> process(audio::ProcessData<1> external_in) override;
    IEngine* by_name(const std::string& name) noexcept override;

  private:
    std::unordered_map<std::string, std::function<IEngine*()>> engineGetters;

    using EffectsDispatcher = EngineDispatcher< //
      EngineType::effect,
      engines::Wormhole,
      engines::Pingpong,
      engines::Chorus>;
    using ArpDispatcher = EngineDispatcher< //
      EngineType::arpeggiator,
      engines::Euclid>;
    using SynthDispatcher = EngineDispatcher< //
      EngineType::synth,
      engines::GossSynth,
      engines::RhodesSynth,
      engines::OTTOFMSynth>;

    SynthDispatcher synth{false};
    ArpDispatcher arpeggiator{true};
    EffectsDispatcher effect1{true};
    EffectsDispatcher effect2{true};

    engines::Master master;
    // engines::Sequencer sequencer;
  };

  struct EffectSend {
    struct Props : engines::Properties<> {
      engines::Property<float> to_FX1 = {this, "to_FX1", 0, engines::has_limits::init(0, 1),
                                         engines::steppable::init(0.01)};
      engines::Property<float> to_FX2 = {this, "to_FX2", 0, engines::has_limits::init(0, 1),
                                         engines::steppable::init(0.01)};
      engines::Property<float> dry = {this, "dry", 1, engines::has_limits::init(0, 1),
                                      engines::steppable::init(0.01)};
      engines::Property<float> dry_pan = {this, "dry_pan", 0, engines::has_limits::init(-1, 1),
                                          engines::steppable::init(0.01)};
    } props;

    struct Screen : ui::Screen {
      Screen(EffectSend& owner) : _owner(owner) {}
      EffectSend& _owner;

      void draw(core::ui::vg::Canvas& ctx) override;
      void rotary(core::ui::RotaryEvent e) override;
    } screen = {*this};
  };

  void EffectSend::Screen::draw(core::ui::vg::Canvas& ctx)
  {
    using namespace core::ui::vg;
    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad = 30;

    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;
    ctx.beginPath();

    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("To FX1", {x_pad, y_pad});
    ctx.beginPath();

    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", _owner.props.to_FX1), {width - x_pad, y_pad});
    ctx.beginPath();

    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("To FX2", {x_pad, y_pad + space});
    ctx.beginPath();

    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", _owner.props.to_FX2), {width - x_pad, y_pad + space});
    ctx.beginPath();

    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Dry", {x_pad, y_pad + 2 * space});
    ctx.beginPath();

    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", _owner.props.dry), {width - x_pad, y_pad + 2 * space});
    ctx.beginPath();

    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Pan", {x_pad, y_pad + 3 * space});
    ctx.beginPath();

    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", _owner.props.dry_pan), {width - x_pad, y_pad + 3 * space});
  }
  void EffectSend::Screen::rotary(core::ui::RotaryEvent e)
  {
    switch (e.rotary) {
    case otto::core::ui::Rotary::blue: _owner.props.to_FX1.step(e.clicks); break;
    case otto::core::ui::Rotary::green: _owner.props.to_FX2.step(e.clicks); break;
    case otto::core::ui::Rotary::yellow: _owner.props.dry.step(e.clicks); break;
    case otto::core::ui::Rotary::red: _owner.props.dry_pan.step(e.clicks); break;
    }
  }

  EffectSend synth_send;
  EffectSend line_in_send;



  std::unique_ptr<EngineManager> EngineManager::create_default()
  {
    return std::make_unique<DefaultEngineManager>();
  }

  DefaultEngineManager::DefaultEngineManager()
  {
    auto& ui_manager = *Application::current().ui_manager;
    auto& state_manager = *Application::current().state_manager;

    engineGetters.try_emplace("Synth", [&]() { return &synth.current(); });
    engineGetters.try_emplace("Effect1",
                              [&]() { return &effect1.current(); });
    engineGetters.try_emplace("Effect2",
                              [&]() { return &effect2.current(); });
    engineGetters.try_emplace("Arpeggiator",
                              [&]() { return &arpeggiator.current(); });

    arpeggiator.init();
    synth.init();
    effect1.init();
    effect2.init();

    ui_manager.register_key_handler(ui::Key::arpeggiator, [&](ui::Key k) {
      if (ui_manager.is_pressed(ui::Key::shift)) {
        ui_manager.display(arpeggiator.selector_screen());
      } else {
        ui_manager.select_engine("Arpeggiator");
        ui_manager.display(arpeggiator->screen());
      }
    });

    ui_manager.register_key_handler(ui::Key::synth, [&](ui::Key k) {
      if (ui_manager.is_pressed(ui::Key::shift)) {
        ui_manager.display(synth.selector_screen());
      } else {
        ui_manager.select_engine("Synth");
      }
    });

    ui_manager.register_key_handler(ui::Key::envelope, [&](ui::Key k) {
      auto* owner = dynamic_cast<engines::EngineWithEnvelope*>(&synth.current());
      if (owner) {
        if (ui_manager.is_pressed(ui::Key::shift)) {
          ui_manager.display(owner->voices_screen());
        } else {
          ui_manager.display(owner->envelope_screen());
        }
      }
    });

    ui_manager.register_key_handler(ui::Key::voices, [&](ui::Key k) {
      auto* owner = dynamic_cast<engines::EngineWithEnvelope*>(&synth.current());
      if (owner) {
        ui_manager.display(owner->voices_screen());
      }
    });

    ui_manager.register_key_handler(ui::Key::fx1, [&](ui::Key k) {
      if (ui_manager.is_pressed(ui::Key::shift)) {
        ui_manager.display(effect1.selector_screen());
      } else {
        ui_manager.select_engine("Effect1");
      }
    });

    ui_manager.register_key_handler(ui::Key::fx2, [&](ui::Key k) {
      if (ui_manager.is_pressed(ui::Key::shift)) {
        ui_manager.display(effect2.selector_screen());
      } else {
        ui_manager.select_engine("Effect2");
      }
    });

    // ui_manager.register_key_handler(ui::Key::sequencer, [&](ui::Key k) {
    //     ui_manager.display(sequencer.screen());
    // });

    static ui::Screen* master_last_screen = nullptr;
    static ui::Screen* send_last_screen = nullptr;

    ui_manager.register_key_handler(ui::Key::master,
                                    [&](ui::Key k) {
                                      master_last_screen = ui_manager.current_screen();
                                      ui_manager.display(master.screen());
                                    },
                                    [&](ui::Key k) {
                                      if (master_last_screen)
                                        ui_manager.display(*master_last_screen);
                                    });

    ui_manager.register_key_handler(ui::Key::send,
                                    [&](ui::Key k) {
                                      send_last_screen = ui_manager.current_screen();
                                      if (ui_manager.selected_engine_name() == "Arpeggiator" ||
                                          ui_manager.selected_engine_name() == "Synth")
                                        ui_manager.display(synth_send.screen);
                                    },
                                    [&](ui::Key k) {
                                      if (send_last_screen) ui_manager.display(*send_last_screen);
                                    });

    auto load = [&](nlohmann::json& data) {
      synth.from_json(data["Synth"]);
      effect1.from_json(data["Effect1"]);
      effect2.from_json(data["Effect2"]);
      master.from_json(data["Master"]);
      arpeggiator.from_json(data["Arpeggiator"]);
    };

    auto save = [&] {
      return nlohmann::json({{"Synth", synth.to_json()},
                             {"Effect1", effect1.to_json()},
                             {"Effect2", effect2.to_json()},
                             {"Master", master.to_json()},
                             {"Arpeggiator", arpeggiator.to_json()}});
    };

    state_manager.attach("Engines", load, save);
  }

  void DefaultEngineManager::start() {}

  audio::ProcessData<2> DefaultEngineManager::process(audio::ProcessData<1> external_in)
  { // Main processor function
    auto midi_in = external_in.midi_only();
    auto arp_out = arpeggiator->process(midi_in);
    auto synth_out = synth->process({external_in.audio, arp_out.midi, external_in.nframes});
    // auto seq_out = sequencer.process(midi_in);
    auto fx1_bus = Application::current().audio_manager->buffer_pool().allocate();
    auto fx2_bus = Application::current().audio_manager->buffer_pool().allocate();
    for (auto&& [snth, fx1, fx2] : util::zip(synth_out.audio, fx1_bus, fx2_bus)) {
      fx1 = snth * synth_send.props.to_FX1;
      fx2 = snth * synth_send.props.to_FX2;
    }
    auto fx1_out = effect1->process(audio::ProcessData<1>(fx1_bus));
    auto fx2_out = effect2->process(audio::ProcessData<1>(fx2_bus));
    for (auto&& [snth, fx1L, fx1R, fx2L, fx2R] :
         util::zip(synth_out.audio, fx1_out.audio[0], fx1_out.audio[1], fx2_out.audio[0],
                   fx1_out.audio[1])) {
      fx1L += fx2L + snth * synth_send.props.dry * (1 - synth_send.props.dry_pan);
      fx1R += fx2R + snth * synth_send.props.dry * (1 + synth_send.props.dry_pan);
    }
    synth_out.audio.release();
    fx2_out.audio[0].release();
    fx2_out.audio[1].release();
    fx1_bus.release();
    fx2_bus.release();
    return master.process(std::move(fx1_out));
    /*
    auto temp = Application::current().audio_manager->buffer_pool().allocate_multi_clear<2>();
    for (auto&& [in, tmp] : util::zip(seq_out, temp)) {
    std::get<0>(tmp) += std::get<0>(in);
        std::get<1>(tmp) += std::get<0>(in);
        }
    return master.process({std::move(temp),external_in.midi,external_in.nframes});
    */
  }

  IEngine* DefaultEngineManager::by_name(const std::string& name) noexcept
  {
    auto getter = engineGetters.find(name);
    if (getter == engineGetters.end()) return nullptr;

    return getter->second();
  }

} // namespace otto::services
