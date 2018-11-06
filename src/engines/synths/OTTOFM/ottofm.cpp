#include "core/ui/vector_graphics.hpp"
#include "ottofm.hpp"

#include "services/application.hpp"

#include "ottofm.faust.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  struct Fraction {
    int numerator;
    int denominator;

    Fraction(int n = 1, int d = 1) : numerator(n), denominator(d) {}

    operator float() const
    {
      return float(numerator) / float(denominator);
    }
  };
  /*
   * Declarations
   */

  struct OTTOFMSynthScreen : EngineScreen<OTTOFMSynth> {
    void draw(Canvas& ctx) override;
    bool keypress(Key key) override;
    bool keyrelease(Key key) override;
    void rotary(RotaryEvent e) override;

    std::array<Fraction, 19> fractions = {{{1, 1},
                                           {1, 64},
                                           {1, 32},
                                           {3, 32},
                                           {1, 8},
                                           {5, 16},
                                           {1, 2},
                                           {5, 8},
                                           {2, 1},
                                           {3, 2},
                                           {3, 4},
                                           {1, 4},
                                           {5, 32},
                                           {1, 16},
                                           {5, 8},
                                           {4, 1},
                                           {7, 4},
                                           {7, 16},
                                           {7, 2}}};

    using EngineScreen<OTTOFMSynth>::EngineScreen;
  };

  // DXOTTOSynth ////////////////////////////////////////////////////////////////

  OTTOFMSynth::OTTOFMSynth()
    : SynthEngine("OTTO.FM", props, std::make_unique<OTTOFMSynthScreen>(this)),
      voice_mgr_(props),
      faust_(std::make_unique<FAUSTCLASS>(), props)
  {}

  audio::ProcessData<1> OTTOFMSynth::process(audio::ProcessData<1> data)
  {
    voice_mgr_.process_before(data.midi_only());
    auto res = faust_.process(data.midi_only());
    voice_mgr_.process_after(data.midi_only());
    return res;
  }

  /*
   * OTTOFMSynthScreen
   */
  bool OTTOFMSynthScreen::keypress(Key key)
  {
    switch (key) {
    case ui::Key::blue_click: engine.props.cur_op = 0;
    case ui::Key::green_click: engine.props.cur_op = 1;
    case ui::Key::white_click: engine.props.cur_op = 2;
    case ui::Key::red_click: engine.props.cur_op = 3;
    case ui::Key::shift: engine.props.shift = true;
    default: return false; ;
    }
  }

  bool OTTOFMSynthScreen::keyrelease(Key key)
  {
    switch (key) {
    case ui::Key::shift: engine.props.shift = false;
    default: return false; ;
    }
  }
  void OTTOFMSynthScreen::rotary(RotaryEvent e)
  {
    auto& props = engine.props;
    auto& current = props.operators.at(props.cur_op);
    switch (e.rotary) {
    case Rotary::Blue:
      if (!props.shift) {
        current.ratio_idx.step(e.clicks);
        current.ratio.set(float(fractions[current.ratio_idx]));
      } else{
        current.detune.step(e.clicks);
      }
      break;
    case Rotary::Green:
      if (!props.shift) {
        current.cAtt.step(e.clicks);
        current.mAtt.step(e.clicks);
      } else {
        current.cSus.step(e.clicks);
        current.mSuspos.step(e.clicks);
      }
      break;
    case Rotary::White:
      if (!props.shift) {
        current.cRel.step(e.clicks);
        current.mDecrel.step(e.clicks);
      } else {
        current.outLev.step(e.clicks);
      }
      break;
    case Rotary::Red:
      if (!props.shift) {
        props.fmAmount.step(e.clicks);
      } else {
        props.algN.step(e.clicks);
      }
      break;
    }
  }

  void OTTOFMSynthScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Preset", {x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", engine.props.algN), {width - x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Algo", {x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", engine.props.cur_op), {width - x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Variable 2", {x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", engine.props.operators.at(engine.props.cur_op).ratio_idx),
                 {width - x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Variable 3", {x_pad, y_pad + 3 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.operators.at(engine.props.cur_op).mAtt),
                 {width - x_pad, y_pad + 3 * space});
  }

} // namespace otto::engines
