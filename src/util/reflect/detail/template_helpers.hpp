// Various useful template stuff
// thanks to Vittorio Romeo and other people who came up with this stuff

#include <tuple>
#include <type_traits>

#pragma once

namespace otto::reflect {
  namespace detail {

    /// for_each_arg - call f for each argument from pack
    template<typename F, typename... Args>
    void for_each_arg(F&& f, Args&&... args);

    /// for_each_arg - call f for each element from tuple
    template<typename F, typename TupleT>
    void for_tuple(F&& f, TupleT&& tuple);

    /// overload for empty tuple which does nothing
    template<typename F>
    void for_tuple(F&& f, const std::tuple<>& tuple);

    /// calls F if condition is true
    /// this is useful for templated lambdas, because they won't be
    /// instantiated with unneeded types
    template<bool Test, typename F, typename... Args, typename = std::enable_if_t<Test>>
    void call_if(F&& f, Args&&... args);

    /// calls F if condition is false
    template<bool Test,
             typename F,
             typename... Args,
             typename = std::enable_if_t<!Test>,
             typename = void> // dummy type for difference between two functions
    void call_if(F&& f, Args&&... args);

  } // end of namespace detail
} // namespace otto::reflect

#include "template_helpers.inl"
