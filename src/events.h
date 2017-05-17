#pragma once

#include <vector>
#include <functional>
#include <plog/Log.h>
#include "module.h"

template<typename ...Args>
class Dispatcher {
private:
  std::vector<std::function<void(Args...)>> handlers;
public:
  Dispatcher() {
    LOGD << "new dispatcher";
  };

  unsigned int add(std::function<void(Args...)> handler) {
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

  void operator()(Args... args) {
    runAll(args...);
  }
};
