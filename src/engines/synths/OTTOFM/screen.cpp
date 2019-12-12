#include "screen.hpp"

#include "core/ui/vector_graphics.hpp"

namespace otto::engines::ottofm {

  using namespace itc;

  using namespace ui;
  using namespace ui::vg;
  using namespace input;

  void OttofmScreen::draw(ui::vg::Canvas& ctx) 
  {
    using namespace ui::vg;

    shift = services::Controller::current().is_pressed(Key::shift);
    ctx.font(Fonts::Norm, 35);

    if (shift)
      draw_with_shift(ctx);
    else
      draw_no_shift(ctx);

    draw_envelope(ctx);
    draw_operators(ctx);
  }

  void OttofmScreen::draw_no_shift(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;
    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad_left = 90;
    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;
    // Ratio and Detune
    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Ratio", {x_pad_left, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fractions[ops.at(cur_op).ratio_idx].to_string(),
                 {width - x_pad, y_pad});

    // FM Amount
    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("FM", {x_pad_left, y_pad + 3 * space});

    ctx.lineWidth(6.f);
    constexpr float x_left = width - 6 * x_pad;
    constexpr float x_right = width - x_pad;
    constexpr float y_low = y_pad + 3 * space + 10;
    constexpr float y_high = y_pad + 3 * space - 10;
    ctx.beginPath();
    ctx.moveTo(x_left, y_low);
    ctx.lineTo(x_right, y_high);
    ctx.lineTo(x_right, y_low);
    ctx.closePath();
    ctx.stroke(Colours::Red);

    float x_middle = x_left * (1 - fm_amount) + x_right * fm_amount;
    float y_middle = y_low * (1 - fm_amount) + y_high * fm_amount;

    ctx.beginPath();
    ctx.moveTo(x_left, y_low);
    ctx.lineTo(x_middle, y_middle);
    ctx.lineTo(x_middle, y_low);
    ctx.closePath();
    ctx.fill(Colours::Red);

    // Operator level
    // vertical line
    float line_top = y_pad + 0.7 * space;
    float line_bot = line_top + 1.5 * space;
    float line_x = 3.5 * x_pad;
    float bar_width = 20.f;
    ctx.beginPath();
    ctx.moveTo(line_x, line_top);
    ctx.lineTo(line_x, line_bot);
    ctx.lineWidth(6.0);
    ctx.lineCap(LineCap::ROUND);
    ctx.closePath();
    // shift not held
    ctx.stroke(Colours::Green);
    // Horizontal line
    ctx.beginPath();
    ctx.moveTo(
      line_x - 0.5 * bar_width,
      line_bot - ops.at(cur_op).out_level * (line_bot - line_top));
    ctx.lineTo(
      line_x + 0.5 * bar_width,
      line_bot - ops.at(cur_op).out_level * (line_bot - line_top));
    ctx.lineWidth(6.0);
    ctx.lineCap(LineCap::ROUND);
    ctx.closePath();
    // shift not held
    ctx.stroke(Colours::Green);
  }

  void OttofmScreen::draw_with_shift(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;
    ctx.font(Fonts::Norm, 35);
    constexpr float x_pad_left = 90;
    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;
    // Ratio and Detune
    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Detune", {x_pad_left, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:2}", ops.at(cur_op).detune),
                 {width - x_pad, y_pad});

    // Operator level
    // vertical line
    float line_top = y_pad + 0.7 * space;
    float line_bot = line_top + 1.5 * space;
    float line_x = 3.5 * x_pad;
    float bar_width = 20.f;
    ctx.beginPath();
    ctx.moveTo(line_x, line_top);
    ctx.lineTo(line_x, line_bot);
    ctx.lineWidth(6.0);
    ctx.lineCap(LineCap::ROUND);
    ctx.closePath();
    // shift is held
    ctx.stroke(Colours::Gray60);
    // Horizontal line
    ctx.beginPath();
    ctx.moveTo(
      line_x - 0.5 * bar_width,
      line_bot - ops.at(cur_op).out_level * (line_bot - line_top));
    ctx.lineTo(
      line_x + 0.5 * bar_width,
      line_bot - ops.at(cur_op).out_level * (line_bot - line_top));
    ctx.lineWidth(6.0);
    ctx.lineCap(LineCap::ROUND);
    ctx.closePath();
    // shift not held
    ctx.stroke(Colours::Gray60);

    // Algorithm
    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Algorithm", {x_pad_left, y_pad + 3 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", algorithm_idx), {width - x_pad, y_pad + 3 * space});
  }

  void OttofmScreen::draw_envelope(Canvas& ctx)
  {
    constexpr float x_pad_left = 130;
    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;

    // Operator envelope
    constexpr auto b =
      vg::Box{x_pad_left, y_pad + 0.7 * space, width - x_pad_left - x_pad, space * 1.5};
    const float spacing = 10.f;
    const float max_width = (b.width - 3 * spacing) / 3.f;

    bool is_modulator = algorithms[algorithm_idx].modulator_flags[cur_op];

    if (is_modulator) {
      float aw, dw, sh, rw;
      aw = max_width * ops.at(cur_op).attack;
      dw = max_width * std::max(0.f, (ops.at(cur_op).decay_release *
                                      (1 - ops.at(cur_op).suspos)));
      sh = b.height * ops.at(cur_op).suspos;
      rw = max_width * std::max(0.f, (ops.at(cur_op).decay_release *
                                      ops.at(cur_op).suspos));

      ctx.lineWidth(6.f);
      // Drawing. Colors depend on whether or not shift is held
      // Attack
      ctx.beginPath();
      ctx.moveTo(b.x, b.y + b.height);
      ctx.lineTo(b.x + aw, b.y);
      ctx.lineTo(b.x + aw, b.y + b.height);
      ctx.closePath();
      // Choose colour
      if (shift) {
        ctx.stroke(Colours::Gray60);
        ctx.fill(Colours::Gray60);
      } else {
        ctx.stroke(Colours::Yellow);
        ctx.fill(Colours::Yellow);
      }

      // Decay
      ctx.beginPath();
      ctx.moveTo(b.x + aw + spacing, b.y + b.height);
      ctx.lineTo(b.x + aw + spacing, b.y);
      ctx.lineTo(b.x + aw + spacing + dw, b.y + b.height - sh);
      ctx.lineTo(b.x + aw + spacing + dw, b.y + b.height);
      ctx.closePath();
      if (!shift) {
        ctx.stroke(Colours::Gray60);
        ctx.fill(Colours::Gray60);
      } else {
        ctx.stroke(Colours::Yellow);
        ctx.fill(Colours::Yellow);
      }

      // Sustain
      ctx.beginPath();
      ctx.moveTo(b.x + aw + spacing + dw + spacing, b.y + b.height - sh);
      ctx.lineTo(b.x + b.width - spacing - rw, b.y + b.height - sh);
      ctx.lineTo(b.x + b.width - spacing - rw, b.y + b.height);
      ctx.lineTo(b.x + aw + spacing + dw + spacing, b.y + b.height);
      ctx.closePath();
      if (shift) {
        ctx.stroke(Colours::Green);
        ctx.fill(Colours::Green);
      } else {
        ctx.stroke(Colours::Gray60);
        ctx.fill(Colours::Gray60);
      }

      // Release
      ctx.beginPath();
      ctx.moveTo(b.x + b.width - rw, b.y + b.height);
      ctx.lineTo(b.x + b.width - rw, b.y + b.height - sh);
      ctx.lineTo(b.x + b.width, b.y + b.height);
      ctx.closePath();
      if (shift) {
        ctx.stroke(Colours::Yellow);
        ctx.fill(Colours::Yellow);
      } else {
        ctx.stroke(Colours::Gray60);
        ctx.fill(Colours::Gray60);
      }
    } else {
      // Feedback
      ctx.beginPath();
      if (!shift)
        ctx.fillStyle(Colours::Yellow);
      else
        ctx.fillStyle(Colours::Gray60);

      ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
      ctx.fillText("Self-mod", {x_pad_left + 10, y_pad + 100});

      float circ_x = 1.6 * x_pad_left;
      float circ_y = 2.3 * y_pad;
      int rad = 15;


      ctx.beginPath();
      ctx.moveTo(circ_x + rad, circ_y);
      ctx.lineTo(circ_x + rad + 20, circ_y);
      ctx.arc(circ_x, circ_y, rad + 20, 0, -M_PI, true);
      ctx.stroke(Colours::Gray60);

      ctx.beginPath();
      ctx.arc(circ_x, circ_y, rad + 20,
              (-1 + ops.at(cur_op).feedback) * M_PI, -M_PI, true);
      ctx.lineTo(circ_x - rad, circ_y);
      if (!shift)
        ctx.stroke(Colours::Yellow);
      else
        ctx.stroke(Colours::White);

      // Inner circle
      ctx.beginPath();
      ctx.circle({circ_x, circ_y}, rad);
      ctx.stroke(Colours::Gray60);
    }
  }

  void OttofmScreen::draw_operators(ui::vg::Canvas& ctx)
  {
    ctx.lineWidth(6.f);
    constexpr float x_pad = 35;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;

    // Draw lines between operators
    for (auto&& line : algorithms[algorithm_idx].operator_lines) {
      int x_middle = x_pad + 12;
      int mid_to_side = 15;
      int horizontal_length = 13;

      if (line.side == Drawside::left) {
        int x_close = x_middle - mid_to_side;
        int x_far = x_close - horizontal_length;

        int y_start = y_pad + (3 - line.start) * space;
        int y_end = y_pad + (3 - line.end) * space;

        ctx.beginPath();
        ctx.moveTo(x_close, y_start);
        ctx.lineTo(x_far, y_start);
        ctx.lineTo(x_far, y_end);
        ctx.lineTo(x_close, y_end);
        ctx.stroke(Colours::White);
      } else if (line.side == Drawside::right) {
        int x_close = x_middle + mid_to_side;
        int x_far = x_close + horizontal_length;

        int y_start = y_pad + (3 - line.start) * space;
        int y_end = y_pad + (3 - line.end) * space;

        ctx.beginPath();
        ctx.moveTo(x_close, y_start);
        ctx.lineTo(x_far, y_start);
        ctx.lineTo(x_far, y_end);
        ctx.lineTo(x_close, y_end);
        ctx.stroke(Colours::White);
      } else {
        int y_start = y_pad + (3 - line.start) * space + 16;
        int y_end = y_pad + (3 - line.end) * space - 16;

        ctx.beginPath();
        ctx.moveTo(x_middle, y_start);
        ctx.lineTo(x_middle, y_end);
        ctx.lineTo(x_middle, y_end);
        ctx.lineTo(x_middle, y_end);
        ctx.stroke(Colours::White);
      }
    }

    // draw operators
    for (int i = 0; i < 4; i++) {
      ctx.beginPath();
      if (algorithms[algorithm_idx].modulator_flags[i]) { // draw modulator
        ctx.rect({x_pad, y_pad + (3 - i) * space - 13}, {25, 25});
      } else { // draw carrier
        ctx.circle({x_pad + 12, y_pad + (3 - i) * space}, 15);
      }
      ctx.closePath();
      // Choose colour
      if (i == 3) {
        if (i == cur_op) {
          ctx.fill(Colours::White);
          ctx.stroke(Colours::Blue.mix(Colours::White, 0.5));
        } else {
          ctx.stroke(Colours::Blue);
        }
      } else if (i == 2) {
        if (i == cur_op) {
          ctx.fill(Colours::White);
          ctx.stroke(Colours::Green.mix(Colours::White, 0.4));
        } else {
          ctx.stroke(Colours::Green);
        }
      } else if (i == 1) {
        if (i == cur_op) {
          ctx.fill(Colours::White);
          ctx.stroke(Colours::Yellow.mix(Colours::White, 0.4));
        } else {
          ctx.stroke(Colours::Yellow);
        }
      } else if (i == 0) {
        if (i == cur_op) {
          ctx.fill(Colours::White);
          ctx.stroke(Colours::Red.mix(Colours::White, 0.4));
        } else {
          ctx.stroke(Colours::Red);
        }
      }

      // Draw activity levels
      float op_level = shared_activity[i];
      ctx.beginPath();
      if (algorithms[algorithm_idx].modulator_flags[i]) {
        ctx.rect(
          {x_pad + 12.5f * (1 - op_level), y_pad + (3 - i) * space - 13 + 12.5f * (1 - op_level)},
          {25 * op_level, 25 * op_level});
      } else { // draw carrier
        ctx.circle({x_pad + 12, y_pad + (3 - i) * space}, 15 * op_level);
      }
      // Choose colour
      Color cl;
      switch (i) {
      case 3: cl = Colours::Blue; break;
      case 2: cl = Colours::Green; break;
      case 1: cl = Colours::Yellow; break;
      case 0: cl = Colours::Red; break;
      default: break;
      }
      if (cur_op == i) cl = cl.mix(Colours::White, 0.5);
      ctx.fill(cl);
    }

    // draw arrowheads
    for (auto&& line : algorithms[algorithm_idx].operator_lines) {
      int x_middle = x_pad + 12;
      int mid_to_side = 15;
      int side_length = 5;



      if (line.side == Drawside::left) {
        int x = x_middle - mid_to_side;
        int y = y_pad + (3 - line.end) * space;

        ctx.group([&] {
          ctx.lineWidth(4.f);
          ctx.beginPath();
          ctx.moveTo(x, y);
          ctx.lineTo(x - side_length, y - side_length);
          ctx.lineTo(x - side_length, y + side_length);
          ctx.closePath();
          ctx.stroke(Colours::White);
          ctx.fill(Colours::White);
        });
      } else if (line.side == Drawside::right) {
        int x = x_middle + mid_to_side;
        int y = y_pad + (3 - line.end) * space;

        ctx.group([&] {
          ctx.lineWidth(4.f);
          ctx.beginPath();
          ctx.moveTo(x, y);
          ctx.lineTo(x + side_length, y - side_length);
          ctx.lineTo(x + side_length, y + side_length);
          ctx.closePath();
          ctx.stroke(Colours::White);
          ctx.fill(Colours::White);
        });
      } else {
        int x = x_middle;
        int y = y_pad + (3 - line.end) * space - mid_to_side;

        ctx.group([&] {
          ctx.lineWidth(4.f);
          ctx.beginPath();
          ctx.moveTo(x, y);
          ctx.lineTo(x + side_length, y - side_length);
          ctx.lineTo(x - side_length, y - side_length);
          ctx.closePath();
          ctx.stroke(Colours::White);
          ctx.fill(Colours::White);
        });
      }
    }
  }

} // namespace otto::engines::ottofm
