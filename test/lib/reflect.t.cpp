#include <cstdint>
#include <type_traits>

template<typename T>
struct remove_member_pointer {
  using type = T;
};
template<typename C, typename T>
struct remove_member_pointer<T C::*> {
  using type = T;
};

template<typename T>
using remove_member_pointer_t = typename remove_member_pointer<T>::type;

template<typename Struct, std::size_t Idx, auto Struct::*MemPtr>
struct MemberBase {
  static constexpr std::size_t index = Idx;
  static constexpr std::size_t next = index + 1;
  using value_type = std::remove_pointer_t<decltype(MemPtr)>;
  constexpr static value_type& get(Struct& self) noexcept
  {
    return self.*MemPtr;
  }
  constexpr static const value_type& get(const Struct& self) noexcept
  {
    return self.*MemPtr;
  }
};

template<typename Struct>
struct StructureBase {
  template<std::size_t Idx, auto Struct::*MemPtr>
  struct Member : MemberBase<Struct, Idx, MemPtr> {};
};

template<typename Struct>
template<std::size_t Idx, auto Struct::*MemPtr>
requires requires
{
  typename remove_member_pointer_t<decltype(MemPtr)>::template Structure<0>;
}
struct StructureBase<Struct>::Member<Idx, MemPtr>
  : MemberBase<Struct, Idx, MemPtr>, remove_member_pointer_t<decltype(MemPtr)>::template Structure<Idx + 1> {};

#define DECL_STRUCTURE(Type, ...)                                                                                      \
  template<std::size_t Idx = 0>                                                                                        \
  struct Structure : StructureBase<Type> {                                                                             \
    Member<&Type::subi1, Idx + 0> subi1;                                                                               \
    static constexpr std::size_t next = decltype(subi1)::next;                                                         \
  };

struct State {
  int i1 = 0;
  int i2 = 0;
  struct SubState {
    int subi1 = 0;
    template<std::size_t Idx = 0>
    struct Structure : StructureBase<SubState> {
      Member<Idx + 0, &SubState::subi1> subi1;
      static constexpr std::size_t next = decltype(subi1)::next;
    };
  } substate;
  template<std::size_t Idx = 0>
  struct Structure : StructureBase<State> {
    Member<Idx + 0, &State::i1> i1;
    Member<Idx + decltype(i1)::next, &State::i2> i2;
    Member<Idx + decltype(i2)::next, &State::substate> substate;
    static constexpr std::size_t next = decltype(substate)::next;
  };
};


static_assert(State::Structure<>().substate.index == 2);
static_assert(State::Structure<>().substate.subi1.index == 3);
