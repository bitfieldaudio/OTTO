#include "testing.t.hpp"

#include "lib/itc/itc.hpp"

#include <bitset>

#include "stubs/state.hpp"

using namespace otto;
using namespace otto::itc;

template<AnAction... Actions>
using ImmRec = WithDomain<StaticDomain<>, Receiver<Actions...>>;

template<AState... States>
using ImmCons = WithDomain<StaticDomain<>, Consumer<States...>>;

// Tests
TEST_CASE ("Basic Context/Receiver/Sender linking and lifetime", "[itc]") {
  struct Action {};

  ImmediateExecutor ex;
  StaticDomain<>::set_static_executor(ex);

  SECTION ("Receiver has a reference to its sender") {
    Context ctx;
    Sender<Action> s{ctx};
    ImmRec<Action> r1(ctx);
    REQUIRE(r1.sender() == &s);
  }

  SECTION ("Receiver has a reference to its context") {
    Context ctx;
    ImmRec<Action> c = {ctx};
    REQUIRE(&c.context() == &ctx);
  }

  SECTION ("Sender has a list of receivers") {
    Context ctx;
    Sender<Action> s1{ctx};
    ImmRec<Action> r1{ctx};
    ImmRec<Action> r2{ctx};
    ImmRec<Action> r3{ctx};
    REQUIRE_THAT(s1.receivers(), Catch::Matchers::Equals(std::vector<Receiver<Action>*>{&r1, &r2, &r3}));
  }

  SECTION ("Bidirectional lifetime management") {
    SECTION ("Sender / Receiver") {
      SECTION ("Sender destroyed before receiver") {
        Context ctx;
        ImmRec<Action> r1(ctx);
        {
          Sender<Action> s = {ctx};
        }
        REQUIRE(r1.sender() == nullptr);
      }
      SECTION ("Receiver destroyed before sender") {
        Context ctx;
        Sender<Action> s{ctx};
        {
          ImmRec<Action> r{ctx};
        }
        REQUIRE(s.receivers().empty());
      }
    }
  }
}
TEST_CASE ("itc Actions", "[itc]") {
  ImmediateExecutor ex;
  StaticDomain<>::set_static_executor(ex);

  struct TestAction1 {
    int param1 = 0;
  };
  Context ctx;
  Sender<TestAction1> sender = {ctx};

  struct R1 : Receiver<TestAction1>, StaticDomain<> {
    using Receiver::Receiver;

    void receive(TestAction1 action) noexcept override
    {
      counter += action.param1;
    }

    int counter = 0;
  } r1 = {ctx};

  SECTION ("Send actions ") {
    sender.send({1});
    REQUIRE(r1.counter == 1);
    sender.send({2});
    REQUIRE(r1.counter == 3);
  }
}

TEST_CASE ("Context walking", "[itc]") {
  ImmediateExecutor ex;
  StaticDomain<>::set_static_executor(ex);

  struct TestAction1 {
    int param1 = 0;
  };

  using S1 = Sender<TestAction1>;

  struct R1 : Receiver<TestAction1>, StaticDomain<> {
    using Receiver::Receiver;

    void receive(TestAction1 action) noexcept override
    {
      counter += action.param1;
    }

    int counter = 0;
  };

  Context ctx;
  Context& sub = ctx["1"]["1"];

  SECTION ("Register receiver first") {
    R1 r1 = {sub};
    S1 s1 = {ctx};
    s1.send({1});
    REQUIRE(r1.counter == 1);
  }

  SECTION ("Register sender first") {
    S1 s1 = {ctx};
    R1 r1 = {sub};
    s1.send({1});
    REQUIRE(r1.counter == 1);
  }
}

TEST_CASE ("Basic state passing", "[itc]") {
  ImmediateExecutor ex;
  StaticDomain<>::set_static_executor(ex);
  ImmediateExecutor ex2;
  StaticDomain<struct tag2>::set_static_executor(ex2);
  struct S {
    int i = 0;
  };
  Context ctx;
  WithDomain<StaticDomain<>, Producer<S>> p = {ctx};
  struct C1 : Consumer<S>, StaticDomain<tag2> {
    using Consumer<S>::Consumer;

    void on_state_change(const S&) noexcept override
    {
      new_state_called++;
    }

    int new_state_called = 0;
  } c1 = {ctx};

  SECTION ("Different state pointers on different domains") {
    REQUIRE(&p.state() != &c1.state());
  }

  SECTION ("Access default state in Consumer") {
    REQUIRE(c1.state().i == 0);
  }

  SECTION ("Publish new state from producer") {
    p.commit([&](auto& state) {
      state.i = 1;
      REQUIRE(p.state().i == 1);
      REQUIRE(c1.state().i == 0);
    });
    REQUIRE(c1.state().i == 1);
    REQUIRE(c1.new_state_called == 1);
    p.commit([&](auto& state) { state.i = 2; });
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
  Context context;

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
  } c1 = {context};

  SECTION ("Access default state in Consumer") {
    c1.check_i1(1);
    c1.check_i2(2);
  }

  struct P1 : StaticDomain<>, Producer<S1, S2> {
    using Producer::Producer;
    void test_produce1(int i)
    {
      commit<S1>([&](auto& state) { state.i1 = i; });
    }
    void test_produce2(int i)
    {
      commit<S2>([&](auto& state) { state.i2 = i; });
    }
  } p1{context};

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
