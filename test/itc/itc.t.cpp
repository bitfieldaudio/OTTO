#include "itc/itc.hpp"
#include "testing.t.hpp"

using namespace otto;
using namespace otto::itc;
struct DummyExecutor : IExecutor {
  void execute(std::function<void()> f) override
  {
    f();
  }
};

// Tests
TEST_CASE (doctest::test_suite("itc") * "Basic Channel/Consumer/Producer linking and lifetime") {
  struct State {
    int i = 0;
  };

  DummyExecutor ex;

  SUBCASE ("Constructing consumer with channel registers it") {
    Channel<State> ch;
    Consumer<State> c1 = {ex, ch};

    REQUIRE(ch.consumers().size() == 1);
    REQUIRE(ch.consumers()[0] == &c1);

    Consumer<State> c2 = {ex, ch};

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
    Consumer<State> c = {ex, ch};
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
          Consumer<State> p = {ex, ch};
        }
        REQUIRE(ch.consumers().empty());
      }
      SUBCASE ("Channel destroyed before consumer") {
        auto ch = std::make_unique<Channel<State>>();
        Consumer<State> c = {ex, *ch};
        ch.reset();
        REQUIRE(c.channel() == nullptr);
      }
    }
  }
}

TEST_CASE (doctest::test_suite("itc") * "Basic state passing") {
  DummyExecutor ex;
  struct S {
    int i = 0;
  };
  Channel<S> ch;
  Producer<S> p = {ch};
  struct C1 : Consumer<S> {
    using Consumer<S>::Consumer;

    void check_i(int i)
    {
      REQUIRE(state().i == i);
    }

    void on_new_state(const S& s) override
    {
      new_state_called++;
    }

    int new_state_called = 0;
  } c1 = {ex, ch};

  SUBCASE ("Access default state in Consumer") {
    c1.check_i(0);
  }

  struct P1 : Producer<S> {
    void test_produce(int i)
    {
      produce(S{.i = i});
    }
  } p1 = {ch};

  SUBCASE ("Publish new state from producer") {
    p1.test_produce(1);
    c1.check_i(1);
    REQUIRE(c1.new_state_called == 1);
  }
}

/*
TEST_CASE(doctest::test_suite("itc") * "prod/cons/chan of multiple states") {
  struct S1 {
    int i1 = 1;
  };

  struct S2 {
    int i2 = 2;
  };

  struct S3 {
    int i3 = 3;
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

  using Ch123 = Channel<S1, meta::list<S2, S3>>;
  using C123 = Consumer<S1, meta::list<S2, S3>>;
  using P123 = Producer<S1, meta::list<S2, S3>>;

  static_assert(std::is_base_of_v<Channel<S1>, Ch123>);
  static_assert(std::is_base_of_v<Channel<S2>, Ch123>);
  static_assert(std::is_base_of_v<Channel<S3>, Ch123>);
  static_assert(std::is_base_of_v<Consumer<S1>, C123>);
  static_assert(std::is_base_of_v<Consumer<S2>, C123>);
  static_assert(std::is_base_of_v<Consumer<S3>, C123>);
  static_assert(std::is_base_of_v<Producer<S1>, P123>);
  static_assert(std::is_base_of_v<Producer<S2>, P123>);
  static_assert(std::is_base_of_v<Producer<S3>, P123>);
}
*/
