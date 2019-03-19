/* -----------------------------------------------------------------------------------------------

Member<Class, T> is a representation of a registered member
Class - a class this member belongs to
T - type of that member

Member contains pointer to data member which can be used to get / set stuff
Different getters and setters can be added via fluent interface (see
addGetter/addConstGetter/addSetter) Getters and setters are always preffered to using raw data
member pointers (because why would you set them in the other place?)

-------------------------------------------------------------------------------------------------*/

#pragma once

#include "util/utility.hpp"

#include "./reflect.hpp"

namespace otto::reflect {

  /// MemberType is Member<T, Class>
  template<typename MemberType>
  using get_member_type = typename std::decay_t<MemberType>::member_type;

  enum struct AccessorType { ReadOnly, ReadWrite, MutableRef };

  template<typename Class, typename T, AccessorType AT, typename Data>
  struct MemberAccessor;

  template<typename Class, typename T, typename Data>
  struct MemberAccessor<Class, T, AccessorType::ReadOnly, Data> {
    constexpr MemberAccessor(util::function_ptr<const T&, const Data&, const Class&> getter,
                             Data const& data)
      : get_const(getter), data(data)
    {}
    util::function_ptr<const T&, const Data&, const Class&> get_const;
    Data data;
  };

  template<typename Class, typename T, typename Data>
  struct MemberAccessor<Class, T, AccessorType::ReadWrite, Data> {
    constexpr MemberAccessor(util::function_ptr<const T&, const Data&, const Class&> get,
                             util::function_ptr<void, const Data&, Class&, const T&> set,
                             const Data& data)
      : get_const(get), set(set), data(data)
    {}
    util::function_ptr<const T&, const Data&, const Class&> get_const;
    util::function_ptr<void, const Data&, Class&, const T&> set;
    Data data;
  };

  template<typename Class, typename T, typename Data>
  struct MemberAccessor<Class, T, AccessorType::MutableRef, Data> {
    constexpr MemberAccessor(util::function_ptr<T&, const Data&, Class&> get,
                             util::function_ptr<const T&, const Data&, const Class&> get_const,
                             const Data& data)
      : get(get), get_const(get_const), data(data)
    {}
    util::function_ptr<T&, const Data&, Class&> get;
    util::function_ptr<const T&, const Data&, const Class&> get_const;
    Data data;
  };

  template<typename Class, typename T, AccessorType AT, typename AccessorData>
  struct Member {
    using MemberAccessor = MemberAccessor<Class, T, AT, AccessorData>;
    using class_type = Class;
    using member_type = T;
    using type = T;

    constexpr Member(util::string_ref name, const MemberAccessor& ma);

    constexpr util::string_ref get_name() const
    {
      return _name;
    }
    constexpr static bool has_setter() noexcept
    {
      return AT != AccessorType::ReadOnly;
    }
    constexpr static bool can_get_ref() noexcept
    {
      return AT == AccessorType::MutableRef;
    }

    // get sets methods can be used to add support
    // for getters/setters for members instead of
    // direct access to them
    constexpr const T& get(const Class& obj) const;
    constexpr decltype(auto) get(Class& obj) const;
    constexpr T& get_ref(Class& obj) const;

    template<typename V, typename = std::enable_if_t<std::is_constructible<T, V>::value>>
    constexpr void set(Class& obj, V&& value) const; // accepts lvalues and rvalues!

  private:
    util::string_ref _name;
    MemberAccessor _accessor;
  };

  // useful function similar to make_pair which is used so you don't have to write this:
  // Member<SomeClass, int>("someName", &SomeClass::someInt); and can just to this:
  // member("someName", &SomeClass::someInt);

  template<typename Class,
           typename Callable,
           typename = std::enable_if_t<std::is_invocable_v<Callable, Class&>>>
  constexpr auto member(util::string_ref, Callable&& ref_getter);

  template<typename Class,
           typename Getter,
           typename Setter,
           typename = std::enable_if_t<std::is_invocable_v<Getter, const Class&>>>
  constexpr auto member(util::string_ref, Getter&& getter, Setter&& setter);

} // namespace otto::reflect

#include "member.inl"

// kak: other_file=member.inl