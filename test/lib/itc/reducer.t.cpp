#include "lib/itc/reducer.hpp"
#include "testing.t.hpp"

using namespace otto::lib;
using namespace otto::lib::itc;

TEST_CASE (doctest::test_suite("itc") * "Reducer") {
  struct State {
    int events = 0;

    bool operator==(const State&) const = default;
  };

  enum struct Event {
    plus,
    minus,
    no_action,
  };

  struct R1 : Reducer<State, Event> {
    using Reducer<State, Event>::Reducer;

    State reduce(State state, const Event& event) noexcept override
    {
      switch (event) {
        case Event::plus: state.events++; break;
        case Event::minus: state.events--; break;
        case Event::no_action: return state;
      }
      return state;
    }
  };

  struct C1 : Consumer<State> {
    using Consumer<State>::Consumer;

    void on_new_state(const State& new_state) override
    {
      new_state_count++;
    }
    int new_state_count = 0;
  };

  {
    ImmediateExecutor ex;
    Channel<State> ch;
    R1 r1{ch};
    C1 c1 = {ex, ch};

    SUBCASE ("Handling an event through the reducer produces a new state") {
      r1.handle(Event::plus);
      REQUIRE(c1.state().events == 1);
      r1.handle(Event::plus);
      REQUIRE(c1.state().events == 2);
    }

    SUBCASE ("When a reducer returns an equal state to the old one, no state update is produced") {
      r1.handle(Event::no_action);
      REQUIRE(c1.new_state_count == 0);
    }
  }

  SUBCASE ("Multiple event types") {
    enum struct Event2 {
      set_to_10,
    };

    struct R2 : Reducer<State, Event, Event2> {
      using Reducer<State, Event, Event2>::Reducer;

      State reduce(State state, const Event& event) noexcept override
      {
        switch (event) {
          case Event::plus: return {state.events + 1};
          case Event::minus: return {state.events - 1};
          case Event::no_action: return state;
        }
        return state;
      }

      State reduce(State state, const Event2& event) noexcept override
      {
        return {10};
      }
    };

    ImmediateExecutor ex;
    Channel<State> ch;
    R2 r2 = {ch};
    C1 c1 = {ex, ch};

    r2.handle(Event::plus);
    REQUIRE(c1.state().events == 1);
    r2.handle(Event::minus);
    REQUIRE(c1.state().events == 0);
    r2.handle(Event2::set_to_10);
    REQUIRE(c1.state().events == 10);
  }
}
