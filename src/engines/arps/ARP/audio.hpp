#pragma once

#include <foonathan/array/small_array.hpp>
#include "arp.hpp"

namespace otto::engines::arp {

  using namespace core;

  struct Audio {
    Audio() noexcept;
    audio::ProcessData<0> process(audio::ProcessData<0>) noexcept;

    using Playmode = detail::ArpPlaymode;
    using OctaveMode = detail::ArpOctaveMode;
    using NoteArray = foonathan::array::small_array<core::midi::NoteOnEvent, 6>;
    void action(itc::prop_change<&Props::playmode>, Playmode pm) noexcept;
    void action(itc::prop_change<&Props::octavemode>, OctaveMode om) noexcept;
    void action(itc::prop_change<&Props::note_length>, float nl) noexcept;
    void action(itc::prop_change<&Props::subdivision>, int sd) noexcept;

    void action(Actions::graphics_outdated, std::atomic<bool>&) noexcept;

    void sort_notes();
    midi::NoteOnEvent transpose_note(midi::NoteOnEvent, int);

  private:
    float note_length_ = 0.4;
    Playmode playmode_ = Playmode::up;
    OctaveMode octavemode_ = OctaveMode::standard;

    int _samples_per_quarternote = 22050;
    int _samples_per_beat = 22050;
    int _counter = _samples_per_beat;
    bool has_changed_ = false;
    int note_off_frames = 1000;
    bool running_ = false;

    std::atomic<bool>* shared_graphics_flag = nullptr;

    std::vector<midi::NoteOnEvent> held_notes_;
    std::vector<NoteArray> output_stack_;
    decltype(util::view::circular(output_stack_).begin()) iter = util::view::circular(output_stack_).begin();
  };

} // namespace otto::engines::arp
