#pragma once

#include <vector>
#include <functional>

namespace otto::util {

  /// An event registry and dispatcher
  template<typename... Args>
  struct Event {
    using handler_type = std::function<void(Args...)>;

    Event() = default;

    int subscribe(handler_type handler)
    {
      handlers.emplace_back(std::move(handler));
      return handlers.size() - 1;
    }

    void fire(Args... args)
    {
      for (auto& handler : handlers) {
        handler(args...);
      }
    }

  private:
    std::vector<handler_type> handlers;
  };
} // namespace otto::util
