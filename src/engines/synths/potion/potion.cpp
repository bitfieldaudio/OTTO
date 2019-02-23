#include "potion.hpp"
#include "services/application.hpp"
#include "services/ui_manager.hpp"

#include "core/ui/vector_graphics.hpp"

//WAV parser by Adam Stark: https://github.com/adamstark/AudioFile
#include "AudioFile.h"



namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  /*
   * Declarations
   */

  struct PotionSynthScreen : EngineScreen<PotionSynth> {

    bool shift = false;

    void draw(Canvas& ctx) override;
    bool keypress(Key key) override;
    void rotary(RotaryEvent e) override;

    using EngineScreen<PotionSynth>::EngineScreen;
  };

  // PotionSynth ////////////////////////////////////////////////////////////////

  PotionSynth::PotionSynth()
    : SynthEngine("Potion", props, std::make_unique<PotionSynthScreen>(this)),
      voice_mgr_(props)
  {

  }

    PotionSynth::Pre::Pre(Props& props) noexcept : PreBase(props)
    {
      ///Load waveforms into vectors.
      for (int i=0; i<4; i++) {
        wavetables[i].load(Application::current().data_dir / "wavetables/wt1.wav");
      }
      //wavetables[1].load(Application::current().data_dir / "wavetables/wt2.wav");
      //wavetables[2].load(Application::current().data_dir / "wavetables/wt3.wav");
      //wavetables[3].load(Application::current().data_dir / "wavetables/wt4.wav");

      ///Normalize wavetables
      ///TODO

      //Fill remap tables
      remap_table.resize(512);
      for (int i=0; i<remap_table.size(); i++) {
        remap_table[i] = (2.f*(float)i/(float)remap_table.size()) / 2.f;
      }

    }

    void PotionSynth::Pre::operator()() noexcept {}


    PotionSynth::Post::Post(Pre& pre) noexcept : PostBase(pre)
    {

    }

    float PotionSynth::Post::operator()(float in) noexcept
    {
      return in;
    }

  audio::ProcessData<1> PotionSynth::process(audio::ProcessData<1> data)
  {
    return voice_mgr_.process(data);
  }

  float PotionSynth::Voice::remapping(float remap, float in) {
    return in;
    /*
    pre.remap_table.phase(in);
    float temp = pre.remap_table.val() * remap + in * (1 - remap);
    return  temp/2;
*/
    /*
    if (in > 1-remap) return 1.f;
    else {
      float temp = in/(1-remap);
      return temp;
    }
     */
  }

  PotionSynth::Voice::Voice(Pre& pre) noexcept : VoiceBase(pre) {
    props.lfo_osc.lfo_speed.on_change().connect([this](float speed) {
      lfo.freq(speed*3);
    });
    props.curve_osc.curve_length.on_change().connect([this](float decaytime) {
      curve.decay(decaytime*10 + 0.2);
    });

    //Let the waveplayers point to correct files
    //Should be moved into on_change for the wave_pair property.
    curve_osc.waves[0] = &pre.wavetables[2];
    curve_osc.waves[1] = &pre.wavetables[0];
    lfo_osc.waves[0] = &pre.wavetables[2];
    lfo_osc.waves[1] = &pre.wavetables[3];

    curve.finish();
  }

  void PotionSynth::Voice::on_note_on() noexcept {
    for (int osc=0; osc<2; osc++) {
      lfo.phase(0.f);
      curve.reset();
    }
  }

  float PotionSynth::Voice::operator()() noexcept {
    float result = 0;
    ///Set frequencies, advance the phase and get next sample from wavetables
    phase.freq(frequency());
    float ph = phase();
    //Oscillator pair 1
    result += props.curve_osc.volume * curve_osc(remapping(props.curve_osc.remap, ph), curve());
    //Oscillator pair 2
    result += props.lfo_osc.volume * lfo_osc(remapping(props.lfo_osc.remap, ph), lfo.tri());

    return result;
  }



  float PotionSynth::DualWavePlayer::operator()(float position, float pan_position) noexcept {
    //Get proper samples. No interpolation.
    int s0 = (int)floorf( position * (waves[0]->getNumSamplesPerChannel()));
    int s1 = (int)floorf( position * (waves[1]->getNumSamplesPerChannel()));

    float p0 = waves[0]->samples[0][s0];
    float p1 = waves[1]->samples[0][s1];

    return pan(pan_position, p0, p1);
  }

  /*
   * PotionSynthScreen
   */

  bool PotionSynthScreen::keypress(Key key)
  {
    return false;
  }

  void PotionSynthScreen::rotary(RotaryEvent e)
  {
    auto& props = engine.props;
    switch (e.rotary) {
    case Rotary::blue:
      if (!shift) {
        props.curve_osc.curve_length.step(e.clicks);
      } else {
        props.curve_osc.volume.step(e.clicks);
      }
    break;
    case Rotary::green:
      if (!shift) {
        props.curve_osc.remap.step(e.clicks);
      } else {

      }
    break;
    case Rotary::yellow:
      if (!shift) {
        props.lfo_osc.lfo_speed.step(e.clicks);
      } else {
        props.lfo_osc.volume.step(e.clicks);
      }
    break;
    case Rotary::red:
      if (!shift) {
        props.lfo_osc.remap.step(e.clicks);
      } else {

      }
    break;
    }
  }

  using namespace ui::vg;

  void PotionSynthScreen::draw(Canvas& ctx)
  {
    using namespace ui::vg;
    using namespace core::ui::vg;

    shift = Application::current().ui_manager->is_pressed(ui::Key::shift);

    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("C-Length", {x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.curve_osc.curve_length), {width - x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Remap1", {x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.curve_osc.remap), {width - x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("LFO", {x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.lfo_osc.lfo_speed), {width - x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Remap2", {x_pad, y_pad + 3 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.lfo_osc.remap), {width - x_pad, y_pad + 3 * space});

  }
} // namespace otto::engines

// namespace otto::engines
