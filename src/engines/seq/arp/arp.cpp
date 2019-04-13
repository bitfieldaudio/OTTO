#include "arp.hpp"

#include "core/ui/vector_graphics.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  struct ArpScreen : EngineScreen<Arp> {
    void draw(Canvas& ctx) override {};

    using EngineScreen::EngineScreen;
  };

  audio::ProcessData<0> Arp::process(audio::ProcessData<0> data)
  {
    ///Check for beat. will be obsolete with master clock
    auto next_beat = _samples_per_beat - _counter;

    ///Add or remove notes from the held_notes_ stack
    for (auto& event : data.midi) {
      util::match(event,
                  [&](midi::NoteOnEvent &ev) {
                      //Add notes to stack
                      held_notes_.push_back(ev);
                      has_changed_ = true;
                  },
                  [&](midi::NoteOffEvent &ev) {
                      //Remove all corresponding notes from the stack
                      util::algorithm::erase_if(held_notes_, [ev](midi::NoteOnEvent noe) { ev.key == noe.key; });
                      has_changed_ = true;
                  },
                  [](auto &&) {});
    };

    /// If we are at a note-off point, send note-off events
    if (next_beat <= data.nframes - note_off_frames) {
      for (auto ev : output_stack_[step]) {
        data.midi.push_back(midi::NoteOffEvent(ev.key));
      }
    }

    /// If we are at a new beat, do stuff. Otherwise, do nothing
    if (next_beat <= data.nframes) {
      /// If the held_notes_ stack has changed, re-sort and reset.
      if (has_changed_) {
        output_stack_ = sort_notes(props);
      }

      /// Go to next value in the output_stack
      //increment in output stack. (wrapping)

      //push new notes
      for (auto ev : output_stack_[step]) {
        data.midi.push_back(ev);
      }
    }

    /// Increment counter. will be obsolete with master clock
    _counter += data.nframes;
    _counter %= _samples_per_beat;

    return data;
  }

  Arp::Arp() : ArpeggiatorEngine<Arp>(std::make_unique<ArpScreen>(this)) {
    ///Set on_change handlers
    props.note_length.on_change().connect([this](float len) {note_off_frames = (int) len * _samples_per_beat;});

  }

    // SCREEN //

    void ArpScreen::rotary(ui::RotaryEvent ev)
    {
      auto& props = engine.props;

      switch (ev.rotary) {
        case Rotary::blue: props.playmode.step(util::math::sgn(ev.clicks)); break;
        case Rotary::green: props.octavemode.step(util::math::sgn(ev.clicks)); break;
        case Rotary::yellow: props.subdivision.step(util::math::sgn(ev.clicks)); break;
        case Rotary::red: props.note_length.step(ev.clicks); break;
      }
      current.update_notes();
      refresh_state();
    }

    void ArpScreen::draw(ui::vg::Canvas& ctx)
    {
      using namespace ui::vg;

      auto& props = engine.props;

      ctx.lineWidth(6);

      ctx.font(Fonts::Norm, 22.0);
      ctx.fillStyle(Colours::White);
      ctx.fillText("Mode", 252, 41.6);

      ctx.restore();
    }
} // namespace otto::engines
