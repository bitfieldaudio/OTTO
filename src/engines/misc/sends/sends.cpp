#include "sends.hpp"

#include "core/ui/vector_graphics.hpp"

#include "services/controller.hpp"

namespace otto::engines {

  using namespace otto::services;

  struct SendsScreen : EngineScreen<Sends> {
    using EngineScreen::EngineScreen;

    void draw(core::ui::vg::Canvas& ctx) override;
    void encoder(core::ui::EncoderEvent e) override;
  };

  Sends::Sends() : MiscEngine<Sends>(std::make_unique<SendsScreen>(this)) {
  }

  LED led_for(ChannelEnum ce) {
    switch (+ce) {
      case ChannelEnum::internal: return LED{Key::synth};
      case ChannelEnum::external: return LED{Key::external};
      case ChannelEnum::sampler0: return LED{Key::S0};
      case ChannelEnum::sampler1: return LED{Key::S1};
      case ChannelEnum::sampler2: return LED{Key::S2};
      case ChannelEnum::sampler3: return LED{Key::S3};
      case ChannelEnum::sampler4: return LED{Key::S4};
      case ChannelEnum::sampler5: return LED{Key::S5};
      case ChannelEnum::sampler6: return LED{Key::S6};
      case ChannelEnum::sampler7: return LED{Key::S7};
      case ChannelEnum::sampler8: return LED{Key::S8};
      case ChannelEnum::sampler9: return LED{Key::S9};
    }
    OTTO_UNREACHABLE;
  }

  void SendsScreen::draw(core::ui::vg::Canvas& ctx)
  {
    Controller::current().set_color(LED{Key::fx1}, LEDColor::Blue * engine.props.to_FX1.get());
    Controller::current().set_color(LED{Key::fx2}, LEDColor::Green * engine.props.to_FX2.get());
    Controller::current().set_color(led_for(UIManager::current().state.active_channel), LEDColor::Red);


    using namespace core::ui::vg;
    ctx.font(Fonts::Norm, 35);

    // constexpr float x_pad = 30;

    // constexpr float y_pad = 50;
    // constexpr float space = (height - 2.f * y_pad) / 3.f;

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
    ctx.fillText(fmt::format("{}", std::round(engine.props.to_FX1 * 100)), 89.2, 89.8);

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
    ctx.fillText(fmt::format("{}", std::round(engine.props.to_FX2 * 100)), 87.7, 211.3);

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
    ctx.fillText(fmt::format("{}", std::round(engine.props.dry * 100)), 219.3, 211.9);

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
    int x_position =
      (295.3 * (engine.props.dry_pan + 1) * 0.5 + 187.0 * (1 - (engine.props.dry_pan + 1) * 0.5));
    ctx.moveTo(x_position, 59.5);
    ctx.lineTo(x_position, 63.1);
    ctx.lineWidth(6.0);
    ctx.strokeStyle(Colours::White);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();
    ctx.restore();
  }

  void SendsScreen::encoder(core::ui::EncoderEvent e)
  {
    switch (e.encoder) {
    case core::ui::Encoder::blue: engine.props.to_FX1.step(e.steps); break;
    case core::ui::Encoder::green: engine.props.to_FX2.step(e.steps); break;
    case core::ui::Encoder::yellow: engine.props.dry_pan.step(e.steps); break;
    case core::ui::Encoder::red: engine.props.dry.step(e.steps); break;
    }
  }

} // namespace otto::engines
