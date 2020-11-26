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
    Voice(const State& state) : state_(state) {}
    // These voices only have process calls.
    // This saves us from checking the current algorithm every sample.
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

  private:
    const State& state_;
    std::array<FMOperator, 4> operators = {
      state_.operators[0],
      state_.operators[1],
      state_.operators[2],
      state_.operators[3],
    };
  };

  struct Audio : services::Audio::Consumer<State>, itc::Producer<AudioState> {
    Audio(itc::ChannelGroup& ch) : Consumer(ch), Producer(ch), voice_mgr_(ch, Consumer::state()) {}

    void process(util::audio_buffer& output) noexcept;

    void on_state_change(const State&) noexcept override
    {
      for (auto& v : voice_mgr_) v.on_state_change();
    }

    friend struct Voice;

    int algN_ = 0;
    int cur_op_ = 0;

    voices::VoiceManager<Voice, 6> voice_mgr_;
  };
} // namespace otto::engines::ottofm
