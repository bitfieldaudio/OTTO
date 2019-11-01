#include "core/voices/voice_manager.hpp"
#include "testing.t.hpp"

namespace otto::core::voices {

  template<typename Cont>
  auto sort_voices(Cont&& cont)
  {
    auto vec = util::view::to_vec(cont);
    util::sort(vec, [](auto&& a, auto&& b) { return a.midi_note() < b.midi_note(); });
    return vec;
  }

  TEST_CASE ("VoiceManager") {
    struct Voice : voices::VoiceBase<Voice> {
      float operator()() noexcept
      {
        return 1.f;
      }
    };

    VoiceManager<Voice, 6> vmgr;
    using Aqh = core2::ActionQueueHelper<VoiceManager<Voice, 6>>;
    core2::ActionQueue queue;
    Aqh aqh = {queue, vmgr};

    EnvelopeProps<Aqh> envelope_props = {&aqh};
    SettingsProps<Aqh> voices_props = {&aqh};

    // This is a lazy view, so its computed each time you loop through it
    auto triggered_voices = util::view::filter(vmgr.voices(), &Voice::is_triggered);

    SECTION ("Simple voice loop") {
      int n = 0;
      for (Voice& voice : vmgr.voices()) {
        n++;
      }
      REQUIRE(n == 6);
    }

    SECTION ("Can switch to mono mode") {
      voices_props.play_mode = +PlayMode::mono;
      queue.pop_call_all();

      REQUIRE(vmgr.play_mode() == +PlayMode::mono);
    }

    SECTION ("Poly mode triggers one voice for a single note") {
      voices_props.play_mode = +PlayMode::poly;
      queue.pop_call_all();

      vmgr.handle_midi(midi::NoteOnEvent{50});
      REQUIRE(util::count(triggered_voices) == 1);
      REQUIRE(triggered_voices.front().midi_note() == 50);
    }

    SECTION ("Poly mode triggers one voice per note") {
      voices_props.play_mode = +PlayMode::poly;
      queue.pop_call_all();

      vmgr.handle_midi(midi::NoteOnEvent{50});
      vmgr.handle_midi(midi::NoteOnEvent{60});
      REQUIRE_THAT(test::sort(util::view::transform(triggered_voices, &Voice::midi_note)),
                   Catch::Equals(std::vector{50, 60}));
    }

    SECTION ("Poly mode discards the oldest note when voice count is exceeded") {
      voices_props.play_mode = +PlayMode::poly;
      queue.pop_call_all();

      vmgr.handle_midi(midi::NoteOnEvent{1});
      vmgr.handle_midi(midi::NoteOnEvent{2});
      vmgr.handle_midi(midi::NoteOnEvent{3});
      vmgr.handle_midi(midi::NoteOnEvent{4});
      vmgr.handle_midi(midi::NoteOnEvent{5});
      vmgr.handle_midi(midi::NoteOnEvent{6});
      vmgr.handle_midi(midi::NoteOnEvent{7});
      REQUIRE_THAT(test::sort(util::view::transform(triggered_voices, &Voice::midi_note)),
                   Catch::Equals(std::vector{2, 3, 4, 5, 6, 7}));
    }

    SECTION ("When switching voice mode, all voices should be released") {
      vmgr.handle_midi(midi::NoteOnEvent{1});
      vmgr.handle_midi(midi::NoteOnEvent{2});
      vmgr.handle_midi(midi::NoteOnEvent{3});

      voices_props.play_mode = +PlayMode::mono;
      queue.pop_call_all();

      REQUIRE(util::count(triggered_voices) == 0);
    }
  }

} // namespace otto::core::voices
