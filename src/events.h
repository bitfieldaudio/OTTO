#ifndef EVENTS_H
#define EVENTS_H
template<typename ...Args>
class Dispatcher {
  public:

  Dispatcher();

  void add(void (*handler)(Args...));

  void remove(unsigned int i);

  void runAll(Args... args);

  void operator()(Args...args) {
    runAll(args...);
  };
};
#endif
