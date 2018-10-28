#include "dxotto.hpp"
#include <fstream>
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
          std::ifstream patchlist(global::data_dir / "dx7patches_list.txt");
          std::string path;
          std::string correct_path;
          int idx = 0;
          while(std::getline(patchlist,path)) {
              if (idx==engine.props.preset) {
                  correct_path = path;
              }
             idx++;
          }
          //Read appropriate JSON file
          //util::JsonFile patch{global::data_dir / "dx7patches/analog-2.json"};
          util::JsonFile patch{global::data_dir / "dx7patches" / correct_path};
          patch.read();
          engine.props.algN.set(patch.data()["algorithm"]);
          engine.props.feedback.set(patch.data()["feedback"]);

          engine.props.opRateScale_0.set(patch.data()["operators"][0]["keyboardRateScaling"]);
          engine.props.opRateScale_1.set(patch.data()["operators"][1]["keyboardRateScaling"]);
          engine.props.opRateScale_2.set(patch.data()["operators"][2]["keyboardRateScaling"]);
          engine.props.opRateScale_3.set(patch.data()["operators"][3]["keyboardRateScaling"]);
          engine.props.opRateScale_4.set(patch.data()["operators"][4]["keyboardRateScaling"]);
          engine.props.opRateScale_5.set(patch.data()["operators"][5]["keyboardRateScaling"]);

          engine.props.opDetune_0.set(patch.data()["operators"][0]["detune"]);
          engine.props.opDetune_1.set(patch.data()["operators"][1]["detune"]);
          engine.props.opDetune_2.set(patch.data()["operators"][2]["detune"]);
          engine.props.opDetune_3.set(patch.data()["operators"][3]["detune"]);
          engine.props.opDetune_4.set(patch.data()["operators"][4]["detune"]);
          engine.props.opDetune_5.set(patch.data()["operators"][5]["detune"]);

          engine.props.opFreq_0.set(patch.data()["operators"][0]["frequency"]);
          engine.props.opFreq_1.set(patch.data()["operators"][1]["frequency"]);
          engine.props.opFreq_2.set(patch.data()["operators"][2]["frequency"]);
          engine.props.opFreq_3.set(patch.data()["operators"][3]["frequency"]);
          engine.props.opFreq_4.set(patch.data()["operators"][4]["frequency"]);
          engine.props.opFreq_5.set(patch.data()["operators"][5]["frequency"]);

          engine.props.opMode_0.set( (patch.data()["operators"][0]["oscillatorMode"]=="fixed") ? 1 : 0);
          engine.props.opMode_1.set( (patch.data()["operators"][1]["oscillatorMode"]=="fixed") ? 1 : 0);
          engine.props.opMode_2.set( (patch.data()["operators"][2]["oscillatorMode"]=="fixed") ? 1 : 0);
          engine.props.opMode_3.set( (patch.data()["operators"][3]["oscillatorMode"]=="fixed") ? 1 : 0);
          engine.props.opMode_4.set( (patch.data()["operators"][4]["oscillatorMode"]=="fixed") ? 1 : 0);
          engine.props.opMode_5.set( (patch.data()["operators"][5]["oscillatorMode"]=="fixed") ? 1 : 0);

          engine.props.ampModSens_0.set(patch.data()["operators"][0]["amSensitivity"]);
          engine.props.ampModSens_1.set(patch.data()["operators"][1]["amSensitivity"]);
          engine.props.ampModSens_2.set(patch.data()["operators"][2]["amSensitivity"]);
          engine.props.ampModSens_3.set(patch.data()["operators"][3]["amSensitivity"]);
          engine.props.ampModSens_4.set(patch.data()["operators"][4]["amSensitivity"]);
          engine.props.ampModSens_5.set(patch.data()["operators"][5]["amSensitivity"]);

          engine.props.keyVelSens_0.set(patch.data()["operators"][0]["keyVelocitySensitivity"]);
          engine.props.keyVelSens_1.set(patch.data()["operators"][1]["keyVelocitySensitivity"]);
          engine.props.keyVelSens_2.set(patch.data()["operators"][2]["keyVelocitySensitivity"]);
          engine.props.keyVelSens_3.set(patch.data()["operators"][3]["keyVelocitySensitivity"]);
          engine.props.keyVelSens_4.set(patch.data()["operators"][4]["keyVelocitySensitivity"]);
          engine.props.keyVelSens_5.set(patch.data()["operators"][5]["keyVelocitySensitivity"]);

          engine.props.outLevel_0.set(patch.data()["operators"][0]["outputLevel"]);
          engine.props.outLevel_1.set(patch.data()["operators"][1]["outputLevel"]);
          engine.props.outLevel_2.set(patch.data()["operators"][2]["outputLevel"]);
          engine.props.outLevel_3.set(patch.data()["operators"][3]["outputLevel"]);
          engine.props.outLevel_4.set(patch.data()["operators"][4]["outputLevel"]);
          engine.props.outLevel_5.set(patch.data()["operators"][5]["outputLevel"]);

          engine.props.egR1_0.set(patch.data()["operators"][0]["eg"]["rate1"]);
          engine.props.egR1_1.set(patch.data()["operators"][1]["eg"]["rate1"]);
          engine.props.egR1_2.set(patch.data()["operators"][2]["eg"]["rate1"]);
          engine.props.egR1_3.set(patch.data()["operators"][3]["eg"]["rate1"]);
          engine.props.egR1_4.set(patch.data()["operators"][4]["eg"]["rate1"]);
          engine.props.egR1_5.set(patch.data()["operators"][5]["eg"]["rate1"]);

          engine.props.egR2_0.set(patch.data()["operators"][0]["eg"]["rate2"]);
          engine.props.egR2_1.set(patch.data()["operators"][1]["eg"]["rate2"]);
          engine.props.egR2_2.set(patch.data()["operators"][2]["eg"]["rate2"]);
          engine.props.egR2_3.set(patch.data()["operators"][3]["eg"]["rate2"]);
          engine.props.egR2_4.set(patch.data()["operators"][4]["eg"]["rate2"]);
          engine.props.egR2_5.set(patch.data()["operators"][5]["eg"]["rate2"]);

          engine.props.egR3_0.set(patch.data()["operators"][0]["eg"]["rate3"]);
          engine.props.egR3_1.set(patch.data()["operators"][1]["eg"]["rate3"]);
          engine.props.egR3_2.set(patch.data()["operators"][2]["eg"]["rate3"]);
          engine.props.egR3_3.set(patch.data()["operators"][3]["eg"]["rate3"]);
          engine.props.egR3_4.set(patch.data()["operators"][4]["eg"]["rate3"]);
          engine.props.egR3_5.set(patch.data()["operators"][5]["eg"]["rate3"]);

          engine.props.egR4_0.set(patch.data()["operators"][0]["eg"]["rate4"]);
          engine.props.egR4_1.set(patch.data()["operators"][1]["eg"]["rate4"]);
          engine.props.egR4_2.set(patch.data()["operators"][2]["eg"]["rate4"]);
          engine.props.egR4_3.set(patch.data()["operators"][3]["eg"]["rate4"]);
          engine.props.egR4_4.set(patch.data()["operators"][4]["eg"]["rate4"]);
          engine.props.egR4_5.set(patch.data()["operators"][5]["eg"]["rate4"]);

          engine.props.egL1_0.set(patch.data()["operators"][0]["eg"]["level1"]);
          engine.props.egL1_1.set(patch.data()["operators"][1]["eg"]["level1"]);
          engine.props.egL1_2.set(patch.data()["operators"][2]["eg"]["level1"]);
          engine.props.egL1_3.set(patch.data()["operators"][3]["eg"]["level1"]);
          engine.props.egL1_4.set(patch.data()["operators"][4]["eg"]["level1"]);
          engine.props.egL1_5.set(patch.data()["operators"][5]["eg"]["level1"]);

          engine.props.egL2_0.set(patch.data()["operators"][0]["eg"]["level2"]);
          engine.props.egL2_1.set(patch.data()["operators"][1]["eg"]["level2"]);
          engine.props.egL2_2.set(patch.data()["operators"][2]["eg"]["level2"]);
          engine.props.egL2_3.set(patch.data()["operators"][3]["eg"]["level2"]);
          engine.props.egL2_4.set(patch.data()["operators"][4]["eg"]["level2"]);
          engine.props.egL2_5.set(patch.data()["operators"][5]["eg"]["level2"]);

          engine.props.egL3_0.set(patch.data()["operators"][0]["eg"]["level3"]);
          engine.props.egL3_1.set(patch.data()["operators"][1]["eg"]["level3"]);
          engine.props.egL3_2.set(patch.data()["operators"][2]["eg"]["level3"]);
          engine.props.egL3_3.set(patch.data()["operators"][3]["eg"]["level3"]);
          engine.props.egL3_4.set(patch.data()["operators"][4]["eg"]["level3"]);
          engine.props.egL3_5.set(patch.data()["operators"][5]["eg"]["level3"]);

          engine.props.egL4_0.set(patch.data()["operators"][0]["eg"]["level4"]);
          engine.props.egL4_1.set(patch.data()["operators"][1]["eg"]["level4"]);
          engine.props.egL4_2.set(patch.data()["operators"][2]["eg"]["level4"]);
          engine.props.egL4_3.set(patch.data()["operators"][3]["eg"]["level4"]);
          engine.props.egL4_4.set(patch.data()["operators"][4]["eg"]["level4"]);
          engine.props.egL4_5.set(patch.data()["operators"][5]["eg"]["level4"]);

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
