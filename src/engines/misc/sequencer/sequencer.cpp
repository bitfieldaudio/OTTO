#include "sequencer.hpp"

#include "services/audio_manager.hpp"
#include "services/clock_manager.hpp"

namespace otto::engines {

  using namespace services;

  using SamplerSequence = Sequencer::SamplerSequence;

  static std::unique_ptr<ui::Screen> make_screen(Sequencer* seq);

  Sequencer::Sequencer() : MiscEngine<Sequencer>(make_screen(this)) {}

  void Sequencer::SamplerSequence::process(audio::AudioBufferHandle audio, int step_n) noexcept
  {
    if (step_n >= 0) {
      auto& step = steps[step_n];
      bool trig = step.triggered() and !muted;

      sampler.process(audio, trig);
    } else {
      sampler.process(audio, false);
    }
  }

  audio::ProcessData<1> Sequencer::process(audio::ProcessData<0> data) noexcept
  {
    auto buf = AudioManager::current().buffer_pool().allocate_clear();

    for (auto& s : props.sampler_seqs) s.process(buf, props.cur_step);

    if (ClockManager::current().running())
      props.cur_step = data.clock.position_of_multiple(clock::notes::eighth / substeps) % (16 * substeps);

    return data.with(buf);
  }

  template<typename F>
  auto Sequencer::for_cur_chan(F&& f)
  {
    for_chan(UIManager::current().state.active_channel.get(), FWD(f));
  }

  template<typename F>
  auto Sequencer::for_chan(ChannelEnum chan, F&& f)
  {
    switch (chan) {
      case ChannelEnum::sampler0: return f(props.sampler_seqs[0]);
      case ChannelEnum::sampler1: return f(props.sampler_seqs[1]);
      case ChannelEnum::sampler2: return f(props.sampler_seqs[2]);
      case ChannelEnum::sampler3: return f(props.sampler_seqs[3]);
      case ChannelEnum::sampler4: return f(props.sampler_seqs[4]);
      case ChannelEnum::sampler5: return f(props.sampler_seqs[5]);
      case ChannelEnum::sampler6: return f(props.sampler_seqs[6]);
      case ChannelEnum::sampler7: return f(props.sampler_seqs[7]);
      case ChannelEnum::sampler8: return f(props.sampler_seqs[8]);
      case ChannelEnum::sampler9: return f(props.sampler_seqs[9]);
      default: return f(props.sampler_seqs[0]);
    }
    OTTO_UNREACHABLE;
  }

  template<typename F>
  void Sequencer::for_all_chans(F&& f)
  {
    f(ChannelEnum::sampler0, props.sampler_seqs[0]);
    f(ChannelEnum::sampler1, props.sampler_seqs[1]);
    f(ChannelEnum::sampler2, props.sampler_seqs[2]);
    f(ChannelEnum::sampler3, props.sampler_seqs[3]);
    f(ChannelEnum::sampler4, props.sampler_seqs[4]);
    f(ChannelEnum::sampler5, props.sampler_seqs[5]);
    f(ChannelEnum::sampler6, props.sampler_seqs[6]);
    f(ChannelEnum::sampler7, props.sampler_seqs[7]);
    f(ChannelEnum::sampler8, props.sampler_seqs[8]);
    f(ChannelEnum::sampler9, props.sampler_seqs[9]);
  }

  ui::Screen& Sequencer::sampler_screen() noexcept
  {
    switch (UIManager::current().state.active_channel.get()) {
      case ChannelEnum::sampler0: return props.sampler_seqs[0].sampler.screen();
      case ChannelEnum::sampler1: return props.sampler_seqs[1].sampler.screen();
      case ChannelEnum::sampler2: return props.sampler_seqs[2].sampler.screen();
      case ChannelEnum::sampler3: return props.sampler_seqs[3].sampler.screen();
      case ChannelEnum::sampler4: return props.sampler_seqs[4].sampler.screen();
      case ChannelEnum::sampler5: return props.sampler_seqs[5].sampler.screen();
      case ChannelEnum::sampler6: return props.sampler_seqs[6].sampler.screen();
      case ChannelEnum::sampler7: return props.sampler_seqs[7].sampler.screen();
      case ChannelEnum::sampler8: return props.sampler_seqs[8].sampler.screen();
      case ChannelEnum::sampler9: return props.sampler_seqs[9].sampler.screen();
      case ChannelEnum::internal: return screen();
      case ChannelEnum::external: return screen();
    }
    OTTO_UNREACHABLE;
  }

  ui::Screen& Sequencer::envelope_screen() noexcept
  {
    switch (UIManager::current().state.active_channel.get()) {
      case ChannelEnum::sampler0: return props.sampler_seqs[0].sampler.envelope_screen();
      case ChannelEnum::sampler1: return props.sampler_seqs[1].sampler.envelope_screen();
      case ChannelEnum::sampler2: return props.sampler_seqs[2].sampler.envelope_screen();
      case ChannelEnum::sampler3: return props.sampler_seqs[3].sampler.envelope_screen();
      case ChannelEnum::sampler4: return props.sampler_seqs[4].sampler.envelope_screen();
      case ChannelEnum::sampler5: return props.sampler_seqs[5].sampler.envelope_screen();
      case ChannelEnum::sampler6: return props.sampler_seqs[6].sampler.envelope_screen();
      case ChannelEnum::sampler7: return props.sampler_seqs[7].sampler.envelope_screen();
      case ChannelEnum::sampler8: return props.sampler_seqs[8].sampler.envelope_screen();
      case ChannelEnum::sampler9: return props.sampler_seqs[9].sampler.envelope_screen();
      case ChannelEnum::internal: return screen();
      case ChannelEnum::external: return screen();
    }
    OTTO_UNREACHABLE;
  }

  // Screen //

  using namespace core::ui;
  using namespace core::ui::vg;

  LED seq_led(int idx)
  {
    switch (idx) {
      case 0: return LED{Key::S0};
      case 1: return LED{Key::S1};
      case 2: return LED{Key::S2};
      case 3: return LED{Key::S3};
      case 4: return LED{Key::S4};
      case 5: return LED{Key::S5};
      case 6: return LED{Key::S6};
      case 7: return LED{Key::S7};
      case 8: return LED{Key::S8};
      case 9: return LED{Key::S9};
      case 10: return LED{Key::S10};
      case 11: return LED{Key::S11};
      case 12: return LED{Key::S12};
      case 13: return LED{Key::S13};
      case 14: return LED{Key::S14};
      case 15: return LED{Key::S15};
    }
    OTTO_UNREACHABLE;
  }

  LED chan_led(ChannelEnum chan)
  {
    switch (chan) {
      case ChannelEnum::sampler0: return LED{Key::C0};
      case ChannelEnum::sampler1: return LED{Key::C1};
      case ChannelEnum::sampler2: return LED{Key::C2};
      case ChannelEnum::sampler3: return LED{Key::C3};
      case ChannelEnum::sampler4: return LED{Key::C4};
      case ChannelEnum::sampler5: return LED{Key::C5};
      case ChannelEnum::sampler6: return LED{Key::C6};
      case ChannelEnum::sampler7: return LED{Key::C7};
      case ChannelEnum::sampler8: return LED{Key::C8};
      case ChannelEnum::sampler9: return LED{Key::C9};
      default: OTTO_UNREACHABLE;
    }
  }

  struct SeqScreen : EngineScreen<Sequencer> {
    SeqScreen(Sequencer* seq);
    void on_show() override {}

    void on_hide() override {}

    void draw(Canvas& ctx) override;

    void update_leds();

    bool keypress(Key k) override;

    void input_handler(const services::Controller::Event& event);

  private:
    util::Slot key_mode_change;
    util::Slot on_draw;
    util::Slot on_input;
  };

  static std::unique_ptr<ui::Screen> make_screen(Sequencer* seq)
  {
    return std::make_unique<SeqScreen>(seq);
  }

  SeqScreen::SeqScreen(Sequencer* seq) : EngineScreen<Sequencer>(seq)
  {
    // Set up LED and input handlers when the keymode is KeyMode::seq
    key_mode_change =
      UIManager::current().state.key_mode.on_change().connect([this](auto&& new_val, auto&& old_val) mutable {
        if (new_val == old_val) return;
        if (new_val == +KeyMode::seq) {
          on_draw = UIManager::current().signals.on_draw.connect([this](ui::vg::Canvas&) { update_leds(); });
          on_input = Controller::current().signals.on_input.connect([this](auto&& event) { input_handler(event); });
        } else {
          on_draw.disconnect();
          on_input.disconnect();
          // Clear LEDs
          engine.for_all_chans(
            [](ChannelEnum i, auto& seq) { Controller::current().set_color(chan_led(i), LEDColor::Black); });
          for (int i : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}) {
            Controller::current().set_color(seq_led(i), LEDColor::Black);
          }
        }
      });
  }
  void SeqScreen::update_leds()
  {
    constexpr auto substeps = Sequencer::substeps;

    engine.for_all_chans([](ChannelEnum chan, SamplerSequence& seq) {
      bool is_current = chan == UIManager::current().state.active_channel;
      bool is_muted = seq.muted;
      LEDColor color = is_current ? LEDColor::White : is_muted ? LEDColor::Red : LEDColor::Blue;
      Sampler& sampler = seq.sampler;
      float progress = sampler.progress();
      if (is_current || is_muted) progress *= 0.5;
      color = color.mix(is_muted ? LEDColor::Red : LEDColor::Black, progress);
      Controller::current().set_color(chan_led(chan), color);
    });

    engine.for_cur_chan([&](SamplerSequence& seq) {
      auto& c = Controller::current();
      for (int i = 0; i < 16; i++) {
        // 0: no trig, 1: trig; 2: trig on substep
        int trig = seq.steps[i * substeps].trig ? 1 : 0;
        if (trig == 0)
          for (int j = 1; j < substeps; j++) {
            if (seq.steps[i * substeps + j].trig) {
              trig = 2;
            }
          }
        auto col = [&] {
          switch (trig) {
            case 0: return LEDColor::Black;
            case 1: return LEDColor::Red;
            case 2: return LEDColor::Red.mix(LEDColor::Blue);
          }
          OTTO_UNREACHABLE;
        }();
        if (i == (props.cur_step / substeps)) col = col.mix(LEDColor::White);
        c.set_color(seq_led(i), col);
      }
    });
  }

  bool SeqScreen::keypress(Key k)
  {
    auto& cm = ClockManager::current();
    switch (k) {
      case Key::play:
        if (cm.running())
          cm.stop();
        else
          cm.start();
        break;
      default: break;
    }
    return false;
  }

  void SeqScreen::input_handler(const services::Controller::Event& event)
  {
    util::match(
      event,
      [this](const services::KeyPressEvent& evt) {
        auto k = evt.key;
        auto toggle_step = [&](int i) {
          engine.for_cur_chan([&](SamplerSequence& seq) {
            DLOGI("Toggle step");
            auto& step = seq.steps[i * Sequencer::substeps];
            if (step.triggered()) {
              step.clear();
            } else {
              step.trig = true;
            }
          });
        };

        auto channel_action = [&](ChannelEnum ch) {
          engine.for_chan(ch, [&](SamplerSequence& seq) {
            if (Controller::current().is_pressed(Key::shift)) {
              seq.muted = !seq.muted;
            } else {
              UIManager::current().state.active_channel = ch;
            }
          });
        };

        switch (k) {
          case Key::S0: toggle_step(0); return;
          case Key::S1: toggle_step(1); return;
          case Key::S2: toggle_step(2); return;
          case Key::S3: toggle_step(3); return;
          case Key::S4: toggle_step(4); return;
          case Key::S5: toggle_step(5); return;
          case Key::S6: toggle_step(6); return;
          case Key::S7: toggle_step(7); return;
          case Key::S8: toggle_step(8); return;
          case Key::S9: toggle_step(9); return;
          case Key::S10: toggle_step(10); return;
          case Key::S11: toggle_step(11); return;
          case Key::S12: toggle_step(12); return;
          case Key::S13: toggle_step(13); return;
          case Key::S14: toggle_step(14); return;
          case Key::S15: toggle_step(15); return;

          case Key::C0: channel_action(ChannelEnum::sampler0); return;
          case Key::C1: channel_action(ChannelEnum::sampler1); return;
          case Key::C2: channel_action(ChannelEnum::sampler2); return;
          case Key::C3: channel_action(ChannelEnum::sampler3); return;
          case Key::C4: channel_action(ChannelEnum::sampler4); return;
          case Key::C5: channel_action(ChannelEnum::sampler5); return;
          case Key::C6: channel_action(ChannelEnum::sampler6); return;
          case Key::C7: channel_action(ChannelEnum::sampler7); return;
          case Key::C8: channel_action(ChannelEnum::sampler8); return;
          case Key::C9: channel_action(ChannelEnum::sampler9); return;

          default: return;
        }
      },
      [](auto&&) {});
  }
  // Draw


  void SeqScreen::draw(Canvas& ctx) {}

} // namespace otto::engines
