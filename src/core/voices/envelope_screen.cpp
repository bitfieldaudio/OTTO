#include "core/ui/vector_graphics.hpp"
#include "voice_manager.hpp"
#include "voices_ui.hpp"

namespace otto::core::voices {
  using namespace ui;
  using namespace ui::vg;

  void EnvelopeScreen::action(attack_tag::action, float a) noexcept
  {
    attack = a;
  }
  void EnvelopeScreen::action(decay_tag::action, float d) noexcept
  {
    decay = d;
  }
  void EnvelopeScreen::action(sustain_tag::action, float s) noexcept
  {
    sustain = s;
  }
  void EnvelopeScreen::action(release_tag::action, float r) noexcept
  {
    release = r;
  }

  void EnvelopeScreen::draw(Canvas& ctx)
  {
    constexpr auto b = vg::Box{30.f, 60.f, 260.f, 110.f};
    const float spacing = 10.f;
    const float max_width = (b.width - 3 * spacing) / 3.f;
    const float aw = max_width * attack;
    const float dw = max_width * decay;
    const float sh = b.height * sustain;
    const float rw = max_width * release;

    ctx.lineWidth(6.f);

    const float arc_size = 0.9;

    ctx.beginPath();
    ctx.moveTo(b.x, b.y + b.height + spacing);
    ctx.lineTo(b.x + b.width, b.y + b.height + spacing);
    ctx.stroke(Colours::White);

    ctx.beginPath();
    ctx.moveTo(b.x, b.y + b.height);
    ctx.quadraticCurveTo({b.x + aw * arc_size, b.y + b.height * arc_size}, {b.x + aw, b.y}); // curve
    ctx.lineTo(b.x + aw, b.y + b.height);
    ctx.closePath();
    ctx.stroke(Colours::Blue);
    ctx.fill(Colours::Blue);

    ctx.beginPath();
    ctx.moveTo(b.x + aw + spacing, b.y + b.height);
    ctx.lineTo(b.x + aw + spacing, b.y);
    ctx.quadraticCurveTo({b.x + aw + spacing + dw * (1 - arc_size), b.y + (b.height - sh) * arc_size},
                         {b.x + aw + spacing + dw, b.y + b.height - sh}); // curve
    ctx.lineTo(b.x + aw + spacing + dw, b.y + b.height);
    ctx.closePath();
    ctx.stroke(Colours::Green);
    ctx.fill(Colours::Green);

    ctx.beginPath();
    ctx.moveTo(b.x + aw + spacing + dw + spacing, b.y + b.height - sh);
    ctx.lineTo(b.x + b.width - spacing - rw, b.y + b.height - sh);
    ctx.lineTo(b.x + b.width - spacing - rw, b.y + b.height);
    ctx.lineTo(b.x + aw + spacing + dw + spacing, b.y + b.height);
    ctx.closePath();
    ctx.stroke(Colours::Yellow);
    ctx.fill(Colours::Yellow);

    ctx.beginPath();
    ctx.moveTo(b.x + b.width - rw, b.y + b.height);
    ctx.lineTo(b.x + b.width - rw, b.y + b.height - sh);
    ctx.quadraticCurveTo({b.x + b.width - rw * arc_size, b.y + b.height - sh * (1 - arc_size)},
                         {b.x + b.width, b.y + b.height});
    ctx.closePath();
    ctx.stroke(Colours::Red);
    ctx.fill(Colours::Red);
  }

} // namespace otto::core::voices
