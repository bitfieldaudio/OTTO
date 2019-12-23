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
  auto get_next_upwards = [](NoteArray& notes, std::uint8_t& current_step)
  {
    NoteArray::iterator it = ( notes.begin() + current_step );
    return std::find_if(it + 1, notes.end(), [](std::uint8_t v){return v > 0;} );
  };

  auto get_next_downwards = [](NoteArray& notes, std::uint8_t& current_step)
  {
    NoteArray::reverse_iterator rit = notes.rend() - 1 - current_step;
    return std::find_if(rit + 1, notes.rend(), [](std::uint8_t v){return v > 0;} );
  };

  auto set_current_step = [](NoteArray& notes, std::uint8_t& current_step, End end, Position pos)
  {
    if (end == End::Low){
      if (pos == Position::First)
      {
        current_step = 0;
        auto next_step_it = get_next_upwards(notes, current_step);
        current_step = next_step_it - notes.begin();
      } else {
        current_step = 0;
      }
    } else {
      if (pos == Position::First)
      {
        current_step = 128;
        auto next_step_rit = get_next_downwards(notes, current_step);
        current_step = std::distance(next_step_rit, notes.rend() - 1);
      } else {
        current_step = 128;
      }
    }
  };

  void up(ArpeggiatorState& state, NoteArray& notes, std::uint8_t& current_step, OctaveModeFunc oct_func, NoteVector& output)
  {
    bool doubleoctave = ((oct_func == octaveup) || (oct_func == octaveupdown) || (oct_func == octavedownup));
    auto next_step_it = get_next_upwards(notes, current_step);
    if (next_step_it == notes.end()){
      // Wrap
      current_step = 0;
      next_step_it = get_next_upwards(notes, current_step);
      state.next_round(false, doubleoctave);   
    }
    if (next_step_it != notes.end()){
      current_step = next_step_it - notes.begin();
      oct_func(state.stage, current_step, output);
    }
  }

  void down(ArpeggiatorState& state, NoteArray& notes, std::uint8_t& current_step, OctaveModeFunc oct_func, NoteVector& output)
  {
    bool doubleoctave = ((oct_func == octaveup) || (oct_func == octaveupdown) || (oct_func == octavedownup));
    auto next_step_rit = get_next_downwards(notes, current_step);
    if (next_step_rit == notes.rend()){
      // Wrap
      current_step = 128;
      next_step_rit = get_next_downwards(notes, current_step);
      state.next_round(false, doubleoctave);   
    }
    if (next_step_rit != notes.rend()){
      current_step = std::distance(next_step_rit, notes.rend() - 1);
      oct_func(state.stage, current_step, output);
    }
  }

  void chord(ArpeggiatorState& state, NoteArray& notes, std::uint8_t& current_step, OctaveModeFunc oct_func, NoteVector& output)
  {
    bool doubleoctave = ((oct_func == octaveup) || (oct_func == octaveupdown) || (oct_func == octavedownup));

    for (auto&& [i, note] : util::view::indexed(notes))
    {
      if (note > 0) {
        oct_func(state.stage, i, output);
      }
    }
    state.next_round(false, doubleoctave);
  }

  void manual(ArpeggiatorState& state, NoteArray& notes, std::uint8_t& current_step, OctaveModeFunc oct_func, NoteVector& output)
  {
    bool doubleoctave = ((oct_func == octaveup) || (oct_func == octaveupdown) || (oct_func == octavedownup));
    // Look for the element in notes with the closest value higher than the one at current step
    auto current_value = notes[current_step];
    auto later_notes =
      util::view::filter(notes, [&](uint8_t& n) { return n > current_value; });
    auto next_note_it = util::min_element(later_notes);
    if (next_note_it != later_notes.end())
    {
      current_step = std::distance(notes.begin(), next_note_it.iter); 
      oct_func(state.stage, current_step, output);
    } else {
      // Wrap
      state.next_round(false, doubleoctave);
      auto triggered_notes =
        util::view::filter(notes, [&](uint8_t& n) { return n > 0; });
      auto first_note_it = util::min_element(triggered_notes);
      if (first_note_it.iter != first_note_it.last){
        current_step = std::distance(notes.begin(), first_note_it.iter); 
        oct_func(state.stage, current_step, output);
      }
    }
  }

  void updown(ArpeggiatorState& state, NoteArray& notes, std::uint8_t& current_step, OctaveModeFunc oct_func, NoteVector& output)
  {
    bool doubleoctave = ((oct_func == octaveup) || (oct_func == octaveupdown) || (oct_func == octavedownup));

    if (state.direction == ArpeggiatorState::Direction::first)
    {
      auto next_step_it = get_next_upwards(notes, current_step);
      if (next_step_it == notes.end())
      {
        // Wrap
        state.next_round(true, doubleoctave);
        //Edge case: If there is only one note pressed
        auto next_step_rit = get_next_downwards(notes, current_step);
        if (next_step_rit == notes.rend()){oct_func(state.stage, current_step, output); return;}
        // Still going up
        if (state.direction == ArpeggiatorState::Direction::first) set_current_step(notes, current_step, End::Low, Position::Zeroth);
        updown(state, notes, current_step, oct_func, output);
      }
      else
      {
        current_step = next_step_it - notes.begin();
        oct_func(state.stage, current_step, output);
      }  
    } 
    else // Going down 
    {
      auto next_step_rit = get_next_downwards(notes, current_step);
      if (next_step_rit == notes.rend()){
        // Wrap
        state.next_round(true, doubleoctave);
        //Edge case: If there is only one note pressed
        auto next_step_it = get_next_upwards(notes, current_step);
        if (next_step_it == notes.end()){oct_func(state.stage, current_step, output); return;}
        // Still going down
        if (state.direction == ArpeggiatorState::Direction::second) set_current_step(notes, current_step, End::High, Position::Zeroth);
        updown(state, notes, current_step, oct_func, output);
      }
      else
      {
        current_step = std::distance(next_step_rit, notes.rend() - 1);
        oct_func(state.stage, current_step, output);
      }
    }
  }

  void updowninc(ArpeggiatorState& state, NoteArray& notes, std::uint8_t& current_step, OctaveModeFunc oct_func, NoteVector& output)
  {
    bool doubleoctave = ((oct_func == octaveup) || (oct_func == octaveupdown) || (oct_func == octavedownup));

    if (state.direction == ArpeggiatorState::Direction::first)
    {
      auto next_step_it = get_next_upwards(notes, current_step);
      if (next_step_it == notes.end())
      {
        // Wrap
        state.next_round(true, doubleoctave);
        // If still going up
        if (state.direction == ArpeggiatorState::Direction::first) set_current_step(notes, current_step, End::Low, Position::Zeroth);
        else set_current_step(notes, current_step, End::High, Position::Zeroth);
        updowninc(state, notes, current_step, oct_func, output);
      }
      else
      {
        current_step = next_step_it - notes.begin();
        oct_func(state.stage, current_step, output);
      }  
    } 
    else // Going down 
    {
      auto next_step_rit = get_next_downwards(notes, current_step);
      if (next_step_rit == notes.rend()){
        // Wrap
        state.next_round(true, doubleoctave);
        // If still going down
        if (state.direction == ArpeggiatorState::Direction::second) set_current_step(notes, current_step, End::High, Position::Zeroth);
        else set_current_step(notes, current_step, End::Low, Position::Zeroth);
        updowninc(state, notes, current_step, oct_func, output);
      }
      else
      {
        current_step = std::distance(next_step_rit, notes.rend() - 1);
        oct_func(state.stage, current_step, output);
      }
    }
  }

  void downup(ArpeggiatorState& state, NoteArray& notes, std::uint8_t& current_step, OctaveModeFunc oct_func, NoteVector& output)
  {
    bool doubleoctave = ((oct_func == octaveup) || (oct_func == octaveupdown) || (oct_func == octavedownup));

    // Going down
    if (state.direction == ArpeggiatorState::Direction::first)
    {
      auto next_step_rit = get_next_downwards(notes, current_step);
      if (next_step_rit == notes.rend()){
        // Wrap
        state.next_round_downup(doubleoctave);
        //Edge case: If there is only one note pressed
        auto next_step_it = get_next_upwards(notes, current_step);
        if (next_step_it == notes.end()){oct_func(state.stage, current_step, output); return;}
        // Still going down
        if (state.direction == ArpeggiatorState::Direction::first) set_current_step(notes, current_step, End::High, Position::Zeroth);
        downup(state, notes, current_step, oct_func, output);
      }
      else
      {
        current_step = std::distance(next_step_rit, notes.rend() - 1);
        oct_func(state.stage, current_step, output);
      }
    } 
    else // Going up
    {
      auto next_step_it = get_next_upwards(notes, current_step);
      if (next_step_it == notes.end())
      {
        // Wrap
        state.next_round_downup(doubleoctave);
        //Edge case: If there is only one note pressed
        auto next_step_rit = get_next_downwards(notes, current_step);
        if (next_step_rit == notes.rend()){oct_func(state.stage, current_step, output); return;}
        // Still going up
        if (state.direction == ArpeggiatorState::Direction::second) set_current_step(notes, current_step, End::Low, Position::Zeroth);
        downup(state, notes, current_step, oct_func, output);
      }
      else
      {
        current_step = next_step_it - notes.begin();
        oct_func(state.stage, current_step, output);
      }  
    }
  }

  void downupinc(ArpeggiatorState& state, NoteArray& notes, std::uint8_t& current_step, OctaveModeFunc oct_func, NoteVector& output)
  {
    bool doubleoctave = ((oct_func == octaveup) || (oct_func == octaveupdown) || (oct_func == octavedownup));

    if (state.direction == ArpeggiatorState::Direction::first)
    {
      auto next_step_rit = get_next_downwards(notes, current_step);
      if (next_step_rit == notes.rend()){
        // Wrap
        state.next_round_downup(doubleoctave);
        // If still going down
        if (state.direction == ArpeggiatorState::Direction::first) set_current_step(notes, current_step, End::High, Position::Zeroth);
        else set_current_step(notes, current_step, End::Low, Position::Zeroth);
        downupinc(state, notes, current_step, oct_func, output);
      }
      else
      {
        current_step = std::distance(next_step_rit, notes.rend() - 1);
        oct_func(state.stage, current_step, output);
      }
    } 
    else // Going down 
    {
      auto next_step_it = get_next_upwards(notes, current_step);
      if (next_step_it == notes.end())
      {
        // Wrap
        state.next_round_downup(doubleoctave);
        // If still going up
        if (state.direction == ArpeggiatorState::Direction::second) set_current_step(notes, current_step, End::Low, Position::Zeroth);
        else set_current_step(notes, current_step, End::High, Position::Zeroth);
        downupinc(state, notes, current_step, oct_func, output);
      }
      else
      {
        current_step = next_step_it - notes.begin();
        oct_func(state.stage, current_step, output);
      }    
    }
  }

  // OctaveMode functions
  void standard(ArpeggiatorState::Stage& stage, std::uint8_t note, NoteVector& output)
  {
    output.push_back(note);
  }

  void octaveupunison(ArpeggiatorState::Stage& stage, std::uint8_t note, NoteVector& output)
  {
    output.push_back(note);
    output.push_back(note + 12);
  }

  void fifthunison(ArpeggiatorState::Stage& stage, std::uint8_t note, NoteVector& output)
  {
    output.push_back(note);
    output.push_back(note + 7);
  }

  void octaveup(ArpeggiatorState::Stage& stage, std::uint8_t note, NoteVector& output)
  {
    
    if (stage == ArpeggiatorState::Stage::A) output.push_back(note);
    else output.push_back(note + 12);
  }

  void octavedownup(ArpeggiatorState::Stage& stage, std::uint8_t note, NoteVector& output)
  {
    if (stage == ArpeggiatorState::Stage::A) output.push_back(note - 12);
    else output.push_back(note + 12);
  }

  void octaveupdown(ArpeggiatorState::Stage& stage, std::uint8_t note, NoteVector& output)
  {
    if (stage == ArpeggiatorState::Stage::A) output.push_back(note + 12);
    else output.push_back(note - 12);
  }

  // Action Handlers //
  void Audio::action(itc::prop_change<&Props::playmode>, Playmode pm) noexcept
  {
    switch(pm){
    case Playmode::up: playmode_func_ = up; break;
    case Playmode::down: playmode_func_ = down; break;
    case Playmode::updown: playmode_func_ = updown; break;
    case Playmode::downup: playmode_func_ = downup; set_current_step(notes_, state_.current_step, End::High, Position::Zeroth); break;
    case Playmode::updowninc: playmode_func_ = updowninc; break;
    case Playmode::downupinc: playmode_func_ = downupinc; set_current_step(notes_, state_.current_step, End::High, Position::Zeroth); break;
    case Playmode::manual: playmode_func_ = manual; break;
    case Playmode::chord: playmode_func_ = chord; break;
    default: playmode_func_ = up; break;
    }
  }
    
  void Audio::action(itc::prop_change<&Props::octavemode>, OctaveMode om) noexcept
  {
    switch(om){
    case OctaveMode::standard: octavemode_func_ = standard; break;
    case OctaveMode::octaveupunison: octavemode_func_ = octaveupunison; break;
    case OctaveMode::fifthunison: octavemode_func_ = fifthunison; break;
    case OctaveMode::octaveup: octavemode_func_ = octaveup; break;
    case OctaveMode::octaveupdown: octavemode_func_ = octaveupdown; break;
    case OctaveMode::octavedownup: octavemode_func_ = octavedownup; break;
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
