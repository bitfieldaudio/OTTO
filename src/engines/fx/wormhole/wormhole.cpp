#include "wormhole.hpp"

#include "core/globals.hpp"
#include "core/ui/vector_graphics.hpp"

#include "util/iterator.hpp"
#include "util/utility.hpp"

#include "wormhole.faust.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  struct WormholeScreen : EngineScreen<Wormhole> {
    void draw(Canvas& ctx) override;
    bool keypress(Key key) override;
    void rotary(RotaryEvent e) override;

    using EngineScreen<Wormhole>::EngineScreen;
  };

  Wormhole::Wormhole() : EffectEngine("Wormhole", props, std::make_unique<WormholeScreen>(this)), faust_(std::make_unique<faust_wormhole>(), props) {}


  audio::ProcessData<2> Wormhole::process(audio::ProcessData<2> data)
  {
    return faust_.process(data);
  }

  // SCREEN //

  void WormholeScreen::rotary(ui::RotaryEvent ev)
  {
    auto& props = engine.props;
    switch (ev.rotary) {
    case Rotary::Blue: props.mix.step(ev.clicks); break;
    case Rotary::Green: props.shimmer.step(ev.clicks); break;
    case Rotary::White: props.length.step(ev.clicks); break;
    case Rotary::Red: props.shape.step(ev.clicks); break;
    }
  }

  bool WormholeScreen::keypress(ui::Key key)
  {
    return false;
  }

  void WormholeScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    auto& props = engine.props;

    ctx.font(Fonts::Bold, 40);

    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Mix", {x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", props.mix), {width - x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Shimmer", {x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", props.shimmer), {width - x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Length", {x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", props.length), {width - x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Shape", {x_pad, y_pad + 3 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", props.shape), {width - x_pad, y_pad + 3 * space});
  }

} // namespace otto::engines
