#include "itc/itc.hpp"
#include "testing.t.hpp"

using namespace otto;
using namespace otto::itc;

// Tests
TEST_CASE ("Basic Channel/Consumer/Producer linking and lifetime" * doctest::test_suite("itc")) {
  struct State {
    int i = 0;
  };

  SUBCASE ("Constructing consumer with channel registers it") {
    Channel<State> ch;
    Consumer<State> c1 = {ch};

    REQUIRE(ch.consumers().size() == 1);
    REQUIRE(ch.consumers()[0] == &c1);

    Consumer<State> c2 = {ch};

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
    Consumer<State> c = {ch};
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
        Producer p = {*ch};
        ch.reset();
        REQUIRE(p.channels().empty());
      }
    }
    SUBCASE ("Consumer / Channel") {
      SUBCASE ("Consumer destroyed before channel") {
        Channel<State> ch;
        {
          Consumer<State> p = {ch};
        }
        REQUIRE(ch.consumers().empty());
      }
      SUBCASE ("Channel destroyed before consumer") {
        auto ch = std::make_unique<Channel<State>>();
        Consumer c = {*ch};
        ch.reset();
        REQUIRE(c.channel() == nullptr);
      }
    }
  }
}
