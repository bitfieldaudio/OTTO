#pragma once

#include "core/engine/engine.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct Arp : ArpeggiatorEngine<Arp> {
    enum struct Playmode {
      up,
      down,
      timed,

      // Number of modes
      n_modes
    };

    enum struct OctaveMode {
      standard,
      octaveup,
      octavedown,
      octaveupdown,
      octaveupdownskip,
      // Number of modes
      n_modes
    };

    struct Props {
      Property<Playmode, wrap> playmode = {Playmode::up, limits(Playmode{0}, Playmode::n_modes)};
      Property<OctaveMode, wrap> octavemode = {OctaveMode::standard, limits(OctaveMode{0}, OctaveMode::n_modes)};
      Property<float> note_length = {0.2f, limits(0.01f, 1.f)};

      DECL_REFLECTION(Props, playmode, octavemode, note_length);
    } props;

    Arp();

    audio::ProcessData<0> process(audio::ProcessData<0> data);

    std::vector<std::vector<midi::NoteOnEvent>> sort_notes(Props&);

  private:
    int _samples_per_beat = 22050 / 4;
    int _counter = _samples_per_beat;
    int step = 0;
    bool has_changed_ = false;
    int note_off_frames = 1000;

    std::vector<midi::NoteOnEvent> held_notes_;
    std::vector<std::vector<midi::NoteOnEvent>> output_stack_;
  };



} // namespace otto::engines
