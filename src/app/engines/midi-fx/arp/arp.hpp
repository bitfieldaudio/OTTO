#pragma once

#include "lib/util/local_vector.hpp"
#include "lib/util/random.hpp"
#include "lib/util/visitor.hpp"
#include "lib/util/with_limits.hpp"

#include "lib/audio.hpp"
#include "lib/engine.hpp"
#include "lib/graphics.hpp"
#include "lib/midi.hpp"

#include "app/services/graphics.hpp"

#include "state.hpp"

using namespace otto;

namespace otto::engines::arp {
  struct ILogic {
    virtual ~ILogic() = default;
  };

  struct IMidiFXAudio : midi::MidiHandler {
    midi::IMidiHandler& target()
    {
      if (target_ == nullptr) return empty_target_;
      return *target_;
    }
    void set_target(midi::IMidiHandler* target)
    {
      target_ = target;
    }
    virtual void process() noexcept = 0;

  private:
    midi::IMidiHandler* target_;
    midi::MidiHandler empty_target_ = {};
  };

  struct MidiFXEngineInstance {
    std::unique_ptr<ILogic> logic;
    std::unique_ptr<IMidiFXAudio> audio;
    ScreenWithHandler screen;
  };

  struct MidiFXEngineFactory {
    fu2::unique_function<std::unique_ptr<ILogic>(itc::Context&) const> make_logic;
    fu2::unique_function<std::unique_ptr<IMidiFXAudio>(itc::Context&) const> make_audio;
    fu2::unique_function<ScreenWithHandler(itc::Context&) const> make_screen;

    MidiFXEngineInstance make_all(itc::Context& chan) const
    {
      return {
        .logic = make_logic(chan),
        .audio = make_audio(chan),
        .screen = make_screen(chan),
      };
    }

    MidiFXEngineInstance make_without_audio(itc::Context& chan) const
    {
      return {
        .logic = make_logic(chan),
        .audio = nullptr,
        .screen = make_screen(chan),
      };
    }

    MidiFXEngineInstance make_without_screen(itc::Context& chan) const
    {
      return {
        .logic = make_logic(chan),
        .audio = make_audio(chan),
        .screen = {nullptr, nullptr},
      };
    }
  };

  struct NoteTPair {
    std::uint8_t note;
    /// The "time" value
    ///
    /// Used by the `manual` playmode to play in insertion order even when releasing in-between notes
    std::int8_t t;

    static NoteTPair initial;

    constexpr bool operator<(const NoteTPair& rhs) const noexcept
    {
      return t < rhs.t;
    }

    constexpr bool operator==(const NoteTPair& rhs) const noexcept
    {
      return t == rhs.t && note == rhs.note;
    }
  };
  inline NoteTPair NoteTPair::initial = {128, -1};
  /// The current step
  /// Placed here to use in both graphics and audio
  using NoteVector = util::local_set<std::uint8_t, 24>;
  /// The input notes
  /// This is always sorted by t
  /// On insertion, insert with `t = note_array.back().t + 1`
  using NoteArray = util::local_vector<NoteTPair, 128>;

  struct ArpeggiatorState {
    NoteTPair current = NoteTPair::initial;
    enum struct Direction : std::uint8_t { first, second } direction = Direction::first;
    /// Some octave modes modify the notes input to the playmode.
    /// This is the cache of those. It should be invalidated (set to nullopt)
    /// whenever the notes or the octave mode changes.
    tl::optional<NoteArray> cached_notes = tl::nullopt;

    /// random number generator used for the Random playmode
    util::fastrand_in_range rng{1234};

    /// Counter. Used to detect wraps for graphics
    int count = 0;

    void invalidate_om_cache()
    {
      cached_notes = tl::nullopt;
    }

    void reset() noexcept
    {
      *this = ArpeggiatorState();
    }
  };
  /// Playmode functions
  using PlayModeFunc = util::function_ptr<NoteVector(ArpeggiatorState&, const NoteArray&)>;
  using OctaveModeFunc = util::function_ptr<NoteVector(ArpeggiatorState&, const NoteArray&, PlayModeFunc)>;
  namespace play_modes {
    NoteVector up(ArpeggiatorState& state, const NoteArray& notes);
    NoteVector down(ArpeggiatorState& state, const NoteArray& notes);
    NoteVector chord(ArpeggiatorState& state, const NoteArray& notes);
    NoteVector manual(ArpeggiatorState& state, const NoteArray& notes);
    NoteVector random(ArpeggiatorState& state, const NoteArray& notes);
    NoteVector updown(ArpeggiatorState& state, const NoteArray& notes);
    NoteVector downup(ArpeggiatorState& state, const NoteArray& notes);
    NoteVector updowninc(ArpeggiatorState& state, const NoteArray& notes);
    NoteVector downupinc(ArpeggiatorState& state, const NoteArray& notes);

    PlayModeFunc func(PlayMode);
  } // namespace play_modes

  namespace octave_modes {
    NoteVector standard(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc);
    NoteVector octaveupunison(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc);
    NoteVector fifthunison(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc);
    NoteVector octaveup(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc);
    NoteVector doubleoctaveup(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc);
    NoteVector octavedownup(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc);
    NoteVector multiply(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc);

    OctaveModeFunc func(OctaveMode);
  } // namespace octave_modes

  std::unique_ptr<ILogic> make_logic(itc::Context&);
  ScreenWithHandler make_screen(itc::Context&);
  std::unique_ptr<IMidiFXAudio> make_audio(itc::Context&);

  // NOLINTNEXTLINE
  inline const MidiFXEngineFactory factory = {
    .make_logic = make_logic,
    .make_audio = make_audio,
    .make_screen = make_screen,
  };

} // namespace otto::engines::arp
