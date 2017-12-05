#include "core/datafile.hpp"
#include "core/globals.hpp"

namespace otto {

  void DataFile::write(OpenOptions options)
  {
    data().clear();
    data()["TapeDeck"]  = Globals::tapedeck;
    data()["Mixer"]     = Globals::mixer;
    data()["Synth"]     = Globals::synth;
    data()["Drums"]     = Globals::drums;
    data()["Metronome"] = Globals::metronome;

    JsonFile::write(options);
  }

  void DataFile::read(OpenOptions options)
  {
    JsonFile::read(options);

    if (data().is_object()) {
      from_json(data()["TapeDeck"],  Globals::tapedeck);
      from_json(data()["Mixer"],     Globals::mixer);
      from_json(data()["Synth"],     Globals::synth);
      from_json(data()["Drums"],     Globals::drums);
      from_json(data()["Metronome"], Globals::metronome);
    } else {
      throw exception(ErrorCode::invalid_data, "Expected object at json root");
    }
  }

}  // namespace otto
