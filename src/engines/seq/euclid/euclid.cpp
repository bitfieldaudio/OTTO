#include "euclid.hpp"

#include "core/globals.hpp"
#include "core/ui/vector_graphics.hpp"

#include "util/cache.hpp"
#include "util/iterator.hpp"
#include "util/utility.hpp"

#include "services/logger.hpp"
#include "services/state.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  using Channel = Euclid::Channel;

  struct EuclidScreen : EngineScreen<Euclid> {
    using EngineScreen<Euclid>::EngineScreen;

    void draw(Canvas& ctx) override;
    bool keypress(Key key) override;
    void rotary(RotaryEvent e) override;

    void draw_normal(Canvas& ctx);
    void draw_recording(Canvas& ctx);


    struct State {
      Point center = {127, 120};
      int max_length = 16;

      struct ChannelState {
        Channel* channel;
        float radius = 40;
        bool is_current = false;
        int length = 0;
        struct Hit {
          Point point = {};
          bool active = false;
        };
        std::array<Hit, Euclid::max_length> hits;
      };
      std::array<ChannelState, 4> channels;

    } state;

    void refresh_state();

    void draw_channel(ui::vg::Canvas& ctx, State::ChannelState& chan);
  };

  Euclid::Euclid() : SequencerEngine("Euclid", props, std::make_unique<EuclidScreen>(this))
  {
    static_cast<EuclidScreen*>(&screen())->refresh_state();
  }

  void Euclid::on_enable()
  {
    for (auto& c : props.channels) c.update_notes();
    static_cast<EuclidScreen*>(&screen())->refresh_state();
  }

  audio::ProcessData<0> Euclid::process(audio::ProcessData<0> data)
  {
    auto& current = current_channel();
    // Copy for thread safety
    if (auto recording = this->recording; recording) {
      for (auto& event : data.midi) {
        util::match(event,
                    [&](midi::NoteOnEvent& ev) {
                      if (!_has_pressed_keys) {
                        util::fill(recording.value(), -1);
                        current.notes.set(recording.value());
                        _has_pressed_keys = true;
                      }
                      for (auto& note : recording.value()) {
                        if (note >= 0) continue;
                        note = ev.key;
                        break;
                      }
                      util::unique(recording.value(), std::equal_to<char>());
                      current.notes = recording.value();
                    },
                    [&](midi::NoteOffEvent& ev) {
                      for (auto& note : recording.value()) {
                        if (note != ev.key) continue;
                        note = -1;
                      }
                      if (util::all_of(recording.value(), [](int note) { return note < 0; })) {
                        recording = std::nullopt;
                      }
                    },
                    [](auto&&) {});
        this->recording = recording;
        if (!recording) break;
        ;
      }
    }
    if (_should_run) running = true;
    if (!running) return data;

    if (!_should_run && running) {
      _counter = _samples_per_beat;
      running = false;
      return data;
    }

    auto next_beat = _samples_per_beat - _counter;

    if (next_beat <= data.nframes) {
      for (auto& channel : props.channels) {
        if (channel.length > 0) {
          channel._beat_counter++;
          channel._beat_counter %= channel.length;
          if (running && channel._hits_enabled.at(channel._beat_counter)) {
            for (auto note : channel.notes.get()) {
              if (note >= 0) {
                data.midi.push_back(midi::NoteOnEvent(note));
                data.midi.push_back(midi::NoteOffEvent(note));
              }
            }
          }
        }
      }
    }

    _counter += data.nframes;
    _counter %= _samples_per_beat;
    return data;
  }

  void Euclid::Channel::update_notes()
  {
    util::fill(_hits_enabled, false);
    if (hits == 0 || length == 0) return;
    for (float i = 0; i < length; i += length / float(hits)) {
      int idx = int(std::round(i) + rotation) % length;
      _hits_enabled.at(idx) = true;
    }
  }

  // SCREEN //

  void EuclidScreen::rotary(ui::RotaryEvent ev)
  {
    if (engine.recording) return;

    auto& props = engine.props;
    auto& current = props.channels.at(props.channel);

    switch (ev.rotary) {
    case Rotary::Blue: props.channel.step(ev.clicks); break;
    case Rotary::Green: current.length.step(ev.clicks); break;
    case Rotary::White: current.hits.step(ev.clicks); break;
    case Rotary::Red: current.rotation.step(ev.clicks); break;
    }
    current.update_notes();
    refresh_state();
  }

  bool EuclidScreen::keypress(ui::Key key)
  {
    switch (key) {
    case ui::Key::blue_click: [[fallthrough]];
    case ui::Key::green_click: [[fallthrough]];
    case ui::Key::white_click: [[fallthrough]];
    case ui::Key::red_click:
      if (engine.recording) {
        engine.recording = std::nullopt;
      } else {
        engine._has_pressed_keys = false;
        engine.recording = engine.current_channel().notes;
      }
      break;
    case ui::Key::play: engine._should_run = !engine._should_run; break;
    default: return false; ;
    }
    return true;
  }

  void EuclidScreen::draw(ui::vg::Canvas& ctx)
  {
    if (engine.recording)
      draw_recording(ctx);
    else
      draw_normal(ctx);
  }

  void EuclidScreen::draw_recording(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    auto& current = engine.current_channel();

    ctx.font(Fonts::Norm, 40);

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Middle);
    ctx.fillText("CHANNEL NOTES", {160, 50});

    ctx.beginPath();
    ctx.fillText(util::join_strings(
                   util::view::transform(
                     util::view::filter(current.notes.get(), [](int note) { return note >= 0; }),
                     [](int note) { return midi::note_name(note); }),
                   " "),
                 {160, 120});
  }

  void EuclidScreen::draw_normal(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    auto& props = engine.props;
    auto& current = props.channels.at(props.channel);


    for (auto& chan : state.channels) {
      draw_channel(ctx, chan);
    }

    ctx.lineWidth(6);
    ctx.beginPath();
    ctx.arc(state.center, 25, -M_PI / 2.f,
            2.0 * M_PI * (current.rotation / float(state.max_length) - 0.25));
    ctx.stroke(Colours::Red);

    ctx.font(Fonts::Norm, 22.0);
    ctx.fillStyle(Colours::White);
    ctx.fillText("length", 252, 41.6);

    ctx.save();
    ctx.font(Fonts::Norm, 35.0);
    ctx.fillStyle(Colours::Green);
    ctx.fillText(std::to_string(current.length), 252, 72.9);

    ctx.font(Fonts::Norm, 22.0);
    ctx.fillStyle(Colours::White);
    ctx.fillText("pulses", 252, 108.7);

    ctx.font(Fonts::Norm, 35.0);
    ctx.fillStyle(Colours::Yellow);
    ctx.fillText(std::to_string(current.hits), 252, 140.0);

    ctx.font(Fonts::Norm, 22.0);
    ctx.fillStyle(Colours::White);
    ctx.fillText("offset", 252, 173.9);

    ctx.font(Fonts::Norm, 35.0);
    ctx.fillStyle(Colours::Red);
    ctx.fillText(std::to_string(current.rotation), 252, 205.3);

    ctx.restore();
  }

  void EuclidScreen::draw_channel(ui::vg::Canvas& ctx, EuclidScreen::State::ChannelState& chan)
  {
    using namespace ui::vg;

    auto hit_colour = chan.is_current ? Colour(Colours::Blue) : Colour::bytes(0x88, 0x72, 0x8E);
    auto len_colour = chan.is_current ? Colour(Colours::Green) : hit_colour;

    if (chan.length == 0) {
      ctx.lineWidth(6);
      ctx.beginPath();
      ctx.circle(state.center, chan.radius);
      ctx.stroke(len_colour);
      return;
    }

    for (auto& hit : util::sequence(chan.hits.begin(), chan.hits.begin() + chan.length)) {
      ctx.beginPath();
      ctx.circle(hit.point, hit.active ? 7 : 3);
      ctx.fill(hit_colour);
    }

    if (chan.length < state.max_length) {
      ctx.lineWidth(6);
      ctx.beginPath();
      ctx.arc(state.center, chan.radius,
              2 * M_PI * ((chan.length - 0.3) / float(state.max_length) - 0.25),
              2 * M_PI * ((state.max_length - 1 + 0.3) / float(state.max_length) - 0.25));
      ctx.stroke(len_colour);
    }


    auto& hit =
      chan.hits.at((chan.channel->_beat_counter + (engine.running ? 0 : 1)) % chan.length);

    ctx.beginPath();
    float r = (hit.active ? 7 : 3);
    if (engine.running) r *= (1 - (engine._counter / float(engine._samples_per_beat)));
    ctx.circle(hit.point, r);
    ctx.fill(Colours::Red);
  }

  void EuclidScreen::refresh_state()
  {
    auto& props = engine.props;
    auto& current = props.channels.at(props.channel);

    state.max_length = 0;
    for (auto& chan : props.channels) {
      if (state.max_length < chan.length) state.max_length = chan.length;
    }

    for (int i = 0; i < 4; i++) {
      auto& chan = props.channels.at(i);
      auto& cs = state.channels.at(i);

      cs.channel = &chan;

      cs.radius = 40 + i * 20;
      cs.is_current = &chan == &current;
      cs.length = chan.length;

      for (int i = 0; i < cs.length; i++) {
        auto& hs = cs.hits.at(i);
        float angle = 2.0 * M_PI * (i / float(state.max_length) - 0.25);
        hs.point = state.center + Point{cs.radius * std::cos(angle), cs.radius * std::sin(angle)};
        hs.active = chan._hits_enabled.at(i);
      }
    }
  }

} // namespace otto::engines
