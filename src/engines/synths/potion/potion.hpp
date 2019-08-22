#pragma once

#include "core/engine/engine.hpp"

#include "core/voices/voice_manager.hpp"

#include <AudioFile.h>
#include <Gamma/Effects.h>
#include <Gamma/Envelope.h>
#include <Gamma/Oscillator.h>
#include <Gamma/SoundFile.h>

#include "util/dsp/pan.hpp"

// WAV parser by Adam Stark: https://github.com/adamstark/AudioFile
#include <AudioFile.h>
#include <Gamma/SamplePlayer.h>

#include "util/filesystem.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct PotionSynth : SynthEngine<PotionSynth> {
    static constexpr util::string_ref name = "Potion";

    struct WaveProps {
      Property<std::string> file = "";
      Property<float> volume = {0.5, limits(0, 1), step_size(0.01)};

      DECL_REFLECTION(WaveProps, file, volume);
    };

    struct CurveOscProps {
      Property<float> curve_length = {0.5, limits(0, 0.99), step_size(0.01)};
      WaveProps wave1;
      WaveProps wave2;
      float pan_position;

      DECL_REFLECTION(CurveOscProps, curve_length, wave1, wave2);
    };

    struct LFOOscProps {
      Property<float> lfo_speed = {0.5, limits(0, 0.99), step_size(0.01)};
      WaveProps wave1;
      WaveProps wave2;
      float pan_position;

      DECL_REFLECTION(LFOOscProps, lfo_speed, wave1, wave2);
    };

    struct Props {
      CurveOscProps curve_osc;
      LFOOscProps lfo_osc;

      std::array<gam::Array<float>, 4> wavetables;
      std::array<float, 4> samplerates;
      std::vector<std::string> filenames;
      std::array<std::vector<std::string>::iterator, 4> file_it = {
        {filenames.begin(), filenames.begin(), filenames.begin(), filenames.begin()}};

      DECL_REFLECTION(Props, curve_osc, lfo_osc);
    } props;

    PotionSynth();

    audio::ProcessData<1> process(audio::ProcessData<1>) override;

    voices::IVoiceManager& voice_mgr() override
    {
      return voice_mgr_;
    }

    struct DualWavePlayer {
      /// These should be external wavetables (in Pre)
      std::array<gam::SamplePlayer<float, gam::ipl::Linear, gam::phsInc::Loop>, 2> waves;
      PanSM pan;

      /// Call operator takes play position and pan value
      float operator()() noexcept;
    };

    DECL_REFLECTION(PotionSynth, props, ("voice_manager", &PotionSynth::voice_mgr_));

  private:
    void load_wavetable(int, std::string);

    struct Voice;

    struct Pre : voices::PreBase<Pre, Props> {
      Pre(Props&) noexcept;
      void operator()() noexcept;

      Voice* last_voice = nullptr;
    };

    struct Voice : voices::VoiceBase<Voice, Pre> {
      gam::LFO<> lfo;
      // Smoothing filter to eliminate pops when resetting the lfo.
      // Cost is 2 multiplications and 1 addition per sample.
      gam::OnePole<> lfo_smoother{20};
      gam::AD<> curve{0.001, 0.2, -2, -4};

      DualWavePlayer curve_osc;
      DualWavePlayer lfo_osc;
      float lfo_pan;

      Voice(Pre&) noexcept;
      float operator()() noexcept;
      void on_note_on(float freq_target) noexcept;
    };

    struct Post : voices::PostBase<Post, Voice> {
      Post(Pre&) noexcept;

      float operator()(float) noexcept;
    };

    voices::VoiceManager<Post, 6> voice_mgr_;
    friend struct PotionSynthScreen;
  };
} // namespace otto::engines
