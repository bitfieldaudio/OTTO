#include "voice_manager.hpp"

#include "core/ui/vector_graphics.hpp"

namespace otto::core::voices {

  struct EnvelopeScreen : ui::Screen {
    EnvelopeScreen(details::EnvelopeProps& props) : props(props) {}

    void draw(ui::vg::Canvas&) override;
    void rotary(ui::RotaryEvent ev) override;

    details::EnvelopeProps& props;
  };

  namespace details {
    std::unique_ptr<ui::Screen> make_envelope_screen(EnvelopeProps& props)
    {
      return std::make_unique<EnvelopeScreen>(props);
    }
  } // namespace details

  using namespace ui;
  using namespace ui::vg;

  void EnvelopeScreen::rotary(RotaryEvent ctx)
  {
    switch (ctx.rotary) {
    case Rotary::blue: props.attack.step(ctx.clicks); break;
    case Rotary::green: props.decay.step(ctx.clicks); break;
    case Rotary::yellow: props.sustain.step(ctx.clicks); break;
    case Rotary::red: props.release.step(ctx.clicks); break;
    }
  }

  void EnvelopeScreen::draw(Canvas& ctx)
  {
    constexpr auto b = vg::Box{30.f, 60.f, 260.f, 110.f};
    const float spacing = 10.f;
    const float max_width = (b.width - 3 * spacing) / 3.f;
    const float aw = max_width * props.attack.normalize();
    const float dw = max_width * props.decay.normalize();
    const float sh = b.height * props.sustain.normalize();
    const float rw = max_width * props.release.normalize();

    ctx.lineWidth(6.f);

    const float arc_size = 0.9;

    ctx.beginPath();
    ctx.moveTo(b.x, b.y + b.height + spacing);
    ctx.lineTo(b.x + b.width, b.y + b.height + spacing);
    ctx.stroke(Colours::White);

    ctx.beginPath();
    ctx.moveTo(b.x, b.y + b.height);
    ctx.quadraticCurveTo({b.x + aw * arc_size, b.y + b.height * arc_size},
                         {b.x + aw, b.y}); // curve
    ctx.lineTo(b.x + aw, b.y + b.height);
    ctx.closePath();
    ctx.stroke(Colours::Blue);
    ctx.fill(Colours::Blue);

    ctx.beginPath();
    ctx.moveTo(b.x + aw + spacing, b.y + b.height);
    ctx.lineTo(b.x + aw + spacing, b.y);
    ctx.quadraticCurveTo(
      {b.x + aw + spacing + dw * (1 - arc_size), b.y + (b.height - sh) * arc_size},
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
