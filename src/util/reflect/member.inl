#pragma once
#include <functional>
#include <stdexcept>

#include "member.hpp"

namespace otto::reflect {

  template<typename Class, typename T, AccessorType AT, typename AD>
  constexpr Member<Class, T, AT, AD>::Member(util::string_ref name, const Accessor& accessor)
    : _name(name), _accessor(accessor)
  {}

  template<typename Class, typename T, AccessorType AT, typename AD>
  constexpr const T& Member<Class, T, AT, AD>::get(const Class& obj) const
  {
    return _accessor.get_const(_accessor.data, obj);
  }

  template<typename Class, typename T, AccessorType AT, typename AD>
  constexpr decltype(auto) Member<Class, T, AT, AD>::get(Class& obj) const
  {
    if constexpr (can_get_ref())  return _accessor.get(_accessor.data, obj);
    else return _accessor.get_const(_accessor.data, obj);
  }


  template<typename Class, typename T, AccessorType AT, typename AD>
  constexpr T& Member<Class, T, AT, AD>::get_ref(Class& obj) const
  {
    static_assert(can_get_ref(), "Cannot return ref to member: no getter or member pointer set");
    return _accessor.get(_accessor.data, obj);
  }

  template<typename Class, typename T, AccessorType AT, typename AD>
  template<typename V, typename>
  constexpr void Member<Class, T, AT, AD>::set(Class& obj, V&& value) const
  {
    static_assert(has_setter(), "Cannot access member: no setter or member pointer set");

    if constexpr (can_get_ref()) {
      get_ref() = std::forward<V>(value);
    } else {
      _accessor.set(_accessor.data, obj, value);
    }
  }

  template<typename Class, typename Callable, typename>
  constexpr auto member(util::string_ref name, Callable&& ref_getter)
  {
    using Res = typename mpark::lib::invoke_result<Callable, Class&>::type;
    using Val = std::decay_t<Res>;
    if constexpr (std::is_lvalue_reference_v<Res> && !std::is_const_v<Res>) {
      using MemberT = Member<Class, Val, AccessorType::MutableRef, Callable>;
      return MemberT(name,
                     typename MemberT::Accessor(
                       [](const Callable& d, Class& obj) -> Val& { return std::invoke(d, obj); },
                       [](const Callable& d, const Class& obj) -> const Val& { return std::invoke(d, obj); },
                       std::forward<Callable>(ref_getter)));
    } else {
      using MemberT = Member<Class, Val, AccessorType::ReadOnly, Callable>;
      return MemberT(name, typename MemberT::Accessor(
                             [](const Callable& d, const Class& obj) -> const Val& {
                               return std::invoke(d, obj);
                             },
                             std::forward<Callable>(ref_getter)));
    }
  }

  template<typename Class, typename Getter, typename Setter, typename>
  constexpr auto member(util::string_ref name, Getter&& getter, Setter&& setter)
  {
    using Res = typename mpark::lib::invoke_result<Getter, const Class&>::type;
    using Val = std::decay_t<Res>;
    static_assert(mpark::lib::is_invocable<Setter, Class&, const Res&>::value);

    using Data = std::pair<Getter, Setter>;

    using MemberT = Member<Class, std::decay_t<Res>, AccessorType::ReadWrite, Data>;
    return MemberT(name, typename MemberT::Accessor{
                           [](const Data& d, const Class& obj) -> const Val& { return std::invoke(d.first, obj); },
                           [](const Data& d, Class& obj, const Val& val) {
                             return std::invoke(d.second, obj, val);
                           },
                           std::make_pair(std::forward<Getter>(getter), std::forward<Setter>(setter))});
  }

} // namespace otto::reflect

// kak: other_file=member.hpp
