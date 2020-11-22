#pragma once

#include <concepts>
#include <string_view>
#include <type_traits>

#include "lib/meta.hpp"
#include "lib/util/constexpr.hpp"
#include "lib/util/string_ref.hpp"
#include "lib/util/utility.hpp"

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
  ///  - `std::size_t index`: Index into the struct
  ///  - `util::string_ref name`: Member name as a string
  /// Should also expose a specialization of `reflect::get<Info>(Struct&)`
  /// This can be done by declaring the following:
  ///  - `value_type struct_t::* mem_ptr`: Pointer to member
  template<auto MemPtr>
  struct MemberInfo;

  // clang-format off
  template<typename Info>
  requires requires { Info::mem_ptr; }
  constexpr decltype(auto) get(util::decays_to<typename Info::struct_t> auto&& s)
  {
    return s.*Info::mem_ptr;
  }

  template<typename Info>
  requires requires(typename Info::struct_t& s) { Info::get(s); }
  constexpr decltype(auto) get(util::decays_to<typename Info::struct_t> auto&& s)
  {
    return Info::get(s);
  }
  // clang-format on

  // clang-format off
  template<typename Info>
  concept AMemberInfo = requires
  {
    typename Info::struct_t;
    typename Info::value_type;
    { ::otto::reflect::get<Info>(std::declval<typename Info::struct_t&>()) } -> std::same_as<typename Info::value_type&>;
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

  namespace detail {
    template<typename T>
    struct is_member : std::false_type {};

    template<AMemberInfo Info, StructureTraits Traits, typename... Parents>
    struct is_member<Member<Info, Traits, Parents...>> : std::true_type {};
  } // namespace detail

  template<typename T>
  concept AMember = detail::is_member<T>::value;

  template<AMemberInfo Info, StructureTraits T, AMemberInfo... Parents>
  constexpr Info info(const Member<Info, T, Parents...>&)
  {
    return Info();
  }

  template<typename T>
  using members_t = std::conditional_t<WithStructure<T>, typename StructInfo<T>::members, meta::list<>>;

  template<WithStructure T>
  constexpr std::size_t size()
  {
    return StructInfo<T>::members::size;
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

  template<AMemberInfo Info, AMemberInfo P1, AMemberInfo... Parents>
  constexpr decltype(auto) get(util::decays_to<typename meta::head_t<meta::list<Parents..., Info>>::struct_t> auto&& s)
  {
    return get<Info, Parents...>(get<P1>(FWD(s)));
  }

  template<AMemberInfo Info, StructureTraits T, AMemberInfo... Parents>
  constexpr decltype(auto) get(const Member<Info, T, Parents...>&,
                               util::decays_to<typename meta::head_t<meta::list<Parents..., Info>>::struct_t> auto&& s)
  {
    return get<Info, Parents...>(FWD(s));
  }

  // Specializations

  template<typename Array, std::size_t Idx>
  struct ArrayMemberInfo {
    using struct_t = Array;
    using value_type = typename Array::value_type;
    constexpr static std::size_t index = Idx;
    constexpr static util::string_ref name = util::cxpr::to_string<Idx>;
    constexpr static decltype(auto) get(util::decays_to<struct_t> auto&& s)
    {
      return std::get<Idx>(s);
    }
  };

  namespace detail {
    template<typename Indicies, typename T, std::size_t N, StructureTraits Traits, AMemberInfo... Parents>
    struct array_struct_tuple;
    template<typename T, std::size_t N, StructureTraits Traits, AMemberInfo... Parents, std::size_t... Idxs>
    struct array_struct_tuple<std::integer_sequence<std::size_t, Idxs...>, T, N, Traits, Parents...> {
      using type = std::tuple<Member<ArrayMemberInfo<std::array<T, N>, Idxs>, Traits, Parents...>...>;
    };

    template<typename Indicies, typename T, std::size_t N>
    struct array_member_list;
    template<typename T, std::size_t N, std::size_t... Idxs>
    struct array_member_list<std::integer_sequence<std::size_t, Idxs...>, T, N> {
      using type = meta::list<ArrayMemberInfo<std::array<T, N>, Idxs>...>;
    };

    template<typename Tuple, typename... Args>
    Tuple init_all(Args&&... args)
    {
      auto impl = [&]<typename... Ts>(meta::one<std::tuple<Ts...>>)
      {
        return std::tuple<Ts...>(Ts(FWD(args)...)...);
      };
      return impl(meta::one<Tuple>());
    }
  } // namespace detail

  template<typename T, std::size_t N, StructureTraits Traits, AMemberInfo... Parents>
  struct structure<std::array<T, N>, Traits, Parents...> {
    using Tuple = typename detail::array_struct_tuple<std::make_index_sequence<N>, T, N, Traits, Parents...>::type;
    [[no_unique_address]] Tuple members;

    template<std::size_t I>
    requires(I < N) constexpr auto get()
    {
      return std::get<I>(members);
    }

    constexpr structure(auto&&... args) : members(detail::init_all<Tuple>(FWD(args)...)) {}
    constexpr structure(const structure&) = default;
    constexpr structure(structure&&) = default;
    constexpr structure& operator=(const structure&) = default;
    constexpr structure& operator=(structure&&) = default;
  };

  template<typename T, std::size_t N>
  struct StructInfo<std::array<T, N>> {
    using members = typename detail::array_member_list<std::make_index_sequence<N>, T, N>::type;
  };

} // namespace otto::reflect
