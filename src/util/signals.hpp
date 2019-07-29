#pragma once

#include <forward_list>
#include <functional>

namespace otto::util {

  /// A signal that can be emitted
  ///
  /// Handlers can be connected, and stored in Connections to be automatically disconnected
  /// on destruction
  template<typename... Args>
  struct Signal;

  /// Type-erased connection
  struct Slot {
    Slot() noexcept = default;
    Slot(Slot*& ptr, std::function<void()> d) noexcept : _ptr(&ptr), _disconnect(std::move(d))
    {
      if (_ptr) *_ptr = this;
    }

    Slot(const Slot&) = delete;
    Slot& operator=(const Slot&) = delete;

    Slot(Slot&& rhs)
    {
      *this = std::move(rhs);
    }
    Slot& operator=(Slot&& rhs)
    {
      disconnect();
      _ptr = rhs._ptr;
      _disconnect = rhs._disconnect;
      if (_ptr) *_ptr = this;
      rhs.clear();
      return *this;
    }

    ~Slot() noexcept
    {
      disconnect();
    }

    void disconnect() noexcept
    {
      if (_disconnect != nullptr) _disconnect();
      _disconnect = nullptr;
      if (_ptr) *_ptr = nullptr;
    }

    /// Called by Signal on destruction
    void clear() noexcept
    {
      _ptr = nullptr;
      _disconnect = nullptr;
    }

  private:
    /// Pointer to the slot field in the Connection object in the list
    Slot** _ptr = nullptr;
    std::function<void()> _disconnect = nullptr;
  };

  template<typename... Args>
  struct SlotRef {
    using Signal = otto::util::Signal<Args...>;
    using Function = typename Signal::Function;
    using ConIterator = typename Signal::ConIterator;

    Signal* signal;
    ConIterator func_iter;

    operator Slot()
    {
      return {func_iter->slot, [cpy = *this] { cpy.signal->disconnect(cpy); }};
    }

    SlotRef& call_now(Args...);
  };

  template<typename... Args>
  struct Signal {
    using SlotRef = otto::util::SlotRef<Args...>;
    using Function = std::function<void(Args...)>;
    struct Connection {
      Connection(const Function& f) : func(f) {}
      Connection(Function&& f) : func(std::move(f)) {}
      ~Connection() noexcept
      {
        if (slot) slot->clear();
      }
      Function func;
      Slot* slot = nullptr;
    };
    using ConIterator = typename std::forward_list<Connection>::iterator;

    Signal() = default;
    ~Signal() noexcept;
    Signal(const Signal&) = default;
    Signal(Signal&&) = default;
    Signal& operator=(const Signal&) = default;
    Signal& operator=(Signal&&) = default;

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
    std::forward_list<Connection> _slots;
  };

  // -- SlotRef IMPLEMENTATIONS -- //

  template<typename... Args>
  SlotRef<Args...>& SlotRef<Args...>::call_now(Args... args)
  {
    func_iter->func(std::forward<Args>(args)...);
    return *this;
  }


  // -- Signal IMPLEMENTATIONS -- //


  template<typename... Args>
  Signal<Args...>::~Signal() noexcept
  {
    disconnect_all();
  }

  template<typename... Args>
  auto Signal<Args...>::connect(const Function& func) -> SlotRef
  {
    _slots.emplace_front(func);
    return {this, _slots.begin()};
  }

  template<typename... Args>
  auto Signal<Args...>::connect(Function&& func) -> SlotRef
  {
    _slots.emplace_front(std::move(func));
    return {this, _slots.begin()};
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
    auto prev = _slots.before_begin();
    for (auto i = _slots.begin(); i != _slots.end(); i++) {
      if (i == sr.func_iter) {
        _slots.erase_after(prev);
        break;
      }
      prev = i;
    }
  }

  template<typename... Args>
  void Signal<Args...>::disconnect_all()
  {
    _slots.clear();
  }

  template<typename... Args>
  void Signal<Args...>::emit(Args... args)
  {
    for (auto&& slot : _slots) {
      slot.func(args...);
    }
  }

} // namespace otto::util
