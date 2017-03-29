#ifndef EVENTS_H
#define EVENTS_H

#include <vector>

template<typename ...Args>
  class Dispatcher {
private:
  std::vector<void (*)(Args...)> handlers;
public:
  Dispatcher() {};

  void add(void (*handler)(Args...)) {
    handlers.push_back(handler);
    return handlers.size - 1;
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
#endif
