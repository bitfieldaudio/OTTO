#pragma once

#include "core/engine/engine.hpp"

#include "core/audio/faust.hpp"
#include "core/voices/voice_manager.hpp"

#include <Gamma/Oscillator.h>
#include <Gamma/SoundFile.h>
#include <AudioFile.h>


namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct PotionSynth : SynthEngine, EngineWithEnvelope {

    struct OscillatorProps : Properties<> {
      using Properties::Properties;
      Property<int> wave_pair        = {this, "wave_pair",     0,  has_limits::init(0,0),     steppable::init(1)};
      Property<float> lfo_speed     = {this, "lfo_speed",     0.1,  has_limits::init(0, 1),    steppable::init(0.01)};
      Property<float> volume        = {this, "volume",        1,  has_limits::init(0, 1),    steppable::init(0.01)};
      Property<float> remap           = {this, "remap",    0.7,  has_limits::init(0, 0.99),    steppable::init(0.01)};

    };

    struct Props : Properties<> {
      std::array<OscillatorProps,2> oscillators = {{{this, "osc1"}, {this, "osc2"}}};
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
    struct Pre : voices::PreBase<Pre, Props> {
      std::array<AudioFile<float>,4> wavetables;
      gam::Osc<> remap_table;

      Pre(Props&) noexcept;
      void operator()() noexcept;
    };

    struct Voice : voices::VoiceBase<Voice, Pre> {
      std::array<gam::LFO<>,2> morph;
      gam::Sweep<> phase;


      float remapping(float, float);

      Voice(Pre&) noexcept;
      float operator()() noexcept;
      void on_note_on() noexcept;
    };

    struct Post : voices::PostBase<Post, Voice> {

      Post(Pre&) noexcept;

      float operator()(float) noexcept;
    };

    voices::VoiceManager<Post, 6> voice_mgr_;

  };
} // namespace otto::engines
