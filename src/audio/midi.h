#pragma once

#include <mapbox/variant.hpp>

struct BaseMidiEvent {

  typedef unsigned char byte;

  virtual ~BaseMidiEvent() {}

  enum EventType {
    NOTE_OFF = 0b1000,
    NOTE_ON = 0b1001,
    CONTROL_CHANGE = 0b1011,
  } type;

  byte channel;

  byte *data;

  int time;

};


struct NoteOnEvent : public BaseMidiEvent {
  byte key = data[0];
  byte velocity = data[1];

  NoteOnEvent(BaseMidiEvent event) : BaseMidiEvent(event) {};
};

struct NoteOffEvent : public BaseMidiEvent {
  byte key = data[0];
  byte velocity = data[1];

  NoteOffEvent(BaseMidiEvent event) : BaseMidiEvent(event) {};
};

struct ControlChangeEvent : public BaseMidiEvent {
  byte controler = data[0];
  byte value = data[1];

  ControlChangeEvent(BaseMidiEvent event) : BaseMidiEvent(event) {};
};

using MidiEvent = mapbox::util::variant<
    NoteOnEvent,
    NoteOffEvent,
    ControlChangeEvent,
    BaseMidiEvent>;

namespace midi {
void generateFreqTable(float tuning = 440.0);

extern float freqTable[128];
}
