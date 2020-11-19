#include "testing.t.hpp"

#include "app/services/config.hpp"
#include "app/services/graphics.hpp"
#include "lib/widget.hpp"

#include <SkFont.h>
#include <SkPath.h>
#include <SkTypeface.h>

#include <iostream>

using namespace otto;
using namespace otto::services;

//////////////
// Stuff we will need!
SkPaint OTTO_paint(void) {
  SkPaint p;
  p.setAntiAlias(true);
  p.setStyle(SkPaint::kStroke_Style);
  p.setStrokeCap(SkPaint::kRound_Cap);
  p.setStrokeJoin(SkPaint::kRound_Join);
  p.setStrokeWidth(6.f);
  return p;
}

namespace Colours {
  constexpr SkColor Blue = SK_ColorBLUE;
  constexpr SkColor Green = SK_ColorGREEN;
  constexpr SkColor Yellow = SK_ColorYELLOW;
  constexpr SkColor Red = SK_ColorRED;
  constexpr SkColor White = SK_ColorWHITE;
}

constexpr std::array<SkColor, 4> operator_colours = {Colours::Red, Colours::Yellow, Colours::Green, Colours::Blue};

// Not the real one, just for testing now
SkColor mix(SkColor a, SkColor b, float m) { return a; }

struct ADSR : otto::graphics::Widget<ADSR> {
  float a, d, s, r;
  ADSR(float a_, float d_, float s_, float r_) : a(a_), d(d_), s(s_), r(r_) {}
  void do_draw(SkCanvas& ctx) {
    //If your are using a different anchor/origin than TopLeft for the coordinate system, translate here
    //otto::graphics::Point diff = bounding_box.get_diff(otto::graphics::Anchors::TopLeft, otto::graphics::Anchors::TopLeft);
    //ctx.translate(diff[0], diff[1]);

    const float width = bounding_box.width();
    const float height = bounding_box.height();
    const float spacing = width / 16.f;
    const float max_width = width / 3.f;
    const float aw = max_width * a;
    const float dw = max_width * d;
    const float sh = height * s;
    const float rw = max_width * r;

    SkPaint paint = OTTO_paint();
    paint.setStyle(SkPaint::kStrokeAndFill_Style);

    const float arc_size = 0.9;

    SkPath p;
    p.moveTo(0, height);
    p.quadTo(aw * arc_size, height * arc_size, aw, 0); // curve
    p.lineTo(aw, height);
    p.close();
    paint.setColor(Colours::Blue);
    ctx.drawPath(p, paint);

    p.reset();
    
    p.moveTo(aw + spacing, height);
    p.lineTo(aw + spacing, 0);
    p.quadTo(aw + spacing + dw * (1 - arc_size), (height - sh) * arc_size,
              aw + spacing + dw, height - sh); // curve
    p.lineTo(aw + spacing + dw, height);
    p.close();
    paint.setColor(Colours::Green);
    ctx.drawPath(p, paint);

    p.reset();

    p.moveTo(aw + spacing + dw + spacing, height - sh);
    p.lineTo(width - spacing - rw, height - sh);
    p.lineTo(width - spacing - rw, height);
    p.lineTo(aw + spacing + dw + spacing, height);
    p.close();
    paint.setColor(Colours::Yellow);
    ctx.drawPath(p, paint);

    p.reset();

    p.moveTo(width - rw, height);
    p.lineTo(width - rw, height - sh);
    p.quadTo(width - rw * arc_size, height - sh * (1 - arc_size),
              width, height);
    p.close();
    paint.setColor(Colours::Red);
    ctx.drawPath(p, paint);
  }
};

////////////////

/// For defining frequency ratios
struct Fraction {
  int numerator;
  int denominator;

  constexpr Fraction(int n = 1, int d = 1) : numerator(n), denominator(d) {}

  operator float() const
  {
    return float(numerator) / float(denominator);
  }

  std::string to_string() const
  {
    if (numerator == 0) return fmt::format("0");
    else return fmt::format("{}/{}", numerator, denominator);
  }
};

/// Used for graphics. Defined here for the Algorithm definitions below.
enum struct Drawside {
  left,
  middle,
  right,
  // Number of sides
  n_sides,
};

struct Operatorline {
  int start = 1;
  int end = 2;
  Drawside side = Drawside::middle;
};

struct Algorithm {
  std::array<bool, 4> modulator_flags = {false, false, false, false};
  std::vector<Operatorline> operator_lines;

  Algorithm(std::initializer_list<int> modulator_idx = {}, std::vector<Operatorline> op_lines = {})
    : operator_lines(op_lines)
  {
    for (auto&& idx : modulator_idx) {
      modulator_flags[idx] = true;
    }
  }
};

const std::array<Fraction, 20> fractions = {{
  {1, 1}, {1, 64}, {1, 32}, {3, 32}, {1, 8}, {5, 16}, {1, 2}, {5, 8},  {2, 1}, {3, 2},
  {3, 4}, {1, 4},  {5, 32}, {1, 16}, {5, 8}, {4, 1},  {7, 4}, {7, 16}, {7, 2}, {0, 1},
}};

/// Defines the algorithms and gives instructions on how to draw them
const std::array<Algorithm, 11> algorithms = {{
  Algorithm({1, 2, 3},
            {
              {3, 2, Drawside::middle},
              {2, 1, Drawside::middle},
              {1, 0, Drawside::middle},
            }),
  Algorithm({1, 2, 3},
            {
              {3, 1, Drawside::left},
              {2, 1, Drawside::right},
              {1, 0, Drawside::middle},
            }),
  Algorithm({1, 2, 3},
            {
              {3, 0, Drawside::left},
              {2, 1, Drawside::middle},
              {1, 0, Drawside::middle},
            }),
  Algorithm({1, 2, 3},
            {
              {3, 2, Drawside::left},
              {3, 1, Drawside::left},
              {2, 0, Drawside::right},
              {1, 0, Drawside::right},
            }),
  Algorithm({2, 3},
            {
              {3, 2, Drawside::middle},
              {2, 1, Drawside::left},
              {2, 0, Drawside::left},
            }),
  Algorithm({2, 3},
            {
              {3, 2, Drawside::middle},
              {2, 1, Drawside::middle},
            }),
  Algorithm({1, 2, 3},
            {
              {3, 0, Drawside::left},
              {2, 0, Drawside::right},
              {1, 0, Drawside::middle},
            }),
  Algorithm({1, 3},
            {
              {3, 2, Drawside::middle},
              {1, 0, Drawside::middle},
            }),
  Algorithm({3},
            {
              {3, 2, Drawside::middle},
              {3, 1, Drawside::right},
              {3, 0, Drawside::left},
            }),
  Algorithm({3},
            {
              {3, 2, Drawside::middle},
            }),
  Algorithm({}),
}};

void draw_operators(SkCanvas& ctx)
{
  SkPaint paint = OTTO_paint();
  constexpr float x_pad = 35;
  constexpr float y_pad = 50;
  float space = (ctx.imageInfo().height() - 2.f * y_pad) / 3.f;

  int algorithm_idx = 4;
  int cur_op = 2;

  // Draw lines between operators
  for (auto&& line : algorithms[algorithm_idx].operator_lines) {
    int x_middle = x_pad + 12;
    int mid_to_side = 15;
    int horizontal_length = 13;

    SkPath path;
    if (line.side == Drawside::left) {
      int x_close = x_middle - mid_to_side;
      int x_far = x_close - horizontal_length;

      int y_start = y_pad + (3 - line.start) * space;
      int y_end = y_pad + (3 - line.end) * space;

      path.moveTo(x_close, y_start);
      path.lineTo(x_far, y_start);
      path.lineTo(x_far, y_end);
      path.lineTo(x_close, y_end);
    } else if (line.side == Drawside::right) {
      int x_close = x_middle + mid_to_side;
      int x_far = x_close + horizontal_length;

      int y_start = y_pad + (3 - line.start) * space;
      int y_end = y_pad + (3 - line.end) * space;

      path.moveTo(x_close, y_start);
      path.lineTo(x_far, y_start);
      path.lineTo(x_far, y_end);
      path.lineTo(x_close, y_end);
    } else {
      int y_start = y_pad + (3 - line.start) * space + 16;
      int y_end = y_pad + (3 - line.end) * space - 16;

      path.moveTo(x_middle, y_start);
      path.lineTo(x_middle, y_end);
      path.lineTo(x_middle, y_end);
      path.lineTo(x_middle, y_end);
    }
    paint.setColor(Colours::White);
    ctx.drawPath(path, paint);
  }

  // draw operators
  SkPaint fillPaint = OTTO_paint();
  SkPaint strokePaint = OTTO_paint();
  fillPaint.setStyle(SkPaint::kFill_Style);
  fillPaint.setColor(Colours::White);
  for (int i = 0; i < 4; i++) {
    // Choose colour
    strokePaint.setColor(mix(operator_colours[i], Colours::White, 0.5*(i == cur_op)));

    if (algorithms[algorithm_idx].modulator_flags[i]) { // draw modulator
      SkRect rect = SkRect::MakeXYWH(x_pad, y_pad + (3 - i) * space - 13, 25, 25);
      if (i == cur_op) ctx.drawRect(rect, fillPaint);
      ctx.drawRect(rect, strokePaint);
    } else { // draw carrier
      if (i == cur_op) ctx.drawCircle(x_pad + 12, y_pad + (3 - i) * space, 15, fillPaint);
      ctx.drawCircle(x_pad + 12, y_pad + (3 - i) * space, 15, strokePaint);
    }
    
    // Draw activity levels
    float op_level = 0.3;
    fillPaint.setColor(mix(operator_colours[i], Colours::White, 0.5*(i == cur_op)));

    if (algorithms[algorithm_idx].modulator_flags[i]) {
      ctx.drawRect(SkRect::MakeXYWH(x_pad + 12.5f * (1 - op_level), 
                                    y_pad + (3 - i) * space - 13 + 12.5f * (1 - op_level),
                                    25 * op_level, 
                                    25 * op_level), fillPaint);
    } else { // draw carrier
      ctx.drawCircle(x_pad + 12, y_pad + (3 - i) * space, 15 * op_level, fillPaint);
    }
  }

  // draw arrowheads
  strokePaint.setStrokeWidth(4.f);
  strokePaint.setColor(Colours::White);
  strokePaint.setStyle(SkPaint::kStrokeAndFill_Style);
  SkPath path;
  for (auto&& line : algorithms[algorithm_idx].operator_lines) {
    int x_middle = x_pad + 12;
    int mid_to_side = 15;
    int side_length = 5;

    if (line.side == Drawside::left) {
      int x = x_middle - mid_to_side;
      int y = y_pad + (3 - line.end) * space;
      path.moveTo(x, y);
      path.lineTo(x - side_length, y - side_length);
      path.lineTo(x - side_length, y + side_length);
      path.close();
    } else if (line.side == Drawside::right) {
      int x = x_middle + mid_to_side;
      int y = y_pad + (3 - line.end) * space;
      path.moveTo(x, y);
      path.lineTo(x + side_length, y - side_length);
      path.lineTo(x + side_length, y + side_length);
      path.close();
    } else {
      int x = x_middle;
      int y = y_pad + (3 - line.end) * space - mid_to_side;
      path.moveTo(x, y);
      path.lineTo(x + side_length, y - side_length);
      path.lineTo(x - side_length, y - side_length);
      path.close();
    }
    ctx.drawPath(path, strokePaint);
  }
}

void draw_envelopes(SkCanvas& ctx) {
  constexpr int active_y = 50;
  constexpr int not_active_y = 0;
  constexpr int y_pad = 40;
  constexpr int x_start = 100;
  constexpr int x_size = 180;
  float step = (ctx.imageInfo().height()  - 2 * y_pad - active_y - not_active_y * 3) / 3.f;

  // op_sizes are Choreograph outputs
  // By always moving them over the same duration, we make sure they always sum to zero.
  // For now:
  std::array<float, 4> op_sizes = {0.f, 0.f, 1.f, 0.f};
 
  int upper_y = y_pad;
  for (int i=0; i<4; i++) {
    int size_y = active_y * op_sizes[i] + not_active_y * (1 - op_sizes[i]);
    ADSR env = {.a = 0.3, .d = 0.3, .s = 0.3, .r = 0.3};
    env.bounding_box.move_to({x_start, upper_y});
    env.bounding_box.resize({x_size, size_y});
    env.draw(ctx);
    upper_y += size_y + step;
  }
  
}

TEST_CASE ("Non-trivial graphics test") {
  auto app = start_app(ConfigManager::make(), Graphics::make());
  SUBCASE ("FM stub") {
    app.service<Graphics>().show([&](SkCanvas& ctx) {
      draw_operators(ctx);
      draw_envelopes(ctx);
    });
    std::this_thread::sleep_for(std::chrono::seconds(20));
    app.stop();
  }
}