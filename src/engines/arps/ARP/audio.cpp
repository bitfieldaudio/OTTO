#include "arp.hpp"

#include "core/ui/vector_graphics.hpp"
#include <algorithm>
#include <numeric>

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
    // Updates array of notes and delete midi stream
    for (auto& event : data.midi) {
      util::match(event,
                  [&](midi::NoteOnEvent& ev) {
                    notes_[ev.key] = state_.last_t;
                    state_.last_t++;
                    has_changed_ = true;
                    running_ = true;
                  },
                  [&](midi::NoteOffEvent& ev) {
                    notes_[ev.key] = 0;
                    has_changed_ = true;
                    if (std::accumulate(notes_.begin(), notes_.end(), 0) == 0){
                      stop_flag = true;
                    }
                  },
                  [](auto&&) {});
    };
    data.midi.clear();
    //Resets state. It is necessary to do this AFTER clearing the midi data, 
    //otherwise we miss note-off events.
    if (stop_flag){
      running_ = false;
      for (auto note : current_notes_)
        data.midi.push_back(midi::NoteOffEvent(note));
      stop_flag = false;
      _counter = 0;
      state_.reset();
    }

    // Check for beat. will be obsolete with master clock
    auto next_beat = (_samples_per_beat - _counter) % _samples_per_beat;

    // If we are running, at a note-off point, and the output stack is not empty send note-off
    // events
    if (running_ && next_beat <= _samples_per_beat - note_off_frames) {
      for (auto note : current_notes_) {
        data.midi.push_back(midi::NoteOffEvent(note));
      }
      current_notes_.clear();
    }

    // If we are running, and at a new beat, do stuff.
    if (running_ && next_beat <= data.nframes) {
      playmode_func_(state_, notes_, state_.current_step, octavemode_func_, current_notes_);
      // Send note-on events to midi stream
      for (auto note : current_notes_) {
        data.midi.push_back(midi::NoteOnEvent(note));
      }
    }

    // Increment counter. will be obsolete with master clock
    if (running_) {
      _counter += data.nframes;
      _counter %= _samples_per_beat;
    }
    

    return data;
  }

  // PlayMode functions
  void up(ArpeggiatorState& state, NoteArray& notes, std::uint8_t& current_step, OctaveModeFunc oct_func, NoteVector& output)
  {
    NoteArray::iterator it = ( notes.begin() + current_step );
    auto next_step_it = std::find_if(it + 1, notes.end(), [](std::uint8_t v){return v > 0;} );
    if (next_step_it == notes.end()){
      // Wrap
      next_step_it = std::find_if(notes.begin(), notes.end(), [](std::uint8_t v){return v > 0;} );
      state.rounds++;   
    }
    if (next_step_it != notes.end()){
      current_step = next_step_it - notes.begin();
      oct_func(state.rounds, current_step, output);
    }
  }

  void down(ArpeggiatorState& state, NoteArray& notes, std::uint8_t& current_step, OctaveModeFunc oct_func, NoteVector& output)
  {
    NoteArray::reverse_iterator rit = notes.rend() - 1 - current_step;
    auto next_step_rit = std::find_if(rit + 1, notes.rend(), [](std::uint8_t v){return v > 0;} );
    if (next_step_rit == notes.rend()){
      // Wrap
      next_step_rit = std::find_if(notes.rbegin(), notes.rend(), [](std::uint8_t v){return v > 0;} );
      state.rounds++;   
    }
    if (next_step_rit != notes.rend()){
      current_step = std::distance(next_step_rit, notes.rend() - 1);
      oct_func(state.rounds, current_step, output);
    }
  }

  // OctaveMode functions
  void standard(std::uint8_t rounds, std::uint8_t note, NoteVector& output)
  {
    output.push_back(note);
  }

  void octaveupunison(std::uint8_t rounds, std::uint8_t note, NoteVector& output)
  {
    output.push_back(note);
    output.push_back(note + 12);
  }

  // Action Handlers //
  void Audio::action(itc::prop_change<&Props::playmode>, Playmode pm) noexcept
  {
    switch(pm){
    case Playmode::up: playmode_func_ = up; break;
    case Playmode::down: playmode_func_ = down; break;
    default: playmode_func_ = up; break;
    }
  }
    
  void Audio::action(itc::prop_change<&Props::octavemode>, OctaveMode om) noexcept
  {
    switch(om){
    case OctaveMode::standard: octavemode_func_ = standard; break;
    case OctaveMode::octaveupunison: octavemode_func_ = octaveupunison; break;
    default: octavemode_func_ = standard; break;
    }
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

} // namespace otto::engines::arp
