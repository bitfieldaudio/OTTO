#include "arp.hpp"

#include "lib/util/algorithm.hpp"

#include "lib/engine.hpp"
#include "lib/itc/itc.hpp"

#include "app/input.hpp"
#include "app/services/controller.hpp"
#include "app/services/logic_thread.hpp"

namespace otto::engines::arp {

  struct Logic final : ILogic, LogicDomain, itc::Producer<State> {
    using Producer::Producer;
  };

  std::unique_ptr<ILogic> make_logic(itc::Context& c)
  {
    return std::make_unique<Logic>(c);
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
      if (notes.size() == 0) return NoteVector{};
      state.count++;
      auto res = std::upper_bound(notes.begin(), notes.end(), state.current);
      if (res == notes.end()) {
        state.count = 0;
        res = notes.begin();
      }
      state.current = *res;
      return NoteVector{res->note};
    }

    NoteVector up(ArpeggiatorState& state, const NoteArray& notes)
    {
      state.count++;
      const auto next = find_next_note_up(notes, state.current).or_else([&] {
        state.count = 0;
        return find_next_note_up(notes, NoteTPair::initial);
      });
      if (next) state.current = *next;
      return next.map_or([](auto pair) { return NoteVector{pair.note}; }, NoteVector{});
    }

    NoteVector down(ArpeggiatorState& state, const NoteArray& notes)
    {
      state.count++;
      const auto next = find_next_note_down(notes, state.current).or_else([&] {
        state.count = 0;
        return find_next_note_down(notes, NoteTPair::initial);
      });
      if (next) state.current = *next;
      return next.map_or([](auto pair) { return NoteVector{pair.note}; }, NoteVector{});
    }

    NoteVector chord(ArpeggiatorState& state, const NoteArray& notes)
    {
      state.count = 0;
      auto res = NoteVector();
      for (auto& [note, t] : notes) {
        res.insert(note);
      }
      return res;
    }

    NoteVector random(ArpeggiatorState& state, const NoteArray& notes)
    {
      // Note that the count variable only works for graphics. It has no other use
      state.count++;
      if (state.count > 8) state.count = 0;
      unsigned int n = notes.size();
      if (n == 0) return NoteVector{};
      auto next = state.rng(n);
      return NoteVector{notes[next].note};
    }

    // The updown and downup patterns need a bit of custom logic for the case where only one note is playing
    auto reset = [](ArpeggiatorState& state, const NoteArray& notes) {
      state.count = 0;
      return find_next_note_up(notes, NoteTPair::initial);
    };

    NoteVector updown(ArpeggiatorState& state, const NoteArray& notes)
    {
      state.count++;
      tl::optional<NoteTPair> next;
      if (state.direction == ArpeggiatorState::Direction::first) {
        next = find_next_note_up(notes, state.current).or_else([&] {
          if (notes.size() == 1) return reset(state, notes);
          state.direction = ArpeggiatorState::Direction::second;
          return find_next_note_down(notes, state.current);
        });
      } else if (state.direction == ArpeggiatorState::Direction::second) {
        next = find_next_note_down(notes, state.current).or_else([&] {
          if (notes.size() == 1) return reset(state, notes);
          state.direction = ArpeggiatorState::Direction::first;
          state.count = 0;
          return find_next_note_up(notes, state.current);
        });
      }
      if (next) state.current = *next;
      return next.map_or([](auto pair) { return NoteVector{pair.note}; }, NoteVector{});
    }

    NoteVector downup(ArpeggiatorState& state, const NoteArray& notes)
    {
      state.count++;
      tl::optional<NoteTPair> next;
      if (state.direction == ArpeggiatorState::Direction::first) {
        next = find_next_note_down(notes, state.current).or_else([&] {
          if (notes.size() == 1) return reset(state, notes);
          state.direction = ArpeggiatorState::Direction::second;
          return find_next_note_up(notes, state.current);
        });
      } else if (state.direction == ArpeggiatorState::Direction::second) {
        next = find_next_note_up(notes, state.current).or_else([&] {
          if (notes.size() == 1) return reset(state, notes);
          state.direction = ArpeggiatorState::Direction::first;
          state.count = 0;
          return find_next_note_down(notes, state.current);
        });
      }
      if (next) state.current = *next;
      return next.map_or([](auto pair) { return NoteVector{pair.note}; }, NoteVector{});
    }

    NoteVector updowninc(ArpeggiatorState& state, const NoteArray& notes)
    {
      state.count++;
      tl::optional<NoteTPair> next;
      if (state.direction == ArpeggiatorState::Direction::first) {
        next = find_next_note_up(notes, state.current).or_else([&] {
          state.direction = ArpeggiatorState::Direction::second;
          return find_next_note_down(notes, NoteTPair::initial);
        });
      } else if (state.direction == ArpeggiatorState::Direction::second) {
        next = find_next_note_down(notes, state.current).or_else([&] {
          state.direction = ArpeggiatorState::Direction::first;
          state.count = 0;
          return find_next_note_up(notes, NoteTPair::initial);
        });
      }
      if (next) state.current = *next;
      return next.map_or([](auto pair) { return NoteVector{pair.note}; }, NoteVector{});
    }

    NoteVector downupinc(ArpeggiatorState& state, const NoteArray& notes)
    {
      state.count++;
      tl::optional<NoteTPair> next;
      if (state.direction == ArpeggiatorState::Direction::first) {
        next = find_next_note_down(notes, state.current).or_else([&] {
          state.direction = ArpeggiatorState::Direction::second;
          return find_next_note_up(notes, NoteTPair::initial);
        });
      } else if (state.direction == ArpeggiatorState::Direction::second) {
        next = find_next_note_up(notes, state.current).or_else([&] {
          state.direction = ArpeggiatorState::Direction::first;
          state.count = 0;
          return find_next_note_down(notes, NoteTPair::initial);
        });
      }
      if (next) state.current = *next;
      return next.map_or([](auto pair) { return NoteVector{pair.note}; }, NoteVector{});
    }

    PlayModeFunc func(PlayMode pm)
    {
      switch (pm) {
        case PlayMode::up: return up; break;
        case PlayMode::down: return down; break;
        case PlayMode::updown: return updown; break;
        case PlayMode::downup: return downup; break;
        case PlayMode::updowninc: return updowninc; break;
        case PlayMode::downupinc: return downupinc; break;
        case PlayMode::manual: return manual; break;
        case PlayMode::chord: return chord; break;
        case PlayMode::random: return random; break;
      }
      OTTO_UNREACHABLE();
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
        util::indexed_for_each(input, [&](std::size_t i, const NoteTPair& pair) {
          state.cached_notes->push_back(
            {static_cast<std::uint8_t>(pair.note + 12), static_cast<std::int8_t>(max_t + 1 + i)});
        });
      }
      return play_mode(state, *state.cached_notes);
    }

    NoteVector doubleoctaveup(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc play_mode)
    {
      if (!state.cached_notes) {
        state.cached_notes = input;
        auto max_t = input.back().t;
        util::indexed_for_each(input, [&](std::size_t i, const NoteTPair& pair) {
          state.cached_notes->push_back(
            {static_cast<std::uint8_t>(pair.note + 12), static_cast<std::int8_t>(max_t + 1 + i)});
        });
        util::indexed_for_each(input, [&](std::size_t i, const NoteTPair& pair) {
          state.cached_notes->push_back(
            {static_cast<std::uint8_t>(pair.note + 24), static_cast<std::int8_t>(2 * max_t + 1 + i)});
        });
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
        util::indexed_for_each(input, [&](std::size_t i, const NoteTPair& pair) {
          state.cached_notes->push_back(
            {static_cast<std::uint8_t>(pair.note + 12), static_cast<std::int8_t>(max_t + 1 + i)});
        });
      }
      return play_mode(state, *state.cached_notes);
    }

    NoteVector multiply(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc play_mode)
    {
      if (!state.cached_notes) {
        state.cached_notes = input;
        state.cached_notes->clear();
        util::indexed_for_each(input, [&](std::size_t i, const NoteTPair& pair) {
          state.cached_notes->push_back({static_cast<std::uint8_t>(pair.note), static_cast<std::int8_t>(pair.t + i)});
          state.cached_notes->push_back(
            {static_cast<std::uint8_t>(pair.note), static_cast<std::int8_t>(pair.t + i + 1)});
        });
      }
      return play_mode(state, *state.cached_notes);
    }

    OctaveModeFunc func(OctaveMode om)
    {
      switch (om) {
        case OctaveMode::standard: return standard; break;
        case OctaveMode::octaveupunison: return octaveupunison; break;
        case OctaveMode::fifthunison: return fifthunison; break;
        case OctaveMode::octaveup: return octaveup; break;
        case OctaveMode::doubleoctaveup: return doubleoctaveup; break;
        case OctaveMode::octavedownup: return octavedownup; break;
        case OctaveMode::multiply: return multiply; break;
      }
      OTTO_UNREACHABLE();
    }
  } // namespace octave_modes

} // namespace otto::engines::arp
