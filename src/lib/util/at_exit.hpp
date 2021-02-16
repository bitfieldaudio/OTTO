#pragma once

#include <function2/function2.hpp>

#include "lib/util/concepts.hpp"

namespace otto::util {

  /// Run a function on destruction
  struct [[nodiscard]] at_exit {
    at_exit(util::callable<void()> auto&& f) // NOLINT
      : destructor(FWD(f))
    {}
    // at_exit(fu2::unique_function<void()>&& d) : destructor(std::move(d)) {}
    ~at_exit()
    {
      if (destructor) destructor();
    }

    at_exit(const at_exit&) = delete;
    at_exit& operator=(const at_exit&) = delete;

    at_exit(at_exit&&) = default;
    at_exit& operator=(at_exit&&) = default;

    void run_now()
    {
      destructor();
      destructor = nullptr;
    }

  private:
    fu2::unique_function<void()> destructor = nullptr;
  };
} // namespace otto::util
