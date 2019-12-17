#include "arp.hpp"

#include "core/ui/vector_graphics.hpp"
#include <algorithm>

namespace otto::engines::arp {

  using namespace ui;
  using namespace ui::vg;

  using Playmode = detail::ArpPlaymode;
  using OctaveMode = detail::ArpOctaveMode;

  Audio::Audio() noexcept
  {

  }

  audio::ProcessData<0> Audio::process(audio::ProcessData<0> data) noexcept
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
      *shared_graphics_flag = true;
      // If stack is now empty, stop the arpeggiator
      if (held_notes_.empty()) {
        running_ = false;
        for (auto&& ev : *iter) {
          data.midi.push_back(midi::NoteOffEvent(ev.key));
        }
        //Necessary to clear the output_stack and the dots on the screen
        sort_notes();
        iter = util::view::circular(output_stack_).begin();
        *shared_graphics_flag = true;
      } else if (!running_) { // If it wasn't running and should start now
        running_ = true;
        _counter = 0;
      }
    }

    // Check for beat. will be obsolete with master clock
    auto next_beat = (_samples_per_beat - _counter) % _samples_per_beat;

    // If we are running, at a note-off point, and the output stack is not empty send note-off
    // events
    if (next_beat <= _samples_per_beat - note_off_frames && running_ && !output_stack_.empty()) {
      for (auto ev : *iter) {
        data.midi.push_back(midi::NoteOffEvent(ev.key));
      }
    }

    // If we are running, and at a new beat, do stuff.
    if (next_beat <= data.nframes && running_) {
      // Resort notes. Wait until this point to make sure that off events have been sent
      if (has_changed_) {
        sort_notes();
        iter = util::view::circular(output_stack_).begin();
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

  void Audio::action(itc::prop_change<&Props::playmode>, Playmode pm) noexcept
  {
    playmode_ = pm;
  }
    
  void Audio::action(itc::prop_change<&Props::octavemode>, OctaveMode om) noexcept
  {
    octavemode_ = om;
  }

  void Audio::action(itc::prop_change<&Props::note_length>, float nl) noexcept
  {
    note_length_ = nl;
    note_off_frames = (int)(nl * (float)_samples_per_beat);
  }

  void Audio::action(itc::prop_change<&Props::subdivision>, int sd) noexcept
  {
    _samples_per_beat = _samples_per_quarternote / sd;
    note_off_frames = (int)(note_length_ * (float)_samples_per_beat);
  }

  void Audio::action(Actions::graphics_outdated, std::atomic<bool>& ref) noexcept
  {
    shared_graphics_flag = &ref;
  }

  // Sorting for the arpeggiator. This is where the magic happens.
  void Audio::sort_notes()
  {
    auto& res = output_stack_;
    res.clear();
    // Sanitize input (remove duplicates)
    //Maybe only needed for development. Let's leave it for now

    // Add new notes depending on octavemode. Most octavemodes add new vectors to the output
    // (separate steps), but unison modes add new notes to the same steps. To keep things
    // "simple", an octavemode cannot do both.
    switch (octavemode_) {
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
    switch (playmode_) {
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

  midi::NoteOnEvent Audio::transpose_note(midi::NoteOnEvent orig, int t)
  {
    midi::NoteOnEvent transposed = orig;
    transposed.key += t;
    return transposed;
  }

} // namespace otto::engines::arp
