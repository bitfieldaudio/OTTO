#pragma once

#include <functional>
#include <memory>

#include <function2/function2.hpp>

#include "lib/util/concepts.hpp"

namespace otto::util {

  /// A `std::function` that can also be constructed from a reference to
  /// an interface.
  ///
  /// Useful for constructing java-style single-function interfaces on the fly:
  ///
  /// Usage:
  /// ```cpp
  /// struct IRunnable {
  ///   virtual bool run(int i);
  /// };
  /// using RunFunc = FuncInterface<&IRunnable::run>;
  /// IRunnable& get_runnable();
  ///
  /// RunFunc f1 = get_runnable();
  /// RunFunc f2 = [] (int i) { return true; };
  /// ```
  template<auto MemFunc, template<typename... Sig> typename Func = fu2::unique_function>
  struct FuncInterface;

  template<typename Interface,
           typename Ret,
           typename... Args,
           Ret (Interface::*MemFunc)(Args...),
           template<typename... Sig>
           typename Func>
  struct FuncInterface<MemFunc, Func> {
    FuncInterface() = default;
    FuncInterface(std::nullptr_t) : func_(nullptr) {}
    FuncInterface(std::unique_ptr<Interface> i)
      : func_([i = std::move(i)](Args... a) -> Ret { return i->*MemFunc(FWD(a)...); })
    {}
    FuncInterface(Interface& i) : func_(std::bind_front(MemFunc, &i)) {}
    FuncInterface(Interface* i) : func_(std::bind_front(MemFunc, i)) {}
    // NOLINTNEXTLINE
    FuncInterface(util::callable<Ret(Args...)> auto&& f) : func_(FWD(f)) {}

    Ret operator()(Args... a)
    {
      return func_(FWD(a)...);
    }

    bool operator==(const FuncInterface&) const = default;
    bool operator==(std::nullptr_t) const
    {
      return func_ == nullptr;
    }

    operator bool() const
    {
      return func_ != nullptr;
    }

  private:
    Func<Ret(Args...)> func_;
  };

  template<typename Interface,
           typename Ret,
           typename... Args,
           Ret (Interface::*MemFunc)(Args...) const,
           template<typename... Sig>
           typename Func>
  struct FuncInterface<MemFunc, Func> {
    FuncInterface() = default;
    FuncInterface(std::nullptr_t) : func_(nullptr) {}
    FuncInterface(std::unique_ptr<const Interface> i)
      : func_([i = std::move(i)](Args... a) -> Ret { return i->*MemFunc(FWD(a)...); })
    {}
    FuncInterface(const Interface& i) : func_(std::bind_front(MemFunc, &i)) {}
    FuncInterface(Interface&& i) = delete;
    FuncInterface(const Interface* i) : func_(std::bind_front(MemFunc, i)) {}
    FuncInterface(util::callable<Ret(Args...)> auto&& f) : func_(FWD(f)) {}

    Ret operator()(Args... a) const
    {
      return func_(FWD(a)...);
    }

    bool operator==(const FuncInterface&) const = default;
    bool operator==(std::nullptr_t) const
    {
      return func_ == nullptr;
    }

    operator bool() const
    {
      return func_ != nullptr;
    }

  private:
    Func<Ret(Args...)> func_;
  };
} // namespace otto::util
