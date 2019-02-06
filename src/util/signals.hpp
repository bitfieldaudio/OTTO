#pragma once

#include <functional>
#include <list>

namespace otto::util {

  /// A signal that can be emitted
  ///
  /// Handlers can be connected, and stored in Connections to be automatically disconnected
  /// on destruction
  template<typename... Args>
  struct Signal;

  template<typename... Args>
  struct Connection;

  template<typename... Args>
  struct SlotRef {
    using Connection = Connection<Args...>;
    using Signal = Signal<Args...>;
    using Function = typename Signal::Function;
    using FuncIterator = typename Signal::FuncIterator;

    Signal* signal;
    FuncIterator func_iter;

    void call_now(Args...);
  };

  template<typename... Args>
  struct Signal {
    using Connection = Connection<Args...>;
    using SlotRef = SlotRef<Args...>;
    using Function = std::function<void(Args...)>;
    using FuncIterator = typename std::list<Function>::iterator;

    SlotRef connect(const Function& func);
    SlotRef connect(Function&& func);

    template<typename T>
    SlotRef connect_member(T* inst, void (T::*func)(Args...));

    template<typename T>
    SlotRef connect_member(const T* inst, void (T::*func)(Args...) const);

    void disconnect(SlotRef);
    void disconnect_all();

    void emit(Args... a);

  private:
    std::list<Function> _slots;
  };

  template<typename... Args>
  struct Connection {
    using Signal = Signal<Args...>;
    using SlotRef = SlotRef<Args...>;
    using Function = typename Signal::Function;
    using FuncIterator = typename Signal::FuncIterator;

    Connection(SlotRef) noexcept;

    Connection(const Connection&) = delete;
    Connection(Connection&&) noexcept = default;
    Connection& operator=(const Connection&) = delete;
    Connection& operator=(Connection&&) noexcept = default;

    operator SlotRef() const noexcept;

    ~Connection() noexcept;

  private:
    SlotRef slot_ref;
  };

  // -- SlotRef IMPLEMENTATIONS -- //

  template<typename... Args>
  void SlotRef<Args...>::call_now(Args... args)
  {
    (*func_iter)(std::forward<Args>(args)...);
  }


  // -- Signal IMPLEMENTATIONS -- //

  template<typename... Args>
  auto Signal<Args...>::connect(const Function& func) -> SlotRef
  {
    return {this, _slots.insert(_slots.end(), func)};
  }

  template<typename... Args>
  auto Signal<Args...>::connect(Function&& func) -> SlotRef
  {
    return {this, _slots.insert(_slots.end(), std::move(func))};
  }

  template<typename... Args>
  template<typename T>
  auto Signal<Args...>::connect_member(T* inst, void (T::*func)(Args...)) -> SlotRef
  {
    return connect([inst, func](Args... args) { inst->*func(std::forward<Args>(args)...); });
  }

  template<typename... Args>
  template<typename T>
  auto Signal<Args...>::connect_member(const T* inst, void (T::*func)(Args...) const) -> SlotRef
  {
    return connect([inst, func](Args... args) { inst->*func(std::forward<Args>(args)...); });
  }

  template<typename... Args>
  void Signal<Args...>::disconnect(SlotRef sr)
  {
    _slots.erase(sr.func_iter);
  }

  template<typename... Args>
  void Signal<Args...>::emit(Args... args)
  {
    for (auto&& slot : _slots) {
      slot(args...);
    }
  }

  // -- Connection IMPLEMENTATIONS -- //

  template<typename... Args>
  Connection<Args...>::Connection(SlotRef sr) noexcept : slot_ref(sr)
  {}

  template<typename... Args>
  Connection<Args...>::~Connection() noexcept
  {
    slot_ref.signal->disconnect(slot_ref);
  }

  template<typename... Args>
  Connection<Args...>::operator SlotRef() const noexcept
  {
    return slot_ref;
  }

} // namespace otto::util
