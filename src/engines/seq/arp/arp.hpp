#pragma once

#include "core/engine/engine.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct Arp : ArpeggiatorEngine<Arp> {
    static constexpr util::string_ref name = "Arp";

    enum struct Playmode {
      up,
      down,
      updown,
      timed,
      chord,

      // Number of modes
      n_modes
    };

    inline std::string to_string(Playmode pm) noexcept
    {
      switch (pm) {
        case Playmode::up: return "Up";
        case Playmode::down: return "Down";
        case Playmode::timed: return "Timed";
        case Playmode::chord: return "Chord";
      };
      return "";
    }

    enum struct OctaveMode {
      standard,
      octaveup,
      octaveupunison,
      fifthunison,
      octavedown,
      octaveupdown,
      octaveupdownskip,
      // Number of modes
      n_modes
    };

    inline std::string to_string(OctaveMode om) noexcept {
      switch (om) {
        case OctaveMode::standard:
          return "Boring";
        case OctaveMode::octaveup:
          return "+1";
        case OctaveMode::octaveupunison:
          return "Octave";

      };
      return "";
    }

    struct Props {
      Property<Playmode, wrap> playmode = {Playmode::up, limits(Playmode{0}, Playmode::n_modes)};
      Property<OctaveMode, wrap> octavemode = {OctaveMode::standard, limits(OctaveMode{0}, OctaveMode::n_modes)};
      Property<float> note_length = {0.2f, limits(0.01f, 1.f)};

      DECL_REFLECTION(Props, playmode, octavemode, note_length);
    } props;

    Arp();

    audio::ProcessData<0> process(audio::ProcessData<0> data);

    std::vector<std::vector<midi::NoteOnEvent>> sort_notes();

    midi::NoteOnEvent transpose_note(midi::NoteOnEvent, int);


  private:
    int _samples_per_beat = 22050 / 2;
    int _counter = _samples_per_beat;
    int step = 0;
    bool has_changed_ = false;
    int note_off_frames = 1000;
    bool running_ = false;

    std::vector<midi::NoteOnEvent> held_notes_;
    std::vector<std::vector<midi::NoteOnEvent>> output_stack_;
    decltype(util::view::circular(output_stack_).begin()) iter = util::view::circular(output_stack_).begin();
  };



} // namespace otto::engines
