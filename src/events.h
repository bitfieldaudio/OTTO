#pragma once

#include <vector>
#include "module.h"

template<typename...Args>
  class EventHandler {
public:
  Module *owner;
  void (*handler)(Args..., Module*);

  EventHandler(Module *owner, void (*handler)(Args..., Module*)) {
    this->owner = owner;
    this->handler = handler;
  }

  void operator()(Args... args) {
    owner->*handler(args..., owner);
  }
};

template<typename ...Args>
  class Dispatcher {
private:
  std::vector<EventHandler<Args...>> handlers;
public:
  Dispatcher() {};

  unsigned int add(Module *owner, void (*handler)(Args..., Module*)) {
    handlers.push_back(EventHandler<Args...>(owner, handler));
    return handlers.size() - 1;
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
