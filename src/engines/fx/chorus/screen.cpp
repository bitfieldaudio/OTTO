#include "screen.hpp"

#include "core/ui/vector_graphics.hpp"

namespace otto::engines::chorus {

  using namespace core::ui;
  using namespace core::ui::vg;

  
  void Screen::action(itc::prop_change<&Props::delay>, float d) noexcept
  {
    delay_ = d;
  }
  
  void Screen::action(itc::prop_change<&Props::depth>, float d) noexcept
  {
    depth_ = d;
  }
  
  void Screen::action(itc::prop_change<&Props::feedback>, float f) noexcept
  {
    feedback_ = f;
  }
  
  void Screen::action(itc::prop_change<&Props::rate>, float r) noexcept
  {
    rate_ = r;
  }

  void Screen::action(Actions::phase_value, std::atomic<float>& val) noexcept
  {
    phase_ = &val;
  }
  
  
  //TODO: Figure out the phase_delay handling
  void Screen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad = 20;
    constexpr float y_pad = 20;

    constexpr float x_right = width - x_pad;
    constexpr float y_bottom = height - y_pad;
    constexpr float number_shift = 30;

    wave_height = depth_ * 12;

    // Text
    ctx.font(Fonts::Norm, 25);
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText("depth", x_right, y_bottom);

    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("rate", x_pad, y_bottom);

    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText("feedback", x_right, y_pad);

    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("delay", x_pad, y_pad);

    // Numbers
    ctx.font(Fonts::Norm, 40);

    // chorus/RedValue/10
    ctx.fillStyle(Colours::Red.dim(1 - env_red()));
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", std::round(100 * depth_)), x_right, y_bottom - number_shift);

    // chorus/GreenValue/10
    ctx.fillStyle(Colours::Green.dim(1 - env_green()));
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", std::round(rate_ * 100)), x_pad, y_bottom - number_shift);

    // chorus/YellowValue/0
    ctx.fillStyle(Colours::Yellow.dim(1 - env_yellow()));
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", std::round(feedback_ * 100)), x_right, y_pad + number_shift);

    // chorus/BlueValue/1
    ctx.fillStyle(Colours::Blue.dim(1 - env_blue()));
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", std::round(100 * delay_)), x_pad, y_pad + number_shift);


    //Heads
    constexpr float spacing_constant = 10;
    constexpr int num_heads = 10;

    float spacing = spacing_constant * delay_ + 10;
    Point start = {120 - delay_ * 50, 165};

    OTTO_ASSERT(phase_ != nullptr);

    for (int i=num_heads; i>=1; i--) {
      float head_height = wave_height * gam::scl::sinP9(gam::scl::wrap(*phase_ - 0.2f*(float)i, 1.f, -1.f));
      //This brightness calculation is HORRIBLY over-engineered...
      float brightness = powf(cosh(abs(feedback_)*1.5)*0.4, 0.3 * float(i));
      draw_background_head(ctx, {start.x + i*spacing, start.y + head_height}, colour_list[i].dim(1 - brightness), 1 - i*0.07);
    }


    float wave_phase = *phase_;
    wave_phase = wave_height * gam::scl::sinP9(wave_phase);
    draw_front_head(ctx, {start.x, start.y + wave_phase}, Colours::Blue, 1);
  }

  void Screen::draw_front_head(ui::vg::Canvas& ctx, Point p, Color c, float scale)
  {
    // chorus/HeadMain
    ctx.beginPath();
    ctx.scaleTowards(scale, p);
    ctx.moveTo(p.x, p.y);
    ctx.lineTo(p.x, p.y - 173.0 + 153.6);
    ctx.bezierCurveTo(p.x + 121.4 - 130.8, p.y - 173.0 + 148.5, p.x + 115.0 - 130.8, p.y - 173.0 + 138.6, p.x + 115.0 - 130.8, p.y - 173.0 + 127.1);
    ctx.lineTo(p.x + 115.0 - 130.8, p.y - 173.0 + 107.3);
    ctx.bezierCurveTo(p.x + 115.0 - 130.8, p.y - 173.0 + 85.1, p.x + 133.0 - 130.8, p.y - 173.0 + 67.0, p.x + 155.2 - 130.8, p.y - 173.0 + 67.0);
    ctx.bezierCurveTo(p.x + 177.4 - 130.8, p.y - 173.0 + 67.0, p.x + 195.5 - 130.8, p.y - 173.0 + 85.1, p.x + 195.5 - 130.8, p.y - 173.0 + 107.3);
    ctx.lineTo(p.x + 195.5 - 130.8, p.y - 173.0 + 117.8);
    ctx.lineTo(p.x + 204.4 - 130.8, p.y - 173.0 + 130.0);
    ctx.bezierCurveTo(p.x + 205.4 - 130.8, p.y - 173.0 + 131.4, p.x + 205.1 - 130.8, p.y - 173.0 + 133.4, p.x + 203.7 - 130.8, p.y - 173.0 + 134.4);
    ctx.bezierCurveTo(p.x + 203.2 - 130.8, p.y - 173.0 + 134.8, p.x + 202.5 - 130.8, p.y - 173.0 + 135.0, p.x + 201.8 - 130.8, p.y - 173.0 + 135.0);
    ctx.lineTo(p.x + 195.5 - 130.8, p.y - 173.0 + 135.0);
    ctx.lineTo(p.x + 195.5 - 130.8, p.y - 173.0 + 152.4);
    ctx.bezierCurveTo(p.x + 195.5 - 130.8, p.y - 173.0 + 155.1, p.x + 193.3 - 130.8, p.y - 173.0 + 157.2, p.x + 190.7 - 130.8, p.y - 173.0 + 157.2);
    ctx.lineTo(p.x + 179.7 - 130.8, p.y - 173.0 + 157.2);
    ctx.lineTo(p.x + 179.7 - 130.8, p.y - 173.0 + 173.0);
    ctx.fill(Colours::Black);
    ctx.strokeStyle(c);
    ctx.stroke();

  }
  void Screen::draw_background_head(ui::vg::Canvas& ctx, Point p, Color c, float scale)
  {
    ctx.group([&] {
      ctx.beginPath();
      ctx.scaleTowards(scale, {p.x, p.y + (67.f - 173.f) / 2.f});
      ctx.lineWidth(6 / scale);
      ctx.moveTo(p.x + 115.0 - 130.8, p.y - 173.0 + 127.1);
      ctx.lineTo(p.x + 115.0 - 130.8, p.y - 173.0 + 107.3);
      ctx.bezierCurveTo(p.x + 115.0 - 130.8, p.y - 173.0 + 85.1, p.x + 133.0 - 130.8, p.y - 173.0 + 67.0,
                        p.x + 155.2 - 130.8, p.y - 173.0 + 67.0);
      ctx.bezierCurveTo(p.x + 177.4 - 130.8, p.y - 173.0 + 67.0, p.x + 195.5 - 130.8, p.y - 173.0 + 85.1,
                        p.x + 195.5 - 130.8, p.y - 173.0 + 107.3);
      ctx.lineTo(p.x + 195.5 - 130.8, p.y - 173.0 + 117.8);
      ctx.lineTo(p.x + 204.4 - 130.8, p.y - 173.0 + 130.0);
      ctx.bezierCurveTo(p.x + 205.4 - 130.8, p.y - 173.0 + 131.4, p.x + 205.1 - 130.8, p.y - 173.0 + 133.4,
                        p.x + 203.7 - 130.8, p.y - 173.0 + 134.4);
      ctx.bezierCurveTo(p.x + 203.2 - 130.8, p.y - 173.0 + 134.8, p.x + 202.5 - 130.8, p.y - 173.0 + 135.0,
                        p.x + 201.8 - 130.8, p.y - 173.0 + 135.0);
      ctx.lineTo(p.x + 195.5 - 130.8, p.y - 173.0 + 135.0);
      ctx.lineTo(p.x + 195.5 - 130.8, p.y - 173.0 + 152.4);
      ctx.bezierCurveTo(p.x + 195.5 - 130.8, p.y - 173.0 + 155.1, p.x + 193.3 - 130.8, p.y - 173.0 + 157.2,
                        p.x + 190.7 - 130.8, p.y - 173.0 + 157.2);
      ctx.lineTo(p.x + 179.7 - 130.8, p.y - 173.0 + 157.2);
      ctx.lineTo(p.x + 179.7 - 130.8, p.y - 173.0 + 173.0);
      ctx.fill(Colours::Black);
      ctx.strokeStyle(c);
      ctx.stroke();
    });
  }
} // namespace otto::engines::wormhole
