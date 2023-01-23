#pragma once

#include <algorithm>
#include <functional>
#include <initializer_list>
#include <numeric>
#include <string>
#include <string_view>

#include "lib/util/type_traits.hpp"

/// \file
/// This file contains the \ref otto::util::algorithm namespace

namespace otto::util {

  /// Inline namespace with algorithms similar to the ones found in the standard `<algorithm>`
  /// header.
  ///
  /// Also, this namespace includes container-based wrappers for all standard algorithms. For more
  /// on those, see \ref container_algos
  ///
  /// \attention `otto::util::algorithm` is an inline namespace, meaning all members can and should
  /// be accessed directly from the `otto::util` namespace i.e. as `nano::find_if(...)`, not
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

    inline std::pair<std::string_view, std::string_view> split_string(std::string_view str, char ch)
    {
      auto pos = str.find_first_of(ch);
      if (pos == std::string_view::npos) return {str, {}};
      return {str.substr(0, pos), str.substr(std::min(pos + 1, str.size()))};
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
      template<typename T, auto N>
      using ignore_index_t = T;
    }

    /// Construct a `std::array<T, N>` where all elements are constructed with the same `args...`
    template<typename T, std::size_t N, typename... Args>
    requires std::is_constructible_v<T, Args...> //
    constexpr auto make_array(Args&&... args)
    {
      auto impl = [&]<std::size_t... Ns>(std::index_sequence<Ns...>) constexpr
      {
        return std::array<T, N>{{algo_detail::ignore_index_t<T, Ns>(args...)...}};
      };
      return impl(std::make_index_sequence<N>());
    }

    /// Construct a `std::array<T, N>` from the result of calling `func(idx)`
    template<std::size_t N, std::invocable<std::size_t> Func>
    constexpr auto generate_array(Func&& func)
    {
      auto impl = [&]<std::size_t... Ns>(std::index_sequence<Ns...>) constexpr
      {
        return std::array<std::decay_t<std::invoke_result_t<Func, std::size_t>>, N>{{std::invoke(func, Ns)...}};
      };
      return impl(std::make_index_sequence<N>());
    }

    template<class Func>
    constexpr auto generate_vector(std::size_t n, Func&& gen)
    {
      using value_type = std::decay_t<decltype(gen(n))>;
      std::vector<value_type> res;
      res.reserve(n);
      std::generate_n(std::back_inserter(res), n, [&gen, i = 0]() mutable { return gen(i++); });
      return res;
    }

    /// Identity function
    constexpr auto identity = [](auto&& x) -> decltype(auto) { return FWD(x); };

    /*
     * Range algorithms
     */

    /// `for_each` with access to an index value. Function called as `f(i, *it)`
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
      return indexed_for_each(std::begin(rng), std::end(rng), std::forward<F>(f));
    }

    /// Container based wrapper for \ref std::accumulate()
    template<typename Cont, typename T>
    constexpr auto accumulate(Cont&& cont, T&& init)
    {
      return std::accumulate(std::ranges::begin(cont), std::ranges::end(cont), FWD(init));
    }

    /// Container based wrapper for \ref std::accumulate()
    template<typename Cont, typename T, typename BinaryOperation>
    constexpr auto accumulate(Cont&& cont, T&& init, BinaryOperation&& op)
    {
      return std::accumulate(std::ranges::begin(cont), std::ranges::end(cont), FWD(init), FWD(op));
    }
  } // namespace algorithm

} // namespace otto::util
