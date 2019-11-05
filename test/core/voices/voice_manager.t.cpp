#include <set>
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

    using VMgr = VoiceManager<Voice, 6>;
    VMgr vmgr;
    using Sndr = itc::ActionSender<VoiceManager<Voice, 6>>;
    itc::ActionQueue queue;
    Sndr sndr = {queue, vmgr};

    EnvelopeProps<Sndr> envelope_props = {&sndr};
    SettingsProps<Sndr> voices_props = {&sndr};

    // This is a lazy view, so its computed each time you loop through it
    auto triggered_voices =
      view::filter(vmgr.voices(), [](Voice& v) { return v.is_triggered() && v.volume() != test::approx(0); });

    auto triggered_voice_ptrs = view::transform(triggered_voices, [](Voice& v){return &v;});

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
        REQUIRE_THAT(test::sort(view::transform(triggered_voices, WRAP_MEM_FUNC(midi_note))),
                     Catch::Equals(std::vector{38, 38, 50}));
        REQUIRE_THAT(test::sort(view::transform(triggered_voices, WRAP_MEM_FUNC(volume))),
                     Catch::Approx(std::vector{0.25f, 0.5f, 1.f}));
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

      SECTION ("Poly mode discards the oldest note when voice count is exceeded and snaps back when released") {
        vmgr.handle_midi(midi::NoteOnEvent{1});
        vmgr.handle_midi(midi::NoteOnEvent{2});
        vmgr.handle_midi(midi::NoteOnEvent{3});
        vmgr.handle_midi(midi::NoteOnEvent{4});
        vmgr.handle_midi(midi::NoteOnEvent{5});
        vmgr.handle_midi(midi::NoteOnEvent{6});
        vmgr.handle_midi(midi::NoteOnEvent{7});
        REQUIRE_THAT(test::sort(view::transform(triggered_voices, WRAP_MEM_FUNC(midi_note))),
                     Catch::Equals(std::vector{2, 3, 4, 5, 6, 7}));
        vmgr.handle_midi(midi::NoteOffEvent{2});
        REQUIRE_THAT(test::sort(view::transform(triggered_voices, WRAP_MEM_FUNC(midi_note))),
                     Catch::Equals(std::vector{1, 3, 4, 5, 6, 7}));
      }

      SECTION ("Poly mode reuses last used voice") {
        vmgr.handle_midi(midi::NoteOnEvent{1});
        Voice* triggered_voice = &triggered_voices.front();
        vmgr.handle_midi(midi::NoteOnEvent{2});
        vmgr.handle_midi(midi::NoteOnEvent{3});
        vmgr.handle_midi(midi::NoteOffEvent{1});
        vmgr.handle_midi(midi::NoteOnEvent{1});
        Voice* new_voice = &*util::find_if(triggered_voices, [](Voice& v) { return v.midi_note() == 1; });
        REQUIRE(triggered_voice == new_voice);
      }

      SECTION ("Poly mode cycles voices") {
        std::set<Voice*> used_voices;

        for (int i : util::view::ints(0, vmgr.voices().size())) {
          vmgr.handle_midi(midi::NoteOnEvent{(int) i});
          used_voices.insert(&*util::find_if(triggered_voices, [i = i](Voice& v) { return v.midi_note() == (int) i; }));
          vmgr.handle_midi(midi::NoteOffEvent{(int) i});
        }
        REQUIRE(used_voices.size() == vmgr.voices().size());
      }
    }

    SECTION ("Unison Mode") {
      voices_props.play_mode = +PlayMode::unison;
      queue.pop_call_all();

      SECTION ("Can switch to unison mode") {
        REQUIRE(vmgr.play_mode() == +PlayMode::unison);
      }

      SECTION ("Uses 5 voices (for 6 total voices)") {
        REQUIRE(VMgr::UnisonAllocator::num_voices_used == 5);
      }

      SECTION ("Unison triggers highest possible odd number of voices per note") {
        vmgr.handle_midi(midi::NoteOnEvent{1});
        REQUIRE(util::count(triggered_voices) == VMgr::UnisonAllocator::num_voices_used);
        vmgr.handle_midi(midi::NoteOffEvent{1});
        REQUIRE(util::count(triggered_voices) == 0);
      }

      SECTION ("steals voices for each new note") {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{60});
        auto expected_midi_notes = std::vector<int>(VMgr::UnisonAllocator::num_voices_used, 60);
        REQUIRE_THAT(test::sort(view::transform(triggered_voices, WRAP_MEM_FUNC(midi_note))),
                     Catch::Equals(expected_midi_notes));
      }

      SECTION ("Snaps back to playing old notes when a note is released") {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{60});
        vmgr.handle_midi(midi::NoteOffEvent{60});
        auto expected_midi_notes = std::vector<int>(VMgr::UnisonAllocator::num_voices_used, 50);
        REQUIRE_THAT(test::sort(view::transform(triggered_voices, WRAP_MEM_FUNC(midi_note))),
                     Catch::Equals(expected_midi_notes));
      }

      SECTION ("Voices keep same order (voice steal)") {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        auto ordered_voices_expected = test::sort(triggered_voice_ptrs, [](Voice* v){return v->frequency();} );
        vmgr.handle_midi(midi::NoteOnEvent{60});
        auto ordered_voices_actual = test::sort(triggered_voice_ptrs, [](Voice* v){return v->frequency();} );
        REQUIRE_THAT(ordered_voices_expected, Catch::Equals(ordered_voices_actual));
      }

      SECTION ("Voices keep same order (voice return)") {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{60});
        auto ordered_voices_expected = test::sort(triggered_voice_ptrs, [](Voice* v){return v->frequency();} );
        vmgr.handle_midi(midi::NoteOffEvent{60});
        auto ordered_voices_actual = test::sort(triggered_voice_ptrs, [](Voice* v){return v->frequency();} );
        REQUIRE_THAT(ordered_voices_expected, Catch::Equals(ordered_voices_actual));
      }

      SECTION ("Repeat above for non-zero detune") {
        voices_props.detune = 0.1;
        queue.pop_call_all();

        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{60});
        auto ordered_voices_expected = test::sort(triggered_voice_ptrs, [](Voice* v){return v->frequency();} );
        vmgr.handle_midi(midi::NoteOffEvent{60});
        auto ordered_voices_actual = test::sort(triggered_voice_ptrs, [](Voice* v){return v->frequency();} );
        REQUIRE_THAT(ordered_voices_expected, Catch::Equals(ordered_voices_actual));
      }
    }

    SECTION ("Interval Mode") {
      voices_props.play_mode = +PlayMode::interval;
      voices_props.interval = 1;
      queue.pop_call_all();
      

      SECTION ("Interval mode triggers two voices for a single note") {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        REQUIRE(util::count(triggered_voices) == 2);
        REQUIRE_THAT(test::sort(view::transform(triggered_voices, WRAP_MEM_FUNC(midi_note))), 
              Catch::Equals(std::vector{50, 51}));
      }

      SECTION ("Interval mode triggers two voices per note") {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{60});
        REQUIRE_THAT(test::sort(view::transform(triggered_voices, WRAP_MEM_FUNC(midi_note))), 
              Catch::Equals(std::vector{50, 51, 60, 61}));
      }

      SECTION ("Note steal works like in poly"){
        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{60});
        vmgr.handle_midi(midi::NoteOnEvent{70});
        vmgr.handle_midi(midi::NoteOnEvent{80});
        // Note steal
        REQUIRE_THAT(test::sort(view::transform(triggered_voices, WRAP_MEM_FUNC(midi_note))), 
              Catch::Equals(std::vector{60, 61, 70, 71, 80, 81}));
        // Note return
        vmgr.handle_midi(midi::NoteOffEvent{70});
        REQUIRE_THAT(test::sort(view::transform(triggered_voices, WRAP_MEM_FUNC(midi_note))), 
              Catch::Equals(std::vector{50, 51, 60, 61, 80, 81}));
      }

      SECTION ("Playing base and interval keys yields four voices"){
        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{51});
        REQUIRE_THAT(test::sort(view::transform(triggered_voices, WRAP_MEM_FUNC(midi_note))), 
              Catch::Equals(std::vector{50, 51, 51, 52}));
      }

      SECTION ("Playing base and interval keys and releasing one yields two voices"){
        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{51});
        vmgr.handle_midi(midi::NoteOffEvent{50});
        REQUIRE_THAT(test::sort(view::transform(triggered_voices, WRAP_MEM_FUNC(midi_note))), 
              Catch::Equals(std::vector{51, 52}));
      }

      SECTION ("Changing interval still allows removal of all notes") {
        vmgr.handle_midi(midi::NoteOnEvent{50});

        voices_props.interval = 2;
        queue.pop_call_all();
        REQUIRE_THAT(test::sort(view::transform(triggered_voices, WRAP_MEM_FUNC(midi_note))), 
              Catch::Equals(std::vector{50, 51}));
        
        vmgr.handle_midi(midi::NoteOnEvent{60});
        REQUIRE_THAT(test::sort(view::transform(triggered_voices, WRAP_MEM_FUNC(midi_note))), 
              Catch::Equals(std::vector{50, 51, 60, 62}));
        vmgr.handle_midi(midi::NoteOffEvent{50});
        REQUIRE_THAT(test::sort(view::transform(triggered_voices, WRAP_MEM_FUNC(midi_note))), 
              Catch::Equals(std::vector{60, 62}));
      }
    }
  }

} // namespace otto::core::voices
