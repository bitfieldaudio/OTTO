#include "screen.hpp"

#include "core/ui/vector_graphics.hpp"
#include "services/application.hpp"
#include "services/ui_manager.hpp"

namespace otto::engines::external {

  using namespace core::ui;
  using namespace core::ui::vg;

  void Screen::action(itc::prop_change<&Props::mode>, int m) noexcept
  {
    mode_ = m;
    switch (mode_) {
      case 0: {
        mode_str = "Disabled";
        gain_1 = "---";
        gain_1_val = 0;
        gain_2 = "---";
        gain_2_val = 0;
        break;
      }
      case 1: {
        mode_str = "Stereo";
        gain_1 = "Gain";
        gain_1_val = stereo_gain_;
        gain_2 = "Balance";
        gain_2_val = stereo_balance_;
        services::Application::current().ui_manager->state.active_channel = +services::ChannelEnum::external_stereo;
        break;
      }
      case 2: {
        mode_str = "Dual Mono";
        gain_1 = "Left Gain";
        gain_1_val = left_gain_;
        gain_2 = "Right Gain";
        gain_2_val = right_gain_;
        if (active_send_ == 0) services::Application::current().ui_manager->state.active_channel = +services::ChannelEnum::external_left;
        else services::Application::current().ui_manager->state.active_channel = +services::ChannelEnum::external_right;
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
      active_send_str = "Left";
      if (mode_ == 2) services::Application::current().ui_manager->state.active_channel = +services::ChannelEnum::external_left;
    }
    else {
      active_send_str = "Right";
      if (mode_ == 2) services::Application::current().ui_manager->state.active_channel = +services::ChannelEnum::external_right;
    }
  }


  void Screen::draw(nvg::Canvas& ctx)
  {
    using namespace ui::vg;
    using namespace core::ui::vg;

    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText(gain_1, {x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1}", gain_1_val), {width - x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText(gain_2, {x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1}", gain_2_val), {width - x_pad, y_pad + space});

    if (mode_ == 2) {
      ctx.beginPath();
      ctx.fillStyle(Colours::Yellow);
      ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
      ctx.fillText("Active send", {x_pad, y_pad + 2 * space});

      ctx.beginPath();
      ctx.fillStyle(Colours::Yellow);
      ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
      ctx.fillText(active_send_str, {width - x_pad, y_pad + 2 * space});
    }

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Mode", {x_pad, y_pad + 3 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1}", mode_str), {width - x_pad, y_pad + 3 * space});
  }

} // namespace otto::engines::external