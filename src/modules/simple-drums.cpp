#include "simple-drums.h"
#include "simple-drums.faust.h"

SimpleDrumVoice::SimpleDrumVoice() : FaustWrapper(
  new faust_simple_drums(), {

    {"D1/FREQ",          &D1.freq},
    {"D1/NOISE",         &D1.noiseLvL},
    {"D1/TONE_DECAY",    &D1.toneDecay},
    {"D1/CUTOFF",        &D1.cutoff},
    {"D1/FILTER_SWITCH", &D1.filterSwitch},
    {"D1/DECAY_GRAPH",   &D1.decayGraph},

    {"D2/FREQ",          &D1.freq},
    {"D2/NOISE",         &D1.noiseLvL},
    {"D2/TONE_DECAY",    &D1.toneDecay},
    {"D2/CUTOFF",        &D1.cutoff},
    {"D2/FILTER_SWITCH", &D1.filterSwitch},
    {"D2/DECAY_GRAPH",   &D1.decayGraph},

    {"ENVELOPE/ATTACK",  &envelope.attack},
    {"ENVELOPE/RELEASE", &envelope.attack},
    {"ENVELOPE/SUSTAIN", &envelope.attack},

    {"TRIGGER",          &trigger},
  }) {

}

SimpleDrumsModule::SimpleDrumsModule() {
  screen = new SimpleDrumsScreen(this);
}

SimpleDrumsModule::~SimpleDrumsModule() {
  delete screen;
}

void SimpleDrumsModule::process(uint nframes) {
  for (auto event : GLOB.midiEvents) {
    if (NoteOnEvent *event = dynamic_cast<NoteOnEvent*>(event)) {
      currentVoiceIdx = event->key % 24;
      *voices[currentVoiceIdx].trigger = 1;
    }
  };
  for (auto voice : voices) {
    voice.process(nframes);
  }
}

bool SimpleDrumsScreen::keypress(ui::Key key) {
  using namespace ui;
  auto &voice = module->voices[module->currentVoiceIdx];
  auto &osc = GLOB.ui.keys[K_SHIFT] ? voice.D1 : voice.D2;
}

void SimpleDrumsScreen::draw(NanoCanvas::Canvas &ctx) {

}
