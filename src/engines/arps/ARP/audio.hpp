#pragma once

#include <foonathan/array/small_array.hpp>
#include "util/local_vector.hpp"
#include "util/utility.hpp"
#include "arp.hpp"

namespace otto::engines::arp {

  using namespace core;

  struct ArpeggiatorState {
    std::uint8_t current_step = 0;
    std::uint8_t last_t = 1;
    int rounds = 0;
    enum struct Direction : std::uint8_t {
      up, down
    } direction = Direction::up;

    void reset()
    {
      current_step = 0;
      last_t = 1;
      rounds = 0;
    };
  };

  /// The current step
  using NoteVector = util::local_vector<std::uint8_t, 24>;
  /// The list of all possible keys
  /// 0: not held
  /// All other numbers: the order they have been pressed in
  using NoteArray = std::array<std::uint8_t, 128>;
  using OctaveModeFunc = util::function_ptr<void, std::uint8_t, std::uint8_t, NoteVector&>;
  using PlayModeFunc = util::function_ptr<void, ArpeggiatorState&, NoteArray&, std::uint8_t&, OctaveModeFunc, NoteVector&>;
  
  /// PlayMode functions
  /// These increment the step according to the playmode and call the octavemode-function passed as a function pointer.
  void up(ArpeggiatorState& state, NoteArray& notes, std::uint8_t& current_step, OctaveModeFunc omf, NoteVector& output);
  void down(ArpeggiatorState& state, NoteArray& notes, std::uint8_t& current_step, OctaveModeFunc omf, NoteVector& output);

  /// OctaveMode functions
  /// These adjust the note as needed. Unison-modes add other notes, Non-unison modes can shift by whole octaves.
  void standard(std::uint8_t rounds, std::uint8_t note, NoteVector& output);
  void octaveunison(std::uint8_t rounds, std::uint8_t note, NoteVector& output);

  struct Audio {
    Audio() noexcept;
    audio::ProcessData<0> process(audio::ProcessData<0>) noexcept;

    using Playmode = detail::ArpPlaymode;
    using OctaveMode = detail::ArpOctaveMode;
    
    void action(itc::prop_change<&Props::playmode>, Playmode pm) noexcept;
    void action(itc::prop_change<&Props::octavemode>, OctaveMode om) noexcept;
    void action(itc::prop_change<&Props::note_length>, float nl) noexcept;
    void action(itc::prop_change<&Props::subdivision>, int sd) noexcept;

    void action(Actions::graphics_outdated, std::atomic<bool>&) noexcept;

  private:

    OctaveModeFunc octavemode_func_ = standard;
    PlayModeFunc playmode_func_ = up;

    float note_length_ = 0.4;

    int _samples_per_quarternote = 22050;
    int _samples_per_beat = 22050;
    int _counter = _samples_per_beat;
    bool has_changed_ = false;
    int note_off_frames = 1000;
    bool running_ = false;
    bool stop_flag = false;

    std::atomic<bool>* shared_graphics_flag = nullptr;

    ArpeggiatorState state_;
    NoteArray notes_ = {0};
    NoteVector current_notes_;
    std::uint8_t current_step_ = 0;

    

  
  };

} // namespace otto::engines::arp
