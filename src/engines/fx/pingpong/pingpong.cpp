#include "pingpong.hpp"

#include "core/ui/vector_graphics.hpp"

#include "util/iterator.hpp"
#include "util/utility.hpp"

#include "pingpong.faust.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  struct PingpongScreen : EngineScreen<Pingpong> {
    void draw(Canvas& ctx) override;
    bool keypress(Key key) override;
    void rotary(RotaryEvent e) override;

    using EngineScreen<Pingpong>::EngineScreen;
  };

  Pingpong::Pingpong()
    : EffectEngine("PingPong", props, std::make_unique<PingpongScreen>(this)),
      faust_(std::make_unique<faust_pingpong>(), props)
  {}


  audio::ProcessData<2> Pingpong::process(audio::ProcessData<2> data)
  {
    return faust_.process(data);
  }

  // SCREEN //

  void PingpongScreen::rotary(ui::RotaryEvent ev)
  {
    auto& props = engine.props;
    switch (ev.rotary) {
    case Rotary::Blue: props.delaytime.step(ev.clicks); break;
    case Rotary::Green: props.feedback.step(ev.clicks); break;
    case Rotary::White: props.tone.step(ev.clicks); break;
    case Rotary::Red: props.spread.step(ev.clicks); break;
    }
  }

  bool PingpongScreen::keypress(ui::Key key)
  {
    switch (key) {
    case ui::Key::blue_click: [[fallthrough]];
    case ui::Key::green_click: [[fallthrough]];
    case ui::Key::white_click: [[fallthrough]];
    case ui::Key::red_click:
      engine.props.bpm_follow = !engine.props.bpm_follow; break;
    default: return false; ;
    }
    return true;
  }

  void PingpongScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;
    using util::math::vec;

    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;
    /*
    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Time", {x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1}", engine.props.delaytime), {width - x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Feedback", {x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1}", engine.props.feedback), {width - x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Tone", {x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.tone), {width - x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Spread", {x_pad, y_pad + 3 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.spread), {width - x_pad, y_pad + 3 * space});

    if (engine.props.bpm_follow) {
      ctx.beginPath();
      ctx.fillStyle(Colours::Red);
      ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
      ctx.fillText("Following!", {x_pad, y_pad + 3 * space - 20});
    }
    */
    int x_spacing = width/12;
    int y_scale = 50;
    int y_base = height - 30;
    int line_length = 20;
    ctx.lineWidth(6.0f);
    for (int i=0;i<10;i++) {
      ctx.beginPath();
      engine.props.delay_level[i].level.refresh_links();
      ctx.moveTo(x_pad + i*x_spacing, y_base - engine.props.delay_level[i].level*y_scale);
      ctx.lineTo(x_pad + i*x_spacing, y_base - engine.props.delay_level[i].level*y_scale - line_length);
      ctx.stroke(Colours::Blue);
    }


  }

} // namespace otto::engines
