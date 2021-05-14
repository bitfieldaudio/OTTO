#include "app/services/audio.hpp"

#include <Gamma/Envelope.h>
#include <Gamma/Oscillator.h>

#include "lib/voices/voice_manager.hpp"

#include "nuke.hpp"

namespace otto::engines::nuke {

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
      env_.attack(envelope_stage_duration(s.envparam0));
      env_.decay(envelope_stage_duration(s.envparam1));
      env_.sustain(s.envparam2);
      env_.release(envelope_stage_duration(s.envparam3));
    }

    const State& state_;

  private:
    gam::Saw<> osc1{600};
    gam::ADSR<> env_;
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
  }

  void Voice::release_envelopes() noexcept
  {
    env_.release();
  }

  void Voice::set_frequencies() noexcept
  {
    float a = frequency();
    osc1.freq(a);
  }

  float Voice::operator()() noexcept
  {
    set_frequencies();
    return osc1() * env_();
  }

} // namespace otto::engines::nuke
