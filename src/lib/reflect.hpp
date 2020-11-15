#pragma once

#include <concepts>
#include <string_view>
#include <type_traits>

#include "lib/meta.hpp"
#include "lib/util/string_ref.hpp"

namespace otto::reflect {

  namespace detail {
    template<typename T>
    struct member_pointer_value {};
    template<typename C, typename T>
    struct member_pointer_value<T C::*> {
      using type = T;
    };

    template<typename T>
    using member_pointer_value_t = typename member_pointer_value<T>::type;

    template<typename T>
    struct member_pointer_owner {};
    template<typename C, typename T>
    struct member_pointer_owner<T C::*> {
      using type = C;
    };

    template<typename T>
    using member_pointer_owner_t = typename member_pointer_owner<T>::type;
  } // namespace detail

  // MEMBERS

  /// Information about a reflected member
  ///
  /// Should contain fields:
  ///  - `typename struct_t`: The struct the member belongs to
  ///  - `typename value_type`: The type of the member
  ///  - `value_type struct_t::* mem_ptr`: Pointer to member
  ///  - `std::size_t index`: Index into the struct
  ///  - `util::string_ref name`: Member name as a string
  template<auto MemPtr>
  struct MemberInfo;

  namespace detail {
    template<typename T>
    struct is_member_data : std::false_type {};

    template<auto MemPtr>
    struct is_member_data<MemberInfo<MemPtr>> : std::true_type {};
  } // namespace detail

  // clang-format off
  template<typename Info>
  concept AMemberInfo = detail::is_member_data<Info>::value && requires
  {
    typename Info::struct_t;
    typename Info::value_type;
    { Info::mem_ptr } -> util::decays_to<typename Info::value_type Info::struct_t::*>;
    { Info::index }   -> util::decays_to<std::size_t>;
    { Info::name }    -> util::decays_to<util::string_ref>;
  };
  // clang-format on

  template<typename Struct>
  struct StructInfo;

  // STRUCTURE

  template<typename T>
  concept StructureTraits = true;

  struct EmptyStructureTraits {
    template<AMemberInfo Info, AMemberInfo... Parents>
    struct Member {};
  };

  template<typename Struct, StructureTraits Traits = EmptyStructureTraits, AMemberInfo... Parents>
  struct structure {
    using structure_not_implemented_for_this_type = void;
  };

  template<typename T>
  concept WithStructure = requires
  {
    typename structure<T>;
  }
  &&!requires
  {
    typename structure<T>::structure_not_implemented_for_this_type;
  };

  static_assert(!WithStructure<int>);

  template<typename T>
  concept AMemberInfoOfStructured = AMemberInfo<T>&& WithStructure<typename T::value_type>;

  template<AMemberInfo Info, StructureTraits Traits, AMemberInfo... Parents>
  struct MemberBase : Traits::template Member<Info, Parents...> {
    using Traits::template Member<Info, Parents...>::Member;
  };

  template<AMemberInfo Info, StructureTraits Traits, typename... Parents>
  struct Member : MemberBase<Info, Traits, Parents...> {
    using MemberBase<Info, Traits, Parents...>::MemberBase;
  };

  template<AMemberInfoOfStructured Info, StructureTraits Traits, typename... Parents>
  struct Member<Info, Traits, Parents...> : MemberBase<Info, Traits, Parents...>,
                                            structure<typename Info::value_type, Traits, Parents..., Info> {
    using MemBase = MemberBase<Info, Traits, Parents...>;
    using Structure = structure<typename Info::value_type, Traits, Parents..., Info>;

    constexpr Member(auto&&... args)                                       //
      requires(std::constructible_from<MemBase, decltype(args)...>         //
                 && std::constructible_from<Structure, decltype(args)...>) //
      : MemBase(args...), Structure(args...)
    {}
  };

  template<AMemberInfo Info, StructureTraits T, AMemberInfo... Parents>
  constexpr Info info(const Member<Info, T, Parents...>&)
  {
    return Info();
  }

  template<typename ValueType>
  requires(!AMemberInfo<ValueType>) constexpr std::size_t flat_size()
  {
    if constexpr (WithStructure<ValueType>) {
      return []<AMemberInfo... Ts>(meta::list<Ts...>)
      {
        return (flat_size<typename Ts::value_type>() + ... + 1);
      }
      (typename StructInfo<ValueType>::members());
    } else {
      return 1;
    }
  }
  template<AMemberInfo Info, AMemberInfo... Parents>
  constexpr std::size_t flat_idx()
  {
    return ((flat_size<typename Parents::value_type>() + 1) + ... + 0) + []<AMemberInfo... Ts>(meta::list<Ts...>)
    {
      return (flat_size<typename Ts::value_type>() + ... + 0);
    }
    (meta::take_t<Info::index, typename StructInfo<typename Info::struct_t>::members>());
  }

  template<AMemberInfo Info, StructureTraits T, AMemberInfo... Parents>
  constexpr std::size_t flat_idx(const Member<Info, T, Parents...>&)
  {
    return flat_idx<Info, Parents...>();
  }

} // namespace otto::reflect
