#include "dxotto.hpp"

#include "core/globals.hpp"
#include "core/ui/vector_graphics.hpp"

#include "dxotto.faust.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  /*
   * Declarations
   */

  struct DXOTTOSynthScreen : EngineScreen<DXOTTOSynth> {
    void draw(Canvas& ctx) override;
    bool keypress(Key key) override;
    void rotary(RotaryEvent e) override;

    using EngineScreen<DXOTTOSynth>::EngineScreen;

  };

  // DXOTTOSynth ////////////////////////////////////////////////////////////////

  DXOTTOSynth::DXOTTOSynth()
    : SynthEngine("DX7", props, std::make_unique<DXOTTOSynthScreen>(this)),
      voice_mgr_(props),
      faust_(std::make_unique<FAUSTCLASS>(), props)
  {}

  audio::ProcessData<1> DXOTTOSynth::process(audio::ProcessData<1> data)
  {
    voice_mgr_.process_before(data.midi_only());
    auto res = faust_.process(data.midi_only());
    voice_mgr_.process_after(data.midi_only());
    return res;
  }

  /*
   * DXOTTOSynthScreen
   */

  bool DXOTTOSynthScreen::keypress(Key key)
  {
    return false;
  }

  void DXOTTOSynthScreen::rotary(RotaryEvent e)
  {
    switch (e.rotary) {
    case Rotary::Blue:
      {
          engine.props.preset.step(e.clicks);
          //Find name of appropriate JSON file depending on preset variable

          //Read appropriate JSON file
          //std::ifstream i("patches/analog-2.json");
          util::JsonFile patch{global::data_dir / "dx7patches/analog-2.json"};
          patch.read();
          engine.props.algN.set(patch.data()["algorithm"]);
          engine.props.feedback.set(patch.data()["feedback"]);

          engine.props.opRateScale_0.set(patch.data()["operators"][0]["keyboardRateScaling"]);
          engine.props.opRateScale_1.set(patch.data()["operators"][1]["keyboardRateScaling"]);
          engine.props.opRateScale_2.set(patch.data()["operators"][2]["keyboardRateScaling"]);
          engine.props.opRateScale_3.set(patch.data()["operators"][3]["keyboardRateScaling"]);
          engine.props.opRateScale_4.set(patch.data()["operators"][4]["keyboardRateScaling"]);
          engine.props.opRateScale_5.set(patch.data()["operators"][5]["keyboardRateScaling"]);

          break;
      }
    case Rotary::Green:
      engine.props.variable1.step(e.clicks);
      break;
    case Rotary::White:
      engine.props.variable2.step(e.clicks);
      break;
    case Rotary::Red:
      engine.props.variable3.step(e.clicks);
      break;
    }
  }

  void DXOTTOSynthScreen::draw(ui::vg::Canvas& ctx)
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
    ctx.fillText(fmt::format("{:1}", engine.props.preset), {width - x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Algo", {x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1}", engine.props.algN), {width - x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Variable 2", {x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.variable2), {width - x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Variable 3", {x_pad, y_pad + 3 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.variable3), {width - x_pad, y_pad + 3 * space});
  }

} // namespace otto::engines
