#pragma once

#include "arp.hpp"
#include "util/local_vector.hpp"
#include "util/utility.hpp"

namespace otto::engines::arp {

  using namespace core;

  struct NoteTPair {
    std::uint8_t note;
    /// The "time" value
    /// 
    /// 
    std::int8_t t;

    static NoteTPair initial;
    static NoteTPair low_first;
    static NoteTPair high_first;
    static NoteTPair low_last;
    static NoteTPair high_last;

    constexpr bool operator<(const NoteTPair& rhs) const noexcept {
      return t < rhs.t;
    }

    constexpr bool operator==(const NoteTPair& rhs) const noexcept {
      return t == rhs.t && note == rhs.note;
    }
  };

  inline NoteTPair NoteTPair::initial = {128, -1};
  inline NoteTPair NoteTPair::low_first = {0, -1};
  inline NoteTPair NoteTPair::high_first = {127, -1};

  /// The current step
  using NoteVector = util::local_set<std::uint8_t, 24>;
  /// The input notes
  /// This is always sorted by t
  /// On insertion, insert with `t = note_array.back().t + 1`
  using NoteArray = util::local_vector<NoteTPair, 128>;

  struct ArpeggiatorState {
    NoteTPair current = NoteTPair::initial;
    enum struct Direction : std::uint8_t { first, second } direction = Direction::first;

    void reset() noexcept {
      *this = ArpeggiatorState();
    }
  };

  using PlayModeFunc = util::function_ptr<NoteVector(ArpeggiatorState&, const NoteArray&)>;
  using OctaveModeFunc = util::function_ptr<NoteVector(ArpeggiatorState&, const NoteArray&, PlayModeFunc)>;

  namespace play_modes {
    /// PlayMode functions
    /// These increment the step according to the playmode and call the octavemode-function passed as a function
    /// pointer.
    NoteVector up(ArpeggiatorState& state, const NoteArray& notes);
    NoteVector down(ArpeggiatorState& state, const NoteArray& notes);
    NoteVector chord(ArpeggiatorState& state, const NoteArray& notes);
    NoteVector manual(ArpeggiatorState& state, const NoteArray& notes);

    /// These add extra steps to the sequence. Since the octavemode/range steps are completed before the extra steps
    /// from the playmode, they contain a check of the octavemode function. For 'octaveup', 'octaveupdown',
    /// 'octavedownup', the sequence repeats every 4 rounds, as opposed to the other octavemodes where it repeats every
    /// 2 rounds.
    NoteVector updown(ArpeggiatorState& state, const NoteArray& notes);
    NoteVector downup(ArpeggiatorState& state, const NoteArray& notes);
    NoteVector updowninc(ArpeggiatorState& state, const NoteArray& notes);
    NoteVector downupinc(ArpeggiatorState& state, const NoteArray& notes);
  } // namespace play_modes

  namespace octave_modes {

    /// OctaveMode functions
    /// These adjust the note as needed. Unison-modes add other notes, Non-unison modes can shift by whole octaves.
    NoteVector standard(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc);
    NoteVector octaveupunison(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc);
    NoteVector fifthunison(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc);
    NoteVector octaveup(ArpeggiatorState& state, const NoteArray& input, PlayModeFunc);
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
    bool has_changed_ = false;
    int note_off_frames = 1000;
    bool running_ = false;
    bool stop_flag = false;

    std::atomic<bool>* shared_graphics_flag = nullptr;

    ArpeggiatorState state_;
    NoteArray notes_;
    NoteVector current_notes_;
    std::uint8_t current_step_ = 0;
  };

} // namespace otto::engines::arp
