#pragma once

#include <bit>
#include <initializer_list>
#include <memory>
#include <span>

#include <tl/expected.hpp>

#include "lib/util/concepts.hpp"
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

    constexpr local_vector() : _data() {}

    constexpr local_vector(util::range_of<value_type> auto&& range) // NOLINT
      requires(!util::decays_to<local_vector, decltype(range)>)
    {
      for (const T& v : FWD(range)) {
        push_back(v);
      }
    }

    constexpr ~local_vector() noexcept
    {
      // Destroy elements
      clear();
    }

    constexpr local_vector(const local_vector&) = default;
    constexpr local_vector& operator=(const local_vector&) = default;
    constexpr local_vector(local_vector&&) noexcept = default;
    constexpr local_vector& operator=(local_vector&&) noexcept = default;

    // Queries

    static constexpr std::size_t capacity() noexcept
    {
      return Capacity;
    }

    [[nodiscard]] constexpr std::size_t size() const noexcept
    {
      return _size;
    }

    [[nodiscard]] constexpr bool empty() const noexcept
    {
      return size() == 0;
    }

    [[nodiscard]] constexpr bool full() const noexcept
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
      // NOLINTNEXTLINE
      return std::launder(reinterpret_cast<value_type*>(&_data));
    }

    constexpr const value_type* data() const noexcept
    {
      // Launder is a pointer optimization barrier. It's necessary to make the
      // reinterpret_cast legal in this case
      // NOLINTNEXTLINE
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

    template<typename... Args>
    requires(std::is_constructible_v<value_type, Args...>) //
      constexpr tl::expected<value_type*, error> emplace_back(Args&&... args) noexcept
    {
      if (full()) return tl::unexpected(error::full);
      std::construct_at<T>(data() + _size, std::forward<Args>(args)...);
      _size++;
      return &back();
    }

    /// Inserts value before pos
    constexpr tl::expected<iterator, error> insert_before(iterator iter, const value_type& value) noexcept
    {
      return push_back(value).map([&](auto&&) {
        // Move the element back until ts placed at the correct location
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
      _size--;
      data()[_size].~T();
      return {};
    }

    constexpr tl::expected<void, error> pop_front() noexcept
    {
      if (empty()) return tl::unexpected(error::empty);
      erase(begin());
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

    [[nodiscard]] constexpr std::size_t size() const noexcept
    {
      return super::size();
    }

    [[nodiscard]] constexpr bool empty() const noexcept
    {
      return super::empty();
    }

    [[nodiscard]] constexpr bool full() const noexcept
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

namespace std { // NOLINT
  template<typename T, std::size_t Capacity, typename U>
  constexpr std::size_t erase(otto::util::local_vector<T, Capacity>& c, const U& value)
  {
    auto it = std::remove(c.begin(), c.end(), value);
    auto r = std::distance(it, c.end());
    c.erase(it, c.end());
    return r;
  }

  template<typename T, std::size_t Capacity, typename Pred>
  constexpr std::size_t erase_if(otto::util::local_vector<T, Capacity>& c, Pred pred)
  {
    auto it = std::remove_if(c.begin(), c.end(), pred);
    auto r = std::distance(it, c.end());
    c.erase(it, c.end());
    return r;
  }
} // namespace std
