#pragma once

#include "arp.hpp"
#include "util/local_vector.hpp"
#include "util/utility.hpp"
#include "util/random.hpp"

namespace otto::engines::arp {

  using namespace core;

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

  inline NoteTPair NoteTPair::initial = {128, -1};

  /// The current step
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

    void invalidate_om_cache() {
      cached_notes = tl::nullopt;
    }

    void reset() noexcept {
      *this = ArpeggiatorState();
    }
  };

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

  struct Audio {
    Audio() noexcept;
    audio::ProcessData<0> process(audio::ProcessData<0>) noexcept;

    void action(itc::prop_change<&Props::playmode>, Playmode pm) noexcept;
    void action(itc::prop_change<&Props::octavemode>, OctaveMode om) noexcept;
    void action(itc::prop_change<&Props::note_length>, float nl) noexcept;
    void action(itc::prop_change<&Props::subdivision>, int sd) noexcept;

    void action(Actions::graphics_outdated, std::atomic<bool>&) noexcept;

  private:
    PlayModeFunc playmode_func_ = play_modes::up;
    OctaveModeFunc octavemode_func_ = octave_modes::standard;

    float note_length_ = 0.4;

    int _samples_per_quarternote = 22050;
    int _samples_per_beat = 22050;
    core::clock::Time note = core::clock::notes::beat;
    int _counter = _samples_per_beat;
    int note_off_frames = 1000;
    bool running_ = false;
    bool stop_flag = false;

    std::atomic<bool>* shared_graphics_flag = nullptr;

    ArpeggiatorState state_;
    NoteArray notes_;
    NoteVector current_notes_;
  };

} // namespace otto::engines::arp
