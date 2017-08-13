#include "core/datafile.hpp"
#include "core/globals.hpp"

using namespace top1;

void DataFile::write() {
  tree::Map m;

  m["TapeDeck"] = GLOB.tapedeck.serialize();
  m["Mixer"] = GLOB.mixer.serialize();
  m["Synth"] = GLOB.synth.serialize();
  m["Drums"] = GLOB.drums.serialize();
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
      GLOB.drums.deserialize(m["Drums"]);
      GLOB.metronome.deserialize(m["Metronome"]);
    },
    [&] (auto) {
      LOGE << "Invalid Json - expected a map at root";
    });
}
