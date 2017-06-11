#include "datafile.h"
#include "../globals.h"

using namespace top1;

void DataFile::write() {
  tree::Map m;

  m["TapeDeck"] = GLOB.tapedeck.serialize();
  m["Mixer"] = GLOB.mixer.serialize();
  m["Synth"] = GLOB.synth.serialize();
  m["Metronome"] = GLOB.metronome.serialize();
  data = m;
  JsonFile::write();
}

void DataFile::read() {
  JsonFile::read();

  data.match(
    [&] (tree::Map &m) {
      GLOB.tapedeck.deserialize(m["TapeDeck"]);
      GLOB.mixer.deserialize(m["Mixer"]);
      GLOB.synth.deserialize(m["Synth"]);
      GLOB.metronome.deserialize(m["Metronome"]);
    },
    [&] (auto) {
      LOGE << "Invalid Json - expected a map at root";
    });
}
