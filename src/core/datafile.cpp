#include "core/datafile.hpp"
#include "core/globals.hpp"

namespace top1 {

  void DataFile::write() {
    tree::Map m;

    m["TapeDeck"] = Globals::tapedeck.serialize();
    m["Mixer"] = Globals::mixer.serialize();
    m["Synth"] = Globals::synth.serialize();
    m["Drums"] = Globals::drums.serialize();
    m["Metronome"] = Globals::metronome.serialize();
    data = m;
    JsonFile::write();
  }

  void DataFile::read() {
    JsonFile::read();

    data.match([&] (tree::Map &m) {
                 Globals::tapedeck.deserialize(m["TapeDeck"]);
                 Globals::mixer.deserialize(m["Mixer"]);
                 Globals::synth.deserialize(m["Synth"]);
                 Globals::drums.deserialize(m["Drums"]);
                 Globals::metronome.deserialize(m["Metronome"]);
               },
               [&] (auto) {
                 LOGE << "Invalid Json - expected a map at root";
               });
  }

} // top1
