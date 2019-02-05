#pragma once

#include "core/engine/engine.hpp"

#include "core/audio/faust.hpp"
#include "core/audio/voice_manager.hpp"

#include <Gamma/Oscillator.h>
#include <Gamma/SoundFile.h>


namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct PotionSynth : SynthEngine, EngineWithEnvelope {

    struct OscillatorProps : Properties<> {
      using Properties::Properties;
      Property<int> wave_pair        = {this, "wave_pair",     0,  has_limits::init(0,0),     steppable::init(1)};
      Property<float> lfo_speed     = {this, "lfo_speed",     0,  has_limits::init(0, 1),    steppable::init(0.01)};
      Property<float> volume        = {this, "volume",        1,  has_limits::init(0, 1),    steppable::init(0.01)};
      Property<int> remap           = {this, "remap",    0,  has_limits::init(0, 4),    steppable::init(1)};

    };

    struct WaveTableProps {
        int frames = 0;

        float allocate(int samples) {
            frames = samples;
            float wave[frames];
        }
    };

    struct Props : Properties<> {

        std::array<OscillatorProps,2> oscillators = {{{this, "osc1"}, {this, "osc2"}}};
        std::array<WaveTableProps,4> wavetables = {{{this, "wt1"}, {this, "wt2"}, {this, "wt3"}, {this, "wt4"}}};

    } props;

    PotionSynth();

    audio::ProcessData<1> process(audio::ProcessData<1>) override;

    ui::Screen& envelope_screen() override {
      return voice_mgr_.envelope_screen();
    }

    ui::Screen& voices_screen() override {
      return voice_mgr_.settings_screen();
    }

  private:
    audio::VoiceManager<6> voice_mgr_;



    struct PreProcessing {
        Props& props;

    };

    struct Voice {
        Props& props;
        gam::LFO<> morph;
        gam::Sweep<> phase();

        float operator()() noexcept;

        float remapping(float, float);

    };
    std::array<Voice, 6> voices = {{{props}, {props}, {props}, {props}, {props}, {props}}};

    struct PostProcessing {
        Props& props;

    };
    PostProcessing post_processing = {props};

  };
} // namespace otto::engines
