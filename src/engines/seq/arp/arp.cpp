#include "arp.hpp"

#include "core/ui/vector_graphics.hpp"
#include <algorithm>

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  using Playmode = Arp::Playmode;
  using OctaveMode = Arp::OctaveMode;

  inline std::string to_string(Playmode pm) noexcept
  {
    switch (pm) {
    case Playmode::up: return "Up";
    case Playmode::down: return "Down";
    case Playmode::updown: return "Up/Down";
    case Playmode::downup: return "Down/Up";
    case Playmode::updowninc: return "Up/Down Inc.";
    case Playmode::downupinc: return "Down/Up Inc.";
    case Playmode::manual: return "Manual";
    case Playmode::chord: return "Chord";
    };
    OTTO_UNREACHABLE;
  }

  inline std::string to_string(OctaveMode om) noexcept
  {
    switch (om) {
    case OctaveMode::standard: return "Boring";
    case OctaveMode::octaveup: return "+1";
    case OctaveMode::octaveupunison: return "+1Unison";
    case OctaveMode::fifthunison: return "Fifth";
    case OctaveMode::octaveupdown: return "+1 & -1";
    };
    OTTO_UNREACHABLE;
  }


  struct ArpScreen : EngineScreen<Arp> {
    int min = 88;
    int max = 0;
    int num_steps = 0;
    std::vector<Point> dots;
    void encoder(ui::EncoderEvent e) override;
    void draw(Canvas& ctx) override;

    void calculate_dots(std::vector<Point>&);

    using EngineScreen::EngineScreen;
  };


  audio::ProcessData<0> Arp::process(audio::ProcessData<0> data)
  {
    // Add or remove notes from the held_notes_ stack
    for (auto& event : data.midi) {
      util::match(event,
                  [&](midi::NoteOnEvent& ev) {
                    // Add notes to stack
                    held_notes_.push_back(ev);
                    has_changed_ = true;
                    // Remove from data struct
                  },
                  [&](midi::NoteOffEvent& ev) {
                    // Remove all corresponding notes from the stack
                    util::erase_if(held_notes_,
                                   [ev](midi::NoteOnEvent& noe) { return ev.key == noe.key; });
                    has_changed_ = true;
                  },
                  [](auto&&) {});
    };

    data.midi.clear();

    // If the held_notes_ stack has changed, re-sort and reset.
    if (has_changed_) {
      //Flag to recalculate on the graphics thread
      props.graphics_outdated = true;
      // If stack is now empty, stop the arpeggiator
      if (held_notes_.empty()) {
        running_ = false;
        for (auto&& ev : *iter) {
          data.midi.push_back(midi::NoteOffEvent(ev.key));
        }
        //Necessary to clear the output_stack and the dots on the screen
        sort_notes();
        iter = util::view::circular(props.output_stack_).begin();
        props.graphics_outdated = true;
      } else if (!running_) { // If it wasn't running and should start now
        running_ = true;
        _counter = 0;
      }
    }

    // Check for beat. will be obsolete with master clock
    auto next_beat = (_samples_per_beat - _counter) % _samples_per_beat;

    // If we are running, at a note-off point, and the output stack is not empty send note-off
    // events
    if (next_beat <= _samples_per_beat - note_off_frames && running_ && !props.output_stack_.empty()) {
      for (auto ev : *iter) {
        data.midi.push_back(midi::NoteOffEvent(ev.key));
      }
    }

    // If we are running, and at a new beat, do stuff.
    if (next_beat <= data.nframes && running_) {
      // Resort notes. Wait until this point to make sure that off events have been sent
      if (has_changed_) {
        sort_notes();
        iter = util::view::circular(props.output_stack_).begin();
        has_changed_ = false;
      }
      // Go to next value in the output_stack
      // increment in output stack (wrapping) and push new notes
      iter++;
      for (auto ev : *iter) {
        data.midi.push_back(ev);
      }
    }

    // Increment counter. will be obsolete with master clock
    _counter += data.nframes;
    _counter %= _samples_per_beat;

    return data;
  }

  Arp::Arp() : ArpeggiatorEngine<Arp>(std::make_unique<ArpScreen>(this))
  {
    // Set on_change handlers
    props.note_length.on_change().connect(
      [this](float len) { note_off_frames = (int)(len * (float)_samples_per_beat); });
    props.subdivision.on_change().connect(
            [this](int mod) {
              _samples_per_beat = _samples_per_quarternote / mod;
              note_off_frames = (int)(props.note_length * (float)_samples_per_beat);
            });
  }

  // Sorting  for the arpeggiator. This is where the magic happens.
  void Arp::sort_notes()
  {
    auto& res = props.output_stack_;
    res.clear();
    // Sanitize input (remove duplicates)
    //Maybe only needed for development. Let's leave it for now

    // Add new notes depending on octavemode. Most octavemodes add new vectors to the output
    // (separate steps), but unison modes add new notes to the same steps. To keep things
    // "simple", an octavemode cannot do both.
    switch (props.octavemode.get()) {
    case OctaveMode::octaveup: {
      for (auto ev : held_notes_) {
        NoteArray orig;
        orig.push_back(ev);
        NoteArray oct;
        oct.push_back(transpose_note(ev, 12));
        res.push_back(orig);
        res.push_back(oct);
      }
      break;
    }
    case OctaveMode::octaveupunison: {
      for (auto ev : held_notes_) {
        NoteArray new_step;
        new_step.push_back(ev);
        new_step.push_back(transpose_note(ev, 12));
        res.push_back(new_step);
      }
      break;
    }
    case OctaveMode::fifthunison: {
      for (auto ev : held_notes_) {
        NoteArray new_step;
        new_step.push_back(ev);
        new_step.push_back(transpose_note(ev, 7));
        res.push_back(new_step);
      }
      break;
    }
    case OctaveMode::octaveupdown: {
      for (auto ev : held_notes_) {
        NoteArray up;
        up.push_back(transpose_note(ev, 12));
        NoteArray down;
        down.push_back(transpose_note(ev, -12));
        res.push_back(up);
        res.push_back(down);
      }
      break;
    }
    case OctaveMode::standard: [[fallthrough]];
    default: {
      for (auto ev : held_notes_) {
        NoteArray new_step;
        new_step.push_back(ev);
        res.push_back(new_step);
      }
      break;
    }
    }

    // Sort vectors (steps) according to the playmode. A mode like updown adds extra steps.
    // The chord mode gathers all vectors into one.
    switch (props.playmode.get()) {
    case Playmode::up: {
      util::sort(res, [](auto& a, auto& b) { return a.front().key < b.front().key; });
    } break;
    case Playmode::down: {
      util::sort(res, [](auto& a, auto& b) { return a.front().key > b.front().key; });
    } break;
    case Playmode::updown: {
      util::sort(res, [](auto& a, auto& b) { return a.front().key < b.front().key; });
      if (res.size() > 2)
        std::reverse_copy(res.begin() + 1, res.end() - 1, std::back_inserter(res));
    } break;
    case Playmode::downup: {
      util::sort(res, [](auto& a, auto& b) { return a.front().key > b.front().key; });
      if (res.size() > 2)
        std::reverse_copy(res.begin() + 1, res.end() - 1, std::back_inserter(res));
    } break;
    case Playmode::updowninc: {
      util::sort(res, [](auto& a, auto& b) { return a.front().key < b.front().key; });
      std::reverse_copy(res.begin(), res.end(), std::back_inserter(res));
    } break;
    case Playmode::downupinc: {
      util::sort(res, [](auto& a, auto& b) { return a.front().key > b.front().key; });
      std::reverse_copy(res.begin(), res.end(), std::back_inserter(res));
    } break;
    case Playmode::manual: break;
    case Playmode::chord: {
      NoteArray chord;
      for (auto& na : res) {
        chord.append(na);
      }
      res.clear();
      res.push_back(std::move(chord));
    } break;
    default: {}
    }
  }

  midi::NoteOnEvent Arp::transpose_note(midi::NoteOnEvent orig, int t)
  {
    midi::NoteOnEvent transposed = orig;
    transposed.key += t;
    return transposed;
  }

  // SCREEN //

  void ArpScreen::encoder(ui::EncoderEvent ev)
  {
    auto& props = engine.props;

    switch (ev.encoder) {
    case Encoder::blue: props.playmode.step(util::math::sgn(ev.steps)); break;
    case Encoder::green: props.octavemode.step(util::math::sgn(ev.steps)); break;
    case Encoder::yellow: props.subdivision.step(util::math::sgn(ev.steps)); break;
    case Encoder::red: props.note_length.step(ev.steps); break;
    }
  }

  void ArpScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    auto& props = engine.props;

    ctx.lineWidth(6);

    ctx.font(Fonts::Norm, 22.0);
    ctx.fillStyle(Colours::Blue);
    ctx.fillText(to_string(props.playmode), 52, 41.6);

    ctx.fillStyle(Colours::Green);
    ctx.fillText(to_string(props.octavemode), 200, 41.6);

    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Speed", 52, 61.6);
    //Draw speed dots
    for (int i=0; i<props.subdivision; i++) {
      ctx.beginPath();
      ctx.circle(200 + (float)i*13, 61.6 , 5);
      ctx.fill(Colours::Yellow);
    }



    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("NoteLength", 52, 81.6);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1}", props.note_length * 100), 200, 81.6);

    ctx.restore();

    //Dots
    //If dots are outdated, recalculate.
    if (props.graphics_outdated) {
      calculate_dots(dots);
      props.graphics_outdated = false;
    }
    //Draw dots
    for (auto& p : dots) {
      ctx.beginPath();
      ctx.circle(p,5);
      ctx.fill(Colours::White);
    }

  }

   void ArpScreen::calculate_dots(std::vector<Point>& dots)
  {
    //Graphics options
    float y_bot = 190;
    float y_size = 100;
    float x_step_width = 30;


    int num_steps = engine.props.output_stack_.size();
    int min = 88;
    int max = 0;
    //Find minimum and maximum key values
    for (auto& v : engine.props.output_stack_)
    {
      auto current_min = util::min_element(v, [](auto& a, auto& b){return a.key < b.key; });
      min = min > current_min->key ? current_min->key : min;
      auto current_max = util::max_element(v, [](auto& a, auto& b){return a.key < b.key; });
      max = max < current_max->key ? current_max->key : max;
    }
    //Calculate new dot values
    dots.clear();
    for (int i=0; i<engine.props.output_stack_.size(); i++)
    {
      for (auto& note : engine.props.output_stack_[i])
      {
        Point p;
        p.x = width/2.f + (2 * i + 1 - num_steps) * x_step_width / 2.f;
        if (min != max) p.y = y_bot - ((float)note.key - (float)min) / ((float)max - (float)min) * y_size;
        else p.y = y_bot - y_size / 2;
        dots.push_back(p);
      }
    }
  }
} // namespace otto::engines
