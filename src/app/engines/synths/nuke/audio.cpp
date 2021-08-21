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

  enum LfoShapes { up, down, tri, sqr, sine, C2, S5 };

  float lfo_take(gam::LFO<>& lfo, LfoShapes& shape)
  {
    switch (shape) {
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
    Voice(const State& state) noexcept;

    float operator()() noexcept;

    void on_note_on() noexcept;
    void on_note_off() noexcept;

    void reset_envelopes() noexcept;
    void release_envelopes() noexcept;

    /// Sets operator frequencies. Call after next() to use updated voice frequency
    void set_frequencies() noexcept;

    // TODO: maybe add some magic here? (i.e: should Voice also be a consumer of state?)
    // The answer is probably yes, once each consumer doesn't need its own separate copies
    // of state, and various other optimizations have been done to make many consumers of
    // the same state on the same thread cheaper.
    /// Must be called manually, no magic here!
    void on_state_change(const State& s) noexcept
    {
      // Synth
      // Osc 2
      osc2_freq_ratio = std::pow(2, neighborhoods(s.param0, -3, 3));
      // osc1.setDutyCycle(0.1 + s.param0 * 0.8);
      // Ring mod
      ring_mod_amount = std::max(0.f, static_cast<float>(s.param1));
      // Oscillator sync
      sync_amount = std::max(-static_cast<float>(s.param1), 0.f);
      // Filter
      // cutoff = 1 + 15000 * s.param2 * s.param2;
      // cutoff = 3 * s.param2 * s.param2;
      cutoff = s.param2;
      // filter_.setCutoff(cutoff);
      filter_.setResonance(0.1 + 0.5 * s.param3);


      // Modulation


      // Volume envelope
      env_.attack(envelope_stage_duration(s.envparam0_0));
      env_.decay(envelope_stage_duration(s.envparam0_1));
      env_.sustain(s.envparam0_2);
      env_.release(envelope_stage_duration(s.envparam0_3));

      // Filter envelope
      env_filter_.attack(envelope_stage_duration(s.envparam1_0));
      env_filter_.decay(envelope_stage_duration(s.envparam1_1));
      env_filter_.sustain(s.envparam1_2);
      env_filter_amount = s.envparam1_3;

      // LFO
      lfo.freq(s.envparam2_0 * s.envparam2_0 * 15 + 0.1);
      lfo_shape = static_cast<LfoShapes>(static_cast<int>(s.envparam2_1));
    }

    const State& state_;

  private:
    bool moog = true;
    float cutoff = 0.5;
    float filter_mod_amount = 0;
    float env_filter_amount = 0;
    float osc2_freq_ratio = 1;
    float ring_mod_amount = 0;
    float sync_amount = 0;
    float duty_cycle = 0.5;
    dsp::MoogSaw<> osc1{440};
    gam::DWO<> osc2;
    gam::ADSR<> env_;
    dsp::MoogLadder<> filter_;
    gam::ADSR<> env_filter_{0.01, 0.5, 1, 100};

    // TODO: Move this out to Audio
    gam::LFO<> lfo{1.0};
    LfoShapes lfo_shape = LfoShapes::up;
  };

  struct Audio final : AudioDomain, itc::Consumer<State>, ISynthAudio {
    Audio(itc::Channel& ch) : Consumer(ch), voice_mgr_(ch, Consumer::state()) {}

    midi::IMidiHandler& midi_handler() noexcept override
    {
      return voice_mgr_;
    }

    util::audio_buffer process() noexcept override
    {
      auto buf = buffer_pool().allocate();
      stdr::generate(buf, std::ref(voice_mgr_));
      return buf;
    }

    void on_state_change(const State& s) noexcept override
    {
      for (auto& v : voice_mgr_) v.on_state_change(s);
    }

    friend struct Voice;

    voices::VoiceManager<Voice, 6> voice_mgr_;
  };

  std::unique_ptr<ISynthAudio> make_audio(itc::Channel& chan)
  {
    return std::make_unique<Audio>(chan);
  }

  // VOICE //
  Voice::Voice(const State& s) noexcept : state_(s)
  {
    env_.finish();
    env_filter_.finish();
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
  }

  void Voice::release_envelopes() noexcept
  {
    env_.release();
    env_filter_.release();
  }

  void Voice::set_frequencies() noexcept
  {
    osc1.freq(frequency());
    osc2.freq(frequency() * osc2_freq_ratio);
    // filter_.setCutoff(1 + (15000 + 0.5 * frequency()) * cutoff * cutoff);
    filter_.setCutoff(
      1 +
      std::min((15000 + 0.5 * frequency()) * cutoff * cutoff * (1 + env_filter_amount * 5 * env_filter_()), 20000.0));
  }

  float Voice::operator()() noexcept
  {
    set_frequencies();

    float lfo_val = lfo_take(lfo, lfo_shape);

    // TODO: remove
    float phs = osc1.phase();

    // Get oscillator 1 value
    float osc_1 = osc1();
    // Oscillator 2. Sync this to oscillator 1, if applicable
    // TODO: Make a class for this, for performance
    if (osc1.phase() < phs && osc2.phase() > 1 - sync_amount) osc2.phase(osc1.phase());
    float osc_2 = osc2.tri();

    // return filter_((osc_1  + ring_mod) * 0.5 * env_());
    float after_filter = filter_(osc_1 + 0.6 * osc_2);
    float ring_mod = after_filter * osc_2 * ring_mod_amount * 4;
    return (after_filter + ring_mod) * env_() * (1 + lfo_val) * 0.5f;
  }

} // namespace otto::engines::nuke
