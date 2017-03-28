#include <string>
#include <vector>
#include <cstdlib>

template<typename ...Args>
class Dispatcher {
  private:
  std::vector<void (*)(Args...)> handlers;
  public:

  void add(void (*handler)(Args...)) {
    handlers.push_back(handler);
  }

  void remove(uint i) {
    handlers.erase(handlers.begin() + i);
  }

  void runAll(Args... args) {
    for (auto handler: handlers) {
      handler(args...);
    }
  }
};
