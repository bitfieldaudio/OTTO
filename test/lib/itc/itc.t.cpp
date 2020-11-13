#include "lib/itc/itc.hpp"
#include <bitset>
#include "testing.t.hpp"

using namespace otto::itc;

// Tests
TEST_CASE (doctest::test_suite("itc") * "Basic Channel/Consumer/Producer linking and lifetime") {
  struct State {
    int i = 0;
    bool operator==(const State&) const = default;
  };

  ImmediateExecutor ex;

  SUBCASE ("Constructing consumer with channel registers it") {
    Channel<State> ch;
    Consumer<State> c1 = {ch, ex};

    REQUIRE(ch.consumers().size() == 1);
    REQUIRE(ch.consumers()[0] == &c1);

    Consumer<State> c2 = {ch, ex};

    REQUIRE(ch.consumers().size() == 2);
    REQUIRE(ch.consumers()[1] == &c2);
  }

  SUBCASE ("Constructing a producer with a channel registers it") {
    Channel<State> ch1;
    Producer<State> p = {ch1};

    REQUIRE(p.channels().size() == 1);
    REQUIRE(p.channels()[0] == &ch1);
    SUBCASE ("A producer can be registered to more channels with ch.set_producer") {
      Channel<State> ch2;
      ch2.set_producer(p);
      REQUIRE(p.channels().size() == 2);
      REQUIRE(p.channels()[1] == &ch2);
    }
  }

  SUBCASE ("Channel has a reference to its producer") {
    Channel<State> ch;
    REQUIRE(ch.producer() == nullptr);
    Producer<State> p = {ch};
    REQUIRE(ch.producer() == &p);

    SUBCASE ("Also when registered with set_producer") {
      Channel<State> ch2;
      ch2.set_producer(p);
      REQUIRE(ch2.producer() == &p);
      REQUIRE(ch.producer() == &p);
    }
  }

  SUBCASE ("Consumer has a reference to its channel") {
    Channel<State> ch;
    Consumer<State> c = {ch, ex};
    REQUIRE(c.channel() == &ch);
  }

  SUBCASE ("Bidirectional lifetime management") {
    SUBCASE ("Producer / Channel") {
      SUBCASE ("Producer destroyed before channel") {
        Channel<State> ch;
        {
          Producer<State> p = {ch};
        }
        REQUIRE(ch.producer() == nullptr);
      }
      SUBCASE ("Channel destroyed before producer") {
        auto ch = std::make_unique<Channel<State>>();
        Producer<State> p = {*ch};
        ch.reset();
        REQUIRE(p.channels().empty());
      }
    }
    SUBCASE ("Consumer / Channel") {
      SUBCASE ("Consumer destroyed before channel") {
        Channel<State> ch;
        {
          Consumer<State> p = {ch, ex};
        }
        REQUIRE(ch.consumers().empty());
      }
      SUBCASE ("Channel destroyed before consumer") {
        auto ch = std::make_unique<Channel<State>>();
        Consumer<State> c = {*ch, ex};
        ch.reset();
        REQUIRE(c.channel() == nullptr);
      }
    }
  }
}

TEST_CASE (doctest::test_suite("itc") * "Basic state passing") {
  ImmediateExecutor ex;
  struct S {
    int i = 0;
    bool operator==(const S&) const = default;
  };
  Channel<S> ch;
  Producer<S> p = {ch};
  struct C1 : Consumer<S> {
    using Consumer<S>::Consumer;

    void check_i(int i)
    {
      REQUIRE(state().i == i);
    }

    void on_state_change(const S& old_state) noexcept override
    {
      old_i = old_state.i;
      new_state_called++;
    }

    int new_state_called = 0;
    int old_i = 0;
  } c1 = {ch, ex};

  SUBCASE ("Access default state in Consumer") {
    c1.check_i(0);
  }

  struct P1 : Producer<S> {
    void test_produce(int i)
    {
      produce(replace(S{.i = i}));
      REQUIRE(state().i == i);
    }
  } p1 = {ch};

  SUBCASE ("Publish new state from producer") {
    p1.test_produce(1);
    c1.check_i(1);
    REQUIRE(c1.new_state_called == 1);
    REQUIRE(c1.old_i == 0);
    p1.test_produce(2);
    c1.check_i(2);
    REQUIRE(c1.new_state_called == 2);
    REQUIRE(c1.old_i == 1);
  }
}

TEST_CASE (doctest::test_suite("itc") * "prod/cons/chan of multiple states") {
  struct S1 {
    int i1 = 1;
    bool operator==(const S1&) const = default;
  };

  struct S2 {
    int i2 = 2;
    bool operator==(const S2&) const = default;
  };

  struct S3 {
    int i3 = 3;
    bool operator==(const S3&) const = default;
  };

  using Ch12 = Channel<S1, S2>;
  using C12 = Consumer<S1, S2>;
  using P12 = Producer<S1, S2>;

  static_assert(std::is_base_of_v<Channel<S1>, Ch12>);
  static_assert(std::is_base_of_v<Channel<S2>, Ch12>);
  static_assert(std::is_base_of_v<Consumer<S1>, C12>);
  static_assert(std::is_base_of_v<Consumer<S2>, C12>);
  static_assert(std::is_base_of_v<Producer<S1>, P12>);
  static_assert(std::is_base_of_v<Producer<S2>, P12>);

  //  using Ch123 = Channel<S1, meta::list<S2, S3>>;
  //  using C123 = Consumer<S1, meta::list<S2, S3>>;
  //  using P123 = Producer<S1, meta::list<S2, S3>>;
  //
  //  static_assert(std::is_base_of_v<Channel<S1>, Ch123>);
  //  static_assert(std::is_base_of_v<Channel<S2>, Ch123>);
  //  static_assert(std::is_base_of_v<Channel<S3>, Ch123>);
  //  static_assert(std::is_base_of_v<Consumer<S1>, C123>);
  //  static_assert(std::is_base_of_v<Consumer<S2>, C123>);
  //  static_assert(std::is_base_of_v<Consumer<S3>, C123>);
  //  static_assert(std::is_base_of_v<Producer<S1>, P123>);
  //  static_assert(std::is_base_of_v<Producer<S2>, P123>);
  //  static_assert(std::is_base_of_v<Producer<S3>, P123>);

  ImmediateExecutor ex;
  Ch12 ch;

  struct C1 : Consumer<S1, S2> {
    // Inherit the constructor
    using Consumer<S1, S2>::Consumer;

    void check_i1(int i)
    {
      REQUIRE(state<S1>().i1 == i);
    }

    void check_i2(int i)
    {
      REQUIRE(state<S2>().i2 == i);
    }

    void on_state_change(const S1& s) noexcept override
    {
      new_state1_called++;
    }

    void on_state_change(const S2& s) noexcept override
    {
      new_state2_called++;
    }

    int new_state1_called = 0;
    int new_state2_called = 0;
  } c1 = {ch, ex};

  SUBCASE ("Access default state in Consumer") {
    c1.check_i1(1);
    c1.check_i2(2);
  }

  struct P1 : Producer<S1, S2> {
    void test_produce1(int i)
    {
      produce(set(&S1::i1, i));
    }
    void test_produce2(int i)
    {
      produce(replace(S2{.i2 = i}));
    }
  } p1 = {ch};

  SUBCASE ("Publish new state from producer") {
    p1.test_produce1(10);
    c1.check_i1(10);
    REQUIRE(c1.new_state1_called == 1);
    c1.check_i2(2);
    REQUIRE(c1.new_state2_called == 0);

    p1.test_produce2(20);
    c1.check_i1(10);
    REQUIRE(c1.new_state1_called == 1);
    c1.check_i2(20);
    REQUIRE(c1.new_state2_called == 1);
  }
}

TEST_CASE ("Sample engine") {
  struct State {
    float frequency = 40.f;
    float resonance = 0.5;

    bool operator==(const State&) const = default;
  };

  struct FilterLogic : Producer<State> {
    void handle_encoder(int steps)
    {
      produce(replace(State{.frequency = 0.f, .resonance = 0.4}));
    };
  };


  struct FilterAudio : Consumer<State> {};

  struct FilterScreen : Consumer<State> {};
}

//#define DECL_REFL(Type, ...)

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

template<typename Struct, auto Struct::*MemPtr, std::size_t Idx>
struct MemberBase {
  static constexpr std::size_t index = Idx;
  static constexpr std::size_t next = index + 1;
  using value_type = std::remove_pointer_t<decltype(MemPtr)>;
};

template<typename T>
concept StructureTraits = true;

struct EmptyStructureTraits {
  template<typename Struct, auto Struct::*MemPtr, std::size_t Idx>
  struct Member {};
};

template<typename Struct, StructureTraits Tr = EmptyStructureTraits, std::size_t Idx = 0>
struct structure {};

template<typename T>
concept WithStructure = requires
{
  structure<T>::next;
};

template<typename Struct>
struct StructureBase {
  template<auto Struct::*MemPtr, StructureTraits Traits, std::size_t Idx>
  struct Member : MemberBase<Struct, MemPtr, Idx>, Traits::template Member<Struct, MemPtr, Idx> {
    using Traits::template Member<Struct, MemPtr, Idx>::Member;
  };
};

template<typename Struct>
template<auto Struct::*MemPtr, StructureTraits Traits, std::size_t Idx>
requires WithStructure<remove_member_pointer_t<decltype(MemPtr)>> //
  struct StructureBase<Struct>::Member<MemPtr, Traits, Idx>
  : MemberBase<Struct, MemPtr, Idx>,
    Traits::template Member<Struct, MemPtr, Idx>,
    structure<remove_member_pointer_t<decltype(MemPtr)>, Traits, Idx + 1> {
  using TraitMem = typename Traits::template Member<Struct, MemPtr, Idx>;
  using Structure = structure<remove_member_pointer_t<decltype(MemPtr)>, Traits, Idx + 1>;

  constexpr Member(auto&&... args) requires std::is_constructible_v<TraitMem, decltype(args)...>&& std::
    is_constructible_v<Structure, decltype(args)...> : TraitMem(args...),
                                                       Structure(args...)
  {}

  using Structure::next;
};

struct State {
  /// The filter frequency
  int i1 = 0;
  int i2 = 0;
  struct SubState {
    int subi1 = 0;
  } substate;
};

template<StructureTraits Tr, std::size_t Idx>
struct structure<::State, Tr, Idx> : StructureBase<::State> {
  [[no_unique_address]] Member<&::State::i1, Tr, Idx + 0> i1;
  [[no_unique_address]] Member<&::State::i2, Tr, Idx + decltype(i1)::next> i2;
  [[no_unique_address]] Member<&::State::substate, Tr, Idx + decltype(i2)::next> substate;
  static constexpr std::size_t next = Idx + decltype(substate)::next;

  constexpr structure(auto&&... args) requires std::is_constructible_v<decltype(i1), decltype(args)...>&& std::
    is_constructible_v<decltype(i2), decltype(args)...>&& std::is_constructible_v<decltype(substate), decltype(args)...>
    : i1(args...), i2(args...), substate(args...)
  {}
  constexpr structure(const structure&) = default;
  constexpr structure(structure&&) = default;
  constexpr structure& operator=(const structure&) = default;
  constexpr structure& operator=(structure&&) = default;
};

template<StructureTraits Tr, std::size_t Idx>
struct structure<::State::SubState, Tr, Idx> : StructureBase<::State::SubState> {
  [[no_unique_address]] Member<&::State::SubState::subi1, Tr, Idx + 0> subi1;
  static constexpr std::size_t next = Idx + decltype(subi1)::next;

  constexpr structure(auto&&... args) requires std::is_constructible_v<decltype(subi1), decltype(args)...>
    : subi1(args...)
  {}
  constexpr structure(const structure&) = default;
  constexpr structure(structure&&) = default;
  constexpr structure& operator=(const structure&) = default;
  constexpr structure& operator=(structure&&) = default;
};

static_assert(structure<State>().substate.index == 2);
static_assert(structure<State>().substate.subi1.index == 3);

struct StateDiffTraits {
  template<typename Struct, auto Struct::*MemPtr, std::size_t Idx>
  struct Member {
    using BitSet = std::bitset<structure<State>::next>;

    Member(BitSet& b) : bitset_(b) {}

    bool has_changed()
    {
      return bitset_.test(Idx);
    }

    void has_changed(bool b)
    {
      bitset_[Idx] = b;
    }

  private:
    BitSet& bitset_;
  };
};

template<WithStructure State>
struct StateDiff : structure<State, StateDiffTraits> {
  using BitSet = std::bitset<structure<State>::next>;

  StateDiff(BitSet b = {}) : bitset_(b), structure<State, StateDiffTraits>(bitset_) {}

  BitSet bitset()
  {
    return bitset_;
  }

private:
  BitSet bitset_;
};

TEST_CASE ("StateDiff") {
  StateDiff<State> diff;
  diff.i1.has_changed(true);
  REQUIRE(diff.i1.has_changed());
  REQUIRE(!diff.i2.has_changed());
  diff.substate.subi1.has_changed(true);
  REQUIRE(diff.substate.subi1.has_changed());
}
