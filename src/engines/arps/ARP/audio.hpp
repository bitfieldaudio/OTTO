#pragma once

#include "arp.hpp"
#include "util/local_vector.hpp"
#include "util/random.hpp"
#include "util/utility.hpp"

namespace otto::engines::arp {

  using namespace core;

  inline NoteTPair NoteTPair::initial = {128, -1};

  struct Audio final : itc::ActionReceiverOnBus<itc::AudioBus,
                                          itc::prop_change<&Props::playmode>,
                                          itc::prop_change<&Props::octavemode>,
                                          itc::prop_change<&Props::note_length>,
                                          itc::prop_change<&Props::subdivision>,
                                          Actions::graphics_outdated> //
  {
    Audio() noexcept;
    audio::ProcessData<0> process(audio::ProcessData<0>) noexcept;

    void action(itc::prop_change<&Props::playmode>, Playmode pm) noexcept final;
    void action(itc::prop_change<&Props::octavemode>, OctaveMode om) noexcept final;
    void action(itc::prop_change<&Props::note_length>, float nl) noexcept final;
    void action(itc::prop_change<&Props::subdivision>, int sd) noexcept final;

    void action(Actions::graphics_outdated, std::atomic<bool>&) noexcept final;

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
