#include "app/services/audio.hpp"

#include <Gamma/Envelope.h>
#include <Gamma/Oscillator.h>

#include "lib/voices/voice_manager.hpp"

#include "ottofm.hpp"

namespace otto::engines::ottofm {
  /// Custom version of the 'Sine' in Gamma. We need to call it with a phase offset
  /// instead of a frequency offset. (Phase modulation, not frequency modulation)
  struct FMOperator {
    struct FMSine : public gam::AccumPhase<> {
      FMSine(float frq = 440, float phs = 0) : AccumPhase<>(frq, phs, 1) {}
      /// Generate next sample with phase offset
      float operator()(float phsOffset) noexcept
      {
        return gam::scl::sinP9(gam::scl::wrap(this->nextPhase() + phsOffset, 1.f, -1.f));
      }
    };

    FMOperator(const OperatorState& state) : state(state) {}

    float operator()(float phaseMod = 0) noexcept
    {
      previous_value_ = sine(phaseMod + feedback_ * previous_value_) * env_() * state.level;
      return previous_value_;
    }

    /// Set frequency
    void freq(float frq) noexcept
    {
      sine.freq(frq * freq_ratio_ + detune_amount_);
    }

    /// For graphics
    [[nodiscard]] float get_activity_level() const noexcept
    {
      return env_.value() * state.level;
    }
    [[nodiscard]] float get_envelope_stage() const noexcept
    {
      if (env_.done()) return 4;
      if (env_.sustained()) return 2;
      auto stage = env_.stage();
      float base = stage == 2 ? 3.f : float(stage);
      return base + float(env_.position()) / float(env_.lengths()[stage] * env_.spu());
    }

    /// Reset envelope
    void reset() noexcept
    {
      env_.resetSoft();
    }

    /// Release envelope
    void release() noexcept
    {
      env_.release();
    }

    /// Finish envelope
    void finish() noexcept
    {
      env_.finish();
    }

    void on_state_change() noexcept
    {
      env_.attack(envelope_stage_duration(state.envelope.attack));
      env_.decay(envelope_stage_duration(state.envelope.decay));
      env_.release(envelope_stage_duration(state.envelope.release));
      env_.sustain(state.envelope.sustain);

      freq_ratio_ = fractions[state.ratio_idx];
      // 10 Hz? Should we find something more appropriate?
      detune_amount_ = 20 * state.detune;
      feedback_ = (state.shape - 0.5f) * 2.f;
    }

  private:
    const OperatorState& state;
    FMSine sine;
    gam::ADSR<> env_;

    float freq_ratio_ = 1;
    float detune_amount_ = 0;
    float feedback_ = 0;
    float previous_value_ = 0;
  };

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
    void on_state_change(const State&) noexcept
    {
      for (auto& op : operators) {
        op.on_state_change();
      }
    }

    const State& state_;
    std::array<FMOperator, 4> operators = {
      state_.operators[0],
      state_.operators[1],
      state_.operators[2],
      state_.operators[3],
    };
  };

  struct Audio final : AudioDomain, itc::Consumer<State>, itc::Producer<AudioState>, ISynthAudio {
    Audio(itc::Context& ch) : Consumer(ch), Producer(ch), voice_mgr_(ch, Consumer::state()) {}

    midi::IMidiHandler& midi_handler() noexcept override
    {
      return voice_mgr_;
    }

    util::audio_buffer process() noexcept override
    {
      auto buf = buffer_pool().allocate();
      stdr::generate(buf, std::ref(voice_mgr_));
      Producer::commit([&](auto& state) {
        for (auto&& [op, act] : util::zip(voice_mgr_.last_triggered_voice().operators, state.activity)) {
          act = op.get_activity_level();
        }
        for (auto&& [op, st] : util::zip(voice_mgr_.last_triggered_voice().operators, state.stage)) {
          st = op.get_envelope_stage();
        }
      });
      return buf;
    }

    void on_state_change(const State& s) noexcept override
    {
      for (auto& v : voice_mgr_) v.on_state_change(s);
    }

    friend struct Voice;

    voices::VoiceManager<Voice, 6> voice_mgr_;
  };

  std::unique_ptr<ISynthAudio> make_audio(itc::Context& ctx)
  {
    return std::make_unique<Audio>(ctx);
  }

  // VOICE //
  Voice::Voice(const State& s) noexcept : state_(s)
  {
    for (auto& op : operators) {
      op.finish();
    }
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
    for (auto& op : operators) op.reset();
  }

  void Voice::release_envelopes() noexcept
  {
    for (auto& op : operators) op.release();
  }

  void Voice::set_frequencies() noexcept
  {
    for (auto& op : operators) op.freq(frequency());
  }

  float Voice::operator()() noexcept
  {
    set_frequencies();
    auto& [op0, op1, op2, op3] = operators;
    switch (state_.algorithm_idx) {
      case 0: {
        return op0(op1(op2(op3(0))));
      }
      case 1: {
        return op0(op1(op2(0) + op3(0)));
      }
      case 2: {
        return op0(op1(op2(0)) + op3(0));
      }
      case 3: {
        float aux = op3(0);
        return op0(op1(aux) + op2(aux));
      }
      case 4: {
        float aux = op2(op3(0));
        return (op0(aux) + op1(aux)) * 0.5f;
      }
      case 5: {
        return (op0(0) + op1(op2(op3(0)))) * 0.5f;
      }
      case 6: {
        return op0(op1(0) + op2(0) + op3(0));
      }
      case 7: {
        return (op0(op1(0)) + op2(op3(0))) * 0.5f;
      }
      case 8: {
        float aux = op3(0);
        return (op0(aux) + op1(aux) + op2(aux)) * 0.33f;
      }
      case 9: {
        return (op0(0) + op1(0) + op2(op3(0))) * 0.33f;
      }
      case 10: {
        return (op0(0) + op1(0) + op2(0) + op3(0)) * 0.25f;
      }
      default: {
        return 0.f;
      }
    }
  }

} // namespace otto::engines::ottofm
