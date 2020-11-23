#include "testing.t.hpp"

#include <algorithm>
#include <set>
#include "lib/util/ranges.hpp"

#include "lib/voice_manager.hpp"

using namespace otto;
using namespace otto::voices;

TEST_CASE ("Voices") {
  struct Voice : VoiceBase<Voice> {
    Voice(int i) : i(i) {}
    int i = 0;
  };

  itc::ImmediateExecutor ex;
  itc::Channel<VoicesState> chan;
  itc::Producer<VoicesState> prod = chan;
  auto upd = prod.make_updater();

  Voices<Voice, 6> voices = {chan, ex, 42};

  SUBCASE ("Construction") {
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

  SUBCASE ("triggering voices") {
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

  SUBCASE ("When switching voice mode, all voices should be released") {
    voices.handle(midi::NoteOn{1});
    voices.handle(midi::NoteOn{2});
    voices.handle(midi::NoteOn{3});

    upd.play_mode() = PlayMode::mono;
    prod.produce(upd);

    REQUIRE(std::ranges::distance(triggered_voices()) == 0);
  }

  SUBCASE ("Poly Mode") {
    // voices_props.play_mode = +PlayMode::poly;
    // queue.pop_call_all();
    SUBCASE ("Poly mode is the initial setting") {
      REQUIRE(voices.play_mode() == PlayMode::poly);
    }

    SUBCASE ("Poly mode triggers one voice for a single note") {
      voices.handle(midi::NoteOn{50});
      REQUIRE(std::ranges::distance(triggered_voices()) == 1);
      REQUIRE(triggered_voices().front().midi_note() == 50);
      REQUIRE(triggered_voices().front().frequency() == test::approx(midi::note_freq(50)));
    }

    SUBCASE ("Poly mode triggers one voice per note") {
      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{60});
      REQUIRE(std::ranges::is_permutation(triggered_voices(), std::vector{50, 60}, std::ranges::equal_to(),
                                          &Voice::midi_note));
    }

    SUBCASE ("Poly mode discards the oldest note when voice count is exceeded and snaps back when released") {
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

    SUBCASE ("Poly mode reuses last used voice") {
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

    SUBCASE ("Poly mode cycles voices") {
      std::set<Voice*> used_voices;

      for (std::uint8_t i = 0; i < voices.size(); i++) {
        voices.handle(midi::NoteOn{i});
        used_voices.insert(
          &*std::ranges::find_if(voices, [i = i](Voice& v) { return v.is_triggered() && v.midi_note() == (int) i; }));
        voices.handle(midi::NoteOff{i});
      }
      REQUIRE(used_voices.size() == voices.size());
    }

    SUBCASE ("Poly mode rand") {
      upd.rand() = 0.5;
      prod.produce(upd);

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

    SUBCASE ("Keys held over the maximum limit are ignored") {
      for (std::uint8_t i = 1; i <= 12 * voices.voice_count_v + 1; i++) {
        voices.handle(midi::NoteOn{i});
      }
      // TODO: REQUIRE_THAT(test::sort(triggered_voices() | transform(MEMBER_CALLER(midi_note))),
      // TODO:              !Catch::Contains(std::vector{12 * voices.voice_count_v + 1}));

      for (std::uint8_t i = 1; i <= 12 * voices.voice_count_v; i++) {
        voices.handle(midi::NoteOff{i});
      }
      REQUIRE(std::ranges::distance(triggered_voices()) == 0);
    }
  }

  SUBCASE ("Interval Mode") {
    upd.play_mode() = PlayMode::interval;
    upd.interval() = 1;
    prod.produce(upd);

    SUBCASE ("Interval mode triggers two voices for a single note") {
      voices.handle(midi::NoteOn{50});
      REQUIRE(std::ranges::distance(triggered_voices()) == 2);
      check_notes({50, 51});
    }

    SUBCASE ("Interval mode triggers two voices per note") {
      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{60});
      check_notes({50, 51, 60, 61});
    }

    SUBCASE ("Note steal works like in poly") {
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

    SUBCASE ("Playing base and interval keys yields four voices") {
      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{51});
      check_notes({50, 51, 51, 52});
    }

    SUBCASE ("Playing base and interval keys and releasing one yields two voices") {
      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{51});
      voices.handle(midi::NoteOff{50});
      check_notes({51, 52});
    }

    SUBCASE ("Changing interval still allows removal of all notes") {
      voices.handle(midi::NoteOn{50});

      upd.interval() = 2;
      prod.produce(upd);
      check_notes({50, 51});

      voices.handle(midi::NoteOn{60});
      check_notes({50, 51, 60, 62});
      voices.handle(midi::NoteOff{50});
      check_notes({60, 62});
    }
  }


  SUBCASE ("Mono mode") {
    upd.play_mode() = PlayMode::mono;
    prod.produce(upd);

    SUBCASE ("Can switch to mono mode") {
      REQUIRE(voices.play_mode() == PlayMode::mono);
    }

    SUBCASE ("triggers one voice for a single note") {
      voices.handle(midi::NoteOn{50});
      REQUIRE(std::ranges::distance(triggered_voices()) == 1);
      REQUIRE(triggered_voices().front().midi_note() == 50);
      REQUIRE(triggered_voices().front().frequency() == test::approx(midi::note_freq(50)));
    }

    SUBCASE ("steals a voice for each new note") {
      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{60});
      check_notes({60});
    }

    SUBCASE ("Snaps back to playing old note when a note is released") {
      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{60});
      voices.handle(midi::NoteOff{60});
      check_notes({50});
    }

    SUBCASE ("Snaps back to playing CORRECT old note when a note is released") {
      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{60});
      voices.handle(midi::NoteOn{70});
      voices.handle(midi::NoteOff{70});
      check_notes({60});
    }

    SUBCASE ("AUX mode: Sub = 0.5") {
      upd.sub() = 0.5f;
      prod.produce(upd);

      voices.handle(midi::NoteOn{50});
      check_notes({38, 38, 50});
    }
  }

  SUBCASE ("Unison Mode") {
    upd.play_mode() = PlayMode::unison;
    prod.produce(upd);

    auto used_voices = VoiceAllocator<PlayMode::unison, Voice, 6>::num_voices_used;

    SUBCASE ("Can switch to unison mode") {
      REQUIRE(voices.play_mode() == PlayMode::unison);
    }

    SUBCASE ("Uses 5 voices (for 6 total voices)") {
      REQUIRE(VoiceAllocator<PlayMode::unison, Voice, 6>::num_voices_used == 5);
    }

    SUBCASE ("Unison triggers highest possible odd number of voices per note") {
      voices.handle(midi::NoteOn{1});
      REQUIRE(std::ranges::distance(triggered_voices()) == used_voices);
      voices.handle(midi::NoteOff{1});
      REQUIRE(std::ranges::distance(triggered_voices()) == 0);
    }

    SUBCASE ("steals voices for each new note") {
      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{60});
      auto expected_midi_notes = std::vector<int>(used_voices, 60);
      check_notes({60, 60, 60, 60, 60});
    }

    SUBCASE ("Snaps back to playing old notes when a note is released") {
      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{60});
      voices.handle(midi::NoteOff{60});
      auto expected_midi_notes = std::vector<int>(used_voices, 50);
      check_notes({50, 50, 50, 50, 50});
    }

    SUBCASE ("Voices keep same order (voice steal)") {
      voices.handle(midi::NoteOn{50});
      auto ordered_voices_expected = triggered_voice_ptrs();
      std::ranges::sort(ordered_voices_expected, {}, &Voice::frequency);
      voices.handle(midi::NoteOn{60});
      auto ordered_voices_actual = triggered_voice_ptrs();
      std::ranges::sort(ordered_voices_actual, {}, &Voice::frequency);
      REQUIRE(ordered_voices_expected == ordered_voices_actual);
    }

    SUBCASE ("Voices keep same order (voice return)") {
      voices.handle(midi::NoteOn{50});
      voices.handle(midi::NoteOn{60});
      auto ordered_voices_expected = triggered_voice_ptrs();
      std::ranges::sort(ordered_voices_expected, {}, &Voice::frequency);
      voices.handle(midi::NoteOff{60});
      auto ordered_voices_actual = triggered_voice_ptrs();
      std::ranges::sort(ordered_voices_actual, {}, &Voice::frequency);
      REQUIRE(ordered_voices_expected == ordered_voices_actual);
    }

    SUBCASE ("Voices keep same order (voice return) for non-zero detune") {
      upd.detune() = 0.1f;
      prod.produce(upd);

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
  SUBCASE ("Portamento") {
    upd.play_mode() = PlayMode::mono;
    prod.produce(upd);

    gam::sampleRate(100);
    float target_freq = midi::note_freq(62);

    SUBCASE ("Portamento = 0") {
      upd.portamento() = 0.f;
      prod.produce(upd);

      voices.handle(midi::NoteOn{50});
      auto& v = triggered_voices().front();
      v.calc_next();
      REQUIRE(v.frequency() == test::approx(midi::note_freq(50)).margin(0.01));
      voices.handle(midi::NoteOn{62});
      v.calc_next();
      REQUIRE(v.frequency() == test::approx(target_freq).margin(0.01));
    }

    SUBCASE ("Portamento = 1") {
      int expected_n = 100;

      upd.portamento() = 1.f;
      prod.produce(upd);

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
#if false
    }

    /// TODO: Make test for expected behaviour then legato is
    /// engaged for glide (jump the portamento step)
    /// and normal legato (on_note_on and on_note_off is not called).

    SUBCASE("Voice receives all envelope and voice settings actions")
    {
      struct Voice : VoiceBase<Voice> {
        float attack = 0;
        void action(attack_tag::action, float attack) noexcept
        {
          this->attack = attack;
        }
        float decay = 0;
        void action(decay_tag::action, float decay) noexcept
        {
          this->decay = decay;
        }
        float sustain = 0;
        void action(sustain_tag::action, float sustain) noexcept
        {
          this->sustain = sustain;
        }
        float release_ = 0;
        void action(release_tag::action, float release) noexcept
        {
          this->release_ = release;
        }
        PlayMode play_mode = PlayMode::poly;
        void action(play_mode_tag::action, PlayMode play_mode) noexcept
        {
          this->play_mode = play_mode;
        }
        bool legato = false;
        void action(legato_tag::action, bool legato) noexcept
        {
          this->legato = legato;
        }
        bool retrig = false;
        void action(retrig_tag::action, bool retrig) noexcept
        {
          this->retrig = retrig;
        }
        float rand = 0;
        void action(rand_tag::action, float rand) noexcept
        {
          this->rand = rand;
        }
        float sub = 0;
        void action(sub_tag::action, float sub) noexcept
        {
          this->sub = sub;
        }
        float detune = 0;
        void action(detune_tag::action, float detune) noexcept
        {
          this->detune = detune;
        }
        int interval = 0;
        void action(interval_tag::action, int interval) noexcept
        {
          this->interval = interval;
        }
        float portamento = 0;
        void action(portamento_tag::action, float portamento) noexcept
        {
          this->portamento = portamento;
        }
      };

      VoiceManager<Voice, 6> voices;

      call_receiver(voices, attack_tag::action::data(1.f));
      for (auto& v : voices.voices()) REQUIRE(v.attack == 1.f);
      call_receiver(voices, decay_tag::action::data(1.f));
      for (auto& v : voices.voices()) REQUIRE(v.decay == 1.f);
      call_receiver(voices, sustain_tag::action::data(1.f));
      for (auto& v : voices.voices()) REQUIRE(v.sustain == 1.f);
      call_receiver(voices, release_tag::action::data(1.f));
      for (auto& v : voices.voices()) REQUIRE(v.release_ == 1.f);
      call_receiver(voices, play_mode_tag::action::data(PlayMode::mono));
      for (auto& v : voices.voices()) REQUIRE(v.play_mode == +PlayMode::mono);
      call_receiver(voices, legato_tag::action::data(true));
      for (auto& v : voices.voices()) REQUIRE(v.legato == true);
      call_receiver(voices, retrig_tag::action::data(true));
      for (auto& v : voices.voices()) REQUIRE(v.retrig == true);
      call_receiver(voices, rand_tag::action::data(0.5));
      for (auto& v : voices.voices()) REQUIRE(v.rand == 0.5);
      call_receiver(voices, sub_tag::action::data(0.5));
      for (auto& v : voices.voices()) REQUIRE(v.sub == 0.5);
      call_receiver(voices, detune_tag::action::data(0.5));
      for (auto& v : voices.voices()) REQUIRE(v.detune == 0.5);
      call_receiver(voices, interval_tag::action::data(5));
      for (auto& v : voices.voices()) REQUIRE(v.interval == 5);
      call_receiver(voices, portamento_tag::action::data(0.5));
      for (auto& v : voices.voices()) REQUIRE(v.portamento == 0.5);
    }

    SUBCASE("call operators and process calls")
    {
      auto app = services::test::make_dummy_application();

      using namespace core::audio;
      SUBCASE("when voice has an operator(), voice and voices gets process() and operator()")
      {
        struct SVoice : voices::VoiceBase<SVoice> {
          float operator()() noexcept
          {
            return 1.f;
          }
        };

        VoiceManager<SVoice, 4> voices;

        REQUIRE(voices.voices()[0]() == 1.f);
        REQUIRE(voices() == test::approx(4.f * voices.normal_volume));
        // Note that voice_manager() applies volume in the example above
        // while voice() does not.

        AudioBufferHandle bh = services::AudioManager::current().buffer_pool().allocate_clear();
        // When running the default voice.process(), volume is applied. This carries over to
        // voice_manager.process()
        auto res = voices.voices()[0].process(ProcessData<0>{{}, {}, {}});
        REQUIRE(std::ranges::all_of(res.audio, util::does_equal(1 * voices.normal_volume)));
        auto res2 = voices.process(ProcessData<0>{{}, {}, {}});
        REQUIRE(std::ranges::all_of(res2.audio, util::does_equal(4 * voices.normal_volume)));
      }

      SUBCASE("when voice has a process(), voices only has process()")
      {
        struct SVoice : voices::VoiceBase<SVoice> {
          ProcessData<1> process(ProcessData<0> data) noexcept
          {
            auto buf = services::AudioManager::current().buffer_pool().allocate();
            std::ranges::fill(buf, 1);
            return data.with(buf);
          }
        };

        VoiceManager<SVoice, 4> voices;

        // We have written our own voice.process() so volume is not applied.
        auto res = voices.voices()[0].process(ProcessData<0>{{}, {}, {}});
        REQUIRE(std::ranges::all_of(res.audio, util::does_equal(1)));

        auto res2 = voices.process(ProcessData<0>{{}, {}, {}});
        REQUIRE(std::ranges::all_of(res2.audio, util::does_equal(4)));
      }
    }
#endif
  }
} // namespace otto::core::voices
