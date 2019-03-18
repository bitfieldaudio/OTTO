#pragma once

#include "core/engine/engine.hpp"

#include "core/audio/faust.hpp"
#include "core/voices/voice_manager.hpp"

#include <AudioFile.h>
#include <Gamma/Effects.h>
#include <Gamma/Envelope.h>
#include <Gamma/Oscillator.h>
#include <Gamma/SoundFile.h>


namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct PotionSynth : SynthEngine<PotionSynth>, EngineWithEnvelope {
    static constexpr std::string_view name = "Potion";

    struct CurveOscProps : Properties<> {
      using Properties::Properties;
      Property<float> curve_length = {this, "curve_length", 0.5, has_limits::init(0, 1),
                                      steppable::init(0.01)};
      Property<int> wave_pair = {this, "wave_pair", 0, has_limits::init(0, 0), steppable::init(1)};
      Property<float> volume = {this, "volume", 1, has_limits::init(0, 1), steppable::init(0.01)};
      Property<float> remap = {this, "remap", 0.7, has_limits::init(0, 0.99),
                               steppable::init(0.01)};

      DECL_REFLECTION(CurveOscProps, curve_length, wave_pair, volume, remap);
    };

    struct LFOOscProps : Properties<> {
      using Properties::Properties;
      Property<float> lfo_speed = {this, "lfo_speed", 0.5, has_limits::init(0, 1),
                                   steppable::init(0.01)};
      Property<int> wave_pair = {this, "wave_pair", 0, has_limits::init(0, 0), steppable::init(1)};
      Property<float> volume = {this, "volume", 1, has_limits::init(0, 1), steppable::init(0.01)};
      Property<float> remap = {this, "remap", 0.7, has_limits::init(0, 0.99),
                               steppable::init(0.01)};

      DECL_REFLECTION(LFOOscProps, lfo_speed, wave_pair, volume, remap);
    };

    struct Props : Properties<> {
      CurveOscProps curve_osc = {this, "curve_osc"};
      LFOOscProps lfo_osc = {this, "lfo_osc"};

      DECL_REFLECTION(Props, curve_osc, lfo_osc);
    } props;

    PotionSynth();

    audio::ProcessData<1> process(audio::ProcessData<1>) override;

    ui::Screen& envelope_screen() override
    {
      return voice_mgr_.envelope_screen();
    }

    ui::Screen& voices_screen() override
    {
      return voice_mgr_.settings_screen();
    }

    /// Equal-power 2-channel panner (Stereo-to-Mono)
    class PanSM {
    public:
      /// \param[in] pos	Position, in [-1, 1]
      PanSM(float pos = 0)
      {
        this->pos(pos);
      }

      /// Filter sample (mono to stereo)
      float operator()(float position, float in1, float in2)
      {
        pos(position);
        return in1 * w1 + in2 * w2;
      }

      /// Set position (constant power law)

      /// This is a constant power pan where the sum of the squares of the two
      /// channel gains is always 1. A quadratic approximation is used to avoid
      /// expensive trig function calls. The approximation is good enough for most
      /// purposes and gives the exact result at positions of -1, 0, 1.
      ///
      /// \param[in] v	Position, in [-1, 1]
      void pos(float v)
      {
        static const float c0 = 1. / sqrt(2);
        static const float c1 = 0.5 - c0;
        static const float c2 = -0.5 / c1;
        v = gam::scl::clip(v, 1.f, -1.f);
        w1 = c1 * v * (v + c2) + c0;
        w2 = w1 + v;
      }

    protected:
      float w1, w2; // channel weights
    };

    struct DualWavePlayer {
      /// Returns the weighted sum of two wavetables.
      /// These should be external wavetables (in Pre)
      AudioFile<float>* waves[2];
      PanSM pan;

      /// Call operator takes play position and pan value
      float operator()(float, float) noexcept;
    };

    DECL_REFLECTION(PotionSynth, props, ("voice_manager", &PotionSynth::voice_mgr_));

  private:
    struct Pre : voices::PreBase<Pre, Props> {
      std::array<AudioFile<float>, 4> wavetables;
      gam::Osc<> remap_table;

      Pre(Props&) noexcept;
      void operator()() noexcept;
    };

    struct Voice : voices::VoiceBase<Voice, Pre> {
      gam::LFO<> lfo;
      gam::Decay<> curve;
      gam::Sweep<> phase;

      DualWavePlayer curve_osc;
      DualWavePlayer lfo_osc;

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
