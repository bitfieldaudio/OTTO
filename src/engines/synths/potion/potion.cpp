#include "potion.hpp"

#include "core/ui/vector_graphics.hpp"

#include "potion.faust.hpp"

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
      voice_mgr_(props),
      faust_(std::make_unique<FAUSTCLASS>(), props)
  {
    ///Load waveforms into vectors.
    AudioFile<double> audioFile;
    audioFile.load( Application::current().data_dir / "wavetables/wt1.wav" );
    std::vector<double> wave1;

    for (int i = 0; i < numSamples; i++)
    {
      wave1.push_back(audioFile.samples[0][i]);
    }
    ///Get number of samples for Faust
    props.oscillators.at(0).numSamples = audioFile.getNumSamplesPerChannel();


  }

  audio::ProcessData<1> PotionSynth::process(audio::ProcessData<1> data)
  {
    voice_mgr_.process_before(data.midi_only());
    auto res = faust_.process(data.midi_only());
    voice_mgr_.process_after(data.midi_only());
    return res;
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
        props.oscillators.at(0).remap_amount.step(e.clicks);
      } else {
        props.oscillators.at(0).remap_type.step(e.clicks);
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
        props.oscillators.at(1).remap_amount.step(e.clicks);
      } else {
        props.oscillators.at(1).remap_type.step(e.clicks);
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
