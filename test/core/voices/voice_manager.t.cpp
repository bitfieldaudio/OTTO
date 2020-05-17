#include <set>

#include "core/voices/voice_manager.hpp"
#include "dummy_services.hpp"
#include "testing.t.hpp"
#include <nanorange.hpp>

namespace otto::core::voices {

  using namespace nano::views;

  TEST_CASE ("VoiceManager") {
    using test_action = itc::Action<struct test_action_tag, float>;

    struct Voice : voices::VoiceBase<Voice> {
      Voice(int& r) noexcept : reference(r){};

      float operator()() noexcept
      {
        return 1.f;
      }

      void action(test_action, float f)
      {
        this->f += f;
      }

      using voices::VoiceBase<Voice>::action;

      int& reference;
      float f = 0;
    };

    int shared_int = 0;

    using VMgr = VoiceManager<Voice, 6>;
    VMgr vmgr = {shared_int};

    using Sndr = itc::ActionSender<VoiceManager<Voice, 6>>;
    itc::ActionQueue queue;
    Sndr sndr = {queue, vmgr};

    // EnvelopeProps<Sndr> envelope_props = {&sndr};
    SettingsProps<Sndr> voices_props = {sndr};

    static_assert(!nano::view<std::decay_t<decltype(vmgr.voices())>>);

    auto triggered_voices = [&]() -> auto&
    {
      auto v = [&] {
        return vmgr.voices() | filter([](Voice& v) {
                 return v.is_triggered() && v.volume() != test::approx(0);
               });
      };
      thread_local static decltype(v()) cached;
      cached = v();
      return cached;
    };

    auto triggered_voice_ptrs = [&]() -> auto&
    {
      auto v = [&] {
        return triggered_voices() | transform([] (Voice& v) { return &v; });
      };
      thread_local static decltype(v()) cached;
      cached = v();
      return cached;
    };

    SUBCASE("Voice receives actions sent to voice manager")
    {
      itc::call_receiver(vmgr, test_action::data(1));
    }

    SUBCASE("Simple voice loop")
    {
      int n = 0;
      for (Voice& voice : vmgr.voices()) {
        n++;
      }
      REQUIRE(n == 6);
    }


    SUBCASE("triggered_voices()")
    {
      REQUIRE(util::count(triggered_voices()) == 0);
      vmgr.handle_midi(midi::NoteOnEvent{1});
      vmgr.handle_midi(midi::NoteOnEvent{2});
      vmgr.handle_midi(midi::NoteOnEvent{3});

      std::set<Voice*> vs;
      for (auto& v : triggered_voices()) {
        vs.insert(&v);
        REQUIRE(v.is_triggered());
      }
      REQUIRE(vs.size() == 3);
      REQUIRE(util::count(triggered_voices()) == 3);
    }

    SUBCASE("When switching voice mode, all voices should be released")
    {
      vmgr.handle_midi(midi::NoteOnEvent{1});
      vmgr.handle_midi(midi::NoteOnEvent{2});
      vmgr.handle_midi(midi::NoteOnEvent{3});

      voices_props.play_mode = +PlayMode::mono;
      queue.pop_call_all();

      REQUIRE(util::count(triggered_voices()) == 0);
    }

    SUBCASE("Mono mode")
    {
      voices_props.play_mode = +PlayMode::mono;
      queue.pop_call_all();

      SUBCASE("Can switch to mono mode")
      {
        REQUIRE(vmgr.play_mode() == +PlayMode::mono);
      }

      SUBCASE("triggers one voice for a single note")
      {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        REQUIRE(util::count(triggered_voices()) == 1);
        REQUIRE(triggered_voices().front().midi_note() == 50);
        REQUIRE(triggered_voices().front().frequency() == test::approx(midi::note_freq(50)));
      }

      SUBCASE("steals a voice for each new note")
      {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{60});
        REQUIRE(test::sort(triggered_voices() | transform(MEMBER_CALLER(midi_note))) == std::vector{60});
      }

      SUBCASE("Snaps back to playing old note when a note is released")
      {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{60});
        vmgr.handle_midi(midi::NoteOffEvent{60});
        REQUIRE(test::sort(triggered_voices() | transform(MEMBER_CALLER(midi_note))) == std::vector{50});
      }

      SUBCASE("Snaps back to playing CORRECT old note when a note is released")
      {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{60});
        vmgr.handle_midi(midi::NoteOnEvent{70});
        vmgr.handle_midi(midi::NoteOffEvent{70});
        REQUIRE(test::sort(triggered_voices() | transform(MEMBER_CALLER(midi_note))) == std::vector{60});
      }



      SUBCASE("AUX mode: Sub = 0.5")
      {
        voices_props.sub = 0.5f;
        queue.pop_call_all();

        vmgr.handle_midi(midi::NoteOnEvent{50});
        REQUIRE(test::sort(triggered_voices() | transform(MEMBER_CALLER(midi_note))) == std::vector{38, 38, 50});
        // REQUIRE(test::sort(triggered_voices() | transform(MEMBER_CALLER(volume))) ==
        //         std::vector<test::approx>{0.25f * vmgr.normal_volume, 0.5f * vmgr.normal_volume,
        //         vmgr.normal_volume});
      }
    }

    SUBCASE("Poly Mode")
    {
      // voices_props.play_mode = +PlayMode::poly;
      // queue.pop_call_all();
      SUBCASE("Poly mode is the initial setting")
      {
        REQUIRE(vmgr.play_mode() == +PlayMode::poly);
      }

      SUBCASE("Poly mode triggers one voice for a single note")
      {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        REQUIRE(util::count(triggered_voices()) == 1);
        REQUIRE(triggered_voices().front().midi_note() == 50);
        REQUIRE(triggered_voices().front().frequency() == test::approx(midi::note_freq(50)));
      }

      SUBCASE("Poly mode triggers one voice per note")
      {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{60});
        REQUIRE(test::sort(triggered_voices() | transform(MEMBER_CALLER(midi_note))) == std::vector{50, 60});
      }

      SUBCASE("Poly mode discards the oldest note when voice count is exceeded and snaps back when released")
      {
        vmgr.handle_midi(midi::NoteOnEvent{1});
        vmgr.handle_midi(midi::NoteOnEvent{2});
        vmgr.handle_midi(midi::NoteOnEvent{3});
        vmgr.handle_midi(midi::NoteOnEvent{4});
        vmgr.handle_midi(midi::NoteOnEvent{5});
        vmgr.handle_midi(midi::NoteOnEvent{6});
        vmgr.handle_midi(midi::NoteOnEvent{7});
        REQUIRE(test::sort(triggered_voices() | transform(MEMBER_CALLER(midi_note))) == std::vector{2, 3, 4, 5, 6, 7});
        vmgr.handle_midi(midi::NoteOffEvent{2});
        REQUIRE(test::sort(triggered_voices() | transform(MEMBER_CALLER(midi_note))) == std::vector{1, 3, 4, 5, 6, 7});
      }

      SUBCASE("Poly mode reuses last used voice")
      {
        vmgr.handle_midi(midi::NoteOnEvent{1});
        Voice* triggered_voice = &triggered_voices().front();
        vmgr.handle_midi(midi::NoteOnEvent{2});
        vmgr.handle_midi(midi::NoteOnEvent{3});
        vmgr.handle_midi(midi::NoteOffEvent{1});
        vmgr.handle_midi(midi::NoteOnEvent{1});
        Voice* new_voice = &*nano::find_if(triggered_voices(), [](Voice& v) { return v.midi_note() == 1; });
        REQUIRE(triggered_voice == new_voice);
      }

      SUBCASE("Poly mode cycles voices")
      {
        std::set<Voice*> used_voices;

        for (int i : iota(0, (int) vmgr.voices().size())) {
          vmgr.handle_midi(midi::NoteOnEvent{(int) i});
          used_voices.insert(
            &*nano::find_if(triggered_voices(), [i = i](Voice& v) { return v.midi_note() == (int) i; }));
          vmgr.handle_midi(midi::NoteOffEvent{(int) i});
        }
        REQUIRE(used_voices.size() == vmgr.voices().size());
      }

      SUBCASE("Poly mode rand")
      {
        voices_props.rand = 0.5;
        queue.pop_call_all();


        std::set<float> vals;
        for (int i = 0; i < 5; i++) {
          auto freq = midi::note_freq(50 + i);
          vmgr.handle_midi(midi::NoteOnEvent{50 + i});
          auto& v = triggered_voices().front();
          CAPTURE(i);
          CHECK(v.frequency() == test::approx(freq).margin(freq * 0.1));
          vals.insert(v.frequency() / freq);
          vmgr.handle_midi(midi::NoteOffEvent{50 + i});
        }
        REQUIRE(vals.size() == 5);
      }

      SUBCASE("Keys held over the maximum limit are ignored")
      {
        for (int i = 1; i <= 12 * vmgr.voice_count_v + 1; i++) {
          vmgr.handle_midi(midi::NoteOnEvent{i});
        }
        // TODO: REQUIRE_THAT(test::sort(triggered_voices() | transform(MEMBER_CALLER(midi_note))),
        // TODO:              !Catch::Contains(std::vector{12 * vmgr.voice_count_v + 1}));

        for (int i = 1; i <= 12 * vmgr.voice_count_v; i++) {
          vmgr.handle_midi(midi::NoteOffEvent{i});
        }
        REQUIRE(util::count(triggered_voices()) == 0);
      }
    }

    SUBCASE("Unison Mode")
    {
      voices_props.play_mode = +PlayMode::unison;
      queue.pop_call_all();

      SUBCASE("Can switch to unison mode")
      {
        REQUIRE(vmgr.play_mode() == +PlayMode::unison);
      }

      SUBCASE("Uses 5 voices (for 6 total voices)")
      {
        REQUIRE(VMgr::UnisonAllocator::num_voices_used == 5);
      }

      SUBCASE("Unison triggers highest possible odd number of voices per note")
      {
        vmgr.handle_midi(midi::NoteOnEvent{1});
        REQUIRE(util::count(triggered_voices()) == VMgr::UnisonAllocator::num_voices_used);
        vmgr.handle_midi(midi::NoteOffEvent{1});
        REQUIRE(util::count(triggered_voices()) == 0);
      }

      SUBCASE("steals voices for each new note")
      {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{60});
        auto expected_midi_notes = std::vector<int>(VMgr::UnisonAllocator::num_voices_used, 60);
        REQUIRE(test::sort(triggered_voices() | transform(MEMBER_CALLER(midi_note))) == expected_midi_notes);
      }

      SUBCASE("Snaps back to playing old notes when a note is released")
      {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{60});
        vmgr.handle_midi(midi::NoteOffEvent{60});
        auto expected_midi_notes = std::vector<int>(VMgr::UnisonAllocator::num_voices_used, 50);
        REQUIRE(test::sort(triggered_voices() | transform(MEMBER_CALLER(midi_note))) == expected_midi_notes);
      }

      SUBCASE("Voices keep same order (voice steal)")
      {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        auto ordered_voices_expected = test::sort(triggered_voice_ptrs(), [](Voice* v) { return v->frequency(); });
        vmgr.handle_midi(midi::NoteOnEvent{60});
        auto ordered_voices_actual = test::sort(triggered_voice_ptrs(), [](Voice* v) { return v->frequency(); });
        REQUIRE(ordered_voices_expected == ordered_voices_actual);
      }

      SUBCASE("Voices keep same order (voice return)")
      {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{60});
        auto ordered_voices_expected = test::sort(triggered_voice_ptrs(), [](Voice* v) { return v->frequency(); });
        vmgr.handle_midi(midi::NoteOffEvent{60});
        auto ordered_voices_actual = test::sort(triggered_voice_ptrs(), [](Voice* v) { return v->frequency(); });
        REQUIRE(ordered_voices_expected == ordered_voices_actual);
      }

      SUBCASE("Voices keep same order (voice return) for non-zero detune")
      {
        voices_props.detune = 0.1;
        queue.pop_call_all();

        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{60});
        auto ordered_voices_expected = test::sort(triggered_voice_ptrs(), [](Voice* v) { return v->frequency(); });
        vmgr.handle_midi(midi::NoteOffEvent{60});
        auto ordered_voices_actual = test::sort(triggered_voice_ptrs(), [](Voice* v) { return v->frequency(); });
        REQUIRE(ordered_voices_expected == ordered_voices_actual);
      }
    }

    SUBCASE("Interval Mode")
    {
      voices_props.play_mode = +PlayMode::interval;
      voices_props.interval = 1;
      queue.pop_call_all();


      SUBCASE("Interval mode triggers two voices for a single note")
      {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        REQUIRE(util::count(triggered_voices()) == 2);
        REQUIRE(test::sort(triggered_voices() | transform(MEMBER_CALLER(midi_note))) == std::vector{50, 51});
      }

      SUBCASE("Interval mode triggers two voices per note")
      {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{60});
        REQUIRE(test::sort(triggered_voices() | transform(MEMBER_CALLER(midi_note))) == std::vector{50, 51, 60, 61});
      }

      SUBCASE("Note steal works like in poly")
      {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{60});
        vmgr.handle_midi(midi::NoteOnEvent{70});
        vmgr.handle_midi(midi::NoteOnEvent{80});
        // Note steal
        REQUIRE(test::sort(triggered_voices() | transform(MEMBER_CALLER(midi_note))) ==
                std::vector{60, 61, 70, 71, 80, 81});
        // Note return
        vmgr.handle_midi(midi::NoteOffEvent{70});
        REQUIRE(test::sort(triggered_voices() | transform(MEMBER_CALLER(midi_note))) ==
                std::vector{50, 51, 60, 61, 80, 81});
      }

      SUBCASE("Playing base and interval keys yields four voices")
      {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{51});
        REQUIRE(test::sort(triggered_voices() | transform(MEMBER_CALLER(midi_note))) == std::vector{50, 51, 51, 52});
      }

      SUBCASE("Playing base and interval keys and releasing one yields two voices")
      {
        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{51});
        vmgr.handle_midi(midi::NoteOffEvent{50});
        REQUIRE(test::sort(triggered_voices() | transform(MEMBER_CALLER(midi_note))) == std::vector{51, 52});
      }

      SUBCASE("Changing interval still allows removal of all notes")
      {
        vmgr.handle_midi(midi::NoteOnEvent{50});

        voices_props.interval = 2;
        queue.pop_call_all();
        REQUIRE(test::sort(triggered_voices() | transform(MEMBER_CALLER(midi_note))) == std::vector{50, 51});

        vmgr.handle_midi(midi::NoteOnEvent{60});
        REQUIRE(test::sort(triggered_voices() | transform(MEMBER_CALLER(midi_note))) == std::vector{50, 51, 60, 62});
        vmgr.handle_midi(midi::NoteOffEvent{50});
        REQUIRE(test::sort(triggered_voices() | transform(MEMBER_CALLER(midi_note))) == std::vector{60, 62});
      }
    }

    SUBCASE("Portamento")
    {
      voices_props.play_mode = +PlayMode::mono;
      queue.pop_call_all();

      static_assert(itc::ActionReceiver::is<VMgr, portamento_tag::action>);

      gam::sampleRate(100);
      float target_freq = midi::note_freq(62);

      SUBCASE("Portamento = 0")
      {
        voices_props.portamento = 0.f;
        queue.pop_call_all();

        vmgr.handle_midi(midi::NoteOnEvent{50});
        auto& v = triggered_voices().front();
        v.next();
        REQUIRE(v.frequency() == test::approx(midi::note_freq(50)).margin(0.01));
        vmgr.handle_midi(midi::NoteOnEvent{62});
        v.next();
        REQUIRE(v.frequency() == test::approx(target_freq).margin(0.01));
      }

      SUBCASE("Portamento = 1")
      {
        int expected_n = 100;

        voices_props.portamento = 1.f;
        queue.pop_call_all();

        vmgr.handle_midi(midi::NoteOnEvent{50});
        vmgr.handle_midi(midi::NoteOnEvent{62});

        auto& v = triggered_voices().front();
        float f = midi::note_freq(50);
        // Skip first frame, which should be the start frequency
        v.next();
        REQUIRE(v.frequency() == f);
        for (int i = 0; i < expected_n; i++) {
          v.next();
          INFO("i = " << i);
          float f2 = v.frequency();
          // Frequency increases for each sample
          REQUIRE(f2 > f);
          f = f2;
        }
        // At the end, the target frequency is reached
        REQUIRE(v.frequency() == test::approx(target_freq).margin(0.01));
      }
    };

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

      VoiceManager<Voice, 6> vmgr;

      call_receiver(vmgr, attack_tag::action::data(1.f));
      for (auto& v : vmgr.voices()) REQUIRE(v.attack == 1.f);
      call_receiver(vmgr, decay_tag::action::data(1.f));
      for (auto& v : vmgr.voices()) REQUIRE(v.decay == 1.f);
      call_receiver(vmgr, sustain_tag::action::data(1.f));
      for (auto& v : vmgr.voices()) REQUIRE(v.sustain == 1.f);
      call_receiver(vmgr, release_tag::action::data(1.f));
      for (auto& v : vmgr.voices()) REQUIRE(v.release_ == 1.f);
      call_receiver(vmgr, play_mode_tag::action::data(PlayMode::mono));
      for (auto& v : vmgr.voices()) REQUIRE(v.play_mode == +PlayMode::mono);
      call_receiver(vmgr, legato_tag::action::data(true));
      for (auto& v : vmgr.voices()) REQUIRE(v.legato == true);
      call_receiver(vmgr, retrig_tag::action::data(true));
      for (auto& v : vmgr.voices()) REQUIRE(v.retrig == true);
      call_receiver(vmgr, rand_tag::action::data(0.5));
      for (auto& v : vmgr.voices()) REQUIRE(v.rand == 0.5);
      call_receiver(vmgr, sub_tag::action::data(0.5));
      for (auto& v : vmgr.voices()) REQUIRE(v.sub == 0.5);
      call_receiver(vmgr, detune_tag::action::data(0.5));
      for (auto& v : vmgr.voices()) REQUIRE(v.detune == 0.5);
      call_receiver(vmgr, interval_tag::action::data(5));
      for (auto& v : vmgr.voices()) REQUIRE(v.interval == 5);
      call_receiver(vmgr, portamento_tag::action::data(0.5));
      for (auto& v : vmgr.voices()) REQUIRE(v.portamento == 0.5);
    }

    SUBCASE("call operators and process calls")
    {
      auto app = services::test::make_dummy_application();

      using namespace core::audio;
      SUBCASE("when voice has an operator(), voice and vmgr gets process() and operator()")
      {
        struct SVoice : voices::VoiceBase<SVoice> {
          float operator()() noexcept
          {
            return 1.f;
          }
        };

        VoiceManager<SVoice, 4> vmgr;

        REQUIRE(vmgr.voices()[0]() == 1.f);
        REQUIRE(vmgr() == test::approx(4.f * vmgr.normal_volume));
        // Note that voice_manager() applies volume in the example above
        // while voice() does not.

        AudioBufferHandle bh = services::AudioManager::current().buffer_pool().allocate_clear();
        // When running the default voice.process(), volume is applied. This carries over to
        // voice_manager.process()
        auto res = vmgr.voices()[0].process(ProcessData<0>{{}, {}, {}});
        REQUIRE(nano::all_of(res.audio, util::does_equal(1 * vmgr.normal_volume)));
        auto res2 = vmgr.process(ProcessData<0>{{}, {}, {}});
        REQUIRE(nano::all_of(res2.audio, util::does_equal(4 * vmgr.normal_volume)));
      }

      SUBCASE("when voice has a process(), vmgr only has process()")
      {
        struct SVoice : voices::VoiceBase<SVoice> {
          ProcessData<1> process(ProcessData<0> data) noexcept
          {
            auto buf = services::AudioManager::current().buffer_pool().allocate();
            nano::fill(buf, 1);
            return data.with(buf);
          }
        };

        VoiceManager<SVoice, 4> vmgr;

        // We have written our own voice.process() so volume is not applied.
        auto res = vmgr.voices()[0].process(ProcessData<0>{{}, {}, {}});
        REQUIRE(nano::all_of(res.audio, util::does_equal(1)));

        auto res2 = vmgr.process(ProcessData<0>{{}, {}, {}});
        REQUIRE(nano::all_of(res2.audio, util::does_equal(4)));
      }
    }
  }
} // namespace otto::core::voices
