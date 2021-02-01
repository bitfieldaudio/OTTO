#include "testing.t.hpp"

#include "lib/itc/itc.hpp"

#include <bitset>

#include "stubs/state.hpp"

using namespace otto;
using namespace otto::itc;

template<AState... States>
using ImmCons = WithDomain<StaticDomain<>, Consumer<States...>>;

// Tests
TEST_CASE ("Basic TypedChannel/Consumer/Producer linking and lifetime", "[itc]") {
  struct State {
    int i = 0;
    bool operator==(const State&) const = default;
  };

  ImmediateExecutor ex;
  StaticDomain<>::set_static_executor(ex);

  SECTION ("Constructing consumer with channel registers it") {
    TypedChannel<State> ch;
    ImmCons<State> c1 = {ch};

    REQUIRE(ch.consumers().size() == 1);
    REQUIRE(ch.consumers()[0] == &c1);

    ImmCons<State> c2 = {ch};

    REQUIRE(ch.consumers().size() == 2);
    REQUIRE(ch.consumers()[1] == &c2);
  }

  SECTION ("Constructing a producer with a channel registers it") {
    TypedChannel<State> ch1;
    Producer<State> p = {ch1};

    REQUIRE(p.channels().size() == 1);
    REQUIRE(p.channels()[0] == &ch1);
    SECTION ("A producer can be registered to more channels with ch.set_producer") {
      TypedChannel<State> ch2;
      ch2.set_producer(p);
      REQUIRE(p.channels().size() == 2);
      REQUIRE(p.channels()[1] == &ch2);
    }
  }

  SECTION ("TypedChannel has a reference to its producer") {
    TypedChannel<State> ch;
    REQUIRE(ch.producer() == nullptr);
    Producer<State> p = {ch};
    REQUIRE(ch.producer() == &p);

    SECTION ("Also when registered with set_producer") {
      TypedChannel<State> ch2;
      ch2.set_producer(p);
      REQUIRE(ch2.producer() == &p);
      REQUIRE(ch.producer() == &p);
    }
  }

  SECTION ("Consumer has a reference to its channel") {
    TypedChannel<State> ch;
    ImmCons<State> c = {ch};
    REQUIRE(c.channel() == &ch);
  }

  SECTION ("Bidirectional lifetime management") {
    SECTION ("Producer / TypedChannel") {
      SECTION ("Producer destroyed before channel") {
        TypedChannel<State> ch;
        {
          Producer<State> p = {ch};
        }
        REQUIRE(ch.producer() == nullptr);
      }
      SECTION ("TypedChannel destroyed before producer") {
        auto ch = std::make_unique<TypedChannel<State>>();
        Producer<State> p = {*ch};
        ch.reset();
        REQUIRE(p.channels().empty());
      }
    }
    SECTION ("Consumer / TypedChannel") {
      SECTION ("Consumer destroyed before channel") {
        TypedChannel<State> ch;
        {
          ImmCons<State> p = {ch};
        }
        REQUIRE(ch.consumers().empty());
      }
      SECTION ("TypedChannel destroyed before consumer") {
        auto ch = std::make_unique<TypedChannel<State>>();
        ImmCons<State> c = {*ch};
        ch.reset();
        REQUIRE(c.channel() == nullptr);
      }
    }
  }
}

TEST_CASE ("Basic state passing", "[itc]") {
  ImmediateExecutor ex;
  StaticDomain<>::set_static_executor(ex);
  struct S {
    int i = 0;
  };
  TypedChannel<S> ch;
  Producer<S> p = {ch};
  struct C1 : Consumer<S>, StaticDomain<> {
    using Consumer<S>::Consumer;

    void on_state_change(const S&) noexcept override
    {
      new_state_called++;
    }

    int new_state_called = 0;
  } c1 = {ch};

  SECTION ("Access default state in Consumer") {
    REQUIRE(c1.state().i == 0);
  }

  struct P1 : Producer<S> {
  } p1 = {ch};

  SECTION ("Publish new state from producer") {
    p1.state().i = 1;
    REQUIRE(p1.state().i == 1);
    REQUIRE(c1.state().i == 0);
    p1.commit();
    REQUIRE(c1.state().i == 1);
    REQUIRE(c1.new_state_called == 1);
    p1.state().i = 2;
    p1.commit();
    REQUIRE(c1.state().i == 2);
    REQUIRE(c1.new_state_called == 2);
  }
}

TEST_CASE ("prod/cons/chan of multiple states", "[itc]") {
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

  ImmediateExecutor ex;
  StaticDomain<>::set_static_executor(ex);
  ChannelGroup channels;

  struct C1 : Consumer<S1, S2>, StaticDomain<> {
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
  } c1 = {channels};

  SECTION ("Access default state in Consumer") {
    c1.check_i1(1);
    c1.check_i2(2);
  }

  struct P1 : Producer<S1, S2> {
    void test_produce1(int i)
    {
      state<S1>().i1 = i;
      commit<S1>();
    }
    void test_produce2(int i)
    {
      state<S2>().i2 = i;
      commit<S2>();
    }
  } p1 = {channels};

  SECTION ("Publish new state from producer") {
    p1.test_produce1(10);
    REQUIRE(c1.state<S1>().i1 == 10);
    REQUIRE(c1.new_state1_called == 1);
    REQUIRE(c1.state<S2>().i2 == 2);
    REQUIRE(c1.new_state2_called == 0);

    p1.test_produce2(20);
    REQUIRE(c1.state<S1>().i1 == 10);
    REQUIRE(c1.new_state1_called == 1);
    REQUIRE(c1.state<S2>().i2 == 20);
    REQUIRE(c1.new_state2_called == 1);
  }
}

struct State1 {
  int i1 = 0;
  DECL_VISIT(i1);
};

struct State2 {
  int i2 = 0;
};

TEST_CASE ("Channel serialization") {
  ImmediateExecutor ex;
  StaticDomain<>::set_static_executor(ex);

  SECTION ("Basic serializable state") {
    ChannelGroup ch;
    Producer<State1> p1{ch};
    ImmCons<State1> c1{ch};

    const auto s = util::serialize(ch);
    p1.state().i1 = 10;
    p1.commit();
    REQUIRE(c1.state().i1 == 10);
    util::deserialize_from(s, ch);
    REQUIRE(c1.state().i1 == 0);
  }

  SECTION ("Unserializable state") {
    ChannelGroup ch;
    Producer<State2> p1{ch};
    ImmCons<State2> c1{ch};

    const auto s = util::serialize(ch);
    REQUIRE(s.is_object());
    p1.state().i2 = 10;
    p1.commit();
    REQUIRE(c1.state().i2 == 10);
    util::deserialize_from(s, ch);
    REQUIRE(c1.state().i2 == 10);
  }
}
