#include "euclid.hpp"

#include "core/globals.hpp"
#include "core/ui/vector_graphics.hpp"

#include "util/cache.hpp"
#include "util/iterator.hpp"
#include "util/utility.hpp"

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
        float radius = 40;
        Colour colour = Colours::Gray70;
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


  audio::ProcessData<0> Euclid::process(audio::ProcessData<0> data)
  {
    auto& current = current_channel();
    if (recording) {
      for (auto& event : data.midi) {
        util::match(event,
                    [&](midi::NoteOnEvent& ev) {
                      if (recording.value() == current.notes &&
                          util::all_of(recording.value(), [](char note) { return note < 0; })) {
                        util::fill(recording.value(), -1);
                        util::fill(current.notes, -1);
                      }
                      for (auto& note : recording.value()) {
                        if (note >= 0) continue;
                        note = ev.key;
                        break;
                      }
                      util::unique(recording.value(), std::equal_to());
                      current.notes = recording.value();
                    },
                    [&](midi::NoteOffEvent& ev) {
                      for (auto& note : recording.value()) {
                        if (note != ev.key) continue;
                        note = -1;
                      }
                      if (util::all_of(recording.value(), [](char note) { return note < 0; })) {
                        recording = std::nullopt;
                      }
                    },
                    [](auto&&) {});
      }
      return data;
    }

    data.midi.clear();

    auto next_beat = _samples_per_beat - _counter;

    if (next_beat <= data.nframes) {
      for (auto& channel : props.channels) {
        if (channel.length > 0) {
          channel._beat_counter++;
          channel._beat_counter %= channel.length;
          if (channel._hits_enabled.at(channel._beat_counter)) {
            for (auto note : channel.notes) {
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
        engine.recording = engine.current_channel().notes;
      }
    default: return false; ;
    }
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

    ctx.font(Fonts::Bold, 40);

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Middle);
    ctx.fillText("CHANNEL NOTES", {160, 50});

    ctx.beginPath();
    ctx.fillText(
      util::join_strings(util::view::transform(
                           util::view::filter(current.notes, [](char note) { return note >= 0; }),
                           [](char note) { return midi::note_name(note); }),
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

    ctx.font(Fonts::Norm, 14.0);
    ctx.fillStyle(Colours::White);
    ctx.fillText("Length", 251.9, 41.6);

    ctx.save();
    ctx.font(Fonts::Norm, 30.0);
    ctx.fillStyle(Colours::Green);
    ctx.fillText(std::to_string(current.length), 251.9, 72.9);

    ctx.font(Fonts::Norm, 14.0);
    ctx.fillStyle(Colours::White);
    ctx.fillText("Pulses", 251.9, 111.7);

    ctx.font(Fonts::Norm, 30.0);
    ctx.fillStyle(Colours::Yellow);
    ctx.fillText(std::to_string(current.hits), 251.9, 143.0);

    ctx.font(Fonts::Norm, 14.0);
    ctx.fillStyle(Colours::White);
    ctx.fillText("rotation", 251.9, 173.9);

    ctx.font(Fonts::Norm, 30.0);
    ctx.fillStyle(Colours::Red);
    ctx.fillText(std::to_string(current.rotation), 251.9, 205.3);

    ctx.restore();
  }

  void EuclidScreen::draw_channel(ui::vg::Canvas& ctx, EuclidScreen::State::ChannelState& chan)
  {
    using namespace ui::vg;

    ctx.lineWidth(2);
    for (auto& hit : util::sequence(chan.hits.begin(), chan.hits.begin() + chan.length)) {
      ctx.beginPath();
      ctx.circle(hit.point, hit.active ? 5 : 3);
      if (hit.active) ctx.fill(chan.colour);
      ctx.stroke(chan.colour);
    }
  }

  void EuclidScreen::refresh_state()
  {
    auto& props = engine.props;
    auto& current = props.channels.at(props.channel);

    state.max_length =
      *util::max_element(util::view::transform(props.channels, FIELD_GETTER(length)));

    for (int i = 0; i < 4; i++) {
      auto& chan = props.channels.at(i);
      auto& cs = state.channels.at(i);

      cs.radius = 40 + i * 20;
      cs.colour = &chan == &current ? Colours::Blue : Colours::Gray70;
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
