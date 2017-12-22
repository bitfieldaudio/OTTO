#include "globals.hpp"

#include <atomic>
#include <condition_variable>

#include "util/jsonfile.hpp"
#include "core/ui/mainui.hpp"

namespace otto::global {

  // Public Variables /////////////////////////////////////////////////////////

  // Local Variables //////////////////////////////////////////////////////////

  namespace {
    std::atomic_bool is_running {true};
    std::atomic<ErrorCode> error_code;

    // TODO: Depends on static initialization
    util::JsonFile data_file{data_dir / "engines.json"};

  }

  // Public Functions /////////////////////////////////////////////////////////

  void init()
  {
    synth.init();
    drums.init();
    read_data();
    audio.init();
    tapedeck.on_enable();
    mixer.on_enable();
    synth.select(std::size_t(0));
    drums.select(std::size_t(0));
  }

  void exit(ErrorCode ec) noexcept
  {
    is_running = false;
    error_code = ec;
  }

  bool running() noexcept
  {
    return is_running;
  }

  ErrorCode error() noexcept
  {
    return error_code;
  }

  void read_data()
  {
    data_file.read(util::JsonFile::OpenOptions::create);

    auto& data = data_file.data();

    if (data.is_object()) {
      from_json(data["TapeDeck"], tapedeck);
      from_json(data["Mixer"], mixer);
      from_json(data["Synth"], synth);
      from_json(data["Drums"], drums);
      from_json(data["Metronome"], metronome);

      ui::from_json(data["UI"]);
    } else {
      LOGE << "Got unexpected json from " << data_file.path().c_str();
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
    data["UI"] = ui::to_json();
    data_file.write();
  }
}
