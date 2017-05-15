#include "faust.h"
#include "module.h"

class FaustSynthModule : public SynthModule, public FaustWrapper {
  bool lastTrig;
protected:
  float *frequency;
  uint midiNote;
  bool trigger;
public:

  FaustSynthModule(dsp *fDSP, std::map<std::string, FAUSTFLOAT**> opts) :
    FaustWrapper (fDSP, opts) {}

  void process(uint nframes) override {
    for (auto event : GLOB.midiEvents) {
      if (event->type == MidiEvent::NOTE_ON) {
        midiNote = dynamic_cast<NoteOnEvent *>(event)->key;
        *frequency = midi::freqTable[midiNote];
        trigger = true;
      }
      if (event->type == MidiEvent::NOTE_OFF) {
        if (midiNote == dynamic_cast<NoteOffEvent *>(event)->key) {
          trigger = false;
        }
      }
    }
    // TODO: Real implementation
    if (trigger) FaustWrapper::process(nframes);
    lastTrig = trigger;
  }
};
