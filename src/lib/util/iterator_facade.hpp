#pragma once

#include <memory>
#include <type_traits>

namespace otto::util {
  template<typename Reference>
  struct arrow_proxy {
    Reference r;
    Reference* operator->()
    {
      return &r;
    }
  };

  namespace detail {

    // Base case
    template<typename>
    struct infer_difference_type {
      using type = std::ptrdiff_t;
    };

    template<typename T>
    concept impls_distance_to = requires(const T it)
    {
      it.distance_to(it);
    };

    // Case when `T` provides a `distance_to`
    template<impls_distance_to T>
    struct infer_difference_type<T> {
      static const T& it;
      using type = decltype(it.distance_to(it));
    };

    template<typename T>
    using infer_difference_type_t = typename infer_difference_type<T>::type;

    template<typename T>
    struct infer_value_type {
      static const T& _it;
      using type = std::remove_cvref_t<decltype(*_it)>;
    };

    template<typename T>
    requires requires
    {
      typename T::value_type;
    }
    struct infer_value_type<T> {
      using type = typename T::value_type;
    };

    template<typename T>
    using infer_value_type_t = typename infer_value_type<T>::type;

    // Check for .decrement
    template<typename T>
    concept impls_decrement = requires(T t)
    {
      t.decrement();
    };

    // Check for .advance
    template<typename T>
    concept impls_advance = requires(T it, const infer_difference_type_t<T> offset)
    {
      it.advance(offset);
    };

    // Check for .equal_to
    template<typename T>
    concept impls_equal_to = requires(const T it)
    {
      {
        it.equal_to(it)
      }
      ->std::same_as<bool>;
    };

    // We can meet "random access" if it provides
    // both .advance() and .distance_to()
    template<typename T>
    concept meets_random_access = impls_advance<T>&& impls_distance_to<T>;

    // We meet `bidirectional` if we are random_access, OR we have .decrement()
    template<typename T>
    concept meets_bidirectional = meets_random_access<T> || impls_decrement<T>;

    // Detect if the iterator declares itself to be a single-pass iterator.
    // (More on this later.)
    template<typename T>
    concept decls_single_pass = bool(T::single_pass_iterator);

    template<typename Arg, typename Iter>
    concept difference_type_arg = std::convertible_to<Arg, infer_difference_type_t<Iter>>;

    template<typename Iter, typename T>
    concept iter_sentinel_arg = std::same_as<T, typename T::sentinel_type>;

    template<typename T>
    concept impls_distance_to_sentinel = requires(const T it, typename T::sentinel_type s)
    {
      it.distance_to(s);
    };
  } // namespace detail


  /// Base class to help implement iterators
  ///
  /// Adapted from: https://vector-of-bool.github.io/2020/06/13/cpp20-iter-facade.html
  ///
  /// forward_iterator requires:
  ///  - `auto& derefence()`
  ///  - `void increment()`
  ///  - `bool equal_to(const Iter&)`
  ///
  /// input_iterator:
  ///  - `static constexpr bool single_pass_iterator = true`
  ///
  /// bidirectional_iterator:
  ///  - `void decrement()`
  ///
  /// random_access_iterator:
  ///  - `void advance(difference_type d)`
  ///  - `difference_type distance_to(const Iter&)`
  ///
  /// `distance_to` and `advance` define default `equal_to` and `increment`/`decrement` respectively.
  ///
  /// Sentinels can be used by adding
  ///  - `struct sentinel_type {};`
  ///  - `bool at_end()`
  /// And optionally:
  ///  - `auto distance_to(sentinel_type)`
  template<typename Derived>
  struct iterator_facade {
    using self_type = Derived;

    constexpr decltype(auto) operator*() const
    {
      return _self().dereference();
    }

    constexpr auto operator->() const
    {
      decltype(auto) ref = *_self();
      if constexpr (std::is_reference_v<decltype(ref)>) {
        return std::addressof(ref);
      } else {
        // Ref is not a reference, returning the address would return the address of a temporary
        return arrow_proxy<decltype(ref)>{std::move(ref)};
      }
    }

    constexpr friend bool operator==(const self_type& lhs, const self_type& rhs)
    {
      return lhs.equal_to(rhs);
    }

    constexpr void increment() requires detail::impls_advance<self_type>
    {
      *this += 1;
    }

    constexpr void decrement() requires detail::impls_advance<self_type>
    {
      *this -= 1;
    }

    constexpr bool equal_to(const self_type& rhs) requires detail::impls_distance_to<self_type>
    {
      return _self().distance_to(rhs) == 0;
    }

    constexpr self_type& operator++()
    {
      _self().increment();
      return _self();
    }

    constexpr auto operator++(int)
    {
      if constexpr (detail::decls_single_pass<self_type>) {
        ++*this;
      } else {
        auto copy = _self();
        ++*this;
        return copy;
      }
    }

    constexpr self_type& operator--() requires detail::impls_decrement<self_type>
    {
      _self().decrement();
      return _self();
    }

    constexpr self_type operator--(int) requires detail::impls_decrement<self_type>
    {
      if constexpr (detail::decls_single_pass<self_type>) {
        --*this;
      } else {
        auto copy = _self();
        --*this;
        return copy;
      }
    }

    friend constexpr self_type& operator+=(
      self_type& self,
      detail::difference_type_arg<self_type> auto offset) requires detail::impls_advance<self_type>
    {
      self.advance(offset);
      return self;
    }

    friend constexpr self_type operator+(
      self_type left,
      detail::difference_type_arg<self_type> auto off) requires detail::impls_advance<self_type>
    {
      return left += off;
    }

    friend constexpr self_type operator+(detail::difference_type_arg<self_type> auto off,
                                         self_type right) requires detail::impls_advance<self_type>
    {
      return right += off;
    }

    friend constexpr self_type operator-(
      self_type left,
      detail::difference_type_arg<self_type> auto off) requires detail::impls_advance<self_type>
    {
      return left + -off;
    }

    friend constexpr self_type& operator-=(
      self_type& left,
      detail::difference_type_arg<self_type> auto off) requires detail::impls_advance<self_type>
    {
      return left = left - off;
    }

    constexpr decltype(auto) operator[](
      detail::difference_type_arg<self_type> auto off) requires detail::impls_advance<self_type>
    {
      return *(_self() + off);
    }

    friend constexpr self_type& operator-(const self_type& left,
                                          const self_type& right) requires detail::impls_distance_to<self_type>
    {
      return right.distance_to(left);
    }
    friend constexpr auto operator<=>(const self_type& left,
                                      const self_type& right) requires detail::impls_distance_to<self_type>
    {
      return (left - right) <=> 0;
    }

    // Sentinels

    friend constexpr self_type& operator-(
      const self_type& left,
      detail::iter_sentinel_arg<self_type> auto right) requires detail::impls_distance_to_sentinel<self_type>
    {
      return right.distance_to(left);
    }

    friend bool operator==(const self_type& lhs, detail::iter_sentinel_arg<self_type> auto)
    {
      return lhs._self().at_end();
    }

  private:
    constexpr self_type& _self() noexcept
    {
      return static_cast<self_type&>(*this);
    }
    constexpr const self_type& _self() const noexcept
    {
      return static_cast<const self_type&>(*this);
    }
  };
} // namespace otto::util

namespace std {
  template<typename Iter>
  requires std::is_base_of_v<otto::util::iterator_facade<Iter>, Iter> //
    struct iterator_traits<Iter> {
    static const Iter& _it;
    using reference = decltype(*_it);
    using pointer = decltype(_it.operator->());
    using difference_type = otto::util::detail::infer_difference_type_t<Iter>;
    using value_type = otto::util::detail::infer_value_type_t<Iter>;
    using iterator_category = //
      std::conditional_t<     //
        otto::util::detail::meets_random_access<Iter>,
        std::random_access_iterator_tag,
        std::conditional_t< //
          otto::util::detail::meets_bidirectional<Iter>,
          std::bidirectional_iterator_tag,
          std::conditional_t< //
            otto::util::detail::decls_single_pass<Iter>,
            std::input_iterator_tag,
            std::forward_iterator_tag>>>;

    using iterator_concept = iterator_category;
  };
} // namespace std
