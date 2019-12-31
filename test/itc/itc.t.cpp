#include "itc/itc.hpp"
#include "testing.t.hpp"

namespace otto::itc {

  TEST_CASE ("ActionReceiver") {
    using void_action = Action<struct void_action_tag>;
    using int_action = Action<struct int_action_tag, int>;
    using float_action = Action<struct float_action_tag, float>;

    struct VoidAR {
      void action(void_action)
      {
        has_run = true;
        run_count++;
      }
      bool has_run = false;
      int run_count = 0;
    };

    struct IntAR {
      void action(int_action, int val)
      {
        value += val;
      }
      int value = 0;
    };

    SUBCASE ("The InvalidActionReceiver concept") {
      struct InvalidAR {
        void action(void_action, int){};
        void action(int_action, float){};
        void action(float_action){};
      };
      struct InvalidAR1 {
        void action(void_action){};
        void action(int_action, int, int){};
        void action(float_action, float){};
      };
      static_assert(InvalidActionReceiver::is<InvalidAR, void_action>);
      // We cant do this one - see below
      static_assert(!InvalidActionReceiver::is<InvalidAR, int_action>);
      static_assert(InvalidActionReceiver::is<InvalidAR, float_action>);

      static_assert(!InvalidActionReceiver::is<InvalidAR1, void_action>);
      static_assert(InvalidActionReceiver::is<InvalidAR1, int_action>);
      static_assert(!InvalidActionReceiver::is<InvalidAR1, float_action>);
    }

    SUBCASE ("The ActionReceiver concept") {
      struct ARTest {
        void action(int_action, float){};
      };

      static_assert(ActionReceiver::is<VoidAR, void_action>);
      static_assert(!ActionReceiver::is<ARTest, void_action>);
      // This one is harder - we use a trick to avoid implicit conversions, but it only works on gcc and clang > 7
      // update: this trick breaks templated handlers
      // static_assert(
      //   !ActionReceiver::is<ARTest, int_action>,
      //   "This doesnt work on clang 7 and below, but it is just error detection. If it fails, comment it out");
    }

    SUBCASE ("ActionData can be created using Action::data") {
      auto ad = int_action::data(10);
      static_assert(std::is_same_v<decltype(ad), ActionData<int_action>>);
      REQUIRE(std::get<0>(ad.args) == 10);
    }

    SUBCASE ("Action with no data can be received using call_receiver") {
      VoidAR void_ar;

      REQUIRE(void_ar.has_run == false);
      call_receiver(void_ar, void_action::data());
      REQUIRE(void_ar.has_run == true);
    }

    SUBCASE ("Action with an int argument can be received using call_receiver") {
      IntAR int_ar;

      call_receiver(int_ar, int_action::data(10));
      REQUIRE(int_ar.value == 10);
    }

    SUBCASE ("try_call_receiver calls action receiver and returns true") {
      IntAR int_ar;

      REQUIRE(try_call_receiver(int_ar, int_action::data(10)));
      REQUIRE(int_ar.value == 10);
    }

    SUBCASE ("try_call_receiver returns false when no receiver avaliable") {
      IntAR int_ar;
      REQUIRE(!try_call_receiver(int_ar, void_action::data()));
      REQUIRE(int_ar.value == 0);
    }

    SUBCASE ("ActionQueue") {
      ActionQueue aq;
      SUBCASE ("ActionQueue is initially empty") {
        REQUIRE(aq.size() == 0);
      }

      SUBCASE ("ActionQueue.push(function)") {
        bool has_run = false;
        aq.push([&] { has_run = true; });
        REQUIRE(aq.size() == 1);
        aq.pop()();
        REQUIRE(has_run);
      }

      SUBCASE ("ActionQueue.pop_call_all()") {
        IntAR iar;
        VoidAR var;
        aq.push(var, void_action::data());
        aq.push(iar, int_action::data(10));
        REQUIRE(aq.size() == 2);
        aq.pop_call_all();
        REQUIRE(var.has_run);
        REQUIRE(iar.value == 10);
      }

      SUBCASE ("ActionQueue.push(function) is FIFO ordered") {
        bool has_run = false;
        aq.push([&] { has_run = true; });
        aq.push([&] { REQUIRE(has_run); });
        REQUIRE(aq.size() == 2);
        aq.pop_call_all();
        REQUIRE(has_run);
      }

      SUBCASE ("ActionQueue.push(ActionReceiver, ActionData) works") {
        VoidAR ar;
        aq.push(ar, void_action::data());
        aq.pop_call();
        REQUIRE(ar.has_run);
      }


      SUBCASE ("ActionQueue.try_push(ActionReceiver, ActionData) works") {
        IntAR ar;
        aq.try_push(ar, int_action::data(10));
        aq.pop_call();
        REQUIRE(ar.value == 10);
      }

      SUBCASE ("ActionQueue.try_push(ActionReceiver, ActionData) does not enqueue an action if the receiver cannot "
               "receive it") {
        IntAR ar;
        REQUIRE(aq.try_push(ar, void_action::data()) == false);
        REQUIRE(aq.size() == 0);
      }
    }

    SUBCASE ("ActionSender") {
      struct OtherIntAR {
        void action(int_action, int val)
        {
          value += val;
        }
        int value = 0;
      } oiar;
      ActionQueue queue;
      VoidAR var;
      IntAR iar;
      ActionSender sndr = {queue, var, iar, oiar};

      SUBCASE ("ActionSender holds references to receivers") {
        REQUIRE(&sndr.receiver<VoidAR>() == &var);
        REQUIRE(&sndr.receiver<IntAR>() == &iar);
        REQUIRE(&sndr.receiver<OtherIntAR>() == &oiar);
      }

      SUBCASE ("ActionSender queues actions to all receivers") {
        sndr.push(int_action::data(10));
        REQUIRE(queue.size() == 2);
        queue.pop_call_all();
        REQUIRE(iar.value == 10);
        REQUIRE(oiar.value == 10);
      }

      SUBCASE ("ActionSender is copy constructible") {
        auto sndr2 = sndr;
        REQUIRE(&sndr.receiver<VoidAR>() == &var);
        REQUIRE(&sndr2.receiver<VoidAR>() == &var);
      }

      SUBCASE ("JoinedActionSender") {
        ActionQueue queue2;
        ActionSender sndr1 = {queue, var};
        ActionSender sndr2 = {queue2, iar, var};
        JoinedActionSender jsndr = {sndr1, sndr2};

        SUBCASE ("can push the same action to multiple queues") {
          jsndr.push(void_action::data());
          REQUIRE(queue.size() == 1);
          REQUIRE(queue2.size() == 1);
          queue.pop_call_all();
          REQUIRE(var.run_count == 1);
          queue2.pop_call_all();
          REQUIRE(var.run_count == 2);
        }
      }
    }

    SUBCASE ("Action with reference parameter") {
      using ref_act = Action<struct ref_act_tag, int&>;
      struct RefAR {
        void action(ref_act, int& ref)
        {
          addr = &ref;
        };
        int* addr = nullptr;
      };
      int an_int = 0;
      RefAR rar;
      call_receiver(rar, ref_act::data(an_int));
      REQUIRE(rar.addr == &an_int);
    }
  }

} // namespace otto::itc
