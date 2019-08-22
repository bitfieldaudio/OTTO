#pragma once

#include "template_helpers.hpp"

namespace otto::reflect {
  namespace detail {

    template<typename F, typename... Args>
    void for_each_arg(F&& f, Args&&... args)
    {
      // Waiting for C++17, so I don't have to write silly stuff like this
      using expand = bool[];
      (void) expand{(f(std::forward<Args>(args)), true)...};
    }

    template<std::size_t N>
    decltype(auto) makeIndexSequence()
    {
      return std::make_index_sequence<N>();
    }

    // Because VS can't properly make index_sequence out of 1 element...
    // Seems to be fixed in VS 2015 Update 3

    template<>
    inline decltype(auto) makeIndexSequence<1>()
    {
      return std::index_sequence<0>();
    }

    template<typename F, typename Tuple, std::size_t... I>
    decltype(auto) apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>)
    {
      return f(std::get<I>(std::forward<Tuple>(t))...);
    }

    template<typename F, typename Tuple>
    decltype(auto) apply(F&& f, Tuple&& t)
    {
      constexpr std::size_t tupleSize = std::tuple_size<std::decay_t<Tuple>>::value;
      return apply_impl(std::forward<F>(f), std::forward<Tuple>(t), makeIndexSequence<tupleSize>());
    }

    template<typename F, typename TupleT>
    void for_tuple(F&& f, TupleT&& tuple)
    {
      // ambiguity with std::apply
      otto::reflect::detail::apply(
        [&f](auto&&... elems) { for_each_arg(f, std::forward<decltype(elems)>(elems)...); },
        std::forward<TupleT>(tuple));
    }

    template<typename F>
    void for_tuple(F&& /* f */, const std::tuple<>& /* tuple */)
    { /* do nothing */
    }

    template<bool Test, typename F, typename... Args, typename>
    void call_if(F&& f, Args&&... args)
    {
      f(std::forward<Args>(args)...);
    }

    template<bool Test, typename F, typename... Args, typename, typename>
    void call_if(F&& /* f */, Args&&... /* args */)
    { /* do nothing */
    }

  } // end of namespace detail
} // namespace otto::reflect
