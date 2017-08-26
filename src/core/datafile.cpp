#include "core/datafile.hpp"
#include "core/globals.hpp"

namespace top1 {

  void DataFile::write() {
    tree::Map m;

    m["TapeDeck"] = Globals::tapedeck.makeNode();
    m["Mixer"] = Globals::mixer.makeNode();
    m["Synth"] = Globals::synth.makeNode();
    m["Drums"] = Globals::drums.makeNode();
    m["Metronome"] = Globals::metronome.makeNode();
    data = m;
    JsonFile::write();
  }

  void DataFile::read() {
    JsonFile::read();

    data.match([&] (tree::Map &m) {
        Globals::tapedeck.readNode(m["TapeDeck"]);
        Globals::mixer.readNode(m["Mixer"]);
        Globals::synth.readNode(m["Synth"]);
        Globals::drums.readNode(m["Drums"]);
        Globals::metronome.readNode(m["Metronome"]);
      }, [&] (auto) {
        LOGE << "Invalid Json - expected a map at root";
      });
  }

} // top1
