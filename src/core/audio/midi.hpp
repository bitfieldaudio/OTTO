#pragma once

#include <cmath>
#include <variant.hpp>

#include "util/poly-ptr.hpp"

namespace otto::midi {

  struct MidiEvent {

    using byte = unsigned char;

    enum class Type {
      NoteOff       = 0b1000,
      NoteOn        = 0b1001,
      ControlChange = 0b1011,
    };

    Type type;

    byte *data;
    int channel;
    int time;

  };

  struct NoteOnEvent : public MidiEvent {
    int key = data[0];
    int velocity = data[1];

    NoteOnEvent(const MidiEvent& event) : MidiEvent(event) {};
  };

  struct NoteOffEvent : public MidiEvent {
    int key = data[0];
    int velocity = data[1];

    NoteOffEvent(const MidiEvent& event) : MidiEvent(event) {};
  };

  struct ControlChangeEvent : public MidiEvent {
    int controler = data[0];
    int value = data[1];

    ControlChangeEvent(const MidiEvent& event) : MidiEvent(event) {};
  };

  // TODO: Replace with variant AnyMidiEvent
  using AnyMidiEvent = mpark::variant<NoteOnEvent, NoteOffEvent, ControlChangeEvent>;

  inline float freqTable[128];

  constexpr void generateFreqTable(float tuning = 440) {
    for (int i = 0; i < 128; i++) {
      freqTable[i] = tuning * std::pow(2, float(i - 69)/float(12));
    }
  }

}
