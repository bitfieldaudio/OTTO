#include <algorithm>
#include <cmath>
#include "core/ui/vector_graphics.hpp"
#include "testing.t.hpp"
#include "graphics.t.hpp"

TEST_CASE("Test sends screen" * doctest::skip()) {
  otto::test::show_gui([&](otto::nvg::Canvas& ctx){
    using namespace otto::core::ui;
    using namespace otto::core::ui::vg;
    ctx.group([&] {
      // Circles
      constexpr float radius = 26;
      constexpr float inner_r = 10;
      constexpr float x_fx = 119 + 26;
      constexpr float x_dry = 167 + 26;
      constexpr float y_fx1 = 26 + 26;
      constexpr float y_dry = 78 + 26;
      constexpr float y_fx2 = 130 + 26;

      auto draw_coloured_circle = [&](Point p, Color cl, float value){
        ctx.beginPath();
        ctx.moveTo(p.x, p.y - inner_r);
        ctx.lineTo(p.x, p.y - radius);
        ctx.arc(p, radius, -M_PI_2, -M_PI_2 + 2 * M_PI * value);
        ctx.lineTo(p.x + inner_r * std::cos(M_PI_2 - 2 * M_PI * value), p.y - inner_r * std::sin(M_PI_2 - 2 * M_PI * value));
        ctx.arc(p, inner_r, -M_PI_2 + 2 * M_PI * value, -M_PI_2, true);
        ctx.closePath();
        ctx.fill(cl);
        ctx.beginPath();
        ctx.circle(p, radius);
        ctx.stroke(Colours::White);
      };

      float fx1_val = 0.6;
      float fx2_val = 0.2;
      float dry_val = 0.9;
      
      draw_coloured_circle({x_fx, y_fx1}, Colours::Blue, fx1_val);
      draw_coloured_circle({x_fx, y_fx2}, Colours::Green, fx2_val);
      draw_coloured_circle({x_dry, y_dry}, Colours::Red, dry_val);
      
     
      
      // Coloured control indicators
      
      

      // Input
      ctx.beginPath();
      ctx.circle({17 + 18, y_dry}, 18);
      ctx.stroke();
      ctx.fill(Colours::White);

      float pan_float = 0.7;

      // Drawing radial lines
      constexpr Point center = {245 + 3.5, 99 + 5};
      constexpr float inner_radius = 35;
      constexpr int num_of_lines = 17;
      constexpr float outer_length = 2;
      constexpr float middle_length = 14;

      // Visual constants
      ctx.lineWidth(4.f);
      constexpr float mix_localisation = 3.5;
      constexpr float lines_to_marker_pad = 13;
      constexpr float marker_radius = 3;

      float angle_step = M_PI / (num_of_lines - 1);
      float line_length = 0; 
      ctx.group([&] {
        ctx.rotateAround(center, M_PI_2);
        for (int i = 0; i < num_of_lines; i++) {
          if (i <= num_of_lines / 2) {
            line_length = 2 * i * middle_length / num_of_lines + (1 -  2 * (float)i /num_of_lines) * outer_length;
          } else {
            line_length = 2 * (1 - (float)i /num_of_lines) * middle_length + (2 * (float)i / num_of_lines - 1) * outer_length;
          }
          ctx.beginPath();
          ctx.moveTo(center.x + inner_radius, center.y);
          ctx.lineTo(center.x + inner_radius + line_length, center.y);
          ctx.rotateAround(center, -angle_step);
          Color cl = Colours::White.mix(Colours::Yellow, std::max(0.f, 1 - mix_localisation * std::abs((float)i/(num_of_lines - 1) - pan_float)));
          ctx.stroke(cl);
        }
      });
      // Dot
      ctx.group([&] {
        ctx.rotateAround(center, M_PI * (0.5 - pan_float));
        if (pan_float < 0.5) {
          line_length = 2 * pan_float * middle_length + (1 -  2 * pan_float) * outer_length;
        } else {
          line_length = 2 * (1 - pan_float) * middle_length + (2 * pan_float - 1) * outer_length;
        }
        ctx.beginPath();
        ctx.circle({center.x + inner_radius + line_length + lines_to_marker_pad, center.y}, marker_radius);
        ctx.stroke(Colours::Yellow);
        ctx.fill(Colours::Yellow);
      });
      
      // Text
      ctx.font(Fonts::Norm, 24);
      ctx.fillStyle(Colours::White);
      ctx.fillText("L", 249.2, 43.0);
      ctx.fillText("R", 249.5, 179.0);
      ctx.fillText("in", 20.1, 224.0);
      ctx.fillText("fx &", 137.0, 224.0);

      ctx.fillStyle(Color{231, 181, 44});
      ctx.fillText("pan", 284.4, 224.0);

      ctx.fillStyle(Color{195, 53, 46});
      ctx.fillText("dry", 171.0, 224.0);

      
    });
  
  });

}