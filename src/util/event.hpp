#pragma once

#include "util/typedefs.hpp"

#include <vector>
#include <functional>
#include <plog/Log.h>

namespace top1 {

/*
 * An event registry and dispatcher
 */
template<typename ...Args>
class EventDispatcher {
public:

  using handler_type = std::function<void(Args...)>
    Dispatcher() {
    LOGD << "new dispatcher";
  };

  uint add(handler_type handler) {
    handlers.push_back(handler);
    return this->handlers.size() - 1;
  }

  void remove(unsigned int i){
    handlers.erase(handlers.begin() + i);
  }

  void runAll(Args... args) {
    for (auto handler: this->handlers)  {
      handler(args...);
    }
  }

  uint operator+=(const handler_type& h) { return add(h); }
private:
  std::vector<handler_type> handlers;
};

}

