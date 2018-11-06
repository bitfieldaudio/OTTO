#include "core/ui/vector_graphics.hpp"
#include "ottofm.hpp"

#include "services/application.hpp"

#include "ottofm.faust.hpp"
#include "services/ui_manager.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

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
        return fmt::format("{}/{}",numerator,denominator);
    }

  };

  struct Algorithm {
    std::array<bool,4> modulator_flags = {false,false,false,false};

    constexpr Algorithm(std::initializer_list<int> modulator_idx = {}) {
      for(auto&& idx : modulator_idx){
        modulator_flags[idx] = true;
      }
    }
  };
  /*
   * Declarations
   */

  struct OTTOFMSynthScreen : EngineScreen<OTTOFMSynth> {
    void draw(Canvas& ctx) override;
    void drawWithShift(Canvas& ctx);
    void drawNoShift(Canvas& ctx);
    bool keypress(Key key) override;
    void rotary(RotaryEvent e) override;

    bool shift = false;
    int cur_op = 0;

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

    std::array<Algorithm,11> algorithms = {{Algorithm({1,2,3}),
                                            Algorithm({1,2,3}),
                                            Algorithm({1,2,3}),
                                            Algorithm({1,2,3}),
                                            Algorithm({2,3}),
                                            Algorithm({2,3}),
                                            Algorithm({1,2,3}),
                                            Algorithm({1,3}),
                                            Algorithm({3}),
                                            Algorithm({3}),
                                            Algorithm({})}};

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
    case ui::Key::blue_click: cur_op = 0; break;
    case ui::Key::green_click: cur_op = 1; break;
    case ui::Key::white_click: cur_op = 2; break;
    case ui::Key::red_click: cur_op = 3; break;
    default: return false; ;
    }
  }

  void OTTOFMSynthScreen::rotary(RotaryEvent e)
  {
    auto& props = engine.props;
    auto& current = props.operators.at(cur_op);
    switch (e.rotary) {
    case Rotary::Blue:
      if (!shift) {
        current.ratio_idx.step(e.clicks);
        current.ratio.set(float(fractions[current.ratio_idx]));
      } else{
        current.detune.step(e.clicks);
      }
      break;
    case Rotary::Green:
      if (!shift) {
        current.cAtt.step(e.clicks);
        current.mAtt.step(e.clicks);
      } else {
        current.cSus.step(e.clicks);
        current.mSuspos.step(e.clicks);
      }
      break;
    case Rotary::White:
      if (!shift) {
        current.cRel.step(e.clicks);
        current.mDecrel.step(e.clicks);
      } else {
        current.outLev.step(e.clicks);
      }
      break;
    case Rotary::Red:
      if (!shift) {
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

    shift = Application::current().ui_manager->is_pressed(ui::Key::shift);
    ctx.font(Fonts::Norm, 35);

    if(shift)
        drawWithShift(ctx);
    else
        drawNoShift(ctx);



  }

  void OTTOFMSynthScreen::drawNoShift(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;
    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;
    //Ratio and Detune
    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Ratio", {x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fractions[engine.props.operators.at(cur_op).ratio_idx].to_string(), {width - x_pad, y_pad});

    //Attack release. Drawn stuff depends on if cur_op is a modulator or carrier.
    if (algorithms[engine.props.algN].modulator_flags[cur_op]) { //Modulator
      //Attack
      ctx.beginPath();
      ctx.fillStyle(Colours::Green);
      ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
      ctx.fillText("Attack", {x_pad, y_pad + space});

      ctx.beginPath();
      ctx.fillStyle(Colours::Green);
      ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
      ctx.fillText(fmt::format("{:2}",engine.props.operators.at(cur_op).mAtt), {width - x_pad, y_pad + space});

      //Release
      ctx.beginPath();
      ctx.fillStyle(Colours::Yellow);
      ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
      ctx.fillText("Release", {x_pad, y_pad + 2 * space});

      ctx.beginPath();
      ctx.fillStyle(Colours::Yellow);
      ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
      ctx.fillText(fmt::format("{:2}", engine.props.operators.at(cur_op).mDecrel),
                   {width - x_pad, y_pad + 2 * space});
    } else {  //Carrier
      //Attack
      ctx.beginPath();
      ctx.fillStyle(Colours::Green);
      ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
      ctx.fillText("Attack", {x_pad, y_pad + space});

      ctx.beginPath();
      ctx.fillStyle(Colours::Green);
      ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
      ctx.fillText(fmt::format("{}",engine.props.operators.at(cur_op).cAtt), {width - x_pad, y_pad + space});

      //Release
      ctx.beginPath();
      ctx.fillStyle(Colours::Yellow);
      ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
      ctx.fillText("Release", {x_pad, y_pad + 2 * space});

      ctx.beginPath();
      ctx.fillStyle(Colours::Yellow);
      ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
      ctx.fillText(fmt::format("{}", engine.props.operators.at(cur_op).cRel),
                   {width - x_pad, y_pad + 2 * space});

    }

    //FM Amount
    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("FM Amt", {x_pad, y_pad + 3 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", engine.props.fmAmount),
                 {width - x_pad, y_pad + 3 * space});
  }

  void OTTOFMSynthScreen::drawWithShift(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;
    ctx.font(Fonts::Norm, 35);
    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;
    //Ratio and Detune
    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Detune", {x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}",engine.props.operators.at(cur_op).detune), {width - x_pad, y_pad});

    if (algorithms[engine.props.algN].modulator_flags[cur_op]) { //Modulator
      //Sustain
      ctx.beginPath();
      ctx.fillStyle(Colours::Green);
      ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
      ctx.fillText("SusPos", {x_pad, y_pad + space});

      ctx.beginPath();
      ctx.fillStyle(Colours::Green);
      ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
      ctx.fillText(fmt::format("{}",engine.props.operators.at(cur_op).mSuspos), {width - x_pad, y_pad + space});
    } else { //Carrier
      //Sustain
      ctx.beginPath();
      ctx.fillStyle(Colours::Green);
      ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
      ctx.fillText("Sustain", {x_pad, y_pad + space});

      ctx.beginPath();
      ctx.fillStyle(Colours::Green);
      ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
      ctx.fillText(fmt::format("{}",engine.props.operators.at(cur_op).cSus), {width - x_pad, y_pad + space});

    }
    //Operator Level
    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Level", {x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:2}", engine.props.operators.at(cur_op).outLev),
                 {width - x_pad, y_pad + 2 * space});
    //Algorithm
    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Algo", {x_pad, y_pad + 3 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", engine.props.algN),{width - x_pad, y_pad + 3 * space});
  }

} // namespace otto::engines
