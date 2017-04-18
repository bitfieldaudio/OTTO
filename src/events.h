#pragma once

#include <vector>
#include <plog/Log.h>
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
    handler(args..., owner);
  }
};

template<typename ...Args>
class Dispatcher {
private:
  std::vector<EventHandler<Args...>> handlers;
public:
  Dispatcher() {
    LOGD << "new dispatcher";
  };

  unsigned int add(Module *owner, void (*handler)(Args..., Module*)) {
    LOGD << "Adding an event";
    EventHandler< Args...> *h = new EventHandler< Args...>(owner, handler);
    this->handlers.push_back(*h);
    LOGD << &handlers.front();
    return this->handlers.size() - 1;
  }

  void remove(unsigned int i){
    handlers.erase(handlers.begin() + i);
  }

  void runAll(Args... args) {
    for (auto handler: this->handlers)  {
      //LOGD << "Running event handlers";
      handler(args...);
    }
  }

  void operator()(Args... args) {
    runAll(args...);
  }
};
