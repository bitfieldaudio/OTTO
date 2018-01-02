#pragma once

#include <functional>
#include <vector>

namespace otto::services {
  struct EventManager {
    /*
     * An event registry and dispatcher
     */
    template<typename... Args>
    struct Event {
      using handler_type = std::function<void(Args...)>;

      Event() = default;

      int add(handler_type handler)
      {
        handlers.push_back(handler);
        return handlers.size() - 1;
      }

      void remove(unsigned int i)
      {
        handlers.erase(handlers.begin() + i);
      }

      void fire(Args... args)
      {
        for (auto handler : handlers) {
          handler(args...);
        }
      }

    private:
      std::vector<handler_type> handlers;
    };

    static EventManager& get();
    Event<> pre_init;
    Event<unsigned> buffersize_change;
    Event<unsigned> samplerate_change;

  private:
    EventManager()  = default;
    ~EventManager() = default;
  };
} // namespace otto::services
