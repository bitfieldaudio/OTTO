#include "globals.hpp"

#include <atomic>
#include <condition_variable>

#include "util/jsonfile.hpp"

namespace otto::global {

  // Public Variables /////////////////////////////////////////////////////////

  // Local Variables //////////////////////////////////////////////////////////

  namespace {
    std::atomic<ErrorCode> error_code;

    // TODO: Depends on static initialization
    util::JsonFile data_file{data_dir / "modules.json"};

  }

  // Public Functions /////////////////////////////////////////////////////////

  void init()
  {
    read_data();
    audio.init();
    tapedeck.init();
    mixer.init();
    synth.current().init();
    drums.current().init();
    ui.init();
  }

  void exit(ErrorCode ec) noexcept
  {
    error_code = ec;
  }

  bool running() noexcept
  {
    return error_code == ErrorCode::none;
  }

  ErrorCode error() noexcept
  {
    return error_code;
  }

  void read_data()
  {
    data_file.read();

    const auto& data = data_file.data();

    if (data.is_object()) {
      from_json(data["TapeDeck"], tapedeck);
      from_json(data["Mixer"], mixer);
      from_json(data["Synth"], synth);
      from_json(data["Drums"], drums);
      from_json(data["Metronome"], metronome);
    } else {
      throw util::JsonFile::exception(util::JsonFile::ErrorCode::invalid_data,
        "Expected object at root of json file {}", data_file.path());
    }
  }

  void save_data()
  {
    auto& data = data_file.data();

    data.clear();
    data["TapeDeck"]  = tapedeck;
    data["Mixer"]     = mixer;
    data["Synth"]     = synth;
    data["Drums"]     = drums;
    data["Metronome"] = metronome;
    data_file.write();
  }
}
