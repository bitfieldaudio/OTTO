#pragma once

#include "util/poly-ptr.hpp"

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

using MidiEventPtr = top1::SmartPolyPtr<MidiEvent,
    NoteOnEvent,
    NoteOffEvent,
    ControlChangeEvent>;

namespace midi {
void generateFreqTable(float tuning = 440.0);

extern float freqTable[128];
}
