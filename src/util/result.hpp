#pragma once

// Use this because of bugs in libstdc++ variant. Replace later
#include <variant.hpp>
#include <optional>
#include <utility>
#include <functional>

namespace top1 {

  /// A sum type, holding either an Ok value, or an Err
  /// Modelled closely after Rust's Result enum.
  template<typename Ok, typename Err>
  class [[nodiscard]] result {
    mpark::variant<Ok, Err> data;
  public:

    result(const Ok& ok) : data (ok) {}
    result(Ok&& ok) : data (std::move(ok)) {}

    result(const Err& err) : data (err) {}
    result(Err&& err) : data (std::move(err)) {}

    /// Returns `true` if the result is `Ok`
    bool is_ok() const {
      return mpark::holds_alternative<Ok>(data);
    }

    /// Returns `true` if the result is `Err`
    bool is_err() const {
      return mpark::holds_alternative<Err>(data);
    }

    /// Convert into a `std::optional<Ok>`, discarding the error, if any
    std::optional<Ok> ok() const {
      if (is_ok()) {
        return std::optional<Ok>(mpark::get<Ok>(data));
      } else {
        return std::optional<Ok>();
      }
    }

    /// Convert into a `std::optional<Err>`, discarding the ok value, if any
    std::optional<Err> err() const {
      if (is_err()) {
        return std::optional<Err>(mpark::get<Err>(data));
      } else {
        return std::optional<Err>();
      }
    }

    /// Map `result<O, E>` to `result<U, E>` by invoking `op` on a contained
    /// `Ok` value, leaving an `Err` value untouched
    ///
    /// Can be used to compose the result of two functions
    template<typename F>
      auto map(F&& op) const ->
      result<decltype(std::invoke(std::forward<F>(op), Ok())), Err> {
      if (is_ok()) {
        return std::invoke(op, mpark::get<Ok>(data));
      }
      return mpark::get<Err>(data);
    }

    /// Map `result<O, E>` to `result<O, F>` by invoking `op` on a contained
    /// `Err` value, leaving an `Ok` value untouched
    ///
    /// Can be used to pass through a successful result while handling the error
    template<typename F>
      auto map_err(F&& op) const ->
      result<Ok, decltype(std::invoke(std::forward<F>(op), Err()))> {
      if (is_err()) {
        return std::invoke(op, mpark::get<Err>(data));
      }
      return mpark::get<Ok>(data);
    }

    /// Returns `r` if the result is `Ok`, otherwise returns its own `Err` value
    ///
    /// Corresponds to the `and` method in rust
    template<typename Ok2>
      result<Ok2, Err> operator&&(const result<Ok2, Err>& r) const {
      if (is_ok()) {
        return r;
      } else {
        return mpark::get<Err>(data);
      }
    }

    /// Invokes `f` with `args` if the result is `Ok`,
    /// otherwise returns its own `Err` value
    template<typename F, typename... Args>
      auto and_then(F&& f, Args&&... args) const ->
      decltype(std::invoke(f, args...)) {
      if (is_ok()) {
        return std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
      } else {
        return mpark::get<Err>(data);
      }
    }

    /// Returns `r` if the result is `Err`, otherwise returns its own `Ok` value
    ///
    /// Corresponds to the `or` method in rust
    template<typename Ok2>
      result<Ok2, Err> operator||(const result<Ok2, Err>& r) const {
      if (is_err()) {
        return r;
      } else {
        return mpark::get<Ok>(data);
      }
    }

    /// Invokes `f` with `args` if the result is `Err`,
    /// otherwise returns its own `Ok` value
    template<typename F, typename... Args>
      auto or_else(F&& f, Args&&... args) const ->
      decltype(std::invoke(f, args...)) {
      if (is_err()) {
        return std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
      } else {
        return mpark::get<Ok>(data);
      }
    }

    /// Returns its own value if the result is `ok`,
    /// otherwise returns `def`
    Ok ok_or(const Ok& def) const {
      if (is_ok()) {
        return mpark::get<Ok>(data);
      } else {
        return def;
      }
    }

    /// Returns its own value if the result is `ok`,
    /// otherwise returns `def`
    Ok&& ok_or(Ok&& def) const {
      if (is_ok()) {
        return mpark::get<Ok>(data);
      } else {
        return std::move(def);
      }
    }

    /// Returns its own value if the result is `err`,
    /// otherwise returns `def`
    Err err_or(const Err& def) const {
      if (is_err()) {
        return mpark::get<Err>(data);
      } else {
        return def;
      }
    }

    /// Returns its own value if the result is `err`,
    /// otherwise returns `def`
    Err&& err_or(Err&& def) const {
      if (is_err()) {
        return mpark::get<Err>(data);
      } else {
        return std::move(def);
      }
    }

    /// Returns its own value if the result is `ok`,
    /// otherwise invokes `f` on `args`
    template<typename F, typename... Args>
      auto get_or_else(F&& f, Args&&... args) const -> std::enable_if_t<
        std::is_invocable<F, Args...>::value,
        Ok> {
      if (is_ok()) {
        return mpark::get<Ok>(data);
      } else {
        return std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
      }
    }

  };
}
