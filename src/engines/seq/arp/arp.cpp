#include "arp.hpp"

#include "core/ui/vector_graphics.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  struct ArpScreen : EngineScreen<Arp> {
    void rotary(ui::RotaryEvent e) override;
    void draw(Canvas& ctx) override;

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
                      //Remove from data struct

                  },
                  [&](midi::NoteOffEvent &ev) {
                      //Remove all corresponding notes from the stack
                      util::algorithm::erase_if(held_notes_, [ev](midi::NoteOnEvent noe) { return ev.key == noe.key; });
                      has_changed_ = true;
                  },
                  [](auto &&) {});
    };

    /// If the held_notes_ stack has changed, re-sort and reset.
    if (has_changed_) {

      ///If stack is now empty, stop the arpeggiator
      if (held_notes_.empty()) {
        running_ = false;
        //Stop all possibly running notes
        for (auto ev : *iter) {
          data.midi.push_back(midi::NoteOffEvent(ev.key));
        }
      }
      else if (!running_) { //If it wasn't running and should start now
        running_ = true;
        _counter = 0;
      }

      output_stack_ = sort_notes();
      iter = util::view::circular(output_stack_).begin();
      has_changed_ = false;
    }

    /// If we are running and at a note-off point, send note-off events
    if (next_beat <= data.nframes - note_off_frames && running_) {
      for (auto ev : *iter) {
        data.midi.push_back(midi::NoteOffEvent(ev.key));
      }
    }

    /// If we are running, and at a new beat, do stuff.
    if (next_beat <= data.nframes && running_) {
      /// Go to next value in the output_stack
      //increment in output stack (wrapping) and push new notes
      iter++;
      for (auto ev : *iter) {
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

  // Sorting algorithm for the arpeggiator. This is where the magic happens.
  std::vector<std::vector<midi::NoteOnEvent>> Arp::sort_notes() {
    std::vector<std::vector<midi::NoteOnEvent>> res;
    /// Sanitize input (remove duplicates)

    /// Add new notes depending on octavemode. Most octavemodes add new vectors to the output
    /// (separate steps), but unison modes add new notes to the same steps. To keep things
    /// "simple", an octavemode cannot do both.
    switch (props.octavemode) {
      case OctaveMode::octaveup: {
        for (auto ev : held_notes_) {
          std::vector<midi::NoteOnEvent> orig;
          orig.push_back(ev);
          std::vector<midi::NoteOnEvent> oct;
          oct.push_back(transpose_note(ev, 12));
          res.push_back(orig);
          res.push_back(oct);
        } break;
      }
      case OctaveMode::octaveupunison: {
        for (auto ev : held_notes_) {
          std::vector<midi::NoteOnEvent> new_step;
          new_step.push_back(ev);
          new_step.push_back(transpose_note(ev, 12));
          res.push_back(new_step);
        } break;
      }
      case OctaveMode::fifthunison: {
        for (auto ev : held_notes_) {
          std::vector<midi::NoteOnEvent> new_step;
          new_step.push_back(ev);
          new_step.push_back(transpose_note(ev, 7));
          res.push_back(new_step);
        } break;
      }
      default: { //(also the OctaveMode::standard version)
        for (auto ev : held_notes_) {
          std::vector<midi::NoteOnEvent> new_step;
          new_step.push_back(ev);
          res.push_back(new_step);
        } break;
      }
    }

    /// Sort vectors (steps) according to the playmode. A mode like updown adds extra steps.
    /// The chord mode gathers all vectors into one.
    switch (props.playmode) {
      case Playmode::up: {
        util::algorithm::sort(res, [](std::vector<midi::NoteOnEvent> a, std::vector<midi::NoteOnEvent> b) {return a[0].key < b[0].key;});
      } break;
      case Playmode::down: {
        util::algorithm::sort(res, [](std::vector<midi::NoteOnEvent> a, std::vector<midi::NoteOnEvent> b) {return a[0].key > b[0].key;});
      } break;
      default: {} //(also the timed option with no sorting)
    }

    return res;
  }

  midi::NoteOnEvent Arp::transpose_note(midi::NoteOnEvent orig, int t) {
    midi::NoteOnEvent transposed = orig;
    transposed.key += t;
    return transposed;
  };

  // SCREEN //

  void ArpScreen::rotary(ui::RotaryEvent ev)
  {
    auto& props = engine.props;

    switch (ev.rotary) {
      case Rotary::blue: props.playmode.step(util::math::sgn(ev.clicks)); break;
      case Rotary::green: props.octavemode.step(util::math::sgn(ev.clicks)); break;
      case Rotary::yellow: break;
      case Rotary::red: props.note_length.step(ev.clicks); break;
    }

  }

  void ArpScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    auto& props = engine.props;

    ctx.lineWidth(6);

    ctx.font(Fonts::Norm, 22.0);
    ctx.fillStyle(Colours::White);
    ctx.fillText(engine.to_string(props.playmode), 252, 41.6);

    ctx.fillText(engine.to_string(props.octavemode), 252, 81.6);

    ctx.restore();
  }
} // namespace otto::engines
