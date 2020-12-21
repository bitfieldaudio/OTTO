#pragma once

#include <memory>
#include <variant>

#include <function2/function2.hpp>

#include "concepts.hpp"

namespace otto::util {

  /// An even smarter smart pointer, which is either a raw pointer or a `std::unique_ptr`.
  ///
  /// Used whenever you just want a pointer to some (polymorphic) object, and don't care
  /// if its owning or not.
  ///
  /// Compared to a shared ptr, this is easier to work with, and still means only one place manages
  /// the pointer, while allowing the user of a class to decide where the object comes from, and
  /// who manages it.
  ///
  /// To avoid issues when copying, this type is also move only. If you want a weak smart_ptr to an
  /// owning smart_ptr, just construct it from `an_owning_ptr.get()`
  ///
  /// This implementation could be optimized by reimplementing the basics of unique_ptr, to
  /// remove the need for using `variant`. If we then stored the info on whether this instance owns or not
  /// in the lower unused bits of the pointer, `sizeof(smart_ptr)` could be the same as a raw pointer
  template<typename T>
  struct smart_ptr {
    using pointer = T*;
    using unique_ptr = std::unique_ptr<T>;
    // using shared_ptr = std::shared_ptr<T>;
    using factory = fu2::unique_function<smart_ptr<T>()>;

    smart_ptr() : variant_(static_cast<pointer>(nullptr)) {}
    smart_ptr(pointer p) noexcept : pointer_(p), variant_(p) {}
    smart_ptr(unique_ptr&& up) noexcept : pointer_(up.get()), variant_(std::move(up)) {}
    // smart_ptr(shared_ptr sp) noexcept : pointer_(sp.get()), variant_(std::move(sp)) {}

    ~smart_ptr() noexcept = default;

    template<std::derived_from<T> U>
    smart_ptr(std::unique_ptr<U>&& up) noexcept : smart_ptr(static_cast<unique_ptr>(std::move(up)))
    {}
    // template<std::derived_from<T> U>
    // smart_ptr(std::shared_ptr<U> sp) noexcept : smart_ptr(static_cast<shared_ptr>(std::move(sp)))
    // {}

    smart_ptr(const smart_ptr&) = delete;
    smart_ptr& operator=(const smart_ptr&) = delete;

    smart_ptr(smart_ptr&&) noexcept = default;
    smart_ptr& operator=(smart_ptr&&) noexcept = default;

    template<util::base_of<T> U>
    operator smart_ptr<U>() && noexcept
    {
      return std::visit(
        fu2::overload([](pointer ptr) { return smart_ptr<U>(static_cast<U*>(ptr)); },
                      //[](shared_ptr&& ptr) { return smart_ptr<U>(static_cast<std::shared_ptr<U>>(std::move(ptr))); },
                      [](unique_ptr&& ptr) { return smart_ptr<U>(static_cast<std::unique_ptr<U>>(std::move(ptr))); }),
        std::move(variant_));
    }

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

    bool operator==(const smart_ptr&) const noexcept = default;
    bool operator==(pointer p) const noexcept
    {
      return get() == p;
    }
    bool operator==(const unique_ptr& p) const noexcept
    {
      return get() == p;
    }
    // bool operator==(const shared_ptr& p) const noexcept
    //{
    //  return get() == p;
    //}

    std::strong_ordering operator<=>(const smart_ptr&) const noexcept = default;
    std::strong_ordering operator<=>(pointer p) const noexcept
    {
      return get() <=> p;
    }

    std::strong_ordering operator<=>(const unique_ptr& p) const noexcept
    {
      return get() <=> p;
    }
    // std::strong_ordering operator<=>(const shared_ptr& p) const noexcept
    //{
    //  return get() <=> p;
    //}

  private:
    /// Cached, so we dont have to switch on the variant type for each access
    pointer pointer_;
    std::variant<pointer, unique_ptr> variant_;
  };
} // namespace otto::util
