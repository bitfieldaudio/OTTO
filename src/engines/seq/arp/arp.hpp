#pragma once

#include <magic_enum.hpp>
#include <foonathan/array/small_array.hpp>

#include "core/engine/engine.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct Arp : ArpeggiatorEngine<Arp> {
    static constexpr util::string_ref name = "Arp";

    using NoteArray = foonathan::array::small_array<midi::NoteOnEvent, 6>;

    enum struct Playmode {
      up,
      down,
      updown,
      downup,
      updowninc,
      downupinc,
      manual,
      chord,
    };

    enum struct OctaveMode {
      standard,
      octaveup,
      octaveupunison,
      fifthunison,
      octaveupdown,
    };

    struct Props {
      Property<Playmode, wrap> playmode = {Playmode::up};
      Property<OctaveMode, wrap> octavemode = {OctaveMode::standard};
      Property<float> note_length = {0.2f, limits(0.01f, 1.f)};

      std::vector<NoteArray> output_stack_;
      bool graphics_outdated = false;

      DECL_REFLECTION(Props, playmode, octavemode, note_length);
    } props;

    Arp();

    audio::ProcessData<0> process(audio::ProcessData<0> data);

    void sort_notes();

    midi::NoteOnEvent transpose_note(midi::NoteOnEvent, int);


  private:
    int _samples_per_beat = 22050 / 2;
    int _counter = _samples_per_beat;
    bool has_changed_ = false;
    int note_off_frames = 1000;
    bool running_ = false;

    std::vector<midi::NoteOnEvent> held_notes_;
    decltype(util::view::circular(props.output_stack_).begin()) iter = util::view::circular(props.output_stack_).begin();
  };



} // namespace otto::engines
