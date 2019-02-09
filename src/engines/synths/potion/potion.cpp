#include "potion.hpp"

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
      wavetables[1].load(Application::current().data_dir / "wavetables/wt2.wav");
      wavetables[2].load(Application::current().data_dir / "wavetables/wt3.wav");
      wavetables[3].load(Application::current().data_dir / "wavetables/wt4.wav");

      //Fill remap tables
      remap_table.resize(512);
      for (int i=0; i<remap_table.size(); i++) {
        remap_table[i] = (2.0*(float)i/(float)remap_table.size() - 1.0) / 2.0;
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

    pre.remap_table.phase(in);
    float temp = pre.remap_table.val() * remap + in * (1 - remap);
    return  temp;

    /*
    if (in > 1-remap) return 1.f;
    else {
      float temp = in/(1-remap);
      return temp;
    }
     */
  }

  PotionSynth::Voice::Voice(Pre& pre) noexcept : VoiceBase(pre) {
    props.oscillators[0].lfo_speed.on_change().connect([this](float speed) {
      morph[0].freq(speed*3);
    });
    props.oscillators[1].lfo_speed.on_change().connect([this](float speed) {
      morph[1].freq(speed*3);
    });
  }

  void PotionSynth::Voice::on_note_on() noexcept {
    for (int osc=0; osc<2; osc++) {
      morph[osc].phase(0.f);
    }
  }

  float PotionSynth::Voice::operator()() noexcept {
    float result = 0;
    ///Set frequencies, advance the phase and get next sample from wavetables
    phase.freq(frequency());
    float ph = phase();
    for (int osc=0; osc<2; osc++) { //Runs over oscillators
      float lfo_value = morph[osc].tri();
      float after_remapping = remapping(props.oscillators[osc].remap, ph);
      ///Wave 1
      int sample = (int)  pre.wavetables[2*osc].getNumSamplesPerChannel()*after_remapping;
      result += (lfo_value + 1) * pre.wavetables[2*osc].samples[0][sample];
      ///Wave 2
      sample = (int)  pre.wavetables[2*osc+1].getNumSamplesPerChannel()*after_remapping;
      result += (1 - lfo_value) * pre.wavetables[2*osc+1].samples[0][sample];
    }

    return result;
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
        props.oscillators[0].lfo_speed.step(e.clicks);
      } else {
        props.oscillators[0].volume.step(e.clicks);
      }
    break;
    case Rotary::green:
      if (!shift) {
        props.oscillators[0].remap.step(e.clicks);
      } else {

      }
    break;
    case Rotary::yellow:
      if (!shift) {
        props.oscillators[1].lfo_speed.step(e.clicks);
      } else {
        props.oscillators[1].volume.step(e.clicks);
      }
    break;
    case Rotary::red:
      if (!shift) {
        props.oscillators[1].remap.step(e.clicks);
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

    //shift = Application::current().ui_manager->is_pressed(ui::Key::shift);

    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("LFO1", {x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.oscillators[0].lfo_speed), {width - x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Remap1", {x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.oscillators[0].remap), {width - x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("LFO2", {x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.oscillators[1].lfo_speed), {width - x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Remap2", {x_pad, y_pad + 3 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.oscillators[1].remap), {width - x_pad, y_pad + 3 * space});

  }
} // namespace otto::engines

// namespace otto::engines
