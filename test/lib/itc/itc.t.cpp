#include "testing.t.hpp"

#include "lib/itc/itc.hpp"

#include <bitset>

#include "stubs/state.hpp"

using namespace otto;
using namespace otto::itc;

template<AnEvent... Events>
using ImmRec = WithDomain<StaticDomain<>, Receiver<Events...>>;

template<AState... States>
using ImmCons = WithDomain<StaticDomain<>, Consumer<States...>>;

// Tests
TEST_CASE ("Basic Channel/Receiver/Sender linking and lifetime", "[itc]") {
  struct Event {};

  ImmediateExecutor ex;
  StaticDomain<>::set_static_executor(ex);

  SECTION ("Receiver has a reference to its sender") {
    Channel ch;
    Sender<Event> s{ch};
    ImmRec<Event> r1(ch);
    REQUIRE(r1.sender() == &s);
  }

  SECTION ("Receiver has a reference to its channel") {
    Channel ch;
    ImmRec<Event> c = {ch};
    REQUIRE(&c.channel() == &ch);
  }

  SECTION ("Sender has a list of receivers") {
    Channel ch;
    Sender<Event> s1{ch};
    ImmRec<Event> r1{ch};
    ImmRec<Event> r2{ch};
    ImmRec<Event> r3{ch};
    REQUIRE_THAT(s1.receivers(), Catch::Matchers::Equals(std::vector<Receiver<Event>*>{&r1, &r2, &r3}));
  }

  SECTION ("Bidirectional lifetime management") {
    SECTION ("Sender / Receiver") {
      SECTION ("Sender destroyed before receiver") {
        Channel ch;
        ImmRec<Event> r1(ch);
        {
          Sender<Event> s = {ch};
        }
        REQUIRE(r1.sender() == nullptr);
      }
      SECTION ("Receiver destroyed before sender") {
        Channel ch;
        Sender<Event> s{ch};
        {
          ImmRec<Event> r{ch};
        }
        REQUIRE(s.receivers().empty());
      }
    }
  }
}
TEST_CASE ("itc Events", "[itc]") {
  ImmediateExecutor ex;
  StaticDomain<>::set_static_executor(ex);

  struct TestEvent1 {
    int param1 = 0;
  };
  Channel ch;
  Sender<TestEvent1> sender = {ch};

  struct R1 : Receiver<TestEvent1>, StaticDomain<> {
    using Receiver::Receiver;

    void handle(TestEvent1 event) noexcept override
    {
      counter += event.param1;
    }

    int counter = 0;
  } r1 = {ch};

  SECTION ("Send events ") {
    sender.send({1});
    REQUIRE(r1.counter == 1);
    sender.send({2});
    REQUIRE(r1.counter == 3);
  }
}

TEST_CASE ("Channel walking", "[itc]") {
  ImmediateExecutor ex;
  StaticDomain<>::set_static_executor(ex);

  struct TestEvent1 {
    int param1 = 0;
  };

  using S1 = Sender<TestEvent1>;

  struct R1 : Receiver<TestEvent1>, StaticDomain<> {
    using Receiver::Receiver;

    void handle(TestEvent1 event) noexcept override
    {
      counter += event.param1;
    }

    int counter = 0;
  };

  Channel ch;
  Channel& sub = ch["1"]["1"];

  SECTION ("Register receiver first") {
    R1 r1 = {sub};
    S1 s1 = {ch};
    s1.send({1});
    REQUIRE(r1.counter == 1);
  }

  SECTION ("Register sender first") {
    S1 s1 = {ch};
    R1 r1 = {sub};
    s1.send({1});
    REQUIRE(r1.counter == 1);
  }
}

TEST_CASE ("Basic state passing", "[itc]") {
  ImmediateExecutor ex;
  StaticDomain<>::set_static_executor(ex);
  struct S {
    int i = 0;
  };
  Channel ch;
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

  SECTION ("Publish new state from producer") {
    p.state().i = 1;
    REQUIRE(p.state().i == 1);
    REQUIRE(c1.state().i == 0);
    p.commit();
    REQUIRE(c1.state().i == 1);
    REQUIRE(c1.new_state_called == 1);
    p.state().i = 2;
    p.commit();
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
  Channel channel;

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
  } c1 = {channel};

  SECTION ("Access default state in Consumer") {
    c1.check_i1(1);
    c1.check_i2(2);
  }

  struct P1 : Producer<S1, S2> {
    using Producer::Producer;
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
  } p1{channel};

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
    Channel ch;
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
    Channel ch;
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
