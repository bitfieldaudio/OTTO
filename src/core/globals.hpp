#pragma once

#include "filesystem.hpp"
#include "util/exception.hpp"

namespace otto {
  namespace global {
    enum struct ErrorCode {
      none = 0,
      ui_closed,
      user_exit,
      audio_error,
      graphics_error,
      input_error
    };

    using exception = util::as_exception<ErrorCode>;

    inline const filesystem::path data_dir {"data"};

    void exit(ErrorCode ec) noexcept;

    bool running() noexcept;

    ErrorCode error() noexcept;
  }

}
