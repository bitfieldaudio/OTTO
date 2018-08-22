#include "euclid.hpp"

#include "core/globals.hpp"
#include "core/ui/vector_graphics.hpp"

#include "util/iterator.hpp"
#include "util/utility.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  struct EuclidScreen : EngineScreen<Euclid> {
    void draw(Canvas& ctx) override;
    bool keypress(Key key) override;
    void rotary(RotaryEvent e) override;

    using EngineScreen<Euclid>::EngineScreen;

    void draw_normal(Canvas& ctx);
    void draw_recording(Canvas& ctx);
  };

  Euclid::Euclid() : SequencerEngine("Euclid", props, std::make_unique<EuclidScreen>(this)) {}


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

    _counter += data.nframes;
    _counter %= _samples_per_beat;
    return data;
  }

  void Euclid::Channel::update_notes()
  {
    util::fill(_hits_enabled, false);
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

  void EuclidScreen::draw_normal(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    auto& props = engine.props;
    auto& current = props.channels.at(props.channel);

    ctx.font(Fonts::Bold, 40);

    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Channel", {x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", props.channel), {width - x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Length", {x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", current.length), {width - x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Hits", {x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", current.hits), {width - x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Rotation", {x_pad, y_pad + 3 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", current.rotation), {width - x_pad, y_pad + 3 * space});
  }

  void EuclidScreen::draw_recording(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    auto& props = engine.props;
    auto& current = engine.current_channel();

    ctx.font(Fonts::Bold, 40);

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Middle);
    ctx.fillText("RED MEANS WHAT?", {160, 50});

    ctx.beginPath();
    ctx.fillText(
      util::join_strings(util::view::transform(
                           util::view::filter(current.notes, [](char note) { return note >= 0; }),
                           [](char note) { return midi::note_name(note); }),
                         " "),
      {160, 120});
  }
} // namespace otto::engines
