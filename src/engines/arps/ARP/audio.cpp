#include <algorithm>
#include <numeric>

#include "arp.hpp"
#include "core/audio/clock.hpp"
#include "engines/arps/ARP/audio.hpp"
#include "services/clock_manager.hpp"

namespace otto::engines::arp {

  using namespace ui;
  using namespace ui::vg;

  namespace view = util::view;

  using Direction = ArpeggiatorState::Direction;

  static void insert_note(NoteArray& notes, std::uint8_t note)
  {
    std::int8_t t = notes.empty() ? 0 : notes.back().t + 1;
    notes.push_back({note, t});
  }

  static void erase_note(NoteArray& notes, std::uint8_t note)
  {
    auto found = util::remove_if(notes, [&](auto& ntp) { return ntp.note == note; });
    notes.erase(found, notes.end());
  }

  Audio::Audio() noexcept {}

  audio::ProcessData<0> Audio::process(audio::ProcessData<0> data) noexcept
  {
    // Updates array of notes and delete midi stream
    for (auto& event : data.midi) {
      util::match(
        event,
        [&](midi::NoteOnEvent& ev) {
          insert_note(notes_, ev.key);
          state_.invalidate_om_cache();
          if (!running_) {
            services::ClockManager::current().start();
            running_ = true;
          }
        },
        [&](midi::NoteOffEvent& ev) {
          erase_note(notes_, ev.key);
          state_.invalidate_om_cache();
          if (notes_.empty()) {
            stop_flag = true;
          }
        },
        [](auto&&) {});
    };
    data.midi.clear();
    // Resets state. It is necessary to do this AFTER clearing the midi data,
    // otherwise we miss note-off events.
    if (stop_flag) {
      services::ClockManager::current().stop(true);
      running_ = false;
      for (auto note : current_notes_) data.midi.push_back(midi::NoteOffEvent(note));
      stop_flag = false;
      _counter = 0;
      state_.reset();
    }

    auto at_note_off = data.clock.contains_multiple(note, note * note_length_);
    if (running_ && at_note_off) {
      for (auto note : current_notes_) {
        data.midi.push_back(midi::NoteOffEvent(note));
      }
      current_notes_.clear();
    }

    auto at_beat = data.clock.contains_multiple(note);
    if (running_ && at_beat) {
      current_notes_ = octavemode_func_(state_, notes_, playmode_func_);
      // Send note-on events to midi stream
      for (auto note : current_notes_) {
        data.midi.push_back(midi::NoteOnEvent(note));
      }
    }
    return data;
  }

  // Action Handlers //
  void Audio::action(itc::prop_change<&Props::playmode>, Playmode pm) noexcept
  {
    using namespace play_modes;
    switch (pm) {
      case Playmode::up: playmode_func_ = up; break;
      case Playmode::down: playmode_func_ = down; break;
      case Playmode::updown: playmode_func_ = updown; break;
      case Playmode::downup: playmode_func_ = downup; break;
      case Playmode::updowninc: playmode_func_ = updowninc; break;
      case Playmode::downupinc: playmode_func_ = downupinc; break;
      case Playmode::manual: playmode_func_ = manual; break;
      case Playmode::chord: playmode_func_ = chord; break;
      case Playmode::random: playmode_func_ = random; break;
    }
  }
  void Audio::action(itc::prop_change<&Props::octavemode>, OctaveMode om) noexcept
  {
    using namespace octave_modes;
    switch (om) {
      case OctaveMode::standard: octavemode_func_ = standard; break;
      case OctaveMode::octaveupunison: octavemode_func_ = octaveupunison; break;
      case OctaveMode::fifthunison: octavemode_func_ = fifthunison; break;
      case OctaveMode::octaveup: octavemode_func_ = octaveup; break;
      case OctaveMode::doubleoctaveup: octavemode_func_ = doubleoctaveup; break;
      case OctaveMode::octavedownup: octavemode_func_ = octavedownup; break;
    }
    state_.invalidate_om_cache();
  }

  void Audio::action(itc::prop_change<&Props::note_length>, float nl) noexcept
  {
    note_length_ = nl;
    note_off_frames = (int) (nl * (float) _samples_per_beat);
  }

  void Audio::action(itc::prop_change<&Props::subdivision>, int sd) noexcept
  {
    _samples_per_beat = _samples_per_quarternote / sd;
    note_off_frames = (int) (note_length_ * (float) _samples_per_beat);
    switch (sd) {
      case 1: note = core::clock::notes::quarter; break;
      case 2: note = core::clock::notes::quartertriplet; break;
      case 3: note = core::clock::notes::eighth; break;
      case 4: note = core::clock::notes::eighthtriplet; break;
      case 5: note = core::clock::notes::sixteenth; break;
      default: OTTO_UNREACHABLE;
    }
  }

  void Audio::action(Actions::graphics_outdated, std::atomic<bool>& ref) noexcept
  {
    shared_graphics_flag = &ref;
  }


  // PlayMode functions


  template<typename Cmp>
  tl::optional<NoteTPair> find_next_note(const NoteArray& notes, NoteTPair current, Cmp&& cmp)
  {
    tl::optional<NoteTPair> res = tl::nullopt;
    auto is_initial = current == NoteTPair::initial;
    for (auto&& [note, t] : notes) {
      auto is_after_break = (t > current.t) && (!res || res->t < current.t);
      auto is_next_of_same_note = (t > current.t && note == current.note);
      auto is_closest = (is_initial || cmp(note, current.note)) &&
                        (!res || (cmp(res->note, note) || (is_after_break && note == res->note)));
      if (is_next_of_same_note || is_closest) {
        res = {note, t};
        if (is_next_of_same_note) break;
      }
    }
    return res;
  }

  tl::optional<NoteTPair> find_next_note_up(const NoteArray& notes, NoteTPair current)
  {
    return find_next_note(notes, current, std::greater<>());
  }

  tl::optional<NoteTPair> find_next_note_down(const NoteArray& notes, NoteTPair current)
  {
    return find_next_note(notes, current, std::less<>());
  }

  namespace play_modes {

    NoteVector manual(ArpeggiatorState& state, const NoteArray& notes)
    {
      auto res = std::upper_bound(notes.begin(), notes.end(), state.current);
      if (res == notes.end()) res = notes.begin();
      state.current = *res;
      return NoteVector{res->note};
    }

    NoteVector up(ArpeggiatorState& state, const NoteArray& notes)
    {
      const auto next =
        find_next_note_up(notes, state.current).or_else([&] { return find_next_note_up(notes, NoteTPair::initial); });
      if (next) state.current = *next;
      return next.map_or([](auto pair) { return NoteVector{pair.note}; }, NoteVector{});
    }

    NoteVector down(ArpeggiatorState& state, const NoteArray& notes)
    {
      const auto next = find_next_note_down(notes, state.current).or_else([&] {
        return find_next_note_down(notes, NoteTPair::initial);
      });
      if (next) state.current = *next;
      return next.map_or([](auto pair) { return NoteVector{pair.note}; }, NoteVector{});
    }

    NoteVector chord(ArpeggiatorState& state, const NoteArray& notes)
    {
      auto res = NoteVector();
      for (auto& [note, t] : notes) {
        res.insert(note);
      }
      return res;
    }

    NoteVector random(ArpeggiatorState& state, const NoteArray& notes)
    {
      unsigned int n = notes.size();
      auto next = state.rng(n); 
      return NoteVector{notes[next].note};
    }

    NoteVector updown(ArpeggiatorState& state, const NoteArray& notes)
    {
      tl::optional<NoteTPair> next;
      if (state.direction == Direction::first) {
        next = find_next_note_up(notes, state.current).or_else([&] {
          state.direction = Direction::second;
          return find_next_note_down(notes, state.current);
        });
      } else if (state.direction == Direction::second) {
        next = find_next_note_down(notes, state.current).or_else([&] {
          state.direction = Direction::first;
          return find_next_note_up(notes, state.current);
        });
      }
      if (next) state.current = *next;
      return next.map_or([](auto pair) { return NoteVector{pair.note}; }, NoteVector{});
    }

    NoteVector downup(ArpeggiatorState& state, const NoteArray& notes)
    {
      tl::optional<NoteTPair> next;
      if (state.direction == Direction::first) {
        next = find_next_note_down(notes, state.current).or_else([&] {
          state.direction = Direction::second;
          return find_next_note_up(notes, state.current);
        });
      } else if (state.direction == Direction::second) {
        next = find_next_note_up(notes, state.current).or_else([&] {
          state.direction = Direction::first;
          return find_next_note_down(notes, state.current);
        });
      }
      if (next) state.current = *next;
      return next.map_or([](auto pair) { return NoteVector{pair.note}; }, NoteVector{});
    }

    NoteVector updowninc(ArpeggiatorState& state, const NoteArray& notes)
    {
      tl::optional<NoteTPair> next;
      if (state.direction == Direction::first) {
        next = find_next_note_up(notes, state.current).or_else([&] {
          state.direction = Direction::second;
          return find_next_note_down(notes, NoteTPair::initial);
        });
      } else if (state.direction == Direction::second) {
        next = find_next_note_down(notes, state.current).or_else([&] {
          state.direction = Direction::first;
          return find_next_note_up(notes, NoteTPair::initial);
        });
      }
      if (next) state.current = *next;
      return next.map_or([](auto pair) { return NoteVector{pair.note}; }, NoteVector{});
    }

    NoteVector downupinc(ArpeggiatorState& state, const NoteArray& notes)
    {
      tl::optional<NoteTPair> next;
      if (state.direction == Direction::first) {
        next = find_next_note_down(notes, state.current).or_else([&] {
          state.direction = Direction::second;
          return find_next_note_up(notes, NoteTPair::initial);
        });
      } else if (state.direction == Direction::second) {
        next = find_next_note_up(notes, state.current).or_else([&] {
          state.direction = Direction::first;
          return find_next_note_down(notes, NoteTPair::initial);
        });
      }
      if (next) state.current = *next;
      return next.map_or([](auto pair) { return NoteVector{pair.note}; }, NoteVector{});
    }

  } // namespace play_modes

  namespace octave_modes {

    // OctaveMode functions
    NoteVector standard(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc play_mode)
    {
      return play_mode(state, input);
    }

    NoteVector octaveupunison(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc play_mode)
    {
      auto notes = play_mode(state, input);
      auto res = notes;
      for (auto note : notes) {
        res.insert(note + 12);
      }
      return res;
    }

    NoteVector fifthunison(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc play_mode)
    {
      auto notes = play_mode(state, input);
      auto res = notes;
      for (auto note : notes) {
        res.insert(note + 7);
      }
      return res;
    }

    NoteVector octaveup(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc play_mode)
    {
      if (!state.cached_notes) {
        state.cached_notes = input;
        auto max_t = input.back().t;
        for (auto [i, pair] : util::view::indexed(input)) {
          state.cached_notes->push_back(
            {static_cast<std::uint8_t>(pair.note + 12), static_cast<std::int8_t>(max_t + 1 + i)});
        }
      }
      return play_mode(state, *state.cached_notes);
    }

    NoteVector doubleoctaveup(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc play_mode)
    {
      if (!state.cached_notes) {
        state.cached_notes = input;
        auto max_t = input.back().t;
        for (auto [i, pair] : util::view::indexed(input)) {
          state.cached_notes->push_back(
            {static_cast<std::uint8_t>(pair.note + 12), static_cast<std::int8_t>(max_t + 1 + i)});
          state.cached_notes->push_back(
            {static_cast<std::uint8_t>(pair.note + 24), static_cast<std::int8_t>(2 * max_t + 1 + i)});
        }
      }
      return play_mode(state, *state.cached_notes);
    }

    NoteVector octavedownup(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc play_mode)
    {
      if (!state.cached_notes) {
        state.cached_notes = input;
        for (auto& pair : *state.cached_notes) {
          pair.note -= 12;
        }
        auto max_t = input.back().t;
        for (auto [i, pair] : util::view::indexed(input)) {
          state.cached_notes->push_back(
            {static_cast<std::uint8_t>(pair.note + 12), static_cast<std::int8_t>(max_t + 1 + i)});
        }
      }
      return play_mode(state, *state.cached_notes);
    }
  } // namespace octave_modes


} // namespace otto::engines::arp
