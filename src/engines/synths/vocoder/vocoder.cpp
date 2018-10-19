#include "vocoder.hpp"

#include "core/globals.hpp"
#include "core/ui/vector_graphics.hpp"

#include "vocoder.faust.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  /*
   * Declarations
   */

  struct VocoderSynthScreen : EngineScreen<VocoderSynth> {
    void draw(Canvas& ctx) override;
    bool keypress(Key key) override;
    void rotary(RotaryEvent e) override;

    using EngineScreen<VocoderSynth>::EngineScreen;

  };

  // VocoderSynth ////////////////////////////////////////////////////////////////

  VocoderSynth::VocoderSynth()
    : SynthEngine("Robot", props, std::make_unique<VocoderSynthScreen>(this)),
      voice_mgr_(props),
      faust_(std::make_unique<FAUSTCLASS>(), props)
  {}

  audio::ProcessData<1> VocoderSynth::process(audio::ProcessData<1> data)
  {
    voice_mgr_.process_before(data.midi_only());
    auto res = faust_.process(data);
    voice_mgr_.process_after(data.midi_only());
    return res;
  }

  /*
   * VocoderSynthScreen
   */

  bool VocoderSynthScreen::keypress(Key key)
  {
    return false;
  }

  void VocoderSynthScreen::rotary(RotaryEvent e)
  {
    switch (e.rotary) {
    case Rotary::Blue:
      engine.props.mix.step(e.clicks);
      break;
    case Rotary::Green:
      engine.props.noise.step(e.clicks);
      break;
    case Rotary::White:
      engine.props.ratio.step(e.clicks);
      break;
    case Rotary::Red:
      engine.props.gateamount.step(e.clicks);
      break;
    }
  }

  void VocoderSynthScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Dry", {x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.mix), {width - x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Sibilance", {x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.noise), {width - x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Ratio", {x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.ratio), {width - x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Gate", {x_pad, y_pad + 3 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.gateamount), {width - x_pad, y_pad + 3 * space});
  }

} // namespace otto::engines
