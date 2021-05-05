#include "app/services/audio.hpp"

#include "arp.hpp"

namespace otto::engines::arp {
  using namespace otto;
  struct Audio final : AudioDomain, itc::Consumer<State>, IMidiFXAudio {
    Audio(itc::Context& ch) : Consumer(ch) {}

    // Necessary state to store in the audio object
    ArpeggiatorState arp_state;
    NoteArray notes_;
    NoteVector current_notes_;
    PlayModeFunc playmode_func_ = play_modes::up;
    OctaveModeFunc octavemode_func_ = octave_modes::standard;
    // Only temporary
    std::size_t buffer_count = 0;
    int buffers_per_beat = 25;

    // Helper functions
    static void insert_note(NoteArray& notes, std::uint8_t note)
    {
      std::int8_t t = notes.empty() ? 0 : notes.back().t + 1;
      notes.push_back({note, t});
    }

    static void erase_note(NoteArray& notes, std::uint8_t note)
    {
      std::erase_if(notes, [&](NoteTPair& ntp) { return ntp.note == note; });
    }
    // Note On
    void handle(const midi::NoteOn ev) noexcept override
    {
      // TODO: Move this to the dispatcher!
      if (!state().active) {
        target().handle(ev);
        return;
      }
      insert_note(notes_, ev.note);
      arp_state.invalidate_om_cache();
    }
    /// Note Off
    void handle(const midi::NoteOff ev) noexcept override
    {
      // TODO: Move this to the dispatcher!
      if (!state().active) {
        target().handle(ev);
        return;
      }
      erase_note(notes_, ev.note);
      arp_state.invalidate_om_cache();
    };

    void process() noexcept override
    {
      // TODO: Should be a part of the EngineDispatcher
      if (!state().active) return;

      auto at_beat = [&](std::size_t cnt) { return cnt % buffers_per_beat == 0; };
      auto at_note_off = [&](std::size_t cnt) {
        return cnt % buffers_per_beat == static_cast<int>(state().note_length * (buffers_per_beat - 2)) + 1;
      };

      // Both should check "if(running && ...)"
      if (at_note_off(buffer_count)) {
        for (auto note : current_notes_) {
          target().handle(midi::NoteOff{.note = note});
        }
        current_notes_.clear();
      }

      if (at_beat(buffer_count)) {
        current_notes_ = octavemode_func_(arp_state, notes_, playmode_func_);
        // Send note-on events to midi stream
        for (auto note : current_notes_) {
          target().handle(midi::NoteOn{.note = note, .velocity = 1 << 7});
        }
      }
      buffer_count++;
    }

    void on_state_change(const State& s) noexcept override
    {
      playmode_func_ = play_modes::func(s.playmode);
      if (octavemode_func_ != octave_modes::func(s.octavemode)) {
        octavemode_func_ = octave_modes::func(s.octavemode);
        arp_state.invalidate_om_cache();
      }

      constexpr float samples_per_buffer = 256;
      constexpr int samples_per_minute = 44100 * 60;
      constexpr float buffers_per_minute = samples_per_minute / samples_per_buffer;
      buffers_per_beat = buffers_per_minute / state().bpm;
    }
  };

  std::unique_ptr<IMidiFXAudio> make_audio(itc::Context& ctx)
  {
    return std::make_unique<Audio>(ctx);
  }

} // namespace otto::engines::arp
