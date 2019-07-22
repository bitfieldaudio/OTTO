#pragma once

#include <foonathan/array/small_array.hpp>

#include "core/engine/engine.hpp"

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  namespace detail {

    BETTER_ENUM(ArpPlaymode, std::uint8_t,
      up,
      down,
      updown,
      downup,
      updowninc,
      downupinc,
      manual,
      chord
    );

    BETTER_ENUM(ArpOctaveMode, std::uint8_t,
      standard,
      octaveup,
      octaveupunison,
      fifthunison,
      octaveupdown
    );

  }

  struct Arp : ArpeggiatorEngine<Arp> {
    static constexpr util::string_ref name = "Arp";

    using Playmode = detail::ArpPlaymode;
    using OctaveMode = detail::ArpOctaveMode;
    using NoteArray = foonathan::array::small_array<midi::NoteOnEvent, 6>;

    struct Props {
      Property<Playmode, wrap> playmode = {Playmode::up};
      Property<OctaveMode, wrap> octavemode = {OctaveMode::standard};
      Property<float> note_length = {0.2f, limits(0.01f, 0.97f), step_size(0.01)};
      Property<int, wrap> subdivision = {1, limits(1, 4)};

      std::vector<NoteArray> output_stack_;
      bool graphics_outdated = false;

      DECL_REFLECTION(Props, playmode, octavemode, note_length);
    } props;

    Arp();

    audio::ProcessData<0> process(audio::ProcessData<0> data);

    void sort_notes();

    midi::NoteOnEvent transpose_note(midi::NoteOnEvent, int);


  private:
    int _samples_per_quarternote = 22050;
    int _samples_per_beat = 22050;
    int _counter = _samples_per_beat;
    bool has_changed_ = false;
    int note_off_frames = 1000;
    bool running_ = false;

    std::vector<midi::NoteOnEvent> held_notes_;
    decltype(util::view::circular(props.output_stack_).begin()) iter = util::view::circular(props.output_stack_).begin();
  };



} // namespace otto::engines
