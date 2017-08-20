#pragma once

#include <cmath>

#include "util/poly-ptr.hpp"

namespace top1::midi {

  struct MidiEvent {

    typedef unsigned char byte;

    enum EventType {
      NOTE_OFF = 0b1000,
      NOTE_ON = 0b1001,
      CONTROL_CHANGE = 0b1011,
    } type;

    int channel;
    byte *data;
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
  using MidiEventPtr = top1::SmartPolyPtr<MidiEvent,
                                          NoteOnEvent,
                                          NoteOffEvent,
                                          ControlChangeEvent>;

  static inline float freqTable[128];

  constexpr void generateFreqTable(float tuning = 440) {
    for (int i = 0; i < 128; i++) {
      freqTable[i] = tuning * std::pow(2, float(i - 69)/float(12));
    }
  }

}
