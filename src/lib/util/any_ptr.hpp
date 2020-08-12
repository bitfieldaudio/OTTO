#pragma once

#include <memory>
#include <variant>

namespace otto::util {

  /// A smart² pointer, which is either a raw pointer, a `std::unique_ptr` or a `std::shared_ptr`.
  ///
  /// Used whenever you just want a pointer to some (polymorphic) object, and don't care
  /// if its owning and how.
  template<typename T>
  struct any_ptr {
    using pointer = T*;
    using unique_ptr = std::unique_ptr<T>;
    using shared_ptr = std::shared_ptr<T>;

    any_ptr() : variant_(static_cast<pointer>(nullptr)) {}
    any_ptr(pointer p) noexcept : pointer_(p), variant_(p) {}
    any_ptr(unique_ptr&& up) noexcept : pointer_(up.get()), variant_(std::move(up)) {}
    any_ptr(shared_ptr sp) noexcept : pointer_(sp.get()), variant_(std::move(sp)) {}

    template<std::derived_from<T> U>
    any_ptr(std::unique_ptr<U>&& up) noexcept : any_ptr(static_cast<unique_ptr>(std::move(up)))
    {}
    template<std::derived_from<T> U>
    any_ptr(std::shared_ptr<U> sp) noexcept : any_ptr(static_cast<shared_ptr>(std::move(sp)))
    {}

    any_ptr(const any_ptr&) = delete;
    any_ptr(any_ptr&&) = default;

    any_ptr& operator=(const any_ptr&) = delete;
    any_ptr& operator=(any_ptr&&) = default;

    pointer get() const noexcept
    {
      return pointer_;
    }

    T& operator*() const noexcept
    {
      return *get();
    }

    pointer operator->() const noexcept
    {
      return get();
    }

    operator bool() const noexcept
    {
      return get() != nullptr;
    }

    bool operator==(const any_ptr&) const noexcept = default;
    bool operator==(const pointer p) const noexcept
    {
      return get() == p;
    }
    bool operator==(const unique_ptr& p) const noexcept
    {
      return get() == p;
    }
    bool operator==(const shared_ptr& p) const noexcept
    {
      return get() == p;
    }

    std::strong_ordering operator<=>(const any_ptr&) const noexcept = default;
    std::strong_ordering operator<=>(const pointer p) const noexcept
    {
      return get() <=> p;
    }

    std::strong_ordering operator<=>(const unique_ptr& p) const noexcept
    {
      return get() <=> p;
    }
    std::strong_ordering operator<=>(const shared_ptr& p) const noexcept
    {
      return get() <=> p;
    }

  private:
    /// Cached, so we dont have to switch on the variant type for each access
    pointer pointer_;
    std::variant<pointer, unique_ptr, shared_ptr> variant_;
  };
} // namespace otto::util
