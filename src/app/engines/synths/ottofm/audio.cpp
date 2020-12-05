#include "ottofm.hpp"

#include <Gamma/Envelope.h>
#include <Gamma/Oscillator.h>

#include "app/services/audio.hpp"
#include "lib/voice_manager.hpp"

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

    FMOperator(const OperatorState& state, bool modulator = false) : state(state), modulator_(modulator) {}

    float operator()(float phaseMod = 0) noexcept
    {
      if (modulator_) {
        return env_() * sine(phaseMod) * state.level;
      }
      previous_value_ = sine(phaseMod + state.feedback * previous_value_) * state.level;
      return previous_value_;
    }

    /// Set frequency
    void freq(float frq) noexcept
    {
      sine.freq(frq * freq_ratio_ + detune_amount_);
    }

    /// Get current level
    [[nodiscard]] float level() const noexcept
    {
      return env_.value() * state.level;
    }

    /// For graphics
    /// If it is a carrier it output a constant value and sould be multiplied by the voice envelope
    /// TODO: Refactor so just operator envelopes are used, so we don't need voice envelope.
    [[nodiscard]] float get_activity_level() const noexcept
    {
      if (modulator_) return level();
      return state.level;
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

    /// Set modulator flag
    void modulator(bool m) noexcept
    {
      modulator_ = m;
    }

    void on_state_change() noexcept
    {
      env_.attack(3 * state.envelope.attack);
      env_.decay(3 * state.envelope.decay);
      env_.release(3 * state.envelope.release);
      env_.sustain(state.envelope.sustain);

      freq_ratio_ = fractions[state.ratio_idx];
    }

  private:
    const OperatorState& state;
    FMSine sine;
    gam::ADSR<> env_;

    bool modulator_ = false; /// If it is a modulator, use the envelope.

    float freq_ratio_ = 1;
    float detune_amount_ = 0;

    float previous_value_ = 0;
  };

  struct Voice : voices::VoiceBase<Voice> {
    Voice(const State& state) noexcept;

    float operator()() noexcept;

    void on_note_on(float) noexcept;
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
    void on_state_change() noexcept
    {
      int i = 0;
      for (auto& op : operators) {
        op.modulator(algorithms[state_.algorithm_idx].modulator_flags[i]);
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

  struct Audio final : AudioDomain,
                       itc::Consumer<State>,
                       itc::Producer<AudioState>,
                       ISynthAudio,
                       core::ServiceAccessor<services::Audio> {
    Audio(itc::ChannelGroup& ch) : Consumer(ch), Producer(ch), voice_mgr_(ch, Consumer::state()) {}

    midi::IMidiHandler& midi_handler() noexcept override
    {
      return voice_mgr_;
    }

    util::audio_buffer process() noexcept override
    {
      auto buf = service<services::Audio>().buffer_pool().allocate();
      stdr::generate(buf, std::ref(voice_mgr_));
      for (auto&& [op, act] : util::zip(voice_mgr_.last_triggered_voice().operators, Producer::state().activity)) {
        act = op.get_activity_level();
      }
      Producer::commit();
      return buf;
    }

    void on_state_change(const State&) noexcept override
    {
      for (auto& v : voice_mgr_) v.on_state_change();
    }

    friend struct Voice;

    int algN_ = 0;
    int cur_op_ = 0;

    voices::VoiceManager<Voice, 6> voice_mgr_;
  };

  std::unique_ptr<ISynthAudio> make_audio(itc::ChannelGroup& chan)
  {
    return std::make_unique<Audio>(chan);
  }

  // VOICE //
  Voice::Voice(const State& s) noexcept : state_(s)
  {
    for (auto& op : operators) {
      op.finish();
    }
  }

  void Voice::on_note_on(float freq_target) noexcept
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
    float aux = 0;
    switch (state_.algorithm_idx) {
      case 0: return op0(op1(op2(op3(0))));
      case 1: return op0(op1(op2(0) + op3(0)));
      case 2: return op0(op1(op2(0)) + op3(0));
      case 3: aux = op3(0); return op0(op1(aux) + op2(aux));
      case 4: aux = op2(op3(0)); return (op0(aux) + op1(aux));
      case 5: return (op0(0) + op1(op2(op3(0))));
      case 6: return op0(op1(0) + op2(0) + op3(0));
      case 7: return (op0(op1(0)) + op2(op3(0)));
      case 8: aux = op3(0); return (op0(aux) + op1(aux) + op2(aux));
      case 9: return (op0(0) + op1(0) + op2(op3(0)));
      case 10: return (op0(0) + op1(0) + op2(0) + op3(0));
      default: return 0.f;
    }
  }

} // namespace otto::engines::ottofm
