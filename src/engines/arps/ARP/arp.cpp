#include "arp.hpp"

#include "audio.hpp"
#include "screen.hpp"
#include "itc/action_bus.hpp"
#include "services/audio_manager.hpp"
#include "services/ui_manager.hpp"

#include "audio.hpp"
#include "screen.hpp"

namespace otto::engines::arp {

  using namespace core::input;

  Arp::Arp(itc::ActionChannel channel) : audio(std::make_unique<Audio>()), screen_(std::make_unique<Screen>())
  {
    set_children({{audio.get(), screen_.get()}});
    register_to(channel);
    props.send_actions();
    
    itc::send_to_bus<itc::AudioBus, itc::GraphicsBus>(Actions::graphics_outdated(), graphics_outdated_);
  }

  void Arp::encoder(EncoderEvent ev)
  {
    switch (ev.encoder) {
      case Encoder::blue: props.playmode.step(util::math::sgn(ev.steps)); break;
      case Encoder::green: props.octavemode.step(util::math::sgn(ev.steps)); break;
      case Encoder::yellow: props.subdivision.step(util::math::sgn(ev.steps)); break;
      case Encoder::red: props.note_length.step(ev.steps); break;
    }
  }

  core::ui::ScreenAndInput Arp::screen()
  {
    return {*screen_, *this};
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
      auto next = state.rng(n);
      return NoteVector{notes[next].note};
    }

    NoteVector updown(ArpeggiatorState& state, const NoteArray& notes)
    {
      state.count++;
      tl::optional<NoteTPair> next;
      if (state.direction == ArpeggiatorState::Direction::first) {
        next = find_next_note_up(notes, state.current).or_else([&] {
          state.direction = ArpeggiatorState::Direction::second;
          return find_next_note_down(notes, state.current);
        });
      } else if (state.direction == ArpeggiatorState::Direction::second) {
        next = find_next_note_down(notes, state.current).or_else([&] {
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
          state.direction = ArpeggiatorState::Direction::second;
          return find_next_note_up(notes, state.current);
        });
      } else if (state.direction == ArpeggiatorState::Direction::second) {
        next = find_next_note_up(notes, state.current).or_else([&] {
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
