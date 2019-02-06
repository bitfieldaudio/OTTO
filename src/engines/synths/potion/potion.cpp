#if false
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
    ///Load waveforms into vectors.
    gam::SoundFile sf(Application::current().data_dir / "wavetables/wt1.wav");
    sf.openRead();// open file in read mode
    int framesA1 = sf.frames();
    props.wavetables[0].allocate(framesA1);
    sf.read(props.wavetables[0].wave, framesA1);

    /*
    AudioFile<float> wave1_1, wave1_2, wave2_1, wave2_2;
    wave1_1.load( Application::current().data_dir / "wavetables/wt1.wav" );
    wave1_2.load( Application::current().data_dir / "wavetables/wt2.wav" );
    wave2_1.load( Application::current().data_dir / "wavetables/wt3.wav" );
    wave2_2.load( Application::current().data_dir / "wavetables/wt4.wav" );
*/
  }

  audio::ProcessData<1> PotionSynth::process(audio::ProcessData<1> data)
  {
    auto buf = Application::current().audio_manager->buffer_pool().allocate_multi<1>();
    for (auto&& [frm] : buf) {
      frm = voices[0]();
    }
    return data.redirect(buf);
  }

  float PotionSynth::Voice::remapping(float remap, float in) {
    return in;
  }

  float PotionSynth::Voice::operator()() noexcept {
    int sample = (int) props.wavetables[0].frames*remapping(0, phase());
    return props.wavetables[0].wave[sample];
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
        props.oscillators.at(0).lfo_speed.step(e.clicks);
      } else {
        props.oscillators.at(0).volume.step(e.clicks);
      }
    break;
    case Rotary::green:
      if (!shift) {
        props.oscillators.at(0).remap.step(e.clicks);
      } else {

      }
    break;
    case Rotary::yellow:
      if (!shift) {
        props.oscillators.at(1).lfo_speed.step(e.clicks);
      } else {
        props.oscillators.at(1).volume.step(e.clicks);
      }
    break;
    case Rotary::red:
      if (!shift) {
        props.oscillators.at(1).remap.step(e.clicks);
      } else {
        props.oscillators.at(1).remap.step(e.clicks);
      }
    break;
    }
  }

  using namespace ui::vg;

  void PotionSynthScreen::draw(Canvas& ctx)
  {
    using namespace ui::vg;
    //shift = Application::current().ui_manager->is_pressed(ui::Key::shift);

  }
} // namespace otto::engines

// namespace otto::engines
#endif