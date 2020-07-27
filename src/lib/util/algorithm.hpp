#pragma once

#include <algorithm>
#include <functional>
#include <initializer_list>
#include <numeric>
#include <string>
#include <string_view>

#include "lib/util/type_traits.hpp"

/// \file
/// This file contains the \ref otto::lib::util::algorithm namespace

namespace otto::lib::util {

  /// Inline namespace with algorithms similar to the ones found in the standard `<algorithm>`
  /// header.
  ///
  /// Also, this namespace includes container-based wrappers for all standard algorithms. For more
  /// on those, see \ref container_algos
  ///
  /// \attention `otto::lib::util::algorithm` is an inline namespace, meaning all members can and should
  /// be accessed directly from the `otto::lib::util` namespace i.e. as `nano::find_if(...)`, not
  /// `util::algorithm::find_if(...)`. It is only a separate namespace for clarification of
  /// documentation and name resolution.
  inline namespace algorithm {
    /// Joins a sequence of strings, separating them using `js`
    template<class StrIterator> // Models InputIterator<std::string>
    std::string join_strings(StrIterator b, StrIterator e, std::string_view js = ", ")
    {
      std::string result;
      std::for_each(b, e, [&](auto&& s) {
        if (!result.empty()) {
          result.append(js);
        }
        result.append(s);
      });
      return result;
    }

    /// Find/Replace
    inline void string_replace(std::string& str, const std::string& oldStr, const std::string& newStr)
    {
      std::string::size_type pos = 0u;
      while ((pos = str.find(oldStr, pos)) != std::string::npos) {
        str.replace(pos, oldStr.length(), newStr);
        pos += newStr.length();
      }
    }

    /// Check if string `str` starts with `prefix`
    inline bool starts_with(std::string_view str, std::string_view prefix)
    {
      return str.compare(0, prefix.size(), prefix) == 0;
    }

    /// Joins a sequence of strings, separating them using `js`
    template<typename Container>
    std::string join_strings(Container&& cont, std::string_view js = ", ")
    {
      return join_strings(std::begin(cont), std::end(cont), js);
    }

    inline std::string_view trim_begin(std::string_view sv, std::string_view rem = " ") noexcept
    {
      auto idx = sv.find_first_not_of(rem);
      idx = idx == std::string_view::npos ? sv.size() : idx;
      return sv.substr(idx, std::string_view::npos);
    }

    inline std::string_view trim_end(std::string_view sv, std::string_view rem = " ") noexcept
    {
      auto idx = sv.find_last_not_of(rem);
      idx = idx == std::string_view::npos ? sv.size() : idx + 1;
      return sv.substr(0, idx);
    }

    inline std::string_view trim(std::string_view sv, std::string_view rem = " ") noexcept
    {
      auto first_idx = sv.find_first_not_of(rem);
      first_idx = (first_idx == std::string_view::npos) ? sv.size() : first_idx;
      auto last_idx = sv.find_last_not_of(rem);
      last_idx = (last_idx == std::string_view::npos) ? sv.size() : last_idx + 1;
      return sv.substr(first_idx, last_idx - first_idx);
    }

    namespace algo_detail {
      template<class Func, int... ns>
      constexpr auto generate_array_impl(std::integer_sequence<int, ns...>&&, Func&& gen)
      {
        return std::array<std::decay_t<decltype(std::invoke(gen, std::declval<int>()))>, sizeof...(ns)>{
          {std::invoke(gen, ns)...}};
      }
    } // namespace algo_detail

    template<int n, class Func>
    constexpr auto generate_array(Func&& gen)
    {
      auto intseq = std::make_integer_sequence<int, n>();
      return algo_detail::generate_array_impl(std::move(intseq), std::forward<Func>(gen));
    }

    template<class Func>
    constexpr auto generate_vector(int n, Func&& gen)
    {
      using value_type = std::decay_t<decltype(gen(n))>;
      std::vector<value_type> res;
      res.reserve(n);
      std::generate_n(std::back_inserter(res), n, [&gen, i = 0]() mutable { return gen(i++); });
      return res;
    }

    /// Identity function
    constexpr auto identity = [](auto&& x) -> decltype(auto) { return FWD(x); };

    /// Erase elements from container
    ///
    /// @param cont Must be a container with a `erase(Iter, Iter)` member function, erasing the
    /// items between the two iterators. Most mutable standard containers qualify.
    ///
    /// @param t elements will be erased if they compare equal to this
    ///
    /// @returns whatever `cont.erase()` returns. For standard containers, this is the iterator
    /// pointing to the element after the last erased one.
    template<typename Container, typename T>
    auto erase(Container&& cont, T&& t)
    {
      return cont.erase(std::remove(std::begin(cont), std::end(cont), std::forward<T>(t)), std::end(cont));
    }

    /// Erase elements from container by predicate
    ///
    /// @param cont Must be a container with a `erase(Iter, Iter)` member function, erasing the
    /// items between the two iterators. Most mutable standard containers qualify.
    ///
    /// @param pred A predicate that takes a element in the container. Each element for which this
    /// predicate returns true will be erased from the container.
    ///
    /// @returns whatever `cont.erase()` returns. For standard containers, this is the iterator
    /// pointing to the element after the last erased one.
    template<typename Container, typename Pred>
    auto erase_if(Container&& cont, Pred&& pred)
    {
      return cont.erase(std::remove_if(std::begin(cont), std::end(cont), std::forward<Pred>(pred)), std::end(cont));
    }

    /*
     * Range algorithms
     */

    template<typename InputIt, typename Size, typename F>
    constexpr InputIt for_each_n(InputIt&& first, Size n, F&& f)
    {
      for (Size i = 0; i < n; ++first, ++i) {
        std::invoke(f, *first);
      }
      return first;
    }

    /// `for_each` with access to an index value. Function called as `f(*it, i)`
    ///
    /// For each item in range `[first, last)`, invoke `f` with args
    /// `i, *iter` where `iter` is the current iterator, and `i` is
    /// an incrementing value, starting at zero. Use this instead of
    /// raw indexed loops wherever possible.
    ///
    /// \param first Input iterator to the begining of the range
    /// \param last Input iterator to the end of the range
    /// \param f Must be invocable with arguments `std::size_t`, `value_type`
    /// \returns The number of iterations performed
    template<typename InputIt, typename F>
    constexpr std::size_t indexed_for_each(InputIt&& first, InputIt&& last, F&& f)
    {
      std::size_t i = 0;
      std::for_each(std::forward<InputIt>(first), std::forward<InputIt>(last), [&](auto&& a) {
        std::invoke(f, i, a);
        i++;
      });
      return i;
    }

    template<typename Rng, typename F>
    constexpr std::size_t indexed_for_each(Rng&& rng, F&& f)
    {
      return indexed_for(std::begin(rng), std::end(rng), std::forward<F>(f));
    }


    /// `for_each_n` with access to an index value. Function called as `f(*it, i)`
    ///
    /// for `n` iterations, invoke `f` with args `*iter, i`
    /// where `iter` is the current iterator starting with `first`,
    /// and `i` is an incrementing value, starting at zero.
    /// Use this instead of raw indexed loops wherever possible.
    ///
    /// \param first Input iterator to the begining of the range
    /// \param n Number of iterations to go through
    /// \param f Must be invocable with arguments `value_type`, `std::size_t`
    /// \returns An iterator one past the last one visited
    template<class InputIt, class Size, class F>
    constexpr InputIt indexed_for_n(InputIt first, Size n, F&& f)
    {
      for (Size i = 0; i < n; ++first, ++i) {
        std::invoke(f, *first, i);
      }
      return first;
    }

    template<class Rng, class Size, class F>
    constexpr std::size_t indexed_for_n(Rng&& rng, Size n, F&& f)
    {
      return indexed_for_n(std::begin(rng), std::end(rng), n, std::forward<F>(f));
    }

    template<typename Iter1, typename Iter2, typename F>
    constexpr void for_both(Iter1&& f1, Iter1&& l1, Iter2&& f2, Iter2&& l2, F&& f)
    {
      Iter1 i1 = std::forward<Iter1>(f1);
      Iter2 i2 = std::forward<Iter2>(f2);
      for (; i1 != l1 && i2 != l2; i1++, i2++) {
        std::invoke(f, *i1, *i2);
      }
    }

    template<typename Rng1, typename Rng2, typename F>
    constexpr void for_both(Rng1&& r1, Rng2&& r2, F&& f)
    {
      for_both(std::begin(r1), std::end(r1), std::begin(r2), std::end(r2), std::forward<F>(f));
    }

    template<typename Cont>
    constexpr std::size_t count(Cont&& cont)
    {
      std::size_t n = 0;
      for (auto&& el : cont) n++;
      return n;
    }

    /// Container based wrapper for \ref std::accumulate()
    template<typename Cont, typename T>
    constexpr auto accumulate(Cont&& cont, T&& init)
    {
      // TODO C++20: std::accumulate is constexpr
      using std::begin, std::end;
      auto first = begin(cont);
      auto last = end(cont);
      for (; first != last; ++first) init = init + *first;
      return init;
    }

    /// Container based wrapper for \ref std::accumulate()
    template<typename Cont, typename T, typename BinaryOperation>
    constexpr auto accumulate(Cont&& cont, T&& init, BinaryOperation&& op)
    {
      // TODO C++20: std::accumulate is constexpr
      using std::begin, std::end;
      auto first = begin(cont);
      auto last = end(cont);
      for (; first != last; ++first) init = op(init, *first);
      return init;
    }
  } // namespace algorithm

} // namespace otto::lib::util
