#include "screen.hpp"

#include "core/ui/vector_graphics.hpp"

#include "util/string_conversions.hpp"

namespace otto::engines::arp {

  using namespace itc;

  using namespace ui;
  using namespace ui::vg;

  void Screen::action(itc::prop_change<&Props::playmode>, Playmode pm) noexcept
  {
    playmode_ = to_string(pm);
  }

  void Screen::action(itc::prop_change<&Props::octavemode>, OctaveMode om) noexcept
  {
    octavemode_ = to_string(om);
  }

  void Screen::action(itc::prop_change<&Props::note_length>, float nl) noexcept
  {
    note_length_ = nl;
  }

  void Screen::action(itc::prop_change<&Props::subdivision>, int s) noexcept
  {
    subdivision_ = s;
  }

  void Screen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    ctx.lineWidth(6);

    ctx.font(Fonts::Norm, 22.0);
    ctx.fillStyle(Colours::Blue);
    ctx.fillText(playmode_, 52, 41.6);

    ctx.fillStyle(Colours::Green);
    ctx.fillText(octavemode_, 200, 41.6);

    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Speed", 52, 61.6);
    //Draw speed dots
    for (int i=0; i<subdivision_; i++) {
      ctx.beginPath();
      ctx.circle(200 + (float)i*13, 61.6 , 5);
      ctx.fill(Colours::Yellow);
    }

    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("NoteLength", 52, 81.6);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1}", note_length_ * 100), 200, 81.6);

    ctx.restore();
  }
} // namespace otto::engines::arp
