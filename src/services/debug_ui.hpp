#pragma once

#include <functional>
#include <vector>

#include "util/algorithm.hpp"
#include "util/locked.hpp"
#include "util/ringbuffer.hpp"

#include "core/service.hpp"
#include "services/application.hpp"

namespace otto::services {

  struct DebugUI : core::Service {

  };

  template<std::size_t N>
  struct graph {
    void push(float val)
    {
      buffer.push(std::move(val));
      min = std::min(min, val);
      max = std::max(max, val);
    }

    void plot(std::string name)
    {
      plot(name, min, max);
    }

    void plot(std::string name, float min, float max) {}

  private:
    util::ringbuffer<float, N> buffer;
    float min = 0, max = 0;
  };

} // namespace otto::services
