#include "screen.hpp"
#include <cmath>

#include "core/ui/nvg/Canvas.hpp"
#include "core/ui/nvg/Color.hpp"
#include "core/ui/nvg/Text.hpp"
#include "core/ui/vector_graphics.hpp"
#include "services/controller.hpp"
#include "services/ui_manager.hpp"

namespace otto::engines::sends {

  using namespace core::ui;
  using namespace core::ui::vg;

  Screen::Screen(core::ui::Icon i) : icon_(i)
  {
    constexpr float input_radius = 30;
    icon_.set_size({input_radius * 1.5, input_radius * 1.5});
    icon_.set_color(Colours::Gray50);
    icon_.set_line_width(5.f);
  }

  void Screen::action(itc::prop_change<&Props::dry>, float d) noexcept
  {
    dry_ = d;
  }
  void Screen::action(itc::prop_change<&Props::fx1>, float fx1) noexcept
  {
    fx1_ = fx1;
  }
  void Screen::action(itc::prop_change<&Props::fx2>, float fx2) noexcept
  {
    fx2_ = fx2;
  }
  void Screen::action(itc::prop_change<&Props::pan>, float p) noexcept
  {
    pan_ = p;
  }

  void Screen::draw(nvg::Canvas &ctx)
  {
    draw_background(ctx);

    // circles
    constexpr float x_fx = 119 + 26;
    constexpr float x_dry = 167 + 26;
    constexpr float y_fx1 = 26 + 26;
    constexpr float y_dry = 78 + 26;
    constexpr float y_fx2 = 130 + 26;

    // Input
    constexpr float input_radius = 30;
    constexpr float input_x = 45;
    ctx.beginPath();
    ctx.circle({input_x, y_dry}, input_radius);
    ctx.stroke();
    ctx.fill(Colours::White);
    // Icon
    ctx.drawAt({input_x - input_radius * 0.75, y_dry - input_radius * 0.75}, icon_);
    
    // Control indicators
    bool shift = services::Controller::current().is_pressed(Key::shift);
    draw_coloured_circle(ctx, {x_fx, y_fx1}, shift ? Colours::White : Colours::Blue, fx1_);
    draw_coloured_circle(ctx, {x_fx, y_fx2}, shift ? Colours::White : Colours::Green, fx2_);
    draw_coloured_circle(ctx, {x_dry, y_dry}, shift ? Colours::White : Colours::Yellow, dry_);
      
    // Pan
    draw_radial_lines(ctx, pan_);
    
    // Text
    ctx.font(Fonts::Norm, 28);
    ctx.fillStyle(Colours::Red);
    ctx.fillText("L", 249.2, 41.0);
    ctx.fillText("R", 249.5, 181.0);
    ctx.fillText("pan", 254.4, 224.0);
    ctx.fillStyle(Colours::Blue);
    ctx.fillText("f", 126.0, 224.0);
    ctx.fillStyle(Colours::Green);
    ctx.fillText("x", 133.0, 224.0);
    ctx.fillStyle(Colours::White);
    ctx.fillText("&", 147.0, 224.0);
    ctx.fillStyle(Colours::Yellow);
    ctx.fillText("dry", 166.0, 224.0);
    ctx.fillStyle(Colours::White);
    ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Baseline);
    ctx.fillText("in", input_x, 224.0);
  }

  void Screen::draw_coloured_circle(Canvas& ctx, Point p, Color cl, float value)
  {
    constexpr float radius = 26;
    constexpr float inner_r = 10;
    if (value > 0.f) {
      ctx.beginPath();
      ctx.moveTo(p.x, p.y - inner_r);
      ctx.lineTo(p.x, p.y - radius);
      ctx.arc(p, radius, -M_PI_2, -M_PI_2 + 2 * M_PI * value);
      ctx.lineTo(p.x + inner_r * std::cos(M_PI_2 - 2 * M_PI * value), p.y - inner_r * std::sin(M_PI_2 - 2 * M_PI * value));
      ctx.arc(p, inner_r, -M_PI_2 + 2 * M_PI * value, -M_PI_2, true);
      ctx.closePath();
      ctx.fill(cl);
    }
    ctx.beginPath();
    ctx.circle(p, radius);
    ctx.stroke(Colours::White);
  }

  void Screen::draw_radial_lines(Canvas& ctx, float pan_float)
  {
    constexpr Point center = {245 + 3.5, 99 + 5};
    constexpr float inner_radius = 35;
    constexpr int num_of_lines = 17;
    constexpr float outer_length = 2;
    constexpr float middle_length = 10;
    constexpr float lines_to_marker_pad = 13;
    constexpr float marker_radius = 3;
    constexpr float middle_marker_pad = 5;
    ctx.lineWidth(4.f);

    float angle_step = M_PI / (num_of_lines - 1);
    float line_length = 0; 
    ctx.group([&] {
      ctx.rotateAround(center, -M_PI_2);
      for (int i = 0; i < num_of_lines; i++) {
        float i_rel = (float)i/(num_of_lines - 1);
        if (i <= num_of_lines / 2) {
          line_length = 2 * i * middle_length / num_of_lines + (1 -  2 * (float)i /num_of_lines) * outer_length;
        } else {
          line_length = 2 * (1 - (float)i /num_of_lines) * middle_length + (2 * (float)i / num_of_lines - 1) * outer_length;
        }
        ctx.beginPath();
        if (i == (num_of_lines - 1) / 2) {ctx.moveTo(center.x + inner_radius - middle_marker_pad, center.y);}
        else {ctx.moveTo(center.x + inner_radius, center.y); }
        ctx.lineTo(center.x + inner_radius + line_length, center.y);
        ctx.rotateAround(center, angle_step);
        bool cl_mix = pan_float > 0.5 ? ((i_rel >= 0.5) && (i_rel <= pan_float)) : ((i_rel <= 0.5) && (i_rel >= pan_float));
        Color cl = cl_mix ? Colours::Red : Colours::White;
        ctx.stroke(cl);
      }
    });
    // Dot
    ctx.group([&] {
      ctx.rotateAround(center, M_PI * (pan_float - 0.5));
      if (pan_float < 0.5) {
        line_length = 2 * pan_float * middle_length + (1 -  2 * pan_float) * outer_length;
      } else {
        line_length = 2 * (1 - pan_float) * middle_length + (2 * pan_float - 1) * outer_length;
      }
      ctx.beginPath();
      ctx.circle({center.x + inner_radius + line_length + lines_to_marker_pad, center.y}, marker_radius);
      ctx.stroke(Colours::Red);
      ctx.fill(Colours::Red);
    });
  }

  void Screen::draw_background(Canvas &ctx)
  {
    // Rounded rectangle around the three circles
    ctx.beginPath();
    ctx.roundedRect({(115.7 + 96.7)/2, 15}, {126, 178}, 10);
    ctx.lineWidth(3.f);
    ctx.stroke(Colours::Gray50);

    // Blocking squares
    ctx.beginPath();
    ctx.moveTo(96.7, 37.0);
    ctx.lineTo(115.7, 37.0);
    ctx.lineTo(115.7, 173.0);
    ctx.lineTo(96.7, 173.0);
    ctx.lineTo(96.7, 37.0);
    ctx.closePath();
    ctx.fill(Colours::Black);

    ctx.fillStyle(Colours::Black);
    ctx.beginPath();
    ctx.moveTo(220.7, 84.0);
    ctx.lineTo(242.7, 84.0);
    ctx.lineTo(242.7, 126.0);
    ctx.lineTo(220.7, 126.0);
    ctx.closePath();
    ctx.fill();

    // White lines
    // layer1/Clip Group/Path
    ctx.lineWidth(4.f);
    ctx.beginPath();
    ctx.moveTo(52.7, 104.0);
    ctx.lineTo(167.0, 104.0);
    ctx.strokeStyle(Colours::White);
    ctx.lineJoin(LineJoin::ROUND);
    ctx.stroke();

    // layer1/Clip Group/Path
    ctx.beginPath();
    ctx.moveTo(64.7, 104.0);
    ctx.lineTo(84.9, 104.0);
    ctx.bezierCurveTo(88.8, 104.0, 91.9, 100.9, 91.9, 97.0);
    ctx.lineTo(91.9, 59.0);
    ctx.bezierCurveTo(91.9, 55.1, 95.0, 52.0, 98.9, 52.0);
    ctx.lineTo(119.7, 52.0);
    ctx.stroke();

    // layer1/Clip Group/Path
    ctx.beginPath();
    ctx.moveTo(51.7, 104.0);
    ctx.lineTo(84.9, 104.0);
    ctx.bezierCurveTo(88.8, 104.0, 91.9, 107.1, 91.9, 111.0);
    ctx.lineTo(91.9, 149.0);
    ctx.bezierCurveTo(91.9, 152.9, 95.0, 156.0, 98.9, 156.0);
    ctx.lineTo(119.7, 156.0);
    ctx.stroke();
  
    // layer1/Clip Group/Path
    ctx.beginPath();
    ctx.moveTo(216.4, 104.0);
    ctx.lineTo(252.3, 104.0);
    ctx.lineWidth(4.f);
    ctx.stroke(Colours::Gray50);

    ctx.beginPath();
    ctx.arc({247, 104.0}, 8.0, -M_PI_2, M_PI_2, false);
    ctx.closePath();
    ctx.fill(Colours::Gray50);    

    // layer1/Clip Group/Path
    ctx.beginPath();
    ctx.moveTo(247.7, 118.0);
    ctx.bezierCurveTo(255.4, 118.0, 261.7, 111.7, 261.7, 104.0);
    ctx.bezierCurveTo(261.7, 96.3, 255.4, 90.0, 247.7, 90.0);
    ctx.lineWidth(4.0f);
    ctx.strokeStyle(Colours::Gray50);
    ctx.lineCap(LineCap::SQUARE);
    ctx.stroke();
    

    // layer1/Clip Group/Path
    ctx.beginPath();
    ctx.moveTo(247.7, 126.0);
    ctx.bezierCurveTo(259.9, 126.0, 269.7, 116.2, 269.7, 104.0);
    ctx.bezierCurveTo(269.7, 91.8, 259.9, 82.0, 247.7, 82.0);
    ctx.stroke();

    // layer1/Clip Group/Path
    ctx.beginPath();
    ctx.moveTo(247.7, 134.0);
    ctx.bezierCurveTo(264.3, 134.0, 277.7, 120.6, 277.7, 104.0);
    ctx.bezierCurveTo(277.7, 87.4, 264.3, 74.0, 247.7, 74.0);
    ctx.stroke();


    
      

  }

}
