#include "core/voices/voice_manager.hpp"
#include "testing.t.hpp"

namespace otto::core::voices {

  namespace view = util::view;

  TEST_CASE ("VoiceManager") {
    struct Voice : voices::VoiceBase<Voice> {
      float operator()() noexcept
      {
        return 1.f;
      }
    };

    VoiceManager<Voice, 6> vmgr;
    using Sndr = itc::ActionSender<VoiceManager<Voice, 6>>;
    itc::ActionQueue queue;
    Sndr sndr = {queue, vmgr};

    EnvelopeProps<Sndr> envelope_props = {&sndr};
    SettingsProps<Sndr> voices_props = {&sndr};

    // This is a lazy view, so its computed each time you loop through it
    auto triggered_voices =
      view::filter(vmgr.voices(), [](Voice& v) { return v.is_triggered() && v.volume() != test::approx(0); });

    SECTION ("Simple voice loop") {
      int n = 0;
      for (Voice& voice : vmgr.voices()) {
        n++;
      }
      REQUIRE(n == 6);
    }

    SECTION ("When switching voice mode, all voices should be released") {
      vmgr.handle_midi(midi::NoteOnEvent{1});
      vmgr.handle_midi(midi::NoteOnEvent{2});
      vmgr.handle_midi(midi::NoteOnEvent{3});

      voices_props.play_mode = +PlayMode::mono;
      queue.pop_call_all();

      REQUIRE(util::count(triggered_voices) == 0);
    }

    SECTION ("Mono mode") {
      voices_props.play_mode = +PlayMode::mono;
      queue.pop_call_all();

      SECTION ("Can switch to mono mode") {
        REQUIRE(vmgr.play_mode() == +PlayMode::mono);
      }

      SECTION ("triggers one voice for a single note") {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        REQUIRE(util::count(triggered_voices) == 1);
        REQUIRE(triggered_voices.front().midi_note() == 50);
      }

      SECTION ("steals a voice for each new note") {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{60});
        REQUIRE_THAT(test::sort(view::transform(triggered_voices, WRAP_MEM_FUNC(midi_note))),
                     Catch::Equals(std::vector{60}));
      }

      SECTION ("Snaps back to playing old note when a note is released") {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{60});
        vmgr.handle_midi(midi::NoteOffEvent{60});
        REQUIRE_THAT(test::sort(view::transform(triggered_voices, WRAP_MEM_FUNC(midi_note))),
                     Catch::Equals(std::vector{50}));
      }

      SECTION ("AUX mode: Sub = 0.5") {
        voices_props.sub = 0.5f;
        queue.pop_call_all();

        vmgr.handle_midi(midi::NoteOnEvent{50});
        // REQUIRE_THAT(test::sort(view::transform(triggered_voices, WRAP_MEM_FUNC(midi_note))), Catch::Equals(std::vector{50, 50, 50}));
        // REQUIRE_THAT(test::sort(view::transform(triggered_voices, WRAP_MEM_FUNC(volume))), Catch::Equals(std::vector{0.5f, 0.5f, 0.5f}));
      }
    }

    SECTION ("Poly Mode") {
      voices_props.play_mode = +PlayMode::poly;
      queue.pop_call_all();

      SECTION ("Poly mode triggers one voice for a single note") {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        REQUIRE(util::count(triggered_voices) == 1);
        REQUIRE(triggered_voices.front().midi_note() == 50);
      }

      SECTION ("Poly mode triggers one voice per note") {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{60});
        REQUIRE_THAT(test::sort(view::transform(triggered_voices, WRAP_MEM_FUNC(midi_note))),
                     Catch::Equals(std::vector{50, 60}));
      }

      SECTION ("Poly mode discards the oldest note when voice count is exceeded") {
        vmgr.handle_midi(midi::NoteOnEvent{1});
        vmgr.handle_midi(midi::NoteOnEvent{2});
        vmgr.handle_midi(midi::NoteOnEvent{3});
        vmgr.handle_midi(midi::NoteOnEvent{4});
        vmgr.handle_midi(midi::NoteOnEvent{5});
        vmgr.handle_midi(midi::NoteOnEvent{6});
        vmgr.handle_midi(midi::NoteOnEvent{7});
        REQUIRE_THAT(test::sort(view::transform(triggered_voices, WRAP_MEM_FUNC(midi_note))),
                     Catch::Equals(std::vector{2, 3, 4, 5, 6, 7}));
      }
    }
  }

} // namespace otto::core::voices
