#include "engine_manager.hpp"

#include <engines/synths/goss/goss.hpp>
#include <engines/synths/potion/potion.hpp>
#include "core/engine/sequencer.hpp"
#include "engines/fx/chorus/chorus.hpp"
#include "engines/fx/pingpong/pingpong.hpp"
#include "engines/fx/wormhole/wormhole.hpp"
#include "engines/fx/FDNReverb/FDNReverb.hpp"
#include "engines/misc/master/master.hpp"
#include "engines/seq/euclid/euclid.hpp"
#include "engines/synths/OTTOFM/ottofm.hpp"
#include "engines/synths/rhodes/rhodes.hpp"
#include "engines/synths/gammasampler/gammasampler.hpp"
#include "engines/synths/potion/potion.hpp"

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
                                          engines::steppable::init(0.02)};
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

    // sends/sendsIcon

    // sends/sendsIcon/redLine
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(38.4, 112.2);
    ctx.lineTo(72.2, 78.4);
    ctx.lineWidth(6.0);
    ctx.strokeStyle(Colours::Gray70);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();

    // sends/sendsIcon/Send1Arrow
    ctx.beginPath();
    ctx.moveTo(62.4, 78.5);
    ctx.lineTo(72.2, 78.4);
    ctx.lineTo(72.2, 88.3);
    ctx.strokeStyle(Colours::Blue);
    ctx.stroke();

    // sends/sendsIcon/yellowLine
    ctx.beginPath();
    ctx.moveTo(38.4, 127.7);
    ctx.lineTo(72.3, 161.6);
    ctx.strokeStyle(Colours::Gray70);
    ctx.stroke();

    // sends/sendsIcon/Send2Arrow
    ctx.beginPath();
    ctx.moveTo(72.2, 151.7);
    ctx.lineTo(72.2, 161.6);
    ctx.lineTo(62.4, 161.5);
    ctx.strokeStyle(Colours::Green);
    ctx.stroke();

    // sends/sendsIcon/circle
    ctx.beginPath();
    ctx.moveTo(41.7, 120.0);
    ctx.bezierCurveTo(41.7, 126.0, 36.8, 130.9, 30.8, 130.9);
    ctx.bezierCurveTo(24.8, 130.9, 19.9, 126.0, 19.9, 120.0);
    ctx.bezierCurveTo(19.9, 114.0, 24.8, 109.1, 30.8, 109.1);
    ctx.bezierCurveTo(36.8, 109.1, 41.7, 114.0, 41.7, 120.0);
    ctx.closePath();
    ctx.strokeStyle(Colours::Gray70);
    ctx.stroke();

    // sends/FX1
    ctx.restore();

    // sends/FX1/FX1
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(115.1, 27.8);
    ctx.bezierCurveTo(114.2, 27.2, 112.9, 27.4, 112.2, 28.3);
    ctx.lineTo(109.3, 32.4);
    ctx.lineTo(106.4, 28.3);
    ctx.bezierCurveTo(106.4, 28.3, 106.4, 28.3, 106.3, 28.2);
    ctx.bezierCurveTo(106.3, 28.2, 106.2, 28.1, 106.2, 28.0);
    ctx.bezierCurveTo(106.1, 28.0, 106.1, 27.9, 106.0, 27.9);
    ctx.bezierCurveTo(106.0, 27.9, 105.9, 27.8, 105.9, 27.8);
    ctx.bezierCurveTo(105.8, 27.7, 105.7, 27.7, 105.7, 27.7);
    ctx.bezierCurveTo(105.6, 27.7, 105.6, 27.6, 105.5, 27.6);
    ctx.bezierCurveTo(105.4, 27.6, 105.4, 27.6, 105.3, 27.5);
    ctx.bezierCurveTo(105.2, 27.5, 105.2, 27.5, 105.1, 27.5);
    ctx.bezierCurveTo(105.0, 27.5, 104.9, 27.5, 104.9, 27.5);
    ctx.bezierCurveTo(104.8, 27.5, 104.8, 27.4, 104.7, 27.4);
    ctx.lineTo(104.7, 27.4);
    ctx.bezierCurveTo(104.7, 27.4, 104.7, 27.4, 104.7, 27.4);
    ctx.lineTo(92.8, 27.4);
    ctx.bezierCurveTo(91.7, 27.4, 90.7, 28.4, 90.7, 29.5);
    ctx.lineTo(90.7, 42.5);
    ctx.bezierCurveTo(90.7, 43.6, 91.7, 44.6, 92.8, 44.6);
    ctx.bezierCurveTo(94.0, 44.6, 94.9, 43.6, 94.9, 42.5);
    ctx.lineTo(94.9, 39.1);
    ctx.lineTo(98.9, 39.1);
    ctx.bezierCurveTo(100.1, 39.1, 101.0, 38.2, 101.0, 37.0);
    ctx.bezierCurveTo(101.0, 35.9, 100.1, 34.9, 98.9, 34.9);
    ctx.lineTo(94.9, 34.9);
    ctx.lineTo(94.9, 31.6);
    ctx.lineTo(103.6, 31.6);
    ctx.lineTo(106.8, 36.0);
    ctx.lineTo(103.0, 41.3);
    ctx.bezierCurveTo(102.3, 42.2, 102.6, 43.5, 103.5, 44.2);
    ctx.bezierCurveTo(103.9, 44.5, 104.3, 44.6, 104.7, 44.6);
    ctx.bezierCurveTo(105.4, 44.6, 106.0, 44.3, 106.4, 43.7);
    ctx.lineTo(109.3, 39.6);
    ctx.lineTo(112.2, 43.7);
    ctx.bezierCurveTo(112.6, 44.3, 113.3, 44.6, 113.9, 44.6);
    ctx.bezierCurveTo(114.3, 44.6, 114.8, 44.5, 115.1, 44.2);
    ctx.bezierCurveTo(116.1, 43.5, 116.3, 42.2, 115.6, 41.3);
    ctx.lineTo(111.9, 36.0);
    ctx.lineTo(115.6, 30.8);
    ctx.bezierCurveTo(116.3, 29.8, 116.1, 28.5, 115.1, 27.8);
    ctx.closePath();
    ctx.fillStyle(Colours::Blue);
    ctx.fill();

    // sends/FX1/FX1dot
    ctx.beginPath();
    ctx.moveTo(122.2, 33.8);
    ctx.bezierCurveTo(121.0, 33.8, 120.0, 34.8, 120.0, 36.0);
    ctx.bezierCurveTo(120.0, 37.2, 121.0, 38.2, 122.2, 38.2);
    ctx.bezierCurveTo(123.4, 38.2, 124.3, 37.2, 124.3, 36.0);
    ctx.bezierCurveTo(124.3, 34.8, 123.4, 33.8, 122.2, 33.8);
    ctx.closePath();
    ctx.fill();

    // sends/FX1value
    ctx.restore();
    ctx.font(Fonts::Norm, 42);
    ctx.fillStyle(Colours::White);
    ctx.fillText(fmt::format("{}", std::round(_owner.props.to_FX1 * 100)), 89.2, 89.8);

    // sends/FX2

    // sends/FX2/FX2
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(115.1, 149.4);
    ctx.bezierCurveTo(114.1, 148.7, 112.8, 148.9, 112.2, 149.9);
    ctx.lineTo(109.3, 153.9);
    ctx.lineTo(106.4, 149.9);
    ctx.bezierCurveTo(106.4, 149.8, 106.3, 149.8, 106.3, 149.8);
    ctx.bezierCurveTo(106.2, 149.7, 106.2, 149.6, 106.1, 149.6);
    ctx.bezierCurveTo(106.1, 149.5, 106.0, 149.5, 106.0, 149.4);
    ctx.bezierCurveTo(105.9, 149.4, 105.9, 149.4, 105.8, 149.3);
    ctx.bezierCurveTo(105.7, 149.3, 105.7, 149.2, 105.6, 149.2);
    ctx.bezierCurveTo(105.6, 149.2, 105.5, 149.2, 105.4, 149.1);
    ctx.bezierCurveTo(105.4, 149.1, 105.3, 149.1, 105.2, 149.1);
    ctx.bezierCurveTo(105.2, 149.0, 105.1, 149.0, 105.1, 149.0);
    ctx.bezierCurveTo(105.0, 149.0, 104.9, 149.0, 104.8, 149.0);
    ctx.bezierCurveTo(104.8, 149.0, 104.7, 149.0, 104.7, 149.0);
    ctx.lineTo(104.6, 149.0);
    ctx.bezierCurveTo(104.6, 149.0, 104.6, 149.0, 104.6, 149.0);
    ctx.lineTo(92.8, 149.0);
    ctx.bezierCurveTo(91.6, 149.0, 90.7, 149.9, 90.7, 151.1);
    ctx.lineTo(90.7, 164.0);
    ctx.bezierCurveTo(90.7, 165.2, 91.6, 166.1, 92.8, 166.1);
    ctx.bezierCurveTo(93.9, 166.1, 94.9, 165.2, 94.9, 164.0);
    ctx.lineTo(94.9, 160.6);
    ctx.lineTo(98.9, 160.6);
    ctx.bezierCurveTo(100.0, 160.6, 101.0, 159.7, 101.0, 158.5);
    ctx.bezierCurveTo(101.0, 157.4, 100.0, 156.5, 98.9, 156.5);
    ctx.lineTo(94.9, 156.5);
    ctx.lineTo(94.9, 153.2);
    ctx.lineTo(103.6, 153.2);
    ctx.lineTo(106.7, 157.5);
    ctx.lineTo(103.0, 162.8);
    ctx.bezierCurveTo(102.3, 163.7, 102.5, 165.1, 103.5, 165.7);
    ctx.bezierCurveTo(103.8, 166.0, 104.3, 166.1, 104.7, 166.1);
    ctx.bezierCurveTo(105.3, 166.1, 106.0, 165.8, 106.4, 165.2);
    ctx.lineTo(109.3, 161.2);
    ctx.lineTo(112.2, 165.2);
    ctx.bezierCurveTo(112.6, 165.8, 113.2, 166.1, 113.9, 166.1);
    ctx.bezierCurveTo(114.3, 166.1, 114.7, 166.0, 115.1, 165.7);
    ctx.bezierCurveTo(116.0, 165.1, 116.3, 163.7, 115.6, 162.8);
    ctx.lineTo(111.8, 157.5);
    ctx.lineTo(115.6, 152.3);
    ctx.bezierCurveTo(116.3, 151.3, 116.0, 150.0, 115.1, 149.4);
    ctx.closePath();
    ctx.fillStyle(Colours::Green);
    ctx.fill();

    // sends/FX2/FX2dot
    ctx.beginPath();
    ctx.moveTo(122.1, 161.2);
    ctx.bezierCurveTo(120.9, 161.2, 119.9, 162.2, 119.9, 163.4);
    ctx.bezierCurveTo(119.9, 164.6, 120.9, 165.6, 122.1, 165.6);
    ctx.bezierCurveTo(123.3, 165.6, 124.3, 164.6, 124.3, 163.4);
    ctx.bezierCurveTo(124.3, 162.2, 123.3, 161.2, 122.1, 161.2);
    ctx.closePath();
    ctx.fill();

    // sends/FX2/FX2dot
    ctx.beginPath();
    ctx.moveTo(122.1, 154.0);
    ctx.bezierCurveTo(123.3, 154.0, 124.3, 153.1, 124.3, 151.9);
    ctx.bezierCurveTo(124.3, 150.7, 123.3, 149.7, 122.1, 149.7);
    ctx.bezierCurveTo(120.9, 149.7, 119.9, 150.7, 119.9, 151.9);
    ctx.bezierCurveTo(119.9, 153.1, 120.9, 154.0, 122.1, 154.0);
    ctx.closePath();
    ctx.fill();

    // sends/FX2value
    ctx.restore();
    ctx.font(Fonts::Norm, 42);
    ctx.fillStyle(Colours::White);
    ctx.fillText(fmt::format("{}", std::round(_owner.props.to_FX2 * 100)), 87.7, 211.3);

    // sends/dryArrow

    // sends/dryArrow/line
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(68.7, 120.0);
    ctx.lineTo(116.5, 120.0);
    ctx.bezierCurveTo(140.0, 120.0, 163.1, 125.1, 184.4, 135.0);
    ctx.lineTo(200.6, 142.5);
    ctx.lineWidth(6.0);
    ctx.strokeStyle(Colours::Gray70);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();

    // sends/dryArrow/arrowhead
    ctx.beginPath();
    ctx.moveTo(196.8, 131.7);
    ctx.lineTo(200.6, 142.6);
    ctx.lineTo(189.7, 146.3);
    ctx.strokeStyle(Colours::White);
    ctx.stroke();

    // sends/dryValue
    ctx.restore();
    ctx.font(Fonts::Norm, 42);
    ctx.fillStyle(Colours::White);
    ctx.fillText(fmt::format("{}", std::round(_owner.props.dry * 100)), 219.3, 211.9);

    // sends/dry
    ctx.font(Fonts::Norm, 30);
    ctx.fillStyle(Colours::Red);
    ctx.fillText("dry", 219.3, 166.1);

    // sends/pan
    ctx.fillStyle(Colours::Yellow);
    ctx.fillText("pan", 219.3, 44.6);

    // sends/7Lines

    // sends/7Lines/7
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(295.3, 74.5);
    ctx.lineTo(295.3, 74.8);
    ctx.lineWidth(6.0);
    ctx.strokeStyle(Colours::Gray70);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();

    // sends/7Lines/6
    ctx.beginPath();
    ctx.moveTo(277.3, 74.5);
    ctx.lineTo(277.3, 78.8);
    ctx.stroke();

    // sends/7Lines/5
    ctx.beginPath();
    ctx.moveTo(259.2, 74.5);
    ctx.lineTo(259.2, 82.8);
    ctx.stroke();

    // sends/7Lines/4
    ctx.beginPath();
    ctx.moveTo(241.1, 74.5);
    ctx.lineTo(241.1, 86.8);
    ctx.stroke();

    // sends/7Lines/3
    ctx.beginPath();
    ctx.moveTo(223.1, 74.5);
    ctx.lineTo(223.1, 82.8);
    ctx.stroke();

    // sends/7Lines/2
    ctx.beginPath();
    ctx.moveTo(205.0, 74.5);
    ctx.lineTo(205.0, 78.8);
    ctx.stroke();

    // sends/7Lines/1
    ctx.beginPath();
    ctx.moveTo(187.0, 74.5);
    ctx.lineTo(187.0, 74.8);
    ctx.stroke();

    // sends/7LinesPointer
    ctx.restore();
    ctx.beginPath();
    int x_position = (295.3 * (_owner.props.dry_pan + 1)*0.5 + 187.0 * (1 - (_owner.props.dry_pan + 1)*0.5));
    ctx.moveTo(x_position, 59.5);
    ctx.lineTo(x_position, 63.1);
    ctx.lineWidth(6.0);
    ctx.strokeStyle(Colours::White);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();
    ctx.restore();
  }

  void EffectSend::Screen::rotary(core::ui::RotaryEvent e)
  {
    switch (e.rotary) {
    case otto::core::ui::Rotary::blue: _owner.props.to_FX1.step(e.clicks); break;
    case otto::core::ui::Rotary::green: _owner.props.to_FX2.step(e.clicks); break;
    case otto::core::ui::Rotary::yellow: _owner.props.dry_pan.step(e.clicks); break;
    case otto::core::ui::Rotary::red: _owner.props.dry.step(e.clicks); break;
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
    synth.register_engine<engines::GossSynth>("Goss");
    synth.register_engine<engines::RhodesSynth>("Rhodes");
    synth.register_engine<engines::OTTOFMSynth>("OTTO.FM");
    synth.register_engine<engines::Sampler>("Sampler");
    synth.register_engine<engines::PotionSynth>("Potion");
    effect1.register_engine<EffectOffEngine>("OFF");
    effect2.register_engine<EffectOffEngine>("OFF");
    effect1.register_engine<engines::Wormhole>("Wormhole");
    effect2.register_engine<engines::Wormhole>("Wormhole");
    effect1.register_engine<engines::Pingpong>("PingPong");
    effect2.register_engine<engines::Pingpong>("PingPong");
    effect1.register_engine<engines::Chorus>("Chorus");
    effect2.register_engine<engines::Chorus>("Chorus");
    effect1.register_engine<engines::KratosReverb>("Kratos");
    effect2.register_engine<engines::KratosReverb>("Kratos");

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
                                      if (send_last_screen) ui_manager.display(*send_last_screen);
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
    auto fx1_bus = Application::current().audio_manager->buffer_pool().allocate();
    auto fx2_bus = Application::current().audio_manager->buffer_pool().allocate();
    for (auto&& [snth, fx1, fx2] : util::zip(synth_out.audio, fx1_bus, fx2_bus)) {
      fx1 = snth * synth_send.props.to_FX1;
      fx2 = snth * synth_send.props.to_FX2;
    }
    auto fx1_out = effect1->process(audio::ProcessData<1>(fx1_bus));
    auto fx2_out = effect2->process(audio::ProcessData<1>(fx2_bus));
    for (auto&& [snth, fx1L, fx1R, fx2L, fx2R] : util::zip(synth_out.audio, fx1_out.audio[0], fx1_out.audio[1], fx2_out.audio[0], fx2_out.audio[1])) {
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

  AnyEngine* DefaultEngineManager::by_name(const std::string& name) noexcept
  {
    auto getter = engineGetters.find(name);
    if (getter == engineGetters.end()) return nullptr;

    return getter->second();
  }

} // namespace otto::services
