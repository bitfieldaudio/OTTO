#include "testsynth.h"

#include <string>

#include "../globals.h"
#include "../ui/utils.h"
#include "../ui/mainui.h"

#include "testsynth.faust.h"

TestSynth::TestSynth() :
  FaustSynthModule (new FAUSTCLASS(), &data),
  screen (new TestSynthScreen(this)) {}

TestSynth::~TestSynth() {}

void TestSynth::display() {
  GLOB.ui.display(screen);
}

void TestSynth::process(uint nframes) {
  for (auto &&nEvent : GLOB.midiEvents) {
    nEvent.match([&] (NoteOnEvent *e) {
       if (e->channel == 0) {
         data.key = e->key;
         data.trigger = 1;
         data.velocity = float(e->velocity)/128.f;
       }
     }, [] (MidiEvent *) {});
  }
  FaustSynthModule::process(nframes);
  for (auto &&nEvent : GLOB.midiEvents) {
    nEvent.match([&] (NoteOffEvent *e) {
       if (e->channel == 0) {
         if (e->key == data.key) {
           data.trigger = 0;
         }
       }
     }, [] (MidiEvent *) {});
  };
}

void TestSynthScreen::draw(drawing::Canvas& ctx) {
  using namespace ui;
  using namespace drawing;
  ctx.beginPath();
  ctx.textAlign(TextAlign::Center, TextAlign::Middle);
  ctx.font(FONT_LIGHT);
  ctx.font(32);
  ctx.fillStyle(Colours::White);
  ctx.fillText("TestSynth", {WIDTH / 2.f, HEIGHT / 2.f});
}

bool TestSynthScreen::keypress(ui::Key key) {
  switch (key) {
  default:
    return false;
  }
}
