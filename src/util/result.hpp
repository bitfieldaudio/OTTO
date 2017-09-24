#pragma once

// Use this because of bugs in libstdc++ variant. Replace later
#include <variant.hpp>
#include <optional>
#include <utility>
#include <functional>
#include "util/type_traits.hpp"

namespace top1 {

  /// A sum type, holding either an Ok value, or an Err
  ///
  /// Modelled closely after Rust's Result enum.
  ///
  /// # Example
  /// ```cpp
  /// result<std::string, int> open_file(File& f) {
  ///   f.open();
  ///   if (f.error()) {
  ///     return f.errorCode();
  ///   }
  ///   return f.path();
  /// }
  /// ```
  template<typename ok_t, typename err_t>
  class [[nodiscard]] result {
  public:
    // if ok_t is void, use std::monostate, since variant cannot hold void
    using Ok = select_type_t<std::is_void_v<ok_t>, std::monostate, ok_t>;
    using Err = select_type_t<std::is_void_v<err_t>, std::monostate, err_t>;

    /// Thrown from <unwrap_ok> and <unwrap_err>.
    ///
    /// Holds an instance of the `result` it was thrown from
    struct result_except {
      result res;
    };

    template<typename = std::enable_if_t<std::is_default_constructible_v<Ok>>>
    result() : data (Ok()) {}

    result(const Ok& ok) : data (ok) {}
    result(Ok&& ok) : data (std::move(ok)) {}

    result(const Err& err) : data (err) {}
    result(Err&& err) : data (std::move(err)) {}

    /// Check if result is ok
    /// @return `true` if the result is `Ok`
    bool is_ok() const noexcept {
      return mpark::holds_alternative<Ok>(data);
    }

    /// Check if result is errored
    /// @return `true` if the result is `Err`
    bool is_err() const noexcept {
      return mpark::holds_alternative<Err>(data);
    }

    /// Convert into a `std::optional<Ok>`, discarding the error, if any
    std::optional<Ok> ok() const noexcept {
      if (is_ok()) {
        return std::optional<Ok>(mpark::get<Ok>(data));
      } else {
        return std::optional<Ok>();
      }
    }

    /// Convert into a `std::optional<Err>`, discarding the ok value, if any
    std::optional<Err> err() const noexcept {
      if (is_err()) {
        return std::optional<Err>(mpark::get<Err>(data));
      } else {
        return std::optional<Err>();
      }
    }

    /// Map <top1::result<O, E>> to `result<U, E>` by invoking `op` on a contained
    /// `Ok` value, leaving an `Err` value untouched
    ///
    /// Can be used to compose the result of two functions
    template<typename F>
      auto map(F&& op) const noexcept ->
      result<std::invoke_result_t<F, Ok>, Err> {
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
      auto map_err(F&& op) const noexcept ->
      result<Ok, std::invoke_result_t<F, Err>> {
      if (is_err()) {
        return std::invoke(op, mpark::get<Err>(data));
      }
      return mpark::get<Ok>(data);
    }

    /// Returns `r` if the result is `Ok`, otherwise returns its own `Err` value
    ///
    /// Corresponds to the `and` method in rust
    template<typename Ok2>
      result<Ok2, Err> operator&&(const result<Ok2, Err>& r) const noexcept {
      if (is_ok()) {
        return r;
      } else {
        return mpark::get<Err>(data);
      }
    }

    /// Invokes `f` with the ok value if the result is `Ok`,
    /// otherwise returns its own `Err` value
    template<typename F>
      auto and_then(F&& f) const noexcept ->
      std::enable_if_t<std::is_invocable_r_v<result<Ok, Err>, F, Ok>,
                       result<Ok, Err>> {
      if (is_ok()) {
        return std::invoke(std::forward<F>(f), mpark::get<Ok>(data));
      } else {
        return mpark::get<Err>(data);
      }
    }

    /// Returns `r` if the result is `Err`, otherwise returns its own `Ok` value
    ///
    /// Corresponds to the `or` method in rust
    template<typename Ok2>
      result<Ok2, Err> operator||(const result<Ok2, Err>& r) const noexcept {
      if (is_err()) {
        return r;
      } else {
        return mpark::get<Ok>(data);
      }
    }

    /// Invokes `f` with the error value if the result is `Err`,
    /// otherwise returns its own `Ok` value
    template<typename F>
      auto or_else(F&& f) const noexcept ->
      std::enable_if_t<std::is_invocable_r_v<result<Ok, Err>, F, Err>,
                       result<Ok, Err>> {
      if (is_err()) {
        return std::invoke(std::forward<F>(f), mpark::get<Err>(data));
      } else {
        return mpark::get<Ok>(data);
      }
    }

    /// Returns its own value if the result is `ok`,
    /// otherwise returns `def`
    Ok ok_or(const Ok& def) const noexcept {
      if (is_ok()) {
        return mpark::get<Ok>(data);
      } else {
        return def;
      }
    }

    /// Returns its own value if the result is `err`,
    /// otherwise returns `def`
    Err err_or(const Err& def) const noexcept {
      if (is_err()) {
        return mpark::get<Err>(data);
      } else {
        return def;
      }
    }

    /// Returns its own value if the result is `ok`,
    /// otherwise invokes `f` with the error value
    template<typename F>
      auto ok_or_else(F&& f) const noexcept ->
      std::enable_if_t<std::is_invocable_r_v<Ok, F, Err>, Ok> {
      if (is_ok()) {
        return mpark::get<Ok>(data);
      } else {
        return std::invoke(std::forward<F>(f), mpark::get<Err>(data));
      }
    }

    /// Returns its own value if the result is `err`,
    /// otherwise invokes `f` with the ok value
    template<typename F>
      auto err_or_else(F&& f) const noexcept ->
      std::enable_if_t<std::is_invocable_r_v<Err, F, Ok>, Err> {
      if (is_err()) {
        return mpark::get<Err>(data);
      } else {
        return std::invoke(std::forward<F>(f), mpark::get<Ok>(data));
      }
    }

    /// If ok, call `f(ok)`
    template<typename F>
      auto if_ok(F&& f) const noexcept ->
      std::enable_if_t<std::is_invocable_v<F, Ok>, void> {
      if (is_ok()) {
        std::invoke(std::forward<F>(f), mpark::get<Ok>(data));
      }
    }

    /// If err, call `f(err)`
    template<typename F>
      auto if_err(F&& f) const noexcept ->
      std::enable_if_t<std::is_invocable_v<F, Err>, void> {
      if (is_err()) {
        return std::invoke(std::forward<F>(f), mpark::get<Err>(data));
      }
    }

    /// If ok, call `fo(ok)`, otherwise call `fe(err)`
    template<typename FO, typename FE,
             typename Ret = std::common_type_t<std::invoke_result_t<FO, Ok>,
                                               std::invoke_result_t<FE, Err>>>
      Ret wrap(FO&& fo, FE&& fe) noexcept {
      if (is_ok()) {
        return std::invoke(std::forward<FO>(fo), mpark::get<Ok>(data));
      } else {
        return std::invoke(std::forward<FE>(fe), mpark::get<Err>(data));
      }
    }

    /// If ok, call `visitor(ok)`, otherwise call `visitor(err)`
    template<typename V,
             typename Ret = std::common_type_t<std::invoke_result_t<V, Ok>,
                                               std::invoke_result_t<V, Err>>>
      Ret visit(V&& visitor) noexcept {
      if (is_ok()) {
        return std::invoke(std::forward<V>(visitor), mpark::get<Ok>(data));
      } else {
        return std::invoke(std::forward<V>(visitor), mpark::get<Err>(data));
      }
    }

    /// Return ok, or throw a `result_except<Err>` holding the result.
    ///
    /// Should only be called when <is_err> or <is_ok> has been used to check.
    Ok unwrap_ok() {
      if (is_ok()) {
        return mpark::get<Ok>(data);
      } else {
        throw result_except{mpark::get<Err>(data)};
      }
    }

    /// Return err, or throw a `result_except<Err>` holding the result.
    ///
    /// Should only be called when <is_err> or <is_ok> has been used to check.
    Err unwrap_err() {
      if (is_err()) {
        return mpark::get<Err>(data);
      } else {
        throw result_except{mpark::get<Ok>(data)};
      }
    }

    private:
      mpark::variant<Ok, Err> data;
  };
}
