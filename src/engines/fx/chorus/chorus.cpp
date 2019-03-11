#include "chorus.hpp"

#include "core/ui/vector_graphics.hpp"

#include "util/iterator.hpp"
#include "util/utility.hpp"

#include "chorus.faust.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  struct ChorusScreen : EngineScreen<Chorus> {
    void draw(Canvas& ctx) override;
    bool keypress(Key key) override;
    void rotary(RotaryEvent e) override;

    using EngineScreen<Chorus>::EngineScreen;
  };

  Chorus::Chorus()
    : EffectEngine(name, props, std::make_unique<ChorusScreen>(this)),
      faust_(std::make_unique<faust_chorus>(), props)
  {}


  audio::ProcessData<2> Chorus::process(audio::ProcessData<1> data)
  {
    return faust_.process(data);
  }

  // SCREEN //

  void ChorusScreen::rotary(ui::RotaryEvent ev)
  {
    auto& props = engine.props;
    switch (ev.rotary) {
    case Rotary::blue: props.delay.step(ev.clicks); break;
    case Rotary::green: props.rate.step(ev.clicks); break;
    case Rotary::yellow: props.deviation.step(ev.clicks); break;
    case Rotary::red: props.depth.step(ev.clicks); break;
    }
  }

  bool ChorusScreen::keypress(ui::Key key)
  {
    return false;
  }

  void ChorusScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;
    using util::math::vec;

    auto& props = engine.props;

    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Delay", {x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", props.delay), {width - x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Rate", {x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", props.rate), {width - x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Deviation", {x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", props.deviation), {width - x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("depth", {x_pad, y_pad + 3 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", props.depth), {width - x_pad, y_pad + 3 * space});
  }

} // namespace otto::engines
