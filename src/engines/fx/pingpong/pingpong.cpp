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
    : EffectEngine(name, props, std::make_unique<PingpongScreen>(this)),
      faust_(std::make_unique<faust_pingpong>(), props)
  {}


  audio::ProcessData<2> Pingpong::process(audio::ProcessData<1> data)
  {
    return faust_.process(data);
  }

  // SCREEN //

  void PingpongScreen::rotary(ui::RotaryEvent ev)
  {
    auto& props = engine.props;
    switch (ev.rotary) {
    case Rotary::blue: props.delaytime.step(ev.clicks); break;
    case Rotary::green: props.feedback.step(ev.clicks); break;
    case Rotary::yellow: props.tone.step(ev.clicks); break;
    case Rotary::red: props.spread.step(ev.clicks); break;
    }
  }

  bool PingpongScreen::keypress(ui::Key key)
  {
    switch (key) {
    case ui::Key::blue_click: [[fallthrough]];
    case ui::Key::green_click: [[fallthrough]];
    case ui::Key::yellow_click: [[fallthrough]];
    case ui::Key::red_click: engine.props.bpm_follow = !engine.props.bpm_follow; break;
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

    int x_spacing_min = width / 25;
    int x_scaling = 50;
    int y_base = height / 2;
    ctx.lineWidth(6.0f);

    int y_height_top = 100;
    int y_height_bot = 100;
    float dim_scale_top = engine.props.feedback - 0.01 - 0.2 * max(0.0, 0.5 - engine.props.tone);
    float dim_scale_bot = engine.props.feedback - 0.01 - 0.2 * max(0.0, engine.props.tone - 0.5);
    for (int i = 0; i < 20; i++) {
      ctx.beginPath();
      int x_pos = x_pad + i * (x_spacing_min + x_scaling * engine.props.delaytime);
      ctx.moveTo(x_pos, y_base - y_height_top);
      ctx.lineTo(x_pos, y_base + y_height_bot);
      ctx.stroke(Colours::Gray50);

      ctx.beginPath();
      engine.props.delay_level[i].level.refresh_links();
      ctx.moveTo(x_pos, y_base - y_height_top * engine.props.delay_level[i].level);
      ctx.lineTo(x_pos, y_base + y_height_bot * engine.props.delay_level[i].level);
      ctx.stroke(Colours::Blue);
      y_height_top *= dim_scale_top;
      y_height_bot *= dim_scale_bot;
    }
  }

} // namespace otto::engines
