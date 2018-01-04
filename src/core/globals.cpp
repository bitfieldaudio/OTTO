#include "globals.hpp"
#include <atomic>
#include <condition_variable>
#include "core/ui/mainui.hpp"
#include "services/state.hpp"
#include "core/audio/audio_manager.hpp"

namespace otto::global {
  namespace {
    std::atomic_bool is_running {true};
    std::atomic<ErrorCode> error_code;
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
