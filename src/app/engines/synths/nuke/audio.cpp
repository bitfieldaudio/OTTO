#include "app/services/audio.hpp"

#include <Gamma/Envelope.h>
#include <Gamma/Oscillator.h>

#include "lib/dsp/moog_components.hpp"
#include "lib/dsp/triangle_wave.hpp"
#include "lib/voices/voice_manager.hpp"

#include "nuke.hpp"

namespace otto::engines::nuke {

  // Divides a float [0, 1] into steps, but with a smooth connection
  // |--0--|-|--1--|-...-|--num_steps--|
  float neighborhoods(float in, int min, int max)
  {
    float num_steps = max - min;

    float scaled = min + 0.9 * in * (num_steps + 1) - 0.49f; // [min - 0.49 , max + 0.49] (top point is approximate)
    // Decomposing this way yields negative and positive fractional parts
    float integral = std::round(scaled);
    float fractional = scaled - integral;
    fractional *= 2;
    float adjusted_fractional = fractional * fractional * fractional; // Must be an odd power to preserve sign
    return integral + adjusted_fractional / 2.f;
  }

  enum class LfoShapes { constant, up, down, tri, sqr, sine, C2, S5 };

  float lfo_take(gam::LFO<>& lfo, LfoShapes& shape)
  {
    switch (shape) {
      case LfoShapes::constant: return 1.f; break;
      case LfoShapes::up: return lfo.up(); break;
      case LfoShapes::down: return lfo.down(); break;
      case LfoShapes::tri: return lfo.tri(); break;
      case LfoShapes::sqr: return lfo.sqr(); break;
      case LfoShapes::sine: return lfo.sineP9(); break;
      case LfoShapes::C2: return lfo.C2(); break;
      case LfoShapes::S5: return lfo.S5(); break;
      default: return 0.f;
    }
  }



  struct Voice : voices::VoiceBase<Voice> {
    Voice(const State& state, float& lfo) noexcept;

    float operator()() noexcept;

    void on_note_on() noexcept;
    void on_note_off() noexcept;

    void reset_envelopes() noexcept;
    void release_envelopes() noexcept;

    void set_pitch_freq(const float) noexcept;
    void set_filter_freq(const float) noexcept;

    void on_state_change(const State& s) noexcept
    {
      // Synth
      // Osc 2
      osc2_freq_ratio = std::pow(2, neighborhoods(s.osc2_pitch, -3, 3));
      // osc1.setDutyCycle(0.1 + s.param0 * 0.8);

      // Ring mod
      ring_mod_amount = s.ringmod;

      // Filter
      cutoff = s.cutoff;
      filter_.setResonance(0.1 + 0.6 * s.resonance);

      // Volume envelope
      env_.attack(envelope_stage_duration(s.attack));
      env_.decay(envelope_stage_duration(s.decay));
      env_.sustain(s.sustain);
      env_.release(envelope_stage_duration(s.release));

      // Filter envelope
      env_filter_.attack(envelope_stage_duration(s.filter_attack));
      env_filter_.decay(4 * envelope_stage_duration(s.filter_decay));
      env_filter_.sustain(s.filter_sustain);
      env_filter_amount = s.filter_amount;

      // LFO
      lfo_envelope_.attack(envelope_stage_duration(s.lfo_attack));
      lfo_envelope_.decay(4 * envelope_stage_duration(s.lfo_decay));
      // Decay can be disabled at the max setting
      if (s.lfo_decay > 0.99) {
        lfo_envelope_.sustainPoint(1);
      } else {
        lfo_envelope_.sustainDisable();
      }

      // LFO targets
      lfo_to_pitch = s.lfo_pitch_amount;
      lfo_to_volume = s.lfo_volume_amount;
      lfo_to_filter = s.lfo_filter_amount;
      lfo_to_ringmod = s.lfo_ringmod_amount;
    }

    const State& state_;

  private:
    float cutoff = 0.5;
    float filter_mod_amount = 0;
    float env_filter_amount = 0;
    dsp::ADS<> env_filter_{0.01, 0.5, 0.5, 4.f};
    float osc2_freq_ratio = 1;
    float ring_mod_amount = 0;
    float duty_cycle = 0.5;
    dsp::MoogSaw<> osc1{440};
    gam::DWO<> osc2;
    gam::ADSR<> env_;
    dsp::MoogLadder<> filter_;


    float& lfo_val_common;
    LfoShapes lfo_shape = LfoShapes::sine;
    gam::AD<> lfo_envelope_{0.1f, 1.f, 1.f, 0.f};

    float lfo_to_pitch = 0;
    float lfo_to_volume = 0;
    float lfo_to_filter = 0;
    float lfo_to_ringmod = 0;
  };

  struct Audio final : AudioDomain, itc::Consumer<State>, ISynthAudio {
    Audio(itc::Context& ch) : Consumer(ch), voice_mgr_(ch, Consumer::state(), lfo_val) {}

    midi::IMidiHandler& midi_handler() noexcept override
    {
      return voice_mgr_;
    }

    util::audio_buffer process() noexcept override
    {
      auto buf = buffer_pool().allocate();
      for (auto& s : buf) {
        lfo_val = lfo_take(lfo, lfo_shape);
        s = voice_mgr_();
      }
      return buf;
    }

    void on_state_change(const State& s) noexcept override
    {
      // LFO
      lfo.freq(s.lfo_speed * s.lfo_speed * 15 + 0.1);
      lfo_shape = static_cast<LfoShapes>(static_cast<int>(s.lfo_type));

      // Voices
      for (auto& v : voice_mgr_) v.on_state_change(s);
    }

    gam::LFO<> lfo;
    LfoShapes lfo_shape = LfoShapes::up;
    float lfo_val;

    friend struct Voice;
    voices::VoiceManager<Voice, 6> voice_mgr_;
  };

  std::unique_ptr<ISynthAudio> make_audio(itc::Context& chan)
  {
    return std::make_unique<Audio>(chan);
  }

  // VOICE //
  Voice::Voice(const State& s, float& lfo) noexcept : state_(s), lfo_val_common(lfo)
  {
    env_.finish();
    env_filter_.finish();
    lfo_envelope_.finish();
  }

  void Voice::on_note_on() noexcept
  {
    reset_envelopes();
  }

  void Voice::on_note_off() noexcept
  {
    release_envelopes();
  }

  void Voice::reset_envelopes() noexcept
  {
    env_.resetSoft();
    env_filter_.reset();
    lfo_envelope_.reset();
  }

  void Voice::release_envelopes() noexcept
  {
    env_.release();
    lfo_envelope_.release();
  }

  void Voice::set_pitch_freq(const float lfo) noexcept
  {
    float freq = frequency() * powf(2, lfo);
    osc1.freq(freq);
    osc2.freq(freq * osc2_freq_ratio);
  }

  void Voice::set_filter_freq(const float lfo) noexcept
  {
    float filter_center_freq = frequency() * cutoff * cutoff * 10;
    filter_center_freq *= powf(2, 0.3 * lfo);
    filter_center_freq += (expf(env_filter_() * env_filter_amount) - 1.f) * 20000.f;
    float filter_freq = std::clamp(filter_center_freq, 1.f, 20000.f);
    filter_.setCutoff(filter_freq);
  }

  float Voice::operator()() noexcept
  {
    // LFO
    float lfo_val = lfo_val_common * lfo_envelope_();
    set_pitch_freq(lfo_val * lfo_to_pitch);
    set_filter_freq(lfo_val * lfo_to_filter);

    // Oscillators
    float osc_1 = osc1();
    float osc_2 = osc2.tri();
    float ring_mod = osc_1 * osc_2 * ring_mod_amount;

    float after_filter = filter_(0.5 * (osc_1 + 0.6 * osc_2 + ring_mod));

    // return after_filter * env_() * (1 + lfo_val * lfo_to_volume) * 0.25f;
    return 0.f;
  }

} // namespace otto::engines::nuke
