#pragma once

#include "util/local_vector.hpp"
#include "util/random.hpp"
#include "core/engine/engine.hpp"
#include "itc/itc.hpp"

namespace otto::engines::arp {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  BETTER_ENUM(Playmode, std::int8_t, up, down, updown, downup, updowninc, downupinc, manual, chord, random);

  BETTER_ENUM(OctaveMode, std::int8_t, standard, octaveup, doubleoctaveup, octaveupunison, fifthunison, octavedownup);

  struct Screen;
  struct Audio;

  struct Actions {
    using graphics_outdated = itc::Action<struct graphics_outdated_tag, std::atomic<bool>&>;
  };

  struct Props {
    itc::GAProp<struct playmode_tag, Playmode, wrap> playmode = {Playmode::up};
    itc::GAProp<struct octavemode_tag, OctaveMode, wrap> octavemode = {OctaveMode::standard};
    itc::GAProp<struct note_length_tag, float> note_length = {0.2f, limits(0.01f, 0.97f), step_size(0.01)};
    itc::GAProp<struct subdivision_tag, int, wrap> subdivision = {1, limits(1, 5)};

    DECL_REFLECTION(Props, playmode, octavemode, note_length, subdivision);
  };

  struct NoteTPair {
    std::uint8_t note;
    /// The "time" value
    /// 
    /// Used by the `manual` playmode to play in insertion order even when 
    std::int8_t t;

    static NoteTPair initial;

    constexpr bool operator<(const NoteTPair& rhs) const noexcept {
      return t < rhs.t;
    }

    constexpr bool operator==(const NoteTPair& rhs) const noexcept {
      return t == rhs.t && note == rhs.note;
    }
  };
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

    void invalidate_om_cache() {
      cached_notes = tl::nullopt;
    }

    void reset() noexcept {
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
  } // namespace play_modes
  namespace octave_modes {
    NoteVector standard(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc);
    NoteVector octaveupunison(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc);
    NoteVector fifthunison(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc);
    NoteVector octaveup(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc);
    NoteVector doubleoctaveup(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc);
    NoteVector octavedownup(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc);

  } // namespace octave_modes
  

  struct Arp : core::engine::ArpeggiatorEngine<Arp> {
    static constexpr util::string_ref name = "Arp";

    Arp();

    void encoder(core::input::EncoderEvent e) override;

    core::ui::ScreenAndInput screen() override;

    const std::unique_ptr<Audio> audio;

    DECL_REFLECTION(Arp, props);

  private:
    const std::unique_ptr<Screen> screen_;

    Props props;

    // Variables shared between audio and graphics
    std::atomic<bool> graphics_outdated_ = false;

  };

} // namespace otto::engines::arp
