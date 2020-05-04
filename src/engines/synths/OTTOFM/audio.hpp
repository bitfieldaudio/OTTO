#pragma once
#include <Gamma/Envelope.h>
#include <Gamma/Filter.h>
#include <Gamma/Noise.h>
#include <Gamma/Oscillator.h>

#include <tuple>

#include "core/voices/voice_manager.hpp"
#include "ottofm.hpp"

namespace otto::engines::ottofm {

  template<int I>
  using OperatorActions = meta::list<itc::prop_change<&Props::OperatorProps<I>::feedback>,
                                     itc::prop_change<&Props::OperatorProps<I>::attack>,
                                     itc::prop_change<&Props::OperatorProps<I>::decay_release>,
                                     itc::prop_change<&Props::OperatorProps<I>::suspos>,
                                     itc::prop_change<&Props::OperatorProps<I>::detune>,
                                     itc::prop_change<&Props::OperatorProps<I>::ratio_idx>,
                                     itc::prop_change<&Props::OperatorProps<I>::out_level>>;

  /// Custom version of the 'Sine' in Gamma. We need to call it with a phase offset
  /// instead of a frequency offset. (Phase modulation, not frequency modulation)
  /// Defines its own action handlers, which is why it is templated.
  template<int I>
  struct FMOperator final : itc::ActionReceiverOnBus<itc::AudioBus,
                                                     OperatorActions<I>,
                                                     itc::prop_change<&Props::fm_amount>,
                                                     itc::prop_change<&Props::algorithm_idx>> {
    struct FMSine : public gam::AccumPhase<> {
      FMSine(float frq = 440, float phs = 0) : AccumPhase<>(frq, phs, 1) {}
      /// Generate next sample with phase offset
      float operator()(float phsOffset) noexcept
      {
        return gam::scl::sinP9(gam::scl::wrap(this->nextPhase() + phsOffset, 1.f, -1.f));
      }
    };

    FMOperator(float frq = 440, float outlevel = 1, bool modulator = false) {}

    float operator()(float phaseMod = 0) noexcept
    {
      if (modulator_)
        return env_() * sine(phaseMod) * outlevel_ * fm_amount_;
      else {
        previous_value_ = sine(phaseMod + feedback_ * previous_value_) * outlevel_;
        return previous_value_;
      }
    }

    /// Set frequency
    void freq(float frq) noexcept
    {
      sine.freq(frq * freq_ratio_ + detune_amount_);
    }

    /// Get current level
    float level() noexcept
    {
      return env_.value() * outlevel_;
    }

    /// For graphics
    /// If it is a carrier it output a constant value and sould be multiplied by the voice envelope
    /// TODO: Refactor so just operator envelopes are used, so we don't need voice envelope.
    float get_activity_level() noexcept
    {
      if (modulator_)
        return level();
      else
        return outlevel_;
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

    /// Actionhandlers. These are all the properties that can vary across operators.
    void action(itc::prop_change<&Props::OperatorProps<I>::feedback>, float f) noexcept final
    {
      feedback_ = f;
    }
    void action(itc::prop_change<&Props::OperatorProps<I>::attack>, float a) noexcept final
    {
      env_.attack(3 * a);
    }
    void action(itc::prop_change<&Props::OperatorProps<I>::suspos>, float s) noexcept final
    {
      suspos_ = s;
      env_.decay(3 * decrel_ * (1 - s));
      env_.release(3 * decrel_ * s);
      env_.sustain(s);
    }
    void action(itc::prop_change<&Props::OperatorProps<I>::decay_release>, float dr) noexcept final
    {
      decrel_ = dr;
      env_.decay(3 * dr * (1 - suspos_));
      env_.release(3 * dr * suspos_);
    }
    void action(itc::prop_change<&Props::OperatorProps<I>::detune>, float d) noexcept final
    {
      detune_amount_ = d * 25;
    }
    void action(itc::prop_change<&Props::OperatorProps<I>::ratio_idx>, int idx) noexcept final
    {
      freq_ratio_ = (float) fractions[idx];
    }
    void action(itc::prop_change<&Props::OperatorProps<I>::out_level>, float l) noexcept final
    {
      outlevel_ = l;
    }
    void action(itc::prop_change<&Props::fm_amount>, float fm) noexcept final
    {
      fm_amount_ = fm;
    }

    void action(itc::prop_change<&Props::algorithm_idx>, int a) noexcept final
    {
      modulator(algorithms[a].modulator_flags[I]);
    }

  private:
    FMSine sine;
    gam::ADSR<> env_;

    bool modulator_ = false; /// If it is a modulator, use the envelope.
    float outlevel_ = 1;
    float feedback_ = 0;
    float fm_amount_ = 1;

    // Necessary for housekeeping under envelope property changes
    float suspos_ = 1;
    float decrel_ = 1;

    float freq_ratio_ = 1;
    float detune_amount_ = 0;

    float previous_value_ = 0;
  };

  struct Voice : voices::VoiceBase<Voice>,
                 itc::ActionReceiverOnBus<itc::AudioBus,
                                          voices::attack_tag::action,
                                          voices::decay_tag::action,
                                          voices::sustain_tag::action,
                                          voices::release_tag::action> {
    Voice(Audio& a) noexcept;

    // These voices only have process calls.
    // This saves us from checking the current algorithm every sample.
    core::audio::ProcessData<1> process(core::audio::ProcessData<0> data) noexcept;

    void on_note_on(float) noexcept;
    void on_note_off() noexcept;

    void reset_envelopes() noexcept;
    void release_envelopes() noexcept;

    /// Sets operator frequencies. Call after next() to use updated voice frequency
    void set_frequencies() noexcept;

    void action(voices::attack_tag::action, float a) noexcept final
    {
      env_.attack(a * a * 8.f + 0.005f);
    }
    void action(voices::decay_tag::action, float d) noexcept final
    {
      env_.decay(d * d * 4.f + 0.005f);
    }
    void action(voices::sustain_tag::action, float s) noexcept final
    {
      env_.sustain(s);
    }
    void action(voices::release_tag::action, float r) noexcept final
    {
      env_.release(r * r * 8.f + 0.005f);
    }

    // Not private because we need to show activity levels on screen
    std::tuple<FMOperator<0>, FMOperator<1>, FMOperator<2>, FMOperator<3>> operators;

  private:
    gam::ADSR<> env_ = {0.1f, 0.1f, 0.7f, 2.0f, 1.f, -4.f};
    Audio& audio;
  };

  struct Audio : itc::ActionReceiverOnBus<itc::AudioBus> {
    Audio(std::array<itc::Shared<float>, 4> activity) : shared_activity(activity) {
      set_children(voice_mgr_);
    }

    // Only a process call, since this sums the process calls of the voices.
    audio::ProcessData<1> process(audio::ProcessData<0>) noexcept;

    friend Voice;

    int algN_ = 0;
    int cur_op_ = 0;

    std::array<itc::Shared<float>, 4> shared_activity;

    voices::VoiceManager<Voice, 6> voice_mgr_ = {*this};
  };

} // namespace otto::engines::ottofm
