#include "testing.t.hpp"

#include "lib/voices/voice_manager.hpp"

#include <algorithm>
#include <set>

#include "lib/util/ranges.hpp"

#include "app/services/config.hpp"

#include "stubs/audio.hpp"

using namespace otto;
using namespace otto::voices;

// TODO: Fix portamento tests
TEST_CASE ("VoiceManager", "[!mayfail]") {
  itc::ImmediateExecutor ex;
  AudioDomain::set_static_executor(ex);

  itc::ImmediateExecutor ex2;
  LogicDomain::set_static_executor(ex2);

  services::RuntimeController rt;

  services::Audio audioman(std::make_unique<stubs::NoProcessAudioDriver>());

  struct Voice : VoiceBase<Voice> {
    Voice(int i) : i(i) {}
    int i = 0;
  };
  itc::Context ctx;
  itc::WithDomain<LogicDomain, itc::Producer<VoicesState>> prod = ctx;

  VoiceManager<Voice, 6> voices = {ctx, 42};

  SECTION ("Construction") {
    REQUIRE(stdr::distance(voices) == 6);
    for (Voice& v : voices) {
      REQUIRE(v.i == 42);
    }
  }

  auto triggered_voices = [&] {
    return util::filter(voices, [](Voice& v) { return v.is_triggered() && (v.volume() > 0); });
  };
  auto triggered_voice_ptrs = [&] {
    std::vector<Voice*> res;
    std::ranges::transform(triggered_voices(), std::back_inserter(res), util::addressof);
    return res;
  };
  auto check_notes = [&](std::initializer_list<int> il) {
    auto tv = util::transform(triggered_voices(), std::mem_fn(&Voice::midi_note));
    INFO(fmt::format("Expected: {}", fmt::join(il, ", ")));
    INFO(fmt::format("Got: {}", fmt::join(tv.begin(), tv.end(), ", ")));
    REQUIRE(std::ranges::is_permutation(triggered_voices(), il, std::ranges::equal_to(), &Voice::midi_note));
  };

  SECTION ("triggering voices") {
    REQUIRE(stdr::distance(triggered_voices()) == 0);
    voices.handle(midi::NoteOn{1});
    REQUIRE(stdr::distance(triggered_voices()) == 1);
    voices.handle(midi::NoteOn{2});
    voices.handle(midi::NoteOn{3});
    REQUIRE(stdr::distance(triggered_voices()) == 3);

    std::set<Voice*> vs;
    for (auto& v : triggered_voices()) {
      vs.insert(&v);
      REQUIRE(v.is_triggered());
    }
    REQUIRE(vs.size() == 3);
    REQUIRE(std::ranges::distance(triggered_voices()) == 3);
  }

  SECTION ("When switching voice mode, all voices should be released") {
    voices.handle(midi::NoteOn{1});
    voices.handle(midi::NoteOn{2});
    voices.handle(midi::NoteOn{3});

    prod.commit([](auto& state) { state.play_mode = PlayMode::mono; });

    REQUIRE(std::ranges::distance(triggered_voices()) == 0);
  }

  SECTION ("Poly Mode") {
    // voices_props.play_mode = +PlayMode::poly;
    // queue.pop_call_all();
    SECTION ("Poly mode is the initial setting") {
      REQUIRE(voices.play_mode() == PlayMode::poly);
    }

    SECTION ("Poly mode triggers one voice for a single note") {
      voices.handle(midi::NoteOn{50});
      REQUIRE(std::ranges::distance(triggered_voices()) == 1);
      REQUIRE(triggered_voices().front().midi_note() == 50);
      REQUIRE(triggered_voices().front().frequency() == test::approx(midi::note_freq(50)));
    }

    SECTION ("Poly mode triggers one voice per note") {
      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{60});
      REQUIRE(std::ranges::is_permutation(triggered_voices(), std::vector{50, 60}, std::ranges::equal_to(),
                                          &Voice::midi_note));
    }

    SECTION ("Poly mode discards the oldest note when voice count is exceeded and snaps back when released") {
      voices.handle(midi::NoteOn{1});
      voices.handle(midi::NoteOn{2});
      voices.handle(midi::NoteOn{3});
      voices.handle(midi::NoteOn{4});
      voices.handle(midi::NoteOn{5});
      voices.handle(midi::NoteOn{6});
      voices.handle(midi::NoteOn{7});
      CAPTURE(std::ranges::distance(triggered_voices()));
      REQUIRE(std::ranges::is_permutation(triggered_voices(), std::vector{2, 3, 4, 5, 6, 7}, std::ranges::equal_to(),
                                          &Voice::midi_note));
      voices.handle(midi::NoteOff{2});
      CAPTURE(std::ranges::distance(triggered_voices()));
      REQUIRE(std::ranges::is_permutation(triggered_voices(), std::vector{1, 3, 4, 5, 6, 7}, std::ranges::equal_to(),
                                          &Voice::midi_note));
    }

    SECTION ("Poly mode reuses last used voice") {
      voices.handle(midi::NoteOn{1});
      Voice* triggered_voice = &triggered_voices().front();
      voices.handle(midi::NoteOn{2});
      voices.handle(midi::NoteOn{3});
      voices.handle(midi::NoteOff{1});
      voices.handle(midi::NoteOn{1});
      Voice* new_voice =
        &*std::ranges::find_if(voices, [](Voice& v) { return v.is_triggered() && v.midi_note() == 1; });
      REQUIRE(triggered_voice == new_voice);
    }

    SECTION ("Poly mode cycles voices") {
      std::set<Voice*> used_voices;

      for (std::uint8_t i = 0; i < std::uint8_t(voices.size()); i++) {
        voices.handle(midi::NoteOn{i});
        used_voices.insert(
          &*std::ranges::find_if(voices, [i = i](Voice& v) { return v.is_triggered() && v.midi_note() == (int) i; }));
        voices.handle(midi::NoteOff{i});
      }
      REQUIRE(used_voices.size() == voices.size());
    }

    SECTION ("Poly mode rand") {
      prod.commit([](auto& state) { state.rand = 0.5; });

      std::set<float> vals;
      for (std::uint8_t i = 0; i < 5; i++) {
        auto freq = midi::note_freq(50 + i);
        voices.handle(midi::NoteOn{std::uint8_t(50 + i)});
        auto& v = triggered_voices().front();
        CAPTURE(i);
        CHECK(v.frequency() == test::approx(freq).margin(freq * 0.1));
        vals.insert(v.frequency() / freq);
        voices.handle(midi::NoteOff{std::uint8_t(50 + i)});
      }
      REQUIRE(vals.size() == 5);
    }

    SECTION ("Keys held over the maximum limit are ignored") {
      for (std::uint8_t i = 1; i <= std::uint8_t(12 * voices.voice_count_v) + 1; i++) {
        voices.handle(midi::NoteOn{i});
      }
      // TODO: REQUIRE_THAT(test::sort(triggered_voices() | transform(MEMBER_CALLER(midi_note))),
      // TODO:              !Catch::Contains(std::vector{12 * voices.voice_count_v + 1}));

      for (std::uint8_t i = 1; i <= 12 * voices.voice_count_v; i++) {
        voices.handle(midi::NoteOff{i});
      }
      REQUIRE(std::ranges::distance(triggered_voices()) == 0);
    }

    SECTION ("Voice::volume() is VoiceManager::normal_volume") {
      REQUIRE(voices[0].volume() == voices.normal_volume);
    }
  }

  SECTION ("Duo Mode") {
    prod.commit([](auto& state) {
      state.play_mode = PlayMode::duo;
      state.interval = 1;
    });

    SECTION ("Duo mode triggers two voices for a single note") {
      voices.handle(midi::NoteOn{50});
      REQUIRE(std::ranges::distance(triggered_voices()) == 2);
      check_notes({50, 51});
    }

    SECTION ("Duo mode triggers two voices per note") {
      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{60});
      check_notes({50, 51, 60, 61});
    }

    SECTION ("Note steal works like in poly") {
      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{60});
      voices.handle(midi::NoteOn{70});
      voices.handle(midi::NoteOn{80});
      // Note steal
      check_notes({60, 61, 70, 71, 80, 81});
      // Note return
      voices.handle(midi::NoteOff{70});
      check_notes({50, 51, 60, 61, 80, 81});
    }

    SECTION ("Playing base and interval keys yields four voices") {
      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{51});
      check_notes({50, 51, 51, 52});
    }

    SECTION ("Playing base and interval keys and releasing one yields two voices") {
      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{51});
      voices.handle(midi::NoteOff{50});
      check_notes({51, 52});
    }

    SECTION ("Changing interval still allows removal of all notes") {
      voices.handle(midi::NoteOn{50});

      prod.commit([](auto& state) { state.interval = 2; });
      check_notes({50, 51});

      voices.handle(midi::NoteOn{60});
      check_notes({50, 51, 60, 62});
      voices.handle(midi::NoteOff{50});
      check_notes({60, 62});
    }
  }


  SECTION ("Mono mode") {
    prod.commit([](auto& state) { state.play_mode = PlayMode::mono; });

    SECTION ("Can switch to mono mode") {
      REQUIRE(voices.play_mode() == PlayMode::mono);
    }

    SECTION ("triggers one voice for a single note") {
      voices.handle(midi::NoteOn{50});
      REQUIRE(std::ranges::distance(triggered_voices()) == 1);
      REQUIRE(triggered_voices().front().midi_note() == 50);
      REQUIRE(triggered_voices().front().frequency() == test::approx(midi::note_freq(50)));
    }

    SECTION ("steals a voice for each new note") {
      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{60});
      check_notes({60});
    }

    SECTION ("Snaps back to playing old note when a note is released") {
      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{60});
      voices.handle(midi::NoteOff{60});
      check_notes({50});
    }

    SECTION ("Snaps back to playing CORRECT old note when a note is released") {
      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{60});
      voices.handle(midi::NoteOn{70});
      voices.handle(midi::NoteOff{70});
      check_notes({60});
    }

    SECTION ("AUX mode: Sub = 0.5") {
      prod.commit([](auto& state) { state.sub = 0.5f; });

      voices.handle(midi::NoteOn{50});
      check_notes({38, 38, 50});
    }
  }

  SECTION ("Unison Mode") {
    prod.commit([](auto& state) { state.play_mode = PlayMode::unison; });

    auto used_voices = VoiceAllocator<PlayMode::unison, Voice, 6>::num_voices_used;

    SECTION ("Can switch to unison mode") {
      REQUIRE(voices.play_mode() == PlayMode::unison);
    }

    SECTION ("Uses 5 voices (for 6 total voices)") {
      REQUIRE(VoiceAllocator<PlayMode::unison, Voice, 6>::num_voices_used == 5);
    }

    SECTION ("Unison triggers highest possible odd number of voices per note") {
      voices.handle(midi::NoteOn{1});
      REQUIRE(std::ranges::distance(triggered_voices()) == used_voices);
      voices.handle(midi::NoteOff{1});
      REQUIRE(std::ranges::distance(triggered_voices()) == 0);
    }

    SECTION ("steals voices for each new note") {
      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{60});
      auto expected_midi_notes = std::vector<int>(used_voices, 60);
      check_notes({60, 60, 60, 60, 60});
    }

    SECTION ("Snaps back to playing old notes when a note is released") {
      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{60});
      voices.handle(midi::NoteOff{60});
      auto expected_midi_notes = std::vector<int>(used_voices, 50);
      check_notes({50, 50, 50, 50, 50});
    }

    SECTION ("Voices keep same order (voice steal)") {
      voices.handle(midi::NoteOn{50});
      auto ordered_voices_expected = triggered_voice_ptrs();
      std::ranges::sort(ordered_voices_expected, {}, &Voice::frequency);
      voices.handle(midi::NoteOn{60});
      auto ordered_voices_actual = triggered_voice_ptrs();
      std::ranges::sort(ordered_voices_actual, {}, &Voice::frequency);
      REQUIRE(ordered_voices_expected == ordered_voices_actual);
    }

    SECTION ("Voices keep same order (voice return)") {
      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{60});
      auto ordered_voices_expected = triggered_voice_ptrs();
      std::ranges::sort(ordered_voices_expected, {}, &Voice::frequency);
      voices.handle(midi::NoteOff{60});
      auto ordered_voices_actual = triggered_voice_ptrs();
      std::ranges::sort(ordered_voices_actual, {}, &Voice::frequency);
      REQUIRE(ordered_voices_expected == ordered_voices_actual);
    }

    SECTION ("Voices keep same order (voice return) for non-zero detune") {
      prod.commit([](auto& state) { state.detune = 0.1f; });

      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{60});
      auto ordered_voices_expected = triggered_voice_ptrs();
      std::ranges::sort(ordered_voices_expected, {}, &Voice::frequency);
      voices.handle(midi::NoteOff{60});
      auto ordered_voices_actual = triggered_voice_ptrs();
      std::ranges::sort(ordered_voices_actual, {}, &Voice::frequency);
      REQUIRE(ordered_voices_expected == ordered_voices_actual);
    }
  }
  SECTION ("Portamento") {
    prod.commit([](auto& state) { state.play_mode = PlayMode::mono; });

    gam::sampleRate(100);
    float target_freq = midi::note_freq(62);

    SECTION ("Portamento = 0") {
      prod.commit([](auto& state) { state.portamento = 0.f; });

      voices.handle(midi::NoteOn{50});
      auto& v = triggered_voices().front();
      v.calc_next();
      REQUIRE(v.frequency() == test::approx(midi::note_freq(50)).margin(0.01));
      voices.handle(midi::NoteOn{62});
      v.calc_next();
      REQUIRE(v.frequency() == test::approx(target_freq).margin(0.01));
    }

    SECTION ("Portamento = 1") {
      int expected_n = 100;

      prod.commit([](auto& state) { state.portamento = 1.f; });

      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{62});

      auto& v = triggered_voices().front();
      float f = midi::note_freq(50);
      // Skip first frame, which should be the start frequency
      v.calc_next();
      REQUIRE(v.frequency() == f);
      for (int i = 0; i < expected_n; i++) {
        v.calc_next();
        INFO("i = " << i);
        float f2 = v.frequency();
        // Frequency increases for each sample
        REQUIRE(f2 > f);
        f = f2;
      }
      // At the end, the target frequency is reached
      REQUIRE(v.frequency() == test::approx(target_freq).margin(0.01));
    }
  }

  // TODO: Make test for expected behaviour when legato is
  // engaged for glide (jump the portamento step)
  // and normal legato (on_note_on and on_note_off is not called).

  SECTION ("call operators and process calls") {
    SECTION ("VoiceManager::operator()") {
      struct SVoice : voices::VoiceBase<SVoice> {
        float operator()() noexcept
        {
          return 1.f;
        }
      };

      itc::Context ctx;
      VoiceManager<SVoice, 4> vmgr(ctx);

      REQUIRE(vmgr[0]() == 1.f);
      // REQUIRE(vmgr() == test::approx(4.f * vmgr.normal_volume));
      // Note that voice_manager() applies volume in the example above
      // while voice() does not.
    }

    SECTION ("Extra args to VoiceManager::operator() are forwarded to Voice::operator()") {
      struct Voice : voices::VoiceBase<Voice> {
        float operator()(int i, int& a, int& b)
        {
          REQUIRE(i == 10);
          REQUIRE(&a == &b);
          return float(i);
        }
      };
      itc::Context ctx;
      VoiceManager<Voice, 4> vmgr(ctx);
      // int a = 0;
      // REQUIRE(vmgr(10, a, a) == Catch::Approx(4 * 10.f * vmgr.normal_volume));
    }

    SECTION ("Voice::calc_next is called before each Voice::operator()") {}
  }
} // namespace otto::core::voices
