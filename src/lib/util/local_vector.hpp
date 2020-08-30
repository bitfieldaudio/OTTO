#pragma once

#include <initializer_list>
#include <new>
#include <span>
#include <tl/expected.hpp>

#include "lib/util/exception.hpp"

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

    constexpr local_vector(std::initializer_list<value_type> il)
    {
      for (const T& v : il) {
        push_back(v);
      }
    }

    constexpr ~local_vector() noexcept
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

    constexpr auto rbegin() noexcept
    {
      return std::make_reverse_iterator(end());
    }

    constexpr auto rbegin() const noexcept
    {
      return std::make_reverse_iterator(end());
    }

    constexpr auto rend() noexcept
    {
      return std::make_reverse_iterator(begin());
    }

    constexpr auto rend() const noexcept
    {
      return std::make_reverse_iterator(begin());
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
    constexpr const value_type& operator[](std::size_t idx) const noexcept
    {
      return data()[idx];
    }
    constexpr value_type* data() noexcept
    {
      // Launder is a pointer optimization barrier. It's necessary to make the
      // reinterpret_cast legal in this case
      return std::launder(reinterpret_cast<value_type*>(&_data));
    }

    constexpr const value_type* data() const noexcept
    {
      // Launder is a pointer optimization barrier. It's necessary to make the
      // reinterpret_cast legal in this case
      return std::launder(reinterpret_cast<const value_type*>(&_data));
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

    constexpr iterator erase(iterator first, iterator last) noexcept
    {
      if (first == last) return first;
      // Save return value
      auto res = first;
      // Move next values down
      while (last != end()) {
        *first = std::move(*last);
        first++;
        last++;
      }
      // Delete remaining entries
      while (first != last) {
        pop_back();
        last--;
      }
      return res;
    }

    constexpr iterator erase(iterator it) noexcept
    {
      return erase(it, std::min(it + 1, end()));
    }

  private:
    /// Uninitialized storage. Always access through data();
    std::aligned_storage_t<capacity() * sizeof(value_type)> _data;
    std::size_t _size = 0;
  };

  template<typename T, std::size_t Capacity>
  struct local_set : private local_vector<T, Capacity> {
    using super = local_vector<T, Capacity>;
    using value_type = typename super::value_type;
    using iterator = typename super::iterator;
    using const_iterator = typename super::const_iterator;
    using error = typename super::error;
    using exception = typename super::exception;

    constexpr local_set() : super() {}

    constexpr local_set(std::initializer_list<value_type> il)
    {
      for (const T& v : il) {
        insert(v);
      }
    }

    // Queries

    static constexpr std::size_t capacity() noexcept
    {
      return super::capacity();
    }

    constexpr std::size_t size() const noexcept
    {
      return super::size();
    }

    constexpr bool empty() const noexcept
    {
      return super::empty();
    }

    constexpr bool full() const noexcept
    {
      return super::full();
    }

    // Iterators

    constexpr auto begin() noexcept
    {
      return super::begin();
    }

    constexpr auto begin() const noexcept
    {
      return super::begin();
    }

    constexpr auto end() noexcept
    {
      return super::end();
    }

    constexpr auto end() const noexcept
    {
      return super::end();
    }

    constexpr auto rbegin() noexcept
    {
      return super::rbegin();
    }

    constexpr auto rbegin() const noexcept
    {
      return super::rbegin();
    }

    constexpr auto rend() noexcept
    {
      return super::rend();
    }

    constexpr auto rend() const noexcept
    {
      return super::rend();
    }

    // Accessors

    constexpr value_type& front() noexcept
    {
      return super::front();
    }

    constexpr const value_type& front() const noexcept
    {
      return super::front();
    }

    constexpr value_type& back() noexcept
    {
      return super::back();
    }

    constexpr const value_type& back() const noexcept
    {
      return super::back();
    }

    constexpr value_type& operator[](std::size_t idx) noexcept
    {
      return super::operator[](idx);
    }
    constexpr const value_type& operator[](std::size_t idx) const noexcept
    {
      return super::operator[](idx);
    }
    constexpr value_type* data() noexcept
    {
      return super::data();
    }

    constexpr const value_type* data() const noexcept
    {
      return super::data();
    }

    // Modifiers

    constexpr tl::expected<value_type*, error> insert(const value_type& e) noexcept
    {
      auto pos = std::upper_bound(begin(), end(), e);
      auto prev = pos - 1;
      if (prev < begin() || *prev != e) return super::insert_before(pos, e);
      return prev;
    }

    constexpr tl::expected<value_type*, error> insert(value_type&& e) noexcept
    {
      auto pos = std::upper_bound(begin(), end(), e);
      auto prev = pos - 1;
      if (prev < begin() || *prev != e) return super::insert_before(pos, std::move(e));
      return prev;
    }

    constexpr tl::expected<void, error> pop_back() noexcept
    {
      return super::pop_back();
    }

    constexpr void clear() noexcept
    {
      super::clear();
    }

    constexpr iterator erase(iterator first, iterator last) noexcept
    {
      return super::erase(first, last);
    }

    constexpr iterator erase(iterator it) noexcept
    {
      return super::erase(it);
    }

    constexpr iterator erase(const value_type& val) noexcept
    {
      return erase(std::find(begin(), end(), val));
    }
  };
} // namespace otto::util
