#pragma once

#include <initializer_list>
#include <new>
#include <tl/expected.hpp>

#include "util/exception.hpp"

namespace otto::util {

  template<typename T, std::size_t Capacity>
  struct local_vector {
    using value_type = T;
    using iterator = value_type*;
    using const_iterator = const value_type*;

    /// Error codes
    enum struct error {
      /// The vector is at capacity
      full,
      /// The vecctor is empty
      empty
    };

    using exception = util::as_exception<error>;

    constexpr local_vector() : _data(), _size(0) {}

    constexpr local_vector(std::initializer_list<value_type> il) : _size(il.size())
    {
      for (T& v : il) {
        push_back(v);
      }
    }

    // TODO: C++20, can be constexpr
    ~local_vector() noexcept
    {
      // Destroy elements
      clear();
    }

    // Queries

    static constexpr std::size_t capacity() noexcept
    {
      return Capacity;
    }

    constexpr std::size_t size() const noexcept
    {
      return _size;
    }

    constexpr bool empty() const noexcept
    {
      return size() == 0;
    }

    constexpr bool full() const noexcept
    {
      return size() == capacity();
    }

    // Iterators

    constexpr auto begin() noexcept
    {
      return data();
    }

    constexpr auto begin() const noexcept
    {
      return data();
    }

    constexpr auto end() noexcept
    {
      return data() + _size;
    }

    constexpr auto end() const noexcept
    {
      return data() + _size;
    }

    // Accessors

    constexpr value_type& front() noexcept
    {
      return *begin();
    }

    constexpr const value_type& front() const noexcept
    {
      return *begin();
    }

    constexpr value_type& back() noexcept
    {
      return data()[_size - 1];
    }

    constexpr const value_type& back() const noexcept
    {
      return data()[_size - 1];
    }

    constexpr value_type& operator[](std::size_t idx) noexcept
    {
      return data()[idx];
    }
    constexpr value_type* data() noexcept
    {
      // Launder is a pointer optimization barrier. It's necessary to make the
      // reinterpret_cast legal in this case
#if __cpp_lib_launder >= 201606
      // have std::launder for sure
      return std::launder(reinterpret_cast<value_type*>(&_data));
#else
      // not sure, could've std::launder either way
      return reinterpret_cast<value_type*>(&_data);
#endif
    }

    constexpr const value_type* data() const noexcept
    {
      // Launder is a pointer optimization barrier. It's necessary to make the
      // reinterpret_cast legal in this case
#if __cpp_lib_launder >= 201606
      // have std::launder for sure
      return std::launder(reinterpret_cast<const value_type*>(&_data));
#else
      // not sure, could've std::launder either way
      return reinterpret_cast<const value_type*>(&_data);
#endif
    }

    // Modifiers

    constexpr tl::expected<value_type*, error> push_back(const value_type& e) noexcept
    {
      return emplace_back(e);
    }

    constexpr tl::expected<value_type*, error> push_back(value_type&& e) noexcept
    {
      return emplace_back(std::move(e));
    }

    template<typename... Args, typename Enable = std::enable_if_t<std::is_constructible_v<value_type, Args...>>>
    constexpr tl::expected<value_type*, error> emplace_back(Args&&... args) noexcept
    {
      if (full()) return tl::unexpected(error::full);
      new (data() + _size) T(std::forward<Args>(args)...);
      _size++;
      return &back();
    }

    /// Inserts value before pos
    constexpr tl::expected<iterator, error> insert_before(iterator iter, const value_type& value) noexcept
    {
      return push_back(value).map([&](auto&&) {
        // Move the element back until its placed at the correct location
        for (auto i = end() - 1; i != iter; --i) {
          std::swap(*(i), *(i - 1));
        }
        return iter;
      });
    }

    /// Inserts value before iter. NOTE: use insert_before for noexcept version
    ///
    /// Mainly provided for use with STL algorithms like transform.
    ///
    /// @throws tl::bad_expected_access<error> if there was an error when inserting
    constexpr iterator insert(iterator iter, const value_type& value)
    {
      return insert_before(iter, value).value();
    }

    constexpr tl::expected<void, error> pop_back() noexcept
    {
      if (empty()) return tl::unexpected(error::empty);
      data()[_size].~T();
      _size--;
      return {};
    }

    constexpr void clear() noexcept
    {
      while (!empty()) {
        pop_back();
      }
    }

  private:
    /// Uninitialized storage. Always access through data();
    std::aligned_storage_t<capacity() * sizeof(value_type)> _data;
    std::size_t _size = 0;
  };
} // namespace otto::util
