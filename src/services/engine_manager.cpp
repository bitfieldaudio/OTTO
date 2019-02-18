#include "engine_manager.hpp"
 
#include "engines/fx/wormhole/wormhole.hpp"
#include "engines/fx/pingpong/pingpong.hpp"
#include "engines/fx/chorus/chorus.hpp"
#include "engines/misc/master/master.hpp"
#include "core/engine/sequencer.hpp"
#include "engines/seq/euclid/euclid.hpp"
#include "engines/synths/OTTOFM/ottofm.hpp"
#include "engines/synths/hammond/hammond.hpp"
#include "engines/synths/nuke/nuke.hpp"
#include <engines/synths/goss/goss.hpp>
#include "engines/synths/potion/potion.hpp"
#include "engines/synths/rhodes/rhodes.hpp"
#include "engines/synths/sampler/sampler.hpp"

#include "services/application.hpp"

#include "core/ui/vector_graphics.hpp"

namespace otto::services {

  using namespace core;
  using namespace core::engine;

  struct OffScreen : ui::Screen {
    void draw(ui::vg::Canvas& ctx) override
    {
      ctx.fillStyle(ui::vg::Colours::Red);
      ctx.font(ui::vg::Fonts::Bold, 80);
      ctx.beginPath();
      ctx.textAlign(ui::vg::HorizontalAlign::Center, ui::vg::VerticalAlign::Middle);
      ctx.fillText("OFF", {160, 120});
    };
  };

  struct EffectOffEngine : EffectEngine {
    props::Properties<> props;
    EffectOffEngine() : EffectEngine("OFF", props, std::make_unique<OffScreen>()) {}
    audio::ProcessData<2> process(audio::ProcessData<1> data) noexcept override
    {
      auto out = Application::current().audio_manager->buffer_pool().allocate_multi_clear<2>();
      return data.redirect(out);
    };
  };

  struct ArpOffEngine : ArpeggiatorEngine {
    props::Properties<> props;
    ArpOffEngine() : ArpeggiatorEngine("OFF", props, std::make_unique<OffScreen>()) {}
    audio::ProcessData<0> process(audio::ProcessData<0> data) noexcept override
    {
      return data;
    }
  };

  struct DefaultEngineManager final : EngineManager {
    DefaultEngineManager();

    void start() override;
    audio::ProcessData<2> process(audio::ProcessData<1> external_in) override;
    AnyEngine* by_name(const std::string& name) noexcept override;

  private:
    std::unordered_map<std::string, std::function<AnyEngine*()>> engineGetters;

    EngineDispatcher<EngineType::arpeggiator> arpeggiator;
    EngineDispatcher<EngineType::synth> synth;
    EngineDispatcher<EngineType::effect> effect1;
    EngineDispatcher<EngineType::effect> effect2;

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

  void EffectSend::Screen::draw(core::ui::vg::Canvas&ctx)  {
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

    engineGetters.try_emplace("Synth", [&]() { return dynamic_cast<AnyEngine*>(synth.current()); });
    engineGetters.try_emplace("Effect1",
    [&]() { return dynamic_cast<AnyEngine*>(effect1.current()); });
    engineGetters.try_emplace("Effect2",
                              [&]() { return dynamic_cast<AnyEngine*>(effect2.current()); });
    engineGetters.try_emplace("Arpeggiator",
                              [&]() { return dynamic_cast<AnyEngine*>(arpeggiator.current()); });

    arpeggiator.register_engine<ArpOffEngine>("OFF");
    arpeggiator.register_engine<engines::Euclid>("Euclid");
    synth.register_engine<engines::HammondSynth>("Woody");
    synth.register_engine<engines::NukeSynth>("Nuke");
    synth.register_engine<engines::GossSynth>("Goss");
    synth.register_engine<engines::PotionSynth>("Potion");
    synth.register_engine<engines::RhodesSynth>("Rhodes");
    synth.register_engine<engines::OTTOFMSynth>("OTTO.FM");
    synth.register_engine<engines::Sampler>("Sampler");
    effect1.register_engine<EffectOffEngine>("OFF");
    effect2.register_engine<EffectOffEngine>("OFF");
    effect1.register_engine<engines::Wormhole>("Wormhole");
    effect2.register_engine<engines::Wormhole>("Wormhole");
    effect1.register_engine<engines::Pingpong>("PingPong");
    effect2.register_engine<engines::Pingpong>("PingPong");
    effect1.register_engine<engines::Chorus>("Chorus");
    effect2.register_engine<engines::Chorus>("Chorus");

    arpeggiator.init();
    synth.init();
    effect1.init();
    effect2.init();



    ui_manager.register_key_handler(ui::Key::arpeggiator, [&](ui::Key k) {
      if (ui_manager.is_pressed(ui::Key::shift)) {
        ui_manager.display(arpeggiator.selector_screen());
      } else {
        ui_manager.select_engine("Sequencer");
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
      auto* owner = dynamic_cast<engines::EngineWithEnvelope*>(synth.current());
      if (owner) {
        if (ui_manager.is_pressed(ui::Key::shift)) {
          ui_manager.display(owner->voices_screen());
        } else {
          ui_manager.display(owner->envelope_screen());
        }
      }
    });

    ui_manager.register_key_handler(ui::Key::voices, [&](ui::Key k) {
      auto* owner = dynamic_cast<engines::EngineWithEnvelope*>(synth.current());
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
                                      if (ui_manager.selected_engine_name() == "Sequencer" ||
                              ui_manager.selected_engine_name() == "Synth")
                                        ui_manager.display(synth_send.screen);
                                    },
                                    [&](ui::Key k) {
                                      if (send_last_screen)
                                          ui_manager.display(*send_last_screen);
                                    });

    auto load = [&](nlohmann::json& data) {
      synth.from_json(data["Synth"]);
      effect1.from_json(data["Effect1"]);
      effect2.from_json(data["Effect2"]);
      master.from_json(data["Master"]);
      arpeggiator.from_json(data["Sequencer"]);
    };

    auto save = [&] {
      return nlohmann::json({{"Synth", synth.to_json()},
                             {"Effect1", effect1.to_json()},
                             {"Effect2", effect2.to_json()},
                             {"Master", master.to_json()},
                             {"Arpeggiator", arpeggiator.to_json()}});
    };

    state_manager.attach("Engines", load, save);

    arpeggiator.select(std::size_t(0));
    synth.select(std::size_t(0));
    effect1.select(std::size_t(0));
    effect2.select(std::size_t(0));
  }

  void DefaultEngineManager::start() {}

  audio::ProcessData<2> DefaultEngineManager::process(audio::ProcessData<1> external_in)
  { // Main processor function
    auto midi_in = external_in.midi_only();
    auto arp_out = arpeggiator->process(midi_in);
    auto synth_out = synth->process({external_in.audio, arp_out.midi, external_in.nframes});
    // auto seq_out = sequencer.process(midi_in);
    auto fx1_bus = Application::current().audio_manager->buffer_pool().allocate_multi<1>();
    auto fx2_bus = Application::current().audio_manager->buffer_pool().allocate_multi<1>();
    for (auto&& [snth, fx1, fx2] : util::zip(synth_out, fx1_bus, fx2_bus)) {
    std::get<0>(fx1) = std::get<0>(snth) * synth_send.props.to_FX1;
      std::get<0>(fx2) = std::get<0>(snth) * synth_send.props.to_FX2;
      }
    auto fx1_out = effect1->process(external_in.redirect(fx1_bus));
    auto fx2_out = effect2->process(external_in.redirect(fx2_bus));
    for (auto&& [snth, fx1, fx2] : util::zip(synth_out, fx1_out, fx2_out)) {
    std::get<0>(fx1) += std::get<0>(fx2) +
      std::get<0>(snth) * synth_send.props.dry * (1 - synth_send.props.dry_pan);
                          std::get<1>(fx1) += std::get<1>(fx2) +
      std::get<0>(snth) * synth_send.props.dry * (1 + synth_send.props.dry_pan);
                          }
    synth_out.audio.release();
    fx2_out.audio.release();
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

  AnyEngine* DefaultEngineManager::by_name(const std::string& name) noexcept
  {
    auto getter = engineGetters.find(name);
    if (getter == engineGetters.end()) return nullptr;

    return getter->second();
  }

} // namespace otto::services
