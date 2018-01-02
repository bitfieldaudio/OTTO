#include "globals.hpp"
#include <atomic>
#include <condition_variable>
#include "core/ui/mainui.hpp"
#include "services/state.hpp"
#include "core/audio/audio_manager.hpp"

namespace otto::global {

  // Public Variables /////////////////////////////////////////////////////////

  // Local Variables //////////////////////////////////////////////////////////

  namespace {
    std::atomic_bool is_running {true};
    std::atomic<ErrorCode> error_code;
  }

  // Public Functions /////////////////////////////////////////////////////////

  void init()
  {
    synth.init();
    drums.init();

    services::state::load();

    audio::AudioManager::get().init();
  
    tapedeck.on_enable();
    metronome.on_enable();
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
}
