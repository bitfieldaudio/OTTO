#include "screen.hpp"

#include "core/ui/vector_graphics.hpp"
#include "services/application.hpp"
#include "services/ui_manager.hpp"

namespace otto::engines::external {

  using namespace core::ui;
  using namespace core::ui::vg;

  void Screen::action(itc::prop_change<&Props::mode>, ModeEnum m) noexcept
  {
    mode_ = m;
    switch (mode_) {
      case ModeEnum::disabled: {
        mode_str = "DISABLED";
        break;
      }
      case ModeEnum::stereo: {
        mode_str = "STEREO";
        services::Application::current().ui_manager->state.active_channel = +services::ChannelEnum::external_stereo;
        break;
      }
      case ModeEnum::dual_mono: {
        mode_str = "DUAL MONO";
        if (active_send_ == 0) {
          services::Application::current().ui_manager->state.active_channel = +services::ChannelEnum::external_left;
        } else {
          services::Application::current().ui_manager->state.active_channel = +services::ChannelEnum::external_right;
        }
        break;
      }
    }
  }
  void Screen::action(itc::prop_change<&Props::stereo_gain>, float g) noexcept
  {
    stereo_gain_ = g;
  }
  void Screen::action(itc::prop_change<&Props::stereo_balance>, float b) noexcept
  {
    stereo_balance_ = b;
  }
  void Screen::action(itc::prop_change<&Props::left_gain>, float g) noexcept
  {
    left_gain_ = g;
  }
  void Screen::action(itc::prop_change<&Props::right_gain>, float g) noexcept
  {
    right_gain_ = g;
  }
  void Screen::action(itc::prop_change<&Props::active_send>, int a) noexcept
  {
    active_send_ = a;
    if (active_send_ == 0) {
      active_send_str = "ACTIVE SEND: L";
      if (mode_ == 2)
        services::Application::current().ui_manager->state.active_channel = +services::ChannelEnum::external_left;
    } else {
      active_send_str = "ACTIVE SEND: R";
      if (mode_ == 2)
        services::Application::current().ui_manager->state.active_channel = +services::ChannelEnum::external_right;
    }
  }

  void Screen::draw(nvg::Canvas& ctx)
  {
    using namespace ui::vg;
    using namespace core::ui::vg;

    ctx.font(Fonts::Norm, 35);

    // Mode name
    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Top);
    ctx.fillText(fmt::format("{:1}", mode_str), {10, 10});

    draw_jack(ctx, mode_ != +ModeEnum::disabled);
    draw_levels(ctx, mode_);
    if (mode_ == +ModeEnum::stereo) draw_pan(ctx, stereo_balance_);
    if (mode_ == +ModeEnum::dual_mono) draw_active_send(ctx, active_send_);
  }

  void Screen::draw_jack(nvg::Canvas &ctx, bool active) 
  {
    // Angled, non-phallic jack 
    // Sleeve
    ctx.save();
    ctx.transform(0.962963, 0.000000, 0.000000, 1.000000, -976.000000, 0.000000);
    ctx.beginPath();
    ctx.strokeStyle(Colours::Gray50);
    ctx.fillStyle(Colours::Gray50);
    ctx.lineWidth(4.f);
    ctx.rect(1190.080000, 142.000000, 49.846000, 36.000000);
    ctx.fill();
    ctx.stroke();
    ctx.restore();
    
    // Ring
    if (active) {
      ctx.strokeStyle(Colours::Red);
      ctx.fillStyle(Colours::Red);
    } else {
      ctx.strokeStyle(Colours::Gray50);
      ctx.fillStyle(Colours::Gray50);
    }
    ctx.save();
    ctx.transform(1.000000, 0.000000, 0.000000, 1.000000, -1022.000000, 0.000000);
    ctx.beginPath();
    
    ctx.lineWidth(4.f);
    ctx.rect(1248.000000, 142.000000, 22.000000, 36.000000);
    ctx.fill();
    ctx.stroke();
    ctx.restore();
    
    // Tip
    ctx.save();
    ctx.transform(1.000000, 0.000000, 0.000000, 1.000000, -1022.000000, 0.000000);
    ctx.beginPath();
    ctx.moveTo(1280.000000, 178.000000);
    ctx.lineTo(1278.000000, 178.000000);
    ctx.lineTo(1278.000000, 142.000000);
    ctx.lineTo(1280.000000, 142.000000);
    ctx.lineTo(1286.000000, 148.000000);
    ctx.lineTo(1322.000000, 144.000000);
    ctx.lineTo(1332.000000, 154.000000);
    ctx.lineTo(1332.000000, 166.000000);
    ctx.lineTo(1322.000000, 176.000000);
    ctx.lineTo(1286.000000, 172.000000);
    ctx.closePath();
    ctx.fill();
    ctx.stroke();
    ctx.restore();
    
    // Outline
    ctx.save();
    ctx.transform(1.000000, 0.000000, 0.000000, 1.000000, -1022.000000, 0.000000);
    ctx.beginPath();
    ctx.strokeStyle(Colours::Gray50);
    ctx.lineWidth(4.f);
    ctx.moveTo(1132.000000, 130.000000);
    ctx.lineTo(1132.000000, 190.000000);
    ctx.lineTo(1184.000000, 190.000000);
    ctx.lineTo(1184.000000, 130.000000);
    ctx.lineTo(1032.000000, 130.000000);
    ctx.lineTo(1032.000000, 190.000000);
    ctx.lineTo(1052.000000, 190.000000);
    ctx.lineTo(1052.000000, 220.000000);
    ctx.lineTo(1060.000000, 224.000000);
    ctx.lineTo(1104.000000, 224.000000);
    ctx.lineTo(1104.000000, 244.000000);
    ctx.lineTo(1060.000000, 244.000000);
    ctx.lineTo(1060.000000, 224.000000);
    ctx.lineTo(1104.000000, 224.000000);
    ctx.lineTo(1112.000000, 220.000000);
    ctx.lineTo(1112.000000, 190.000000);
    ctx.lineTo(1132.000000, 190.000000);
    ctx.stroke();
    ctx.restore();
    ctx.restore();

  }

  void Screen::draw_levels(nvg::Canvas &ctx, ModeEnum mode)
  {
    

    if (mode == +ModeEnum::dual_mono) 
    {
      float change_width = 60.f;
      ctx.save();
      ctx.transform(1.000000, 0.000000, 0.000000, 1.444440, -1022.000000, -123.111000);

      ctx.beginPath();
      ctx.fillStyle(Colours::Blue);
      ctx.strokeStyle(Colours::Blue);
      ctx.lineWidth(3.22f);
      ctx.moveTo(1270.000000, 178.000000);
      ctx.lineTo(1248.000000, 178.000000);
      ctx.lineTo(1248.000000, 178.f - 3 - change_width * left_gain_);
      ctx.lineTo(1270.000000, 178.f - 3 - (change_width + 3) * left_gain_);
      ctx.lineTo(1270.000000, 178.000000);
      ctx.fill();
      ctx.stroke();
      ctx.restore();
      
      change_width = 80.f;
      ctx.save();
      ctx.transform(1.000000, 0.000000, 0.000000, 1.000000, -1020.000000, -520.000000);
      ctx.beginPath();
      ctx.fillStyle(Colours::Green);
      ctx.strokeStyle(Colours::Green);
      ctx.lineWidth(3.22f);
      ctx.moveTo(1323.000000, 656.000000);
      ctx.lineTo(1330.000000, 663.000000);
      ctx.lineTo(1330.000000, 654.f - 5 - (change_width + 6) * right_gain_);
      ctx.lineTo(1276.000000, 654.f - 5 - change_width * right_gain_);
      ctx.lineTo(1276.000000, 654.000000);
      ctx.lineTo(1281.000000, 654.000000);
      ctx.lineTo(1287.000000, 660.000000);
      ctx.closePath();
      ctx.fill();
      ctx.stroke();
      ctx.restore();
    } 
    else if (mode == +ModeEnum::stereo)
    {
      constexpr float min_width = 5.f;
      constexpr float change_width = 80.f;
      ctx.save();
	    ctx.transform(1.000000, 0.000000, 0.000000, 1.000000, -1020.000000, -260.000000);
      ctx.beginPath();
      ctx.fillStyle(Colours::Blue);
      ctx.strokeStyle(Colours::Blue);
      ctx.lineWidth(4.f);
      ctx.moveTo(1246.000000, 394.000000);
      ctx.lineTo(1281.000000, 394.000000);
      ctx.lineTo(1287.000000, 400.000000);
      ctx.lineTo(1323.000000, 396.000000);
      ctx.lineTo(1330.000000, 403.000000);
      ctx.lineTo(1330.000000, 394.f - min_width - (change_width + 6) * stereo_gain_);
      ctx.lineTo(1246.000000, 394.f - min_width - change_width * stereo_gain_);
      ctx.closePath();
      ctx.fill();
      ctx.stroke();
      ctx.restore();
    }
  }

  void Screen::draw_pan(Canvas& ctx, float pan_float)
  {
    constexpr Point center = {86, 122};
    constexpr float spacing = 11;
    constexpr int num_of_lines = 13;
    constexpr float start_x = center.x - (num_of_lines - 1) * spacing * 0.5f;

    constexpr float outer_length = 6.f;
    constexpr float middle_length = 19.f;
    constexpr float length_step = (middle_length - outer_length) / ((num_of_lines - 1) / 2);

    constexpr float marker_radius = 3;
    constexpr float marker_pad = 13;
    ctx.lineWidth(6.f);

    float line_length = outer_length; 
    for (int i = 0; i < num_of_lines; i++) {
      float i_rel = (float)i/(num_of_lines - 1);
      // Draw line
      ctx.beginPath();
      ctx.moveTo(start_x + spacing * i, center.y);
      ctx.lineTo(start_x + spacing * i, center.y - line_length);
      bool cl_mix = pan_float > 0.5 ? ((i_rel >= 0.5) && (i_rel <= pan_float)) : ((i_rel <= 0.5) && (i_rel >= pan_float));
      Color cl = cl_mix ? Colours::Green : Colours::White;
      ctx.stroke(cl);
      // Increment line length
      if (i < num_of_lines / 2) {
        line_length += length_step;
      } else {
        line_length -= length_step;
      }
    }

    // Dot
    if (pan_float <= 0.5) {
      line_length = 2 * pan_float * middle_length + (1 -  2 * pan_float) * outer_length;
    } else {
      line_length = 2 * (1 - pan_float) * middle_length + (2 * pan_float - 1) * outer_length;
    }
    ctx.beginPath();
    ctx.circle({start_x + spacing * (num_of_lines - 1) * pan_float, center.y - line_length - marker_pad}, marker_radius);
    ctx.stroke(Colours::Green);
    ctx.fill(Colours::Green);

  }

  void Screen::draw_active_send(Canvas& ctx, int active_send)
  {
    ctx.font(Fonts::Norm, 24);
    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Bottom);
    ctx.fillText(fmt::format("{:1}", active_send_str), {15, 130});

    ctx.save();
    ctx.transform(1.000000, 0.000000, 0.000000, -1.444440, -1022.000000, 443.111000);
    ctx.beginPath();
    if (active_send == 0) {
      ctx.fillStyle(Colours::Yellow);
      ctx.strokeStyle(Colours::Yellow);
      ctx.lineWidth(3.22f);
    } else {
      ctx.fillStyle(Colours::Gray50);
      ctx.strokeStyle(Colours::Gray50);
      ctx.lineWidth(4.f);
    }
    ctx.moveTo(1270.000000, 178.000000);
    ctx.lineTo(1248.000000, 178.000000);
    ctx.stroke();
    ctx.restore();

    ctx.save();
    ctx.transform(1.000000, 0.000000, 0.000000, 1.000000, -1360.000000, -520.000000);
    ctx.beginPath();
    if (active_send == 1) {
      ctx.fillStyle(Colours::Yellow);
      ctx.strokeStyle(Colours::Yellow);
      ctx.lineWidth(3.22f);
    } else {
      ctx.fillStyle(Colours::Gray50);
      ctx.strokeStyle(Colours::Gray50);
      ctx.lineWidth(4.f);
    }
    ctx.moveTo(1616.000000, 706.000000);
    ctx.lineTo(1621.000000, 706.000000);
    ctx.lineTo(1627.000000, 700.000000);
    ctx.lineTo(1663.000000, 704.000000);
    ctx.lineTo(1670.000000, 696.000000);
    ctx.stroke();
    ctx.restore();
  }
  


} // namespace otto::engines::external